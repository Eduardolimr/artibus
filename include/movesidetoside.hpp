#ifndef __GAME_CODE_MOVE_SIDE_TO_SITE__
#define __GAME_CODE_MOVE_SIDE_TO_SITE__

#include "log.h"

#include "game.hpp"
#include "components/code.hpp"

class MoveSideToSide : public engine::CodeComponent {
public:
    bool right = true;
    double velocity = 1;

    MoveSideToSide() : engine::CodeComponent() {}

    void update()
    {
        if(engine::Game::instance.input_manager().is_button_down("w")) {
            INFO("W is down");
        }

        auto dx = velocity;
        if (!right) dx *= -1;

        dx = m_game_object->x + dx;

        if (dx >= engine::Game::instance.window_size().first || dx < 0)
        {
            right = !right;
        }

        m_game_object->x = dx;
    }

};

#endif
