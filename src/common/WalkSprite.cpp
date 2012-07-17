#include "common/WalkSprite.h"

namespace common {
    
const char *WalkSprite::TypeName = "common::WalkSprite";
const unsigned int WalkSprite::DirectionCount = 8;

WalkSprite::WalkSprite(const da::TexturePtr &texture,
                       const sf::Vector2i &offset,
                       const sf::Vector2i &frameSize,
                       unsigned int framesPerDirection) :
da::Attribute(TypeName) {
    
    for (unsigned int i = 0; i < DirectionCount; i++) {
        directions[i].setTexture(texture);
        for (unsigned int j = 0; j < framesPerDirection; j++) {
            sf::IntRect frame(offset.x + (frameSize.x * j),
                              offset.y + (frameSize.y * i),
                              frameSize.x, frameSize.y);
            directions[i].addFrame(frame);
        }
        directions[i].setSecondsPerFrame(1.f);
        directions[i].play();
    }
}
    
}