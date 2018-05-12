#ifndef __ENGINE_VISUALNOVEL_SCENE__
#define __ENGINE_VISUALNOVEL_SCENE__

#include <string>
#include <unordered_map>
#include <map>
#include <vector>

#include "gameobject.hpp"
#include "assets_manager.hpp"
 
namespace engine {

typedef struct vn_objects{
    std::map<std::string, GameObject *> m_background;
    std::map<std::string, GameObject *> m_character;
    std::map<std::string, GameObject *> m_text;
}vn_objects;

class VisualNovelScene{
public:
    enum class State{
        created,
        loaded,
        playing,
        invalid
    };
    const static int n_layers = 100;

    VisualNovelScene() : VisualNovelScene("", State::invalid) {}
    VisualNovelScene(std::string name, State _state=State::created)
        : m_name(name), m_state(_state) {}

    virtual ~VisualNovelScene() {}

    bool add_background(GameObject & obj);
    bool add_character(GameObject & obj);
    bool add_text(GameObject & obj);
    bool add_game_object(GameObject & obj);

    GameObject & get_game_object(const std::string & id);
    GameObject & get_background(const std::string & id);
    GameObject & get_character(const std::string & id);
    GameObject & get_text(const std::string & id);

    bool remove_background(const std::string & id);
    bool remove_character(const std::string & id);
    bool remove_text(const std::string & id);
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
    vn_objects m_vn_objects;
    std::unordered_map<std::string, GameObject *> m_objects;

    State m_state;
    AssetsManager m_assets_manager;
    std::vector<GameObject *> m_layers[VisualNovelScene::n_layers];
};

}

#endif
