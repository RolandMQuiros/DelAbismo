//#include <thread>
#include <da/twod/attr/Transform.h>
#include "attr/Collider.h"
#include "bhvr/CollisionManager.h"

namespace bhvr {

CollisionManager::CollisionManager(float width, float height,
                                   unsigned int maxDepth) :
mRoot(new Node),
mMaxDepth(maxDepth) {
    // The root encapsulates the entire collision field
    mRoot->bounds.left = 0.f;
    mRoot->bounds.top = 0.f;
    mRoot->bounds.width = width;
    mRoot->bounds.height = height;
    
    mRoot->parent = NULL;
    mRoot->hasChildren = false;
    mRoot->depth = 0;
}

void CollisionManager::insert(Node *node, const sf::FloatRect &bounds,
                              const da::EntityRef &entity)
{
    sf::FloatRect intersection;
    
    // Make sure the entity exists in the node
    if (!node->bounds.intersects(bounds, intersection)) {
        return;
    }
    
    // Make sure we're under the depth limit
    if (node->depth >= mMaxDepth) {
        // We've hit the maximum subdivisions, so we'll insert the entity here
        node->entities.insert(entity);
        
        // Keep track of where we've inserted the entity, for updating its
        // position, or removing the entity
        mSearchMap[entity].push_back(node);
        
        return;
    }
    
    // Populate children
    if (!node->hasChildren) {
        subdivide(node);
    }
    
    // Recurse into children
    for (unsigned int i = 0; i < NQUADTREE; i++) {
        insert(node->children[i].get(), bounds, entity);
    }
}

void CollisionManager::subdivide(Node *node) {
    sf::FloatRect newBounds = node->bounds;
    newBounds.width /= 2.f;
    newBounds.height /= 2.f;
    
    for (unsigned int i = 0; i < NQUADTREE; i++) {
        node->children[i] = std::unique_ptr<Node>(new Node);
        Node *child = node->children[i].get();
        
        child->parent = node;
        child->depth = node->depth + 1;
        child->hasChildren = false;
    }
    
    node->children[0]->bounds = newBounds;
    newBounds.left += newBounds.width;
    node->children[1]->bounds = newBounds;
    newBounds.left = node->bounds.left;
    newBounds.top += newBounds.height;
    node->children[2]->bounds = newBounds;
    newBounds.left += newBounds.width;
    node->children[3]->bounds = newBounds;
    
    node->hasChildren = true;
}

sf::FloatRect &CollisionManager::transformRect(const da::EntityPtr &entity) {
    da::attr::Transform &xform = entity->getAttribute<da::attr::Transform>();
    attr::Collider &collider = entity->getAttribute<attr::Collider>();
    
    switch (collider.method) {
        case attr::Collider::SAT:
            // Resize collider.boundingBox to fit the transformed polygon
            break;
        case attr::Collider::AABB:
        default:
            sf::Vector2f scale(xform.getScale().x * xform.getOrigin().x,
                       xform.getScale().y * xform.getOrigin().y);
            sf::Vector2f topLeft = xform.getPosition() - scale;
            
            collider.boundingBox.left = topLeft.x;
            collider.boundingBox.top = topLeft.y;
            collider.boundingBox.width = xform.getScale().x * collider.width;
            collider.boundingBox.height = xform.getScale().y * collider.height;
            break;
    }
    
    // TODO: SAT
    
    return collider.boundingBox;
}

bool CollisionManager::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::attr::Transform>() &&
           entity.hasAttribute<attr::Collider>();
}

void CollisionManager::addedEntity(const da::EntityRef &entity) {    
    insert(mRoot.get(), transformRect(entity.lock()), entity);
}

void CollisionManager::removedEntity(const da::EntityRef &entity) {
    SearchMap::iterator search = mSearchMap.find(entity);
    
    if (search == mSearchMap.end()) {
        return;
    }
    
    // Go to each node recorded and remove the occurrence of the entity
    for (unsigned int i = 0; i < search->second.size(); i++) {
        search->second[i]->entities.erase(entity);
    }
}

void CollisionManager::reinsert(const da::EntityPtr &entity) {
    // Grab attributes
    attr::Collider &collider = entity->getAttribute<attr::Collider>();
    
    // TODO: if the collider is in SAT mode, change the bounding box according
    // to the transform.  This might be better suited for a seperate system,
    // though.  Not gonna do it for AABB mode, so...
    
    da::EntityRef ref(entity);
    SearchMap::iterator search;
    
    // If the collider bounding box has changed position or dimensions, remove
    // it from the quadtree and re-insert it    
    if (collider.isChanged) {
        search = mSearchMap.find(ref);
        if (search != mSearchMap.end()) {
            // Remove all entity instances from the quadtree
            for (unsigned int i = 0; i < search->second.size(); i++) {
                search->second[i]->entities.erase(entity);
            }
            search->second.clear();
            
            // Transform the bounding box
            sf::FloatRect &bounds = transformRect(entity);
            
            // Reinsert the entity
            insert(mRoot.get(), bounds, ref);
        }
    }
}

