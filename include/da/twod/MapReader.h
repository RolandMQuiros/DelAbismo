#ifndef DA_MAPREADER_H
#define	DA_MAPREADER_H

#include <vector>
#include <map>
#include <tr1/memory>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "da/DAException.h"
#include "da/twod/TileRect.h"

#include "rapidxml/rapidxml.hpp"

namespace da {

class MapProperties {
public:
    std::map<std::string, std::string> Properties;
protected:
    void loadProperties(rapidxml::xml_node<> *node);
};

class MapReader : private MapProperties {
public:    
    struct Object : public MapProperties {
        Object();
        Object(rapidxml::xml_node<> *node);
        std::string Name;
        std::string Type;
        sf::FloatRect Rect;
        std::vector<sf::Vector2f> Points;
    };
    
    struct Layer : public MapProperties {
        Layer();
        Layer(rapidxml::xml_node<> *node);
        
        std::string Name;
        unsigned int WidthInTiles;
        unsigned int HeightInTiles;
        std::vector<int> Tiles;
        float Opacity;
        bool Visible;
    };
    
    struct ObjectGroup : public MapProperties {
        ObjectGroup();
        ObjectGroup(rapidxml::xml_node<> *node);
        
        std::string Name;
        unsigned int WidthInTiles;
        unsigned int HeightInTiles;
        std::vector<Object> Objects;
        float Opacity;
        bool Visible;
    };
    
    struct TileSet : public MapProperties {
        TileSet();
        TileSet(rapidxml::xml_node<> *node);
        
        std::string Name;
        unsigned int FirstGid;
        unsigned int TileWidth;
        unsigned int TileHeight;
        std::string ImageSource;
    };
    
    unsigned int Width;
    unsigned int Height;
    unsigned int TileWidth;
    unsigned int TileHeight;
    
    std::map<std::string, ObjectGroup> ObjectGroups;
    typedef std::map<std::string, ObjectGroup>::iterator ObjectGroupIter;
    
    std::map<std::string, Layer> Layers;
    typedef std::map<std::string, Layer>::iterator LayerIter;
    
    std::map<std::string, TileSet> TileSets;
    typedef std::map<std::string, TileSet>::iterator TileSetIter;
    
    typedef std::map<std::string, std::string>::iterator PropertyIter;
    
    MapReader();
    MapReader(const std::string &filename);
    void loadFromFile(const std::string &filename);
    
    struct Exception : public da::DAException {
        Exception(const std::string &where, unsigned long line,
                  const std::string &source, const std::string &what);
    };
};

}

#endif
