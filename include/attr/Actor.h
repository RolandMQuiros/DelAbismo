#ifndef ATTR_ACTOR_H
#define ATTR_ACTOR_H

#include <string>
#include <da/Attribute.h>
#include "Signals/Signal.h"

using namespace Gallant;

namespace attr {

struct Actor : public da::Attribute<Actor> {
    std::string name;
};

}

#endif
