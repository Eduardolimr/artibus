#ifndef __ENGINE_COMPONENTS_CODE__
#define __ENGINE_COMPONENTS_CODE__

#include <string>

#include "components/component.hpp"

namespace engine {

class CodeComponent : public Component {
public:
    CodeComponent() : Component() {}

    virtual ~CodeComponent() {}

    virtual bool init() { return Component::init(); };
    virtual bool shutdown() { return Component::shutdown(); };
    virtual void update() { Component::update(); } ;
};

}

#endif

