#include "gameobject.hpp"
#include "components/component.hpp"
#include "log.h"

using namespace engine;

bool GameObject::init()
{
    INFO("Init game object " << m_name);

    for(auto id_componentlist: m_components)
    {
        for (auto component: id_componentlist.second)
        {
            if(component->init() == false) return false;
        }
    }

    return true;
}

void GameObject::setup()
{
    INFO("Setup game object " << m_name);

    for(auto id_componentlist: m_components)
        for (auto component: id_componentlist.second)
            component->setup();
}

bool GameObject::shutdown()
{
    INFO("Shutdown game object " << m_name);

    for(auto id_componentlist: m_components)
    {
        for (auto component: id_componentlist.second)
        {
            if(component->shutdown() == false) return false;
        }
    }

    return true;
}

void GameObject::update()
{
    for(auto id_componentlist: m_components)
    {
        for (auto component: id_componentlist.second)
        {
            if(component->state() == Component::State::enabled)
                component->update();
        }
    }
}

void GameObject::draw()
{
    for(auto id_componentlist: m_components)
    {
        for (auto component: id_componentlist.second)
        {
            if(component->state() == Component::State::enabled)
                component->draw();
        }
    }
}

bool GameObject::add_component(Component & component)
{
    INFO("Adding component to game object " << m_name);
    m_components[std::type_index(typeid(component))].push_back(&component);

    component.m_game_object = this;
    component.m_state = Component::State::enabled;

    return true;
}

template<typename T>
std::list<Component *> GameObject::get_components()
{
    return m_components[std::type_index(typeid(T))];
}
