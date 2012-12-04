#include <cstring>
#include <iostream>

#include <da/Entity.h>
#include <da/NotImplementedException.h>
#include <da/StringHelper.h>
#include <da/XmlExceptions.h>
#include <da/XmlHelper.h>

#include <da/twod/attr/Transform.h>
#include <da/twod/attr/Depth.h>

#include "attr/TileLayer.h"
#include "prefab/Tiled.h"

namespace prefab {


void parseObjectGroup(da::ContentManager &content, da::EntityManager &entities,
                      xml_node<> *node);

/**
 * A Tiled Prefab takes the game's ContentManager, an entity to affect, and
 * an XML node from which we extract the entity's properties.
 */
typedef std::function<void(da::ContentManager &, const da::EntityPtr &,
                           xml_node<> *)> TiledPrefab;
void createTileLayer(da::ContentManager &content, const da::EntityPtr &entity,
                     xml_node<> *node);
void createNPC(da::ContentManager &content, const da::EntityPtr &entity,
               xml_node<> *node);

/**
 * Holds entity prefab functions, keyed by a type string specified in Tiled.
 * If you're creating new entity types, just create the function and its forward
 * decalaration, and add it to this map.
 */
std::map<const char *, TiledPrefab> gObjectPrefabs {
    { "NPC", createNPC }
};

/**
 * Compares two tilesets by their "firstgid" properties.
 * Note to devs: Replace this with a lambda once you can.
 */
bool compareTileSetPair(const std::pair<unsigned int, da::TexturePtr> &a,
                       const std::pair<unsigned int, da::TexturePtr> &b)
{
    return a.first < b.first;
}

void createMapFromFile(da::ContentManager &content, da::EntityManager &entities,
                       const std::string &filename)
{
    xml_document<> doc;
    xml_node<> *node;
    
    std::string tmxText = da::StringHelper::getFileText(filename);
    
    try {
        doc.parse<0>((char *)tmxText.c_str());
        node = doc.first_node();
    } catch (parse_error &e) {
        throw da::DAException(__EXCEPTSRC__, e.what());
    }
    
    unsigned int tileWidth = da::StringHelper::convert<unsigned int>(
        da::XmlHelper::getAttribute(node, "tilewidth")
    );
    unsigned int tileHeight = da::StringHelper::convert<unsigned int>(
        da::XmlHelper::getAttribute(node, "tileheight")
    );
    
    std::pair<unsigned int, da::TexturePtr> tileSet;
    std::vector<std::pair<unsigned int, da::TexturePtr>> tileSetPairs;
    std::vector<da::EntityPtr> tileLayers;
    
    // Parse all nodes
    for (node = node->first_node(); node; node = node->next_sibling()) {
        if (strcmp(node->name(), "tileset") == 0) {
            // Get source filename
            xml_node<> *imgNode = node->first_node("image");
            std::string imgFile =
                    da::XmlHelper::getAttribute(imgNode, "source");
            
            // Get first Gid
            tileSet.first = da::StringHelper::convert<unsigned int>(
                da::XmlHelper::getAttribute(node, "firstgid")
            );
            
            // Load texture
            tileSet.second = content.load<sf::Texture>(imgFile);
            tileSetPairs.push_back(tileSet);
        } else if (strcmp(node->name(), "layer") == 0) {
            // Create a tile layer entity
            da::EntityPtr entity = entities.create();
            
            try {
                createTileLayer(content, entity, node);
            } catch (da::DAException &e) {
                std::cerr << e.message() << std::endl;
                continue;
            }
            
            attr::TileLayer &tileLayer =
                entity->getAttribute<attr::TileLayer>();
            
            tileLayer.tileWidth = tileWidth;
            tileLayer.tileHeight = tileHeight;
            
            tileLayers.push_back(entity);
        } else if (strcmp(node->name(), "objectgroup") == 0) {
            parseObjectGroup(content, entities, node);
        } else if (strcmp(node->name(), "properties") == 0) {
            
        }
    }
    
    // Sort tileSetPairs by gid, and assign them to the tilelayers
    std::sort(tileSetPairs.begin(), tileSetPairs.end(), compareTileSetPair); 
    for (unsigned int i = 0; i < tileSetPairs.size(); i++) {
        attr::TileLayer::sTileSets.push_back(tileSetPairs[i].second);
    }
    
    for (unsigned int i = 0; i < tileLayers.size(); i++) {        
        entities.refresh(tileLayers[i]);
    }
}


void parseObjectGroup(da::ContentManager &content, da::EntityManager &entities,
                      xml_node<> *node)
{
    xml_node<> *obj;
    
    for (obj = node->first_node(); obj; obj = obj->next_sibling()) {
        if (strcmp(obj->name(), "object") != 0) {
            continue;
        }
        
        xml_attribute<> *attr = obj->first_attribute("type");
        if (attr == NULL) {
            continue;
        }
        
        std::string type = da::StringHelper::toLower(attr->value());
        
        std::map<const char *, TiledPrefab>::iterator iter =
            gObjectPrefabs.find(type.c_str());
        if (iter != gObjectPrefabs.end()) {
            da::EntityPtr entity = entities.create();
            iter->second(content, entity, obj);
            entities.refresh(entity);
        }
    }
}

void createTileLayer(da::ContentManager &content, const da::EntityPtr &entity, 
                     xml_node<> *node) {
    // Read the Tiled XML, and gather the TileLayer data
    attr::TileLayer *tileLayer = new attr::TileLayer;

    // Get dimensions
    tileLayer->width = da::StringHelper::convert<unsigned int>(
        da::XmlHelper::getAttribute(node, "width")
    );
    
    tileLayer->height = da::StringHelper::convert<unsigned int>(
        da::XmlHelper::getAttribute(node, "height")
    );
    
    // Get tile IDs
    xml_node<> *data = node->first_node("data");
    if (!data) {
        delete tileLayer;
        throw da::NoSuchNodeXmlException(__EXCEPTSRC__, node->name(), "data");
    }
    
    // We only handle comma-seperated values right now
    if (da::XmlHelper::getAttribute(data, "encoding") == "csv") {
        std::vector<std::string> tokens = da::StringHelper::tokenize(
            data->value(), ", "
        );
        
        for (unsigned int i = 0; i < tokens.size(); i++) {
            int id = da::StringHelper::convert<int>(tokens[i]);
            
            tileLayer->tileIds.push_back(id);
        }
    } else {
        delete tileLayer;
        throw da::NotImplementedException(__EXCEPTSRC__, "Non-CSV map data");
    }
    
    // Add tilelayer to the entity
    entity->addAttribute(tileLayer);
    
    entity->addAttribute(new da::attr::Transform);
    entity->addAttribute(new da::attr::Depth);
}

void createNPC(da::ContentManager &content, const da::EntityPtr &entity,
               xml_node<> *node)
{
    
}

}
