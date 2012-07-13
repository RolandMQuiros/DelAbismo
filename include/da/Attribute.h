#ifndef DA_ATTRIBUTE_H
#define DA_ATTRIBUTE_H

#include <string>
#include <memory>

namespace da {

struct Attribute {
public:
    Attribute(const std::string &typeName);
    const std::string &getTypeName() const;
private:
    std::string mvTypeName;
};

typedef std::shared_ptr<Attribute> AttributePtr;
typedef std::weak_ptr<Attribute> AttributeRef;

}

#endif
