#include "scene_setup.hpp"
#include "log.h"
#include <fstream>

namespace engine{

SceneSetup::SceneSetup(){
    create_scenes();
}

bool SceneSetup::IsEmpty(){
	return m_paths.empty();
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
        cont = 0;
        while(cont < 6 && !input.eof()){
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
                        m_paths.insert(std::pair<int, scene_paths>(paths.id, paths));
					std::cerr << "SceneSetup adicionado no m_paths" << "\n";
//                    m_paths[paths.id] =  paths;
                    cont = 0;
                    break;
                }
        }
    }else{
		std::cerr << "Cound not open file " << path << "\n";
	}
    input.close();
	
}

}
