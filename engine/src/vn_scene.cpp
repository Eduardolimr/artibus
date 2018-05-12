#include <algorithm>

#include "log.h"
#include "vn_scene.hpp"

using namespace engine;

GameObject INVALID_GAME_OBJECT;

bool VisualNovelScene::add_background(GameObject & obj)
{
    auto id = obj.name();
    INFO("Add background " << id << " to VisualNovelScene " << m_name);

    if (m_vn_objects.m_background.find(id) != m_vn_objects.m_background.end())
    {
        WARN("Background " << id << " already exists!");
        return false;
    }
    if (obj.get_layer() >= VisualNovelScene::n_layers)
    {
        WARN("BACKGROUND " << id << " has invalid layer " << obj.get_layer()
             << "\nLayer must be less than " << VisualNovelScene::n_layers);
        return false;
    }

    m_vn_objects.m_background[id] = &obj;
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

bool VisualNovelScene::add_character(GameObject & obj)
{
    auto id = obj.name();
    INFO("Add character " << id << " to VisualNovelScene " << m_name);

    if (m_vn_objects.m_character.find(id) != m_vn_objects.m_character.end())
    {
        WARN("Character " << id << " already exists!");
        return false;
    }
    if (obj.get_layer() >= VisualNovelScene::n_layers)
    {
        WARN("Character " << id << " has invalid layer " << obj.get_layer()
             << "\nLayer must be less than " << VisualNovelScene::n_layers);
        return false;
    }

    m_vn_objects.m_character[id] = &obj;
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


bool VisualNovelScene::add_text(GameObject & obj)
{
    auto id = obj.name();
    INFO("Add text " << id << " to VisualNovelScene " << m_name);

    if (m_vn_objects.m_text.find(id) != m_vn_objects.m_text.end())
    {
        WARN("Text " << id << " already exists!");
        return false;
    }
    if (obj.get_layer() >= VisualNovelScene::n_layers)
    {
        WARN("Text " << id << " has invalid layer " << obj.get_layer()
             << "\nLayer must be less than " << VisualNovelScene::n_layers);
        return false;
    }

    m_vn_objects.m_text[id] = &obj;
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

bool VisualNovelScene::add_game_object(GameObject & obj)
{
    auto id = obj.name();
    INFO("Add game object " << id << " to scene " << m_name);

    if (m_objects.find(id) != m_objects.end())
    {
        WARN("Game object " << id << " already exists!");
        return false;
    }
    if (obj.get_layer() >= VisualNovelScene::n_layers)
    {
        WARN("Game object " << id << " has invalid layer " << obj.get_layer()
             << "\nLayer must be less than " << VisualNovelScene::n_layers);
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

GameObject & VisualNovelScene::get_background(const std::string & id)
{
    if (m_vn_objects.m_background.find(id) == m_vn_objects.m_background.end())
    {
        WARN("Could not find background " << id);
        return INVALID_GAME_OBJECT;
    }

    return *m_vn_objects.m_background[id];
}

GameObject & VisualNovelScene::get_character(const std::string & id)
{
    if (m_vn_objects.m_character.find(id) == m_vn_objects.m_character.end())
    {
        WARN("Could not find character " << id);
        return INVALID_GAME_OBJECT;
    }

    return *m_vn_objects.m_character[id];
}

GameObject & VisualNovelScene::get_text(const std::string & id)
{
    if (m_vn_objects.m_text.find(id) == m_vn_objects.m_text.end())
    {
        WARN("Could not find text " << id);
        return INVALID_GAME_OBJECT;
    }

    return *m_vn_objects.m_text[id];
}

GameObject & VisualNovelScene::get_game_object(const std::string & id)
{
    if (m_objects.find(id) == m_objects.end())
    {
        WARN("Could not find game object " << id);
        return INVALID_GAME_OBJECT;
    }

    return *m_objects[id];
}

bool VisualNovelScene::remove_background(const std::string & id)
{
    INFO("Remove background " << id << " from VisualNovelScene " << m_name);

    if (m_vn_objects.m_background.find(id) == m_vn_objects.m_background.end())
    {
        WARN("Could not find background " << id);
        return false;
    }

    int layer = m_vn_objects.m_background[id]->get_layer();
    int i = 0;
    for(auto obj: m_layers[layer]) {
        if (obj->name() == id) {
            m_layers[layer].erase(m_layers[layer].begin() + i);
            break;
        }
        i++;
    }
    m_vn_objects.m_background.erase(id);
    return true;
}

bool VisualNovelScene::remove_character(const std::string & id)
{
    INFO("Remove character " << id << " from VisualNovelScene " << m_name);

    if (m_vn_objects.m_character.find(id) == m_vn_objects.m_character.end())
    {
        WARN("Could not find character " << id);
        return false;
    }

    int layer = m_vn_objects.m_character[id]->get_layer();
    int i = 0;
    for(auto obj: m_layers[layer]) {
        if (obj->name() == id) {
            m_layers[layer].erase(m_layers[layer].begin() + i);
            break;
        }
        i++;
    }
    m_vn_objects.m_character.erase(id);
    return true;
}

bool VisualNovelScene::remove_text(const std::string & id)
{
    INFO("Remove text " << id << " from VisualNovelScene " << m_name);

    if (m_vn_objects.m_text.find(id) == m_vn_objects.m_text.end())
    {
        WARN("Could not find character " << id);
        return false;
    }

    int layer = m_vn_objects.m_text[id]->get_layer();
    int i = 0;
    for(auto obj: m_layers[layer]) {
        if (obj->name() == id) {
            m_layers[layer].erase(m_layers[layer].begin() + i);
            break;
        }
        i++;
    }
    m_vn_objects.m_text.erase(id);
    return true;
}

bool VisualNovelScene::remove_game_object(const std::string & id)
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

bool VisualNovelScene::init()
{
    INFO("Init VisualNovelScene " << m_name);

    for (auto id_obj: m_vn_objects.m_background)
    {
        auto obj = id_obj.second;
        if (obj->init() == false)
        {
            WARN("Could not init game object " << obj->name());
            return false;
        }
    }
    for (auto id_obj: m_vn_objects.m_character)
    {
        auto obj = id_obj.second;
        if (obj->init() == false)
        {
            WARN("Could not init game object " << obj->name());
            return false;
        }
    }
    for (auto id_obj: m_vn_objects.m_text)
    {
        auto obj = id_obj.second;
        if (obj->init() == false)
        {
            WARN("Could not init game object " << obj->name());
            return false;
        }
    }
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

void VisualNovelScene::setup()
{
    INFO("Setup VisualNovelScene " << m_name);

    for (auto id_obj: m_vn_objects.m_background){
        id_obj.second->setup();
    }
    for (auto id_obj: m_vn_objects.m_character){
        id_obj.second->setup();
    }

    for (auto id_obj: m_vn_objects.m_text){
        id_obj.second->setup();
    }
    for (auto id_obj: m_objects){
        id_obj.second->setup();
    }
}

bool VisualNovelScene::shutdown()
{
    INFO("Shutdown VisualNovelScene " << m_name);

    for (auto id_obj: m_vn_objects.m_background)
    {
        auto obj = id_obj.second;
        if (obj->shutdown() == false)
        {
            WARN("Could not shutdown game object " << obj->name());
        }
    }
    for (auto id_obj: m_vn_objects.m_character)
    {
        auto 
        obj = id_obj.second;
        if (obj->shutdown() == false)
        {
            WARN("Could not shutdown game object " << obj->name());
        }
    }

    for (auto id_obj: m_vn_objects.m_text)
    {
        auto obj = id_obj.second;
        if (obj->shutdown() == false)
        {
            WARN("Could not shutdown game object " << obj->name());
        }
    }

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

void VisualNovelScene::update()
{
    for (auto layer: m_layers) {
        for (auto obj: layer) {
            if (obj->state() == GameObject::State::enabled) obj->update();
        }
    }
}

void VisualNovelScene::draw()
{
     for (auto layer: m_layers) {
        for (auto obj: layer) {
            if (obj->state() == GameObject::State::enabled) obj->draw();
        }
    }
}
