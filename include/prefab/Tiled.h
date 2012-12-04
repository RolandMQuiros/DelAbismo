/**
 * Entities created by reading a Tiled .tmx file.
 */

#ifndef PREFAB_TILED_H
#define PREFAB_TILED_H

#include <rapidxml/rapidxml.hpp>

#include <da/ContentManager.h>
#include <da/EntityManager.h>

using namespace rapidxml;

namespace prefab {

void createMapFromFile(da::ContentManager &content, da::EntityManager &manager,
                       const std::string &filename);
    
}

#endif
