#ifndef DA_CONTENTTYPES_H
#define DA_CONTENTTYPES_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <memory>

namespace da {

typedef std::shared_ptr<sf::Font> FontPtr;
typedef std::shared_ptr<sf::Image> ImagePtr;
typedef std::shared_ptr<sf::SoundBuffer> SoundBufferPtr;
typedef std::shared_ptr<sf::Texture> TexturePtr;
typedef std::shared_ptr<sf::Shader> ShaderPtr;

}

#endif
