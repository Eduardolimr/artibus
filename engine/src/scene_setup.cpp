#include "scene_setup.hpp"
#include "log.h"

using namespace engine;

SceneSetup::SceneSetup(){
    create_scenes();
}

/* Creates an ordered map of scene_paths containing the id and paths to a scene's assets/buttons. 
   Scene file can be found at assets/scenes/scenes.txt */

void create_scenes(){
    std::string base_path = "assets/";
    std::string path = "scenes/scenes.txt";
    int cont;

    scene_paths paths;

    ifstream input;
    input.open(path);
    if (input.is_open()){
        while (!input.eof()){
            cont = 0;
            while(cont < 5){
                getline(input, data);
                switch(cont){
                    case 0:
                        paths.id = atoi(data.c_str());
                        INFO(paths.id.c_str());
                    case 1:
                        paths.text_path = data;
                        INFO(paths.text_path);
                        break;
                    case 2:
                        paths.image_path[0] = data;
                        INFO(paths.image_path[0]);
                        break;
                    case 3:
                        paths.image_path[1] = data;
                        INFO(paths.image_path[1]);
                        break;
                    case 4:
                        paths.sound_path = data;
                        INFO(paths.sound_path);
                        break;
                    case 5:
                        paths.button_path.first = atoi(data.c_str());
                        getline(input, data);
                        paths.button_path.second = atoi(data.c_str());
                        m_path.insert(to_string(paths.id), paths);
                        cont = 0;
                }
            }
        }
    }
    input.close();
}