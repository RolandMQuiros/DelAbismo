#include <algorithm>
#include <iostream>
#include <limits.h>
#include <SFML/Window/Keyboard.hpp>

#include "da/DAException.h"
#include "da/StringHelper.h"
#include "da/Transform.h"
#include "common/WalkSprite.h"
#include "sim/CharacterRenderer.h"
#include "sim/PlayerRenderer.h"
#include "sim/PlayerUpdater.h"
#include "sim/Sim.h"

namespace sim {

std::shared_ptr<CharacterRenderer> renderer;
std::shared_ptr<PlayerUpdater> updater;
    
Sim::Sim(da::Game &game) :
mvGame(game) {
}

void Sim::initialize() {
    renderer = std::shared_ptr<CharacterRenderer>(
        new CharacterRenderer(mvDrawList)
    );
    renderer->setTarget(mvGame);
    
    updater = std::shared_ptr<PlayerUpdater>(new PlayerUpdater());
    
    mvEntities.addBehavior(renderer);
    mvEntities.addBehavior(updater);
    
    createCharacter();
}

void Sim::dispose() {
    
}

void Sim::update() {
    updater->update(mvGame.getFrameTime());
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
        mvEntities.clear();
    }
}

void Sim::draw() {
    renderer->update(mvGame.getFrameTime());
    
    mvDrawList.sort();
    mvGame.draw(mvDrawList);
    mvDrawList.clear();
}

void Sim::loadMap(const std::string &fileName) {
    da::MapReader reader;
    try {
        reader.loadFromFile(fileName);
    } catch (da::MapReader::Exception &e) {
        std::cerr << e.message();
        return;
    }
    
    // Extract the TileSets, which hold the tile dimensions.
    loadTileSets(reader);
    if (mvTileSets.empty()) {
        da::DAException except(
            __FILE__, __LINE__,
            "WorldState::LoadMap(const string &)",
            "No TileSets could be loaded"
        );
        std::cerr << except.message();
        return;
    }
    
    // Next, we extract the TileLayers
    loadTileLayers(reader);
    
    // Then, the Entities
    // loadEntities(reader);
    
    // Clear our TileSet cache, since the layers already have their own
    // references
    mvTileSets.clear();
}

da::EntityPtr Sim::createCharacter() {
    da::EntityPtr entity = mvEntities.create();
    
    entity->addAttribute(new da::Transform()); // Segfaults
    entity->addAttribute(da::AttributePtr(new da::Depth()));  // Doesn't
    
    da::TexturePtr texture = mvGame.content.load<sf::Texture>(
        "content/textures/Slamsona 3.jpg"
    );
    
    entity->addAttribute(da::AttributePtr(new common::WalkSprite(
        texture, sf::Vector2i(), sf::Vector2i(64, 64), 5
    )));
    
    mvEntities.refresh(entity);
    return entity;
}

void Sim::loadTileSets(da::MapReader &reader) {
    da::MapReader::TileSetIter iter;
    for (iter = reader.TileSets.begin(); iter != reader.TileSets.end();
         iter++) {
        da::TexturePtr texture =
            mvGame.content.load<sf::Texture>(iter->second.ImageSource);
        
        std::shared_ptr<da::TileSet> tsPtr(
            new da::TileSet(
                texture, iter->second.TileWidth, iter->second.TileHeight
            )
        );
        
        if (tsPtr) {
            mvTileSets.push_back(tsPtr);
        }
    }
}

void Sim::loadTileLayers(da::MapReader &reader) {
    da::MapReader::LayerIter iter;
    int depth = 0;
    for (iter = reader.Layers.begin(); iter != reader.Layers.end(); iter++) {
        da::MapReader::Layer &layerData = iter->second;
        // Construct TileLayer
        std::unique_ptr<da::TileLayer> layer(
            new da::TileLayer(layerData.WidthInTiles,
                              layerData.HeightInTiles,
                              reader.TileWidth,
                              reader.TileHeight)
        );
        
        if (!layer) {
            continue;
        }
        
        // Add TileSet references
        for (unsigned int i = 0; i < mvTileSets.size(); i++) {
            layer->addTileSet(mvTileSets[i]);
        }
        
        // Add Tile IDs
        for (unsigned int i = 0; i < layerData.Tiles.size(); i++) {
            int row, col;
            
            // Get the row and column of current tile
            layer->indexToRowCol(i, row, col);
            // Assign tile ID to location in layer
            layer->setTileId(row, col, layerData.Tiles[i]);
        }
        
        // Get TileLayer properties
        da::MapReader::PropertyIter pIter;
        sf::Vector2f scroll;
        sf::Color color = sf::Color::White;
        for (pIter = layerData.Properties.begin();
             pIter != layerData.Properties.end(); pIter++) {
            std::string name(pIter->first);
            std::string value(pIter->second);
            if (name == "wrap") {
                layer->setWrap(da::StringHelper::convert<bool>(value));
            } /*else if (name == "depth") {
                layer->setDepth(0, da::StringHelper::convert<long>(value));
            }*/ else if (name == "xscroll") {
                scroll.x = da::StringHelper::convert<float>(value);
            } else if (name == "yscroll") {
                scroll.y = da::StringHelper::convert<float>(value);
            } else if (name == "r") {
                color.r = da::StringHelper::convert<unsigned char>(value);
            } else if (name == "g") {
                color.g = da::StringHelper::convert<unsigned char>(value);
            } else if (name == "b") {
                color.b = da::StringHelper::convert<unsigned char>(value);
            }
        }
        
        //layer->setScroll(scroll);
        color.a = (layerData.Opacity * UCHAR_MAX);
        layer->setColor(color);
        
        mvTileLayers.push_back(std::move(layer));
    }
}

}
