#include <cstring>

#include "da/StringHelper.h"
#include "da/XmlExceptions.h"
#include "da/XmlHelper.h"
#include "da/NotImplementedException.h"

#include "da/twod/MapReader.h"

namespace da {
////////////////////////////////////////////////////////////////////////////////

void MapProperties::loadProperties(rapidxml::xml_node<> *node) {
    rapidxml::xml_attribute<> *tattr;
    rapidxml::xml_node<> *tnode;
    std::string exsource("MapReader::MapElement::LoadProperties"
                         "(xml_node<> *node)");
    
    for (tnode = tnode->first_node(); tnode; tnode = tnode->next_sibling()) {
        std::string nodeName(tnode->name());        
        if (nodeName != "property") {
            continue;
        }
        
        std::string name = da::XmlHelper::getAttribute(tnode, "name");
        std:: string value = da::XmlHelper::getAttribute(tnode, "value");
        
        Properties[name] = value;
    }    
}
////////////////////////////////////////////////////////////////////////////////
MapReader::Object::Object() { }

MapReader::Object::Object(rapidxml::xml_node<> *node) try {
    rapidxml::xml_attribute<> *tattr;
    rapidxml::xml_node<> *tnode;
    std::string exsource("MapReader::Object::Object(xml_node<> *)");
    
    // Load Object name
    Name = da::XmlHelper::getAttribute(node, "name");
    
    // Get Object Type
    Type = da::XmlHelper::getAttribute(node, "type");
    
    // Get Object x-coordinate
    Rect.left = da::StringHelper::convert<float>(da::XmlHelper::getAttribute(node, "x"));
    
    // Get Object y-coordinate
    Rect.top = da::StringHelper::convert<float>(da::XmlHelper::getAttribute(node, "y"));
    
    // Get Object polyline points, if they exist
    std::string points;
    if ((tnode = node->first_node("polygon")) != NULL &&
        (tattr = tnode->first_attribute("points")) != NULL) {
        std::vector<std::string> pairTokens;
        // Tokenize ordered pairs
        points = tattr->value();
        
        pairTokens = da::StringHelper::tokenize(points, " ");
        for (unsigned int i = 0; i < pairTokens.size(); i++) {
            std::vector<std::string> tokens =
                da::StringHelper::tokenize(pairTokens[i], ",");
            if (tokens.size() == 2) {
                sf::Vector2f pt(da::StringHelper::convert<float>(tokens[0]),
                                da::StringHelper::convert<float>(tokens[1]));
                Points.push_back(pt);
            }
        }
    }
    
    // Get Object properties
    if ((tnode = node->first_node("properties")) != NULL) {
        loadProperties(tnode);
    }
} catch (da::DAException &e) {
    Exception except(__FILE__, __LINE__,
                     "MapReader::Object::Object(xml_node<> *)",
                     "Error reading Map Object");
    except.pushMessage(e);
    
    throw except;
}
////////////////////////////////////////////////////////////////////////////////

MapReader::Layer::Layer() { }

MapReader::Layer::Layer(rapidxml::xml_node<> *node) try {
    rapidxml::xml_node<> *tnode;
    std::string exsource("MapReader::Layer::Layer(xml_node<> *)");
    std::string tmp;

    Name = da::XmlHelper::getAttribute(node, "name");
    
    WidthInTiles = da::StringHelper::convert<float>(
        da::XmlHelper::getAttribute(node, "width")
    );
    
    HeightInTiles = da::StringHelper::convert<float>(
        da::XmlHelper::getAttribute(node, "height")
    );
    
    try {
        Opacity = da::StringHelper::convert<float>(
            da::XmlHelper::getAttribute(node, "opacity")
        );
    } catch (da::DAException &e) {
        // Opacity is optional
        Opacity = 1.f;
    }
    
    try {
        Visible = da::StringHelper::convert<bool>(da::XmlHelper::getAttribute(node, "visible"));
    } catch (da::DAException &e) {
        // Visibility is optional
        Visible = true;
    }
    
    if ((tnode = node->first_node("data")) == NULL) {
        throw da::NoSuchNodeXmlException(
            __FILE__, __LINE__, exsource, node->name(), "data"
        );
    }
    
    // Get tile data
    std::string encoding = da::XmlHelper::getAttribute(tnode, "encoding");
    if (encoding == "csv") {
        std::string data(tnode->value());
        std::vector<std::string> tokens = da::StringHelper::tokenize(data, ",");
        
        for (unsigned int i = 0; i < tokens.size(); i++) {
            Tiles.push_back(da::StringHelper::convert<int>(tokens[i]));
        }
    } else {
        throw da::NotImplementedException(
            __FILE__, __LINE__, exsource, "Non-CSV formats not supported"
        );
    }
    
    // Get Layer properties
    if ((tnode = node->first_node("properties")) != NULL) {
        loadProperties(tnode);
    }
} catch (da::DAException &e) {
    Exception except(__FILE__, __LINE__,
                     "MapReader::Layer::Layer(xml_node<> *)",
                     "Error loading Layer");
    except.pushMessage(e);
    throw except;
}
////////////////////////////////////////////////////////////////////////////////
MapReader::ObjectGroup::ObjectGroup() {
    
}

MapReader::ObjectGroup::ObjectGroup(rapidxml::xml_node<> *node) try {    
    std::string tmp;
    
    Name = da::XmlHelper::getAttribute(node, "name");
    
    tmp = da::XmlHelper::getAttribute(node, "width");
    WidthInTiles = da::StringHelper::convert<unsigned int>(tmp);
    tmp = da::XmlHelper::getAttribute(node, "height");
    HeightInTiles = da::StringHelper::convert<unsigned int>(tmp);
    
    try {
        Opacity = da::StringHelper::convert<float>(da::XmlHelper::getAttribute(node, "opacity"));
    } catch (da::XmlException &e) {
        // Opacity is optional
        Opacity = 1.f;
    }
    
    try {
        Visible = da::StringHelper::convert<bool>(da::XmlHelper::getAttribute(node, "visible"));
    } catch (da::DAException &e) {
        // Visibility is optional
        Visible = true;
    }
    
    for (rapidxml::xml_node<> *tnode = node->first_node(); tnode;
         tnode = tnode->next_sibling()) {
        Objects.push_back(Object(tnode));
    }
} catch (da::DAException &e) {
    Exception except(__FILE__, __LINE__,
                     "MapReader::ObjectGroup::ObjectGroup(xml_node<> *)",
                     "Error loading ObjectGroup");
    except.pushMessage(e);
    throw except;
}
////////////////////////////////////////////////////////////////////////////////
MapReader::TileSet::TileSet() {
}

MapReader::TileSet::TileSet(rapidxml::xml_node<> *node) try {
    Name = da::XmlHelper::getAttribute(node, "name");
    
    FirstGid = da::StringHelper::convert<unsigned int>(
        da::XmlHelper::getAttribute(node, "firstgid")
    );
    
    TileWidth = da::StringHelper::convert<unsigned int>(
        da::XmlHelper::getAttribute(node, "tilewidth")
    );
    
    TileHeight = da::StringHelper::convert<unsigned int>(
        da::XmlHelper::getAttribute(node, "tileheight")
    );
    
    for (rapidxml::xml_node<> *tnode = node->first_node(); tnode;
         tnode = tnode->next_sibling()) {
        std::string nodeName = tnode->name();
        if (nodeName == "image") {
            ImageSource = da::XmlHelper::getAttribute(tnode, "source");
        }
    }
} catch (da::DAException &e) {
    Exception except(__FILE__, __LINE__,
                     "MapReader::ObjectGroup::ObjectGroup(xml_node<> *)",
                     "Error loading ObjectGroup");
    except.pushMessage(e);
    throw except;
}

////////////////////////////////////////////////////////////////////////////////
MapReader::MapReader() {
}

MapReader::MapReader(const std::string &filename) try {
    loadFromFile(filename);
} catch (da::DAException &e) {
    da::DAException except(__FILE__, __LINE__,
                       "MapReader::MapReader(const string&)",
                       "Error parsing Map file " + filename);
    e.pushMessage(except);
    throw e;
}

void MapReader::loadFromFile(const std::string &filename) {
    std::string exsource("MapReader::OpenFromFile");
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *node;
    
    std::string xmlText = da::StringHelper::getFileText(filename);
    if (xmlText.empty()) {
        throw Exception(__FILE__, __LINE__, exsource, "Problem opening file " +
                        filename);
    }
    
    try {
        // Parse XML document into DOM
        doc.parse<0>((char*)xmlText.c_str());
        // Interpret fields
        node = doc.first_node();
    } catch (rapidxml::parse_error &e) {
        throw Exception(__FILE__, __LINE__, exsource, e.what());
    }
    
    if (node == NULL && strcmp(node->name(), "map") != 0) {
        throw Exception(__FILE__, __LINE__, exsource, "Map " + filename +
                        " is missing or malformed");
    }
    
    try {
        TileWidth = da::StringHelper::convert<unsigned int>(
            da::XmlHelper::getAttribute(node,"tilewidth")
        );
        
        TileHeight = da::StringHelper::convert<unsigned int>(
            da::XmlHelper::getAttribute(node, "tileheight")
        );
        
        for (node = node->first_node(); node; node = node->next_sibling()) {
            std::string nodeName(node->name());
            if (nodeName == "properties") {
                loadProperties(node);
            } else if (nodeName == "tileset") {
                TileSet ts(node);
                TileSets[ts.Name] = ts;
            } else if (nodeName == "layer") {
                Layer layer(node);
                Layers[layer.Name] = layer;
            } else if (nodeName == "objectgroup") {
                ObjectGroup group(node);
                ObjectGroups[group.Name] = group;
            }
        }
    } catch (da::DAException &e) {
        Exception except(__FILE__, __LINE__, exsource, "Error loading map " +
                         filename);
        except.pushMessage(e);
        
        throw except;
    }
}

MapReader::Exception::Exception(const std::string &where, unsigned long line,
                                const std::string &source,
                                const std::string &what) :
da::DAException(where, line, source, what) { }

}
