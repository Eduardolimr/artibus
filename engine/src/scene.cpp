#include <algorithm>

#include "log.h"
#include "scene.hpp"

using namespace engine;

GameObject INVALID_GAME_OBJECT;

bool Scene::add_game_object(GameObject & obj)
{
    auto id = obj.name();
    INFO("Add game object " << id << " to scene " << m_name);

    if (m_objects.find(id) != m_objects.end())
    {
        WARN("Game object " << id << " already exists!");
        return false;
    }
    if (obj.get_layer() >= Scene::n_layers)
    {
        WARN("Game object " << id << " has invalid layer " << obj.get_layer()
             << "\nLayer must be less than " << Scene::n_layers);
        return false;
    }

    m_objects[id] = &obj;
    m_layers[obj.get_layer()].push_back(&obj);
    std::sort(m_layers[obj.get_layer()].begin(), m_layers[obj.get_layer()].end(),
         [](const GameObject * a, const GameObject * b) -> bool
         {
             if (a->get_layer_order() == b->get_layer_order())
                 return a->name() > b->name();
             return a->get_layer_order() < b->get_layer_order();
         }
    );
    return true;
}

GameObject & Scene::get_game_object(const std::string & id)
{
    if (m_objects.find(id) == m_objects.end())
    {
        WARN("Could not find game object " << id);
        return INVALID_GAME_OBJECT;
    }

    return *m_objects[id];
}

bool Scene::remove_game_object(const std::string & id)
{
    INFO("Remove game object " << id << " from scene " << m_name);

    if (m_objects.find(id) == m_objects.end())
    {
        WARN("Could not find game object " << id);
        return false;
    }

    int layer = m_objects[id]->get_layer();
    int i = 0;
    for(auto obj: m_layers[layer]) {
        if (obj->name() == id) {
            m_layers[layer].erase(m_layers[layer].begin() + i);
            break;
        }
        i++;
    }
    m_objects.erase(id);
    return true;
}

bool Scene::init()
{
    INFO("Init scene " << m_name);

    for (auto id_obj: m_objects)
    {
        auto obj = id_obj.second;
        if (obj->init() == false)
        {
            WARN("Could not init game object " << obj->name());
            return false;
        }
    }

    return true;
}

void Scene::setup()
{
    INFO("Setup scene " << m_name);

    for (auto id_obj: m_objects)
        id_obj.second->setup();
}

bool Scene::shutdown()
{
    INFO("Shutdown scene " << m_name);

    for (auto id_obj: m_objects)
    {
        auto obj = id_obj.second;
        if (obj->shutdown() == false)
        {
            WARN("Could not shutdown game object " << obj->name());
        }
    }

    return true;
}

void Scene::update()
{
    for (auto layer: m_layers) {
        for (auto obj: layer) {
            if (obj->state() == GameObject::State::enabled) obj->update();
        }
    }
}

void Scene::draw()
{
     for (auto layer: m_layers) {
        for (auto obj: layer) {
            if (obj->state() == GameObject::State::enabled) obj->draw();
        }
    }
}
