#ifndef DEPTHDRAWLIST_H
#define DEPTHDRAWLIST_H

#include <vector>
#include <functional>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "attr/Depth.h"

typedef std::function<void(sf::RenderTarget &, sf::RenderStates)>
    DrawFunction;

class DepthDrawList {
public:
    void push(const DrawFunction &draw, const attr::Depth &depth,
              const sf::RenderStates &states);
    void sort();
    void clear();
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    struct DrawRequest {
        DrawFunction draw;
        const attr::Depth *depth;
        sf::RenderStates states;
        
        DrawRequest(const DrawFunction &draw, const attr::Depth &depth,
                    const sf::RenderStates &states);
        bool operator<(const DrawRequest &other) const;
    };

    std::vector<DrawRequest> mvList;
    
};

#endif
