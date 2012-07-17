#include "da/Depth.h"

namespace da {

const char *Depth::TypeName = "da::Depth";
    
Depth::Depth() :
Attribute(TypeName) {
    mvDepths.push_back(0);
}

void Depth::pushDepth(int depth) {
    mvDepths.push_back(depth);
}

void Depth::setDepth(unsigned int level, int depth) {
    if (level < mvDepths.size()) {
        mvDepths[level] = depth;
    }
}

unsigned int Depth::getLevelCount() const {
    return mvDepths.size();
}

int Depth::getDepth(unsigned int level) const {
    return mvDepths[level];
}

bool Depth::operator<(const Depth &other) const {
    unsigned int i;
    for (i = 0; i < getLevelCount() && i < other.getLevelCount(); i++) {
        if (mvDepths[i] < other.mvDepths[i]) {
            return true;
        } else if (mvDepths[i] > other.mvDepths[i]) {
            return false;
        }
    }
    
    if (i < getLevelCount()) {
        return true;
    } else if (i < other.getLevelCount()) {
        return false;
    }
    
    return false;
}

bool Depth::operator==(const Depth &other) const {
    if (getLevelCount() != other.getLevelCount()) {
        return false;
    }
    
    for (unsigned int i = 0; i < getLevelCount() &&
                             i < other.getLevelCount(); i++) {
        if (mvDepths[i] != other.mvDepths[i]) {
            return false;
        }
    }
    
    return true;
}

bool Depth::operator>(const Depth &other) const {
    return !(*this < other);
}
    
}
