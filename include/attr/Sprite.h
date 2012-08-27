#ifndef ATTR_SPRITE_H
#define ATTR_SPRITE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "da/Attribute.h"
#include "da/ContentTypes.h"

namespace attr {

class Sprite : public da::Attribute<Sprite>,
               public sf::Sprite {
public:    
    Sprite();
    Sprite(const da::TexturePtr &texture);
    Sprite(const da::TexturePtr &texture, const sf::IntRect &rectangle);
    void setTexture(const da::TexturePtr &texture, bool resetRect=false);
    const da::TexturePtr &getTexture() const;
    
    void setRenderStates(const sf::RenderStates &states);
    const sf::RenderStates &getRenderStates() const;

private:
    da::TexturePtr mvTexture;
    sf::RenderStates mvStates;

};

}

#endif
