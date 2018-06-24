#ifndef __GAME_CODE_MOVE__
#define __GAME_CODE_MOVE__

#include "log.h"

#include "game.hpp"
#include "components/code.hpp"

class Move : public engine::CodeComponent {
public:
    Move() : engine::CodeComponent() {}

    void update()
    {
        auto dx = 0;
        if(engine::Game::instance.input_manager().is_button_down("a")) {
            dx = -1;
        }
        if(engine::Game::instance.input_manager().is_button_down("d")) {
            dx = 1;
        }
        dx = m_game_object->x + dx;
        if (dx >= engine::Game::instance.window_size().first || dx < 0)
        {
            dx = 0;
        }
        m_game_object->x = dx;
    }

};

#endif
