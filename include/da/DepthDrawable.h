#ifndef DA_DEPTHDRAWABLE_H
#define DA_DEPTHDRAWABLE_H

#include <vector>
#include <SFML/Graphics/Drawable.hpp>

namespace da {

class DepthDrawable : public sf::Drawable {
public:
    DepthDrawable();
    
    void pushDepth(int depth);
    void setDepth(unsigned int level, int depth);
    
    unsigned int getLevels() const;
    int getDepth(unsigned int level=0) const;
    
    bool operator<(const DepthDrawable &other);
private:
    std::vector<int> mvDepths;
};

}

#endif
