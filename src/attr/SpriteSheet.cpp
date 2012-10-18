#include "attr/SpriteSheet.h"

namespace attr {

void SpriteSheet::setTexture(const da::TexturePtr &texture) {
    mTexture = texture;
}

const da::TexturePtr &SpriteSheet::getTexture() const {
    return mTexture;
}

void SpriteSheet::addFrame(const std::string &pose,
                           const sf::IntRect &subrect) {
    mPoses[pose].push_back(subrect);
}

sf::IntRect SpriteSheet::getFrame(const std::string &pose,
                                  unsigned int index) const {
    sf::IntRect ret;
    
    PoseMap::const_iterator search = mPoses.find(pose);
    if (search != mPoses.end() && search->second.size() > index) {
        ret = search->second[index];
    }
    
    return ret;
}

unsigned int SpriteSheet::getFrameCount(const std::string &pose) const {
    unsigned int ret = 0;
    
    PoseMap::const_iterator search = mPoses.find(pose);
    if (search != mPoses.end()) {
        ret = search->second.size();
    }
    
    return ret;
}

}
