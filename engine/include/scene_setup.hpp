#ifndef __ENGINE_SCENE_SETUP__
#define __ENGINE_SCENE_SETUP__

#include <vector>
#include <list>
#include <string>
#include <map>

#include "sdl2include.h"

typedef struct scene_paths{
    int id;

    std::string text_path;
    std::vector<std::string> image_path;
    std::string sound_path;
    std::pair<int, int> button_path;
}scene_paths;

namespace engine {

class SceneSetup {
public:
    SceneSetup();

    std::map<std::string, scene_paths> m_paths;
private:
    void create_scenes();
};

}

#endif