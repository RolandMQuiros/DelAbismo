#include <cstring>
#include <iostream>
#include <fstream>

#include "da/MapReader.h"
#include "da/Helper.h"
#include "da/TileRect.h"
#include "da/XmlExceptions.h"
#include "da/NotImplementedException.h"

namespace da {

std::string GetAttribute(rapidxml::xml_node<> *node,
                         const std::string &attributeName) {
    std::string ret;
    rapidxml::xml_attribute<> *attr;
    
    if (node == NULL) {
        return ret;
    }
    
    if ((attr = node->first_attribute(attributeName.c_str())) == NULL) {
        throw NoSuchAttributeXmlException(
            __FILE__, __LINE__, "GetAttribute(xml_node<> *, const string &)",
             node->name(), attributeName
        );
    }
    
    return attr->value();
}

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
        
        std::string name = GetAttribute(tnode, "name");
        std:: string value = GetAttribute(tnode, "value");
        
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
    Name = GetAttribute(node, "name");
    
    // Get Object Type
    Type = GetAttribute(node, "type");
    
    // Get Object x-coordinate
    Rect.left = stringConvert<float>(GetAttribute(node, "x"));
    
    // Get Object y-coordinate
    Rect.top = stringConvert<float>(GetAttribute(node, "y"));
    
    // Get Object polyline points, if they exist
    std::string points;
    if ((tnode = node->first_node("polygon")) != NULL &&
        (tattr = tnode->first_attribute("points")) != NULL) {
        std::vector<std::string> pairTokens;
        // Tokenize ordered pairs
        points = tattr->value();
        
        pairTokens = tokenize(points, " ");
        for (unsigned int i = 0; i < pairTokens.size(); i++) {
            std::vector<std::string> tokens = tokenize(pairTokens[i], ",");
            if (tokens.size() == 2) {
                sf::Vector2f pt(stringConvert<float>(tokens[0]),
                                stringConvert<float>(tokens[1]));
                Points.push_back(pt);
            }
        }
    }
    
    // Get Object properties
    if ((tnode = node->first_node("properties")) != NULL) {
        loadProperties(tnode);
    }
} catch (DAException &e) {
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

    Name = GetAttribute(node, "name");
    WidthInTiles = stringConvert<float>(GetAttribute(node, "width"));
    HeightInTiles = stringConvert<float>(GetAttribute(node, "height"));
    
    try {
        Opacity = stringConvert<float>(GetAttribute(node, "opacity"));
    } catch (DAException &e) {
        // Opacity is optional
        Opacity = 1.f;
    }
    
    try {
        Visible = stringConvert<bool>(GetAttribute(node, "visible"));
    } catch (DAException &e) {
        // Visibility is optional
        Visible = true;
    }
    
    if ((tnode = node->first_node("data")) == NULL) {
        throw NoSuchNodeXmlException(
            __FILE__, __LINE__, exsource, node->name(), "data"
        );
    }
    
    // Get tile data
    std::string encoding = GetAttribute(tnode, "encoding");
    if (encoding == "csv") {
        std::string data(tnode->value());
        std::vector<std::string> tokens = tokenize(data, ",");
        
        for (unsigned int i = 0; i < tokens.size(); i++) {
            Tiles.push_back(stringConvert<int>(tokens[i]));
        }
    } else {
        throw NotImplementedException(
            __FILE__, __LINE__, exsource, "Non-CSV formats not supported"
        );
    }
    
    // Get Layer properties
    if ((tnode = node->first_node("properties")) != NULL) {
        loadProperties(tnode);
    }
} catch (DAException &e) {
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
    
    Name = GetAttribute(node, "name");
    
    tmp = GetAttribute(node, "width");
    WidthInTiles = stringConvert<unsigned int>(tmp);
    tmp = GetAttribute(node, "height");
    HeightInTiles = stringConvert<unsigned int>(tmp);
    
    try {
        Opacity = stringConvert<float>(GetAttribute(node, "opacity"));
    } catch (XmlException &e) {
        // Opacity is optional
        Opacity = 1.f;
    }
    
    try {
        Visible = stringConvert<bool>(GetAttribute(node, "visible"));
    } catch (DAException &e) {
        // Visibility is optional
        Visible = true;
    }
    
    for (rapidxml::xml_node<> *tnode = node->first_node(); tnode;
         tnode = tnode->next_sibling()) {
        Objects.push_back(Object(tnode));
    }
} catch (DAException &e) {
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
    Name = GetAttribute(node, "name");
    FirstGid = stringConvert<unsigned int>(GetAttribute(node, "firstgid"));
    TileWidth = stringConvert<unsigned int>(GetAttribute(node, "tilewidth"));
    TileHeight = stringConvert<unsigned int>(GetAttribute(node, "tileheight"));
    
    for (rapidxml::xml_node<> *tnode = node->first_node(); tnode;
         tnode = tnode->next_sibling()) {
        std::string nodeName = tnode->name();
        if (nodeName == "image") {
            ImageSource = GetAttribute(tnode, "source");
        }
    }
} catch (DAException &e) {
    Exception except(__FILE__, __LINE__,
                     "MapReader::ObjectGroup::ObjectGroup(xml_node<> *)",
                     "Error loading ObjectGroup");
    except.pushMessage(e);
    throw except;
}

////////////////////////////////////////////////////////////////////////////////
MapReader::MapReader() {
}

MapReader::MapReader(const std::string &fileName) try {
    loadFromFile(fileName);
} catch (DAException &e) {
    DAException except(__FILE__, __LINE__,
                       "MapReader::MapReader(const string&)",
                       "Error parsing Map file " + fileName);
    e.pushMessage(except);
    throw e;
}

void MapReader::loadFromFile(const std::string &fileName) {
    std::string exsource("MapReader::OpenFromFile");
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<> *node;
    std::ifstream ifs(fileName.c_str());
    
    if (!ifs.is_open()) {
        throw Exception(__FILE__, __LINE__, exsource, "Problem opening file " +
                        fileName);
    }
    
    std::string xmlText;
    
    // Load XML file text into memory
    ifs.seekg(0, std::ios::end);
    xmlText.reserve((unsigned long int)ifs.tellg());
    ifs.seekg(0, std::ios::beg);
    xmlText.assign((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());
    ifs.close();
    
    try {
        // Parse XML document into DOM
        doc.parse<0>((char*)xmlText.c_str());
        // Interpret fields
        node = doc.first_node();
    } catch (rapidxml::parse_error &e) {
        throw Exception(__FILE__, __LINE__, exsource, e.what());
    }
    
    if (node == NULL && strcmp(node->name(), "map") != 0) {
        throw Exception(__FILE__, __LINE__, exsource, "Map " + fileName +
                        " is missing or malformed");
    }
    
    try {
        TileWidth = stringConvert<unsigned int>(
            GetAttribute(node,"tilewidth")
        );
        
        TileHeight = stringConvert<unsigned int>(
            GetAttribute(node, "tileheight")
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
    } catch (DAException &e) {
        Exception except(__FILE__, __LINE__, exsource, "Error loading map " +
                         fileName);
        except.pushMessage(e);
        
        throw except;
    }
}

MapReader::Exception::Exception(const std::string &where, unsigned long line,
                                const std::string &source,
                                const std::string &what) :
DAException(where, line, source, what) { }

}