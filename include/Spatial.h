#ifndef Spatial_H
#define Spatial_H

#include <unordered_map>
#include <functional>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include "da/Entity.h"

typedef unsigned int SpatialId;

class SpatialBase : public sf::Drawable {
private:
    da::Entity &mEntity;

public:
    SpatialBase(da::Entity &entity) :
    mEntity(entity) { }
    
    da::Entity &getEntity() {
        return mEntity;
    }
    
protected:
    static SpatialId sNextId;

};

template <class Derived>
class Spatial : public SpatialBase {
private:
    static SpatialId msTypeId;

public:
    Spatial(da::Entity &entity) :
    SpatialBase(entity) {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
    }
    
    virtual ~Spatial() { }
    
    static SpatialId typeId() {
        if (msTypeId == 0) {
            msTypeId = ++sNextId;
        }
        
        return msTypeId;
    }
    
    SpatialId getTypeId() const {
        return msTypeId;
    }
};

template <class Derived> SpatialId Spatial<Derived>::msTypeId = 0;

#endif
