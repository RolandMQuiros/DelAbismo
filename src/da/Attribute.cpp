#include "da/Attribute.h"

namespace da {

Attribute::Attribute(const std::string &typeName) :
mvTypeName(typeName) {
    
}

const std::string &Attribute::getTypeName() const {
    return mvTypeName;
}

}
