#ifndef DA_DEPTHDRAWABLE_H
#define DA_DEPTHDRAWABLE_H

#include <vector>
#include "da/Attribute.h"

namespace da {

class Depth : public Attribute {
public:
    static const char *TypeName;
    
    Depth();
    
    void pushDepth(int depth);
    void setDepth(unsigned int level, int depth);
    
    unsigned int getLevelCount() const;
    int getDepth(unsigned int level=0) const;
    
    bool operator<(const Depth &other) const;
    bool operator==(const Depth &other) const;
    bool operator>(const Depth &other) const;
private:
    std::vector<int> mvDepths;
};

}

#endif
