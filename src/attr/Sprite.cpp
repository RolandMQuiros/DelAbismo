#include "attr/Sprite.h"

namespace attr {

Sprite::Sprite() {
    
}

Sprite::Sprite(const da::TexturePtr &texture) :
sf::Sprite(*texture),
mvTexture(texture) {
    
}

Sprite::Sprite(const da::TexturePtr &texture, const sf::IntRect &rectangle) :
sf::Sprite(*texture, rectangle),
mvTexture(texture) {
    
}

void Sprite::setTexture(const da::TexturePtr &texture, bool resetRect) {
    sf::Sprite::setTexture(*texture, resetRect);
    mvTexture = texture;
}

const da::TexturePtr &Sprite::getTexture() const {
    return mvTexture;
}

void Sprite::setRenderStates(const sf::RenderStates &states) {
    mvStates = states;
}

const sf::RenderStates &Sprite::getRenderStates() const {
    return mvStates;
}

}
