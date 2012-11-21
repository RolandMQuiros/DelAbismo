#ifndef BHVR_COLLISIONMANAGER_H
#define BHVR_COLLISIONMANAGER_H

#include <set>
#include <unordered_map>
#include <map>

#include <SFML/Graphics/Rect.hpp>
#include <da/Behavior.h>

#define NQUADTREE 4

namespace bhvr {

class CollisionManager : public da::Behavior {
public:
    /**
     * Constructs a new Collision Manager.  Internally, the CollisionManager
     * uses a <a href=http://en.wikipedia.org/wiki/Quadtree>quadtree</a>
     * structure to optimize collision checking.
     *
     * @param $width
     *   width of the game world
     * @param $height
     *   height of the game world
     * @param $maxDepth
     *   maximum depth of the quadtree used to optimize collision checks
     */
    CollisionManager(float width, float height, unsigned int maxDepth);
    
private:
    struct Node {
        sf::FloatRect bounds;
        da::EntityGroup entities;
        
        Node *parent;
        bool hasChildren;
        unsigned int depth;
        std::unique_ptr<Node> children[NQUADTREE];
    };
    typedef std::map<da::EntityRef, std::vector<Node *>,
                     std::owner_less<da::EntityRef>> SearchMap;
    typedef std::map<da::EntityRef, da::EntityGroup,
                     std::owner_less<da::EntityRef>> CollisionMap;
    
    std::unique_ptr<Node> mRoot;
    SearchMap mSearchMap;
    CollisionMap mCollisionMap;
    unsigned int mMaxDepth;
    
    /**
     * Inserts $entity represented by the bounding box $bounds inside $node or
     * one of $node's descendants in the quadtree
     * @param $node
     *   The node into which we're inserting $entity
     * @param $bounds
     *   The bounding box representing $entity
     * @param $entity
     *   The entity to insert
     */
    void insert(Node *node, const sf::FloatRect &bounds,
                const da::EntityRef &entity);
    void subdivide(Node *node);
    sf::FloatRect &transformRect(const da::EntityPtr &entity);
    
    bool isCompatible(const da::Entity &entity) const;
    void addedEntity(const da::EntityRef &entity);
    void removedEntity(const da::EntityRef &entity);
    
    void reinsert(const da::EntityPtr &entity);
    void checkCollisions(const da::EntityPtr &entity);
    void updateEntities(da::EntityGroup &entities);
};

}

#endif
