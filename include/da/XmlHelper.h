#ifndef DA_XMLHELPER_H
#define DA_XMLHELPER_H

#include <string>
#include <rapidxml/rapidxml.hpp>

namespace da {

std::string getXmlAttribute(rapidxml::xml_node<> *node,
                            const std::string &attributeName);
}

#endif
