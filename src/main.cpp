#include "game.hpp"
#include "vn_scene.hpp"
#include "gameobject.hpp"
#include "vn_actions.hpp"
#include "gameglobals.hpp"
#include "image.hpp"
#include "text.hpp"
#include "animation.hpp"
#include "animation_controller.hpp"
#include "audio.hpp"

using namespace engine;

int main(int, char**)
{
    // Configure game
//    Game::GetInstance().set_properties(globals::game_name, globals::window_size);

    // Game loop
    Game::GetInstance().run();

    return 0;
}
