#ifndef __GAME_CODE_VN_ACTIONS__
#define __GAME_CODE_VN_ACTIONS__

#include "log.h"

#include "game.hpp"
#include "components/code.hpp"
#include "components/text.hpp"

namespace engine{

class Action: public Component{
public:
    Action(): Component(){}

    int current = 1;
    bool is_over;

    virtual ~Action() {};

    virtual bool init() { return Component::init(); };
    virtual bool shutdown() { return Component::shutdown(); };

    void update(){
        auto text = m_game_object->get_component<engine::TextComponent>();
        if(engine::Game::instance.input_manager().is_button_down("z")) {
            if(text->next_line(current)){
                current++;
            }
            else{
                is_over = true;
            }
        }
        if(is_over){
            engine::Game::instance.change_scene("1");
        }
    }
};

}
#endif
