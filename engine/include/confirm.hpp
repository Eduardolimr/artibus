#ifndef __GAME_CODE_CONFIRM__
#define __GAME_CODE_CONFIRM__

#include "log.h"

#include "game.hpp"
#include "components/code.hpp"

class Confirm: public engine::CodeComponent{
public:
    Confirm() : engine::CodeComponent() {}

    void update(){
        if(engine::Game::instance.input_manager().is_button_down("z")){
        }
    }
};

#endif