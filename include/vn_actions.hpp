#ifndef __GAME_CODE_VN_ACTIONS__
#define __GAME_CODE_VN_ACTIONS__

#include "log.h"

#include "game.hpp"
#include "code.hpp"
#include "text.hpp"

namespace engine{

class Action: public Component{
public:
    Action(): Component(){}

    int current = 1;
    bool is_over = false;

    virtual ~Action() {};

    virtual bool init() { return Component::init(); };
    virtual bool shutdown() { return Component::shutdown(); };

    void update(){
        auto text = m_game_object->get_component<engine::TextComponent>();
        if(engine::Game::GetInstance().input_manager().is_button_down("z")) {
            if(text->next_line(current)){
                current++;
            }
            else{
                is_over = true;
            }
        }
        if(is_over){
            engine::Game::GetInstance().change_scene("1");
        }
    }
};

}
#endif
