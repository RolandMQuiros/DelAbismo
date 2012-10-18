#ifndef DA_XMLHELPER_H
#define DA_XMLHELPER_H

#include <string>
#include <rapidxml/rapidxml.hpp>

namespace da {
namespace XmlHelper {

std::string getAttribute(rapidxml::xml_node<> *node,
                         const std::string &attributeName);
}
}

#endif
