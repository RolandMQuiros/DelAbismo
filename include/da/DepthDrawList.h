#ifndef DA_DEPTHDRAWLIST_H
#define DA_DEPTHDRAWLIST_H

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "da/Depth.h"

namespace da {

class DepthDrawList : public sf::Drawable {
public:
    void push(const sf::Drawable &drawable, const Depth &depth,
              const sf::RenderStates &states);
    void sort();
    void clear();
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    struct DrawRequest {
        const sf::Drawable *drawable;
        const Depth *depth;
        sf::RenderStates states;
        
        bool operator<(const DrawRequest &other) const;
    };

    std::vector<DrawRequest> mvList;
};

}

#endif