void CollisionManager::checkCollisions(const da::EntityPtr &entity) {       
    // Make sure this entity is eligible for collision detection.
    // Remember, inactive entities are checked against, but don't do any
    // checking, themselves.
    attr::Collider &collider = entity->getAttribute<attr::Collider>();
    if (!collider.isEnabled || !collider.isActive) {
        return;
    }
    
    da::EntityRef ref(entity);
    da::attr::Transform &xform = entity->getAttribute<da::attr::Transform>();
    
    // Check this entity's collisions against all other entities it shares a
    // node with
    sf::FloatRect &bounds = collider.boundingBox;
    sf::FloatRect intersection;
    da::EntityGroup::iterator otherIt;
    da::EntityGroup &oldCollisions = mCollisionMap[ref];
    da::EntityGroup newCollisions;
    
    // Clear the current entity's collision event list
    collider.collisions.clear();
    
    // Find list of nodes this entity belongs to
    SearchMap::iterator search = mSearchMap.find(ref);
    
    // Stop if there are no nodes to search
    if (search == mSearchMap.end()) {
        return;
    }
    
    // Loop through nodes
    for (unsigned int i = 0; i < search->second.size(); i++) {
        da::EntityGroup &others = search->second[i]->entities;
        
        // Loop through entities in the current node
        for (otherIt = others.begin(); otherIt != others.end(); otherIt++) {
            // Make sure the other entity is still valid
            if (otherIt->expired()) {
                continue;
            }
            
            da::EntityPtr other = otherIt->lock();
            if (entity == other) {
                continue;
            }
            
            attr::Collider &otherCollider =
                other->getAttribute<attr::Collider>();
            sf::FloatRect &otherBounds = otherCollider.boundingBox;
            
            // Make sure the other's collider is enabled, and is colliding with
            // the current entity.
            if (!otherCollider.isEnabled ||
                !bounds.intersects(otherBounds, intersection)) {
                continue;
            }
            
            // Add the other entity to the current entity's collision set
            newCollisions.insert(*otherIt);
            
            // If both entities are solid, move the current entity outside the
            // collision
            if (!collider.isSolid || !otherCollider.isSolid) {
                continue;
            }
            
            sf::Vector2f center(bounds.left + bounds.width / 2.f,
                                bounds.top + bounds.height / 2.f);
            
            sf::Vector2f otherCenter(
                otherBounds.left + otherBounds.width / 2.f,
                otherBounds.top + otherBounds.height / 2.f
            );
            
            // Move along the smallest axis of the intersection box
            if (intersection.width < intersection.height) {
                if (center.x < otherCenter.x) {
                    bounds.left -= intersection.width;
                    xform.move(-intersection.width, 0.f);
                } else {
                    bounds.left += intersection.width;
                    xform.move(intersection.width, 0.f);
                }
            } else {
                if (center.y < otherCenter.y) {
                    bounds.top -= intersection.height;
                    xform.move(0.f, -intersection.height);
                } else {
                    bounds.top += intersection.height;
                    xform.move(0.f, intersection.height);
                }
            }
        }
    }
    
    // Compare new collisions to old collisions, and emit the
    // appropriate events
    Collision collision;
    for (da::EntityGroup::iterator i = newCollisions.begin();
         i != newCollisions.end(); i++) {
        da::EntityGroup::iterator colSearch = oldCollisions.find(*i);
        collision.other = *i;
        
        if (colSearch == oldCollisions.end()) {
            collision.type = Collision::Enter;
            collider.collisions.push_back(collision);
        } else {
            collision.type = Collision::Stay;
            collider.collisions.push_back(collision);
            
            // Remove any common collisions, so the ones remaining are
            // the difference of the old and new sets (collision exits)
            oldCollisions.erase(colSearch);
        }
    }
    
    // Examine the remaining elements in oldCollision--these are what
    // do not exist in newCollision, or the collision exits
    collision.type = Collision::Exit;
    for (da::EntityGroup::iterator i = oldCollisions.begin();
         i != oldCollisions.end(); i++) {
        collision.other = *i;
        collider.collisions.push_back(collision);
    }
    
    // Update our collision map
    oldCollisions = newCollisions;
}

void CollisionManager::updateEntities(da::EntityGroup &entities) {
    da::EntityGroup::iterator iter;
    
    // TODO: Parallelization
    
    // Reinsert the entity into the quadtree, if necessary
    for (iter = entities.begin(); iter != entities.end(); iter++) {
        if (iter->expired()) {
            removeEntity(*iter);
            continue;
        }
        
        reinsert(iter->lock());
        checkCollisions(iter->lock());
    }
}

}
