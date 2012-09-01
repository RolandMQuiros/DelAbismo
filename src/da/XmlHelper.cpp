#include "da/XmlHelper.h"
#include "da/XmlExceptions.h"

namespace da {
namespace XmlHelper {

std::string getAttribute(rapidxml::xml_node<> *node,
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

}

}
