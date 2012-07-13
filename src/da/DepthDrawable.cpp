#include "da/DepthDrawable.h"

namespace da {

DepthDrawable::DepthDrawable() {
    mvDepths.push_back(0);
}

void DepthDrawable::pushDepth(int depth) {
    mvDepths.push_back(depth);
}

void DepthDrawable::setDepth(unsigned int level, int depth) {
    if (level < mvDepths.size()) {
        mvDepths[level] = depth;
    }
}

unsigned int DepthDrawable::getLevels() const {
    return mvDepths.size();
}

int DepthDrawable::getDepth(unsigned int level) const {
    return mvDepths[level];
}

bool DepthDrawable::operator<(const DepthDrawable &other) {
    for (unsigned int i = 0; i < other.getLevels(); i++) {
        if (mvDepths[i] < other.mvDepths[i]) {
            return true;
        } else if (mvDepths[i] > other.mvDepths[i]) {
            return false;
        }
    }
    
    return false;
}
    
}
