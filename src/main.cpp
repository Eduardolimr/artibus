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

    auto text = GameObject("Title", 3, 0);
    auto box = GameObject("Box", 2, 0);
    auto bg = GameObject("Background", 0, 0);
    auto npc = GameObject("NPC", 1, 0);

    text.set_position(40, 490);
    box.set_position(0, 470);
    bg.set_position(0,0);
    npc.set_position(90, 175);

    auto scene_text = TextComponent("test.txt", "font.ttf", 30,
                                    Color(0x00, 0x00, 0x00));

    auto bg_music = AudioComponent("music.ogg", true);

    auto text_box = ImageComponent("text_box.png");
    
    auto background = ImageComponent("stand.png");

    auto person = ImageComponent("junko.png");

    Action action;


    text.add_component(action);
    text.add_component(scene_text);
    box.add_component(bg_music); 
    box.add_component(text_box);
    bg.add_component(background);
    npc.add_component(person);

    menu.add_text(text);
    menu.add_game_object(box);
    menu.add_background(bg);
    menu.add_character(npc);

    Game::instance.add_scene(menu);

    // Game loop
    Game::instance.run();

    return 0;
}