#include "da/ContentManager.h"

namespace da {

template <>
TexturePtr ContentManager::load<sf::Texture>(const std::string &source) {
    {
        std::map<std::string, TexturePtr>::iterator iter;
        if ((iter = mvTextures.find(source)) != mvTextures.end()) {
            return iter->second;
        }
    }
    
    TexturePtr ret;
    sf::Texture *newTexture = new sf::Texture();
    if (newTexture->loadFromFile(source)) {
        ret = TexturePtr(newTexture);
        mvTextures[source] = ret;
    }
    
    return ret;
}

template <>
FontPtr ContentManager::load<sf::Font>(const std::string &source) {
    {
        std::map<std::string, FontPtr>::iterator iter;
        if ((iter = mvFonts.find(source)) != mvFonts.end()) {
            return iter->second;
        }
    }
    
    FontPtr ret;
    sf::Font *newFont = new sf::Font();
    if (newFont->loadFromFile(source)) {
        ret = FontPtr(newFont);
        mvFonts[source] = ret;
    }
    
    return ret;
}

template <>
SoundBufferPtr
ContentManager::load<sf::SoundBuffer>(const std::string &source) {
    {
        std::map<std::string, SoundBufferPtr>::iterator iter;
        if ((iter = mvSoundBuffers.find(source)) != mvSoundBuffers.end()) {
            return iter->second;
        }
    }
    
    SoundBufferPtr ret;
    sf::SoundBuffer *newSoundBuffer = new sf::SoundBuffer();
    if (newSoundBuffer->loadFromFile(source)) {
        ret = SoundBufferPtr(newSoundBuffer);
        mvSoundBuffers[source] = ret;
    }
    
    return ret;
}

template <>
TexturePtr ContentManager::load<sf::Texture>(const std::string &key,
                                         const char *data,
                                         std::size_t sizeInBytes) {
    {
        std::map<std::string, TexturePtr>::iterator iter;
        if ((iter = mvTextures.find(key)) != mvTextures.end()) {
            return iter->second;
        }
    }
    
    TexturePtr ret;
    sf::Texture *newTexture = new sf::Texture();
    if (newTexture->loadFromMemory(data, sizeInBytes)) {
        ret = TexturePtr(newTexture);
        mvTextures[key] = ret;
    }
    
    return ret;
}

template <>
FontPtr ContentManager::load<sf::Font>(const std::string &key,
                                         const char *data,
                                         std::size_t sizeInBytes) {
    {
        std::map<std::string, FontPtr>::iterator iter;
        if ((iter = mvFonts.find(key)) != mvFonts.end()) {
            return iter->second;
        }
    }
    
    FontPtr ret;
    sf::Font *newFont = new sf::Font();
    if (newFont->loadFromMemory(data, sizeInBytes)) {
        ret = FontPtr(newFont);
        mvFonts[key] = ret;
    }
    
    return ret;
}

template <>
SoundBufferPtr ContentManager::load<sf::SoundBuffer>(const std::string &key,
                                         const char *data,
                                         std::size_t sizeInBytes) {
    {
        std::map<std::string, SoundBufferPtr>::iterator iter;
        if ((iter = mvSoundBuffers.find(key)) != mvSoundBuffers.end()) {
            return iter->second;
        }
    }
    
    SoundBufferPtr ret;
    sf::SoundBuffer *newSoundBuffer = new sf::SoundBuffer();
    if (newSoundBuffer->loadFromMemory(data, sizeInBytes)) {
        ret = SoundBufferPtr(newSoundBuffer);
        mvSoundBuffers[key] = ret;
    }
    
    return ret;
}

}
