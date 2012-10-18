#ifndef ATTR_SPRITE_H
#define ATTR_SPRITE_H

#include <SFML/Graphics/Sprite.hpp>

#include <da/Attribute.h>
#include <da/ContentTypes.h>

namespace attr {

class Sprite : public da::Attribute<Sprite>,
               public sf::Sprite {
public:
    Sprite(const da::TexturePtr &texture);
    Sprite(const da::TexturePtr &texture, const sf::IntRect &rectangle);
    void setTexture(const da::TexturePtr &texture, bool resetRect=false);
    
    void setEnabled(bool enabled);
    bool isEnabled() const;
    
private:
    bool mIsEnabled;
    da::TexturePtr mTexture;
    
};

}

#endif
