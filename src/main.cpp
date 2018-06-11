#include "game.hpp"
#include "scene.hpp"
#include "vn_scene.hpp"
#include "gameobject.hpp"
#include "vn_actions.hpp"
#include "components/image.hpp"
#include "components/text.hpp"
#include "components/animation.hpp"
#include "components/animation_controller.hpp"
#include "components/audio.hpp"

#include "gameglobals.hpp"

using namespace engine;

int main(int, char**)
{
    // Configure game
    Game::instance.set_properties(globals::game_name, globals::window_size);

    // Setup scenes
    VisualNovelScene menu("Main Menu");

    auto text = GameObject("Text", 3, 0);
    auto box = GameObject("Box", 2, 0);
    auto npc = GameObject("NPC", 1, 0);
    auto bg = GameObject("Background", 0, 0);

    text.set_position(150, 200);
    box.set_position(0, 0);
    bg.set_position(0,0);
    npc.set_position(90, 175);

    auto scene_text = TextComponent("intro.txt", "font.ttf", 30,
                                    Color(0x00, 0x00, 0x00), 500);

    auto bg_music = AudioComponent("introsong.mp3", true);

    auto text_box = ImageComponent("CaixaTextoRamiewDescricaoGde.png");
    
    auto background = ImageComponent("stand.png");

    Action action;

    text.add_component(action);
    text.add_component(scene_text);
    box.add_component(bg_music); 
    box.add_component(text_box);
    bg.add_component(background);

    menu.add_text(text);
    menu.add_game_object(box);
    menu.add_background(bg);
    menu.add_character(npc);


    VisualNovelScene teste("1");

    auto test_text = GameObject("Text", 1, 0);

    test_text.set_position(40, 490);

    auto scene_test_text = TextComponent("outra.txt", "font.ttf", 30,
                                    Color(0x00, 0x00, 0x00));

    test_text.add_component(scene_test_text);

    teste.add_text(test_text);

    Game::instance.add_scene(menu);
    Game::instance.add_scene(teste);
    // Game loop
    Game::instance.run();

    return 0;
}