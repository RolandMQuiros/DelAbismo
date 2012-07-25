#include "da/Attribute.h"

namespace da {

Attribute::Attribute(const std::string &typeName) :
mvTypeName(typeName) {
    
}

Attribute::~Attribute() {
    // Reminder: You need this here, or else you'll get a segfault when an
    // Entity destroys its Attributes.
}

const std::string &Attribute::getTypeName() const {
    return mvTypeName;
}

}
