#ifndef __ENGINE_SCENE_SETUP__
#define __ENGINE_SCENE_SETUP__

#include <vector>
#include <list>
#include <string>
#include <map>

#include "sdl2include.h"
namespace engine {
typedef struct scene_paths{
    int id;

    std::string text_path;
    std::vector<std::string> image_path;
    std::string sound_path;
    std::pair<int, int> button_path;
}scene_paths;

class SceneSetup {
public:
    SceneSetup();
    SceneSetup(int a){
        create_scenes();
    }
	bool IsEmpty();

    std::map<int, scene_paths> m_paths;
private:
    void create_scenes();
};

}

#endif
