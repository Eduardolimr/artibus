#ifndef __ENGINE_SCENE__
#define __ENGINE_SCENE__

#include <string>
#include <unordered_map>
#include <vector>

#include "gameobject.hpp"
#include "assets_manager.hpp"
 
namespace engine {

class Scene {
public:
    enum class State {
        created,
        loaded,
        playing,
        invalid
    };
    const static int n_layers = 100;

    Scene() : Scene("", State::invalid) {}
    Scene(std::string name, State _state=State::created)
        : m_name(name), m_state(_state) {}

    virtual ~Scene() {}

    bool add_game_object(GameObject & obj);
    GameObject & get_game_object(const std::string & id);
    bool remove_game_object(const std::string & id);

    virtual bool init();
    virtual void setup();
    virtual bool shutdown();

    virtual void update();
    virtual void draw();

    inline std::string name() const { return m_name; }
    inline AssetsManager & assets_manager() { return m_assets_manager; }

protected:
    std::string                                 m_name;
    std::unordered_map<std::string, GameObject *> m_objects;

    State m_state;
    AssetsManager m_assets_manager;
    std::vector<GameObject *> m_layers[Scene::n_layers];
};

}

#endif
