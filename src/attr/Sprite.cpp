#include "attr/Sprite.h"

namespace attr {

Sprite::Sprite(const da::TexturePtr &texture) :
sf::Sprite(*texture),
mTexture(texture) { }

Sprite::Sprite(const da::TexturePtr &texture, const sf::IntRect &rectangle) :
sf::Sprite(*texture, rectangle),
mTexture(texture) { }

void Sprite::setTexture(const da::TexturePtr &texture, bool resetRect) {
    mTexture = texture;
    sf::Sprite::setTexture(*mTexture, resetRect);
}

void Sprite::setEnabled(bool enabled) {
    mIsEnabled = enabled;
}

bool Sprite::isEnabled() const {
    return mIsEnabled;
}

}
