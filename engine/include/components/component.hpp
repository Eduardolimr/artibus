#ifndef __ENGINE_COMPONENTS_COMPONENT__
#define __ENGINE_COMPONENTS_COMPONENT__

#include "gameobject.hpp"

namespace engine {

class Component {
    friend bool GameObject::add_component(Component & component);

public:
    enum class State {
        enabled,
        disabled,
        invalid
    };

    Component() : m_game_object(NULL), m_state(State::invalid) {}

    virtual ~Component() {}

    virtual bool init()     { return true; }
    virtual void setup()    { return; }
    virtual bool shutdown() { return true; }
    virtual void update()   { return; }
    virtual void draw()     { return; }

    inline State              state()       { return m_state; }
    inline const GameObject * game_object() { return m_game_object; }

    inline void enable()  { m_state = State::enabled; }
    inline void disable() { m_state = State::disabled; }

protected:
    GameObject * m_game_object;
    State        m_state;
};

}

#endif
