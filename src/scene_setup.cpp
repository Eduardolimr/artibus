#include "scene_setup.hpp"
#include "log.h"
#include <fstream>

namespace engine{

SceneSetup::SceneSetup(){
    create_scenes();
}

/* Creates an ordered map of scene_paths containing the id and paths to a scene's assets/buttons. 
   Scene file can be found at assets/scenes/scenes.txt */

void SceneSetup::create_scenes(){
    std::string base_path = "assets/";
    std::string path = "scenes/scenes.txt";
    std::string data;
    std::ifstream input;

    scene_paths paths;

    path = base_path + path;
    int cont;
    
    input.open(path);
    if (input.is_open()){
        while (!input.eof()){
            cont = 0;
            while(cont < 5){
                getline(input, data);
                switch(cont){
                    case 0:
                        paths.id = atoi(data.c_str());
                        cont++;
                        break;
                    case 1:
                        paths.text_path = data;
                        cont++;
                        break;
                    case 2:
                        std::cout<<paths.id<<"\n";
                        std::cout<<data<<"\n";
                        paths.image_path.emplace(paths.image_path.begin(), data);
                        cont++;
                        break;
                    case 3:
                        std::cout<<paths.id<<"\n";
                        std::cout<<data<<"\n";
                        paths.image_path.emplace(paths.image_path.begin()+1, data);
                        cont++;
                        break;
                    case 4:
                        paths.sound_path = data;
                        cont++;
                        break;
                    case 5:
                        paths.button_path.first = atoi(data.c_str());
                        getline(input, data);
                        paths.button_path.second = atoi(data.c_str());
                        m_paths.insert(std::to_string(paths.id), paths);
                        //m_paths[std::to_string(paths.id)] =  paths;
                        cont = 0;
                        break;
                }
            }
        }
    }
    input.close();
}

}
