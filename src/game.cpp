#include  "game.hpp"
#include "image.hpp"
#include "text.hpp"
#include "audio.hpp"
#include "log.h"
#include "sdl_log.h"


using namespace engine;

Game Game::instance;

void Game::set_properties(std::string name, std::pair<int, int> window_size,
                          unsigned int fps)
{
    m_name = name;
    m_window_size = window_size;
    m_fps = fps;
}

bool setup_sdl()
{
    INFO("Setup SDL");

    INFO("Init video and audio");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_ERROR("SDL_Init");
        return false;
    }

    INFO("Init image png");
    int img_flags = IMG_INIT_PNG;
    if(!(IMG_Init(img_flags) & img_flags))
    {
        SDL_IMG_ERROR("IMG_Init");
        return false;
    }

    INFO("Init TTF");
    if(TTF_Init() == -1)
    {
        SDL_TTF_ERROR("TTF_Init");
        return false;
    }

    INFO("Open audio Mixer");
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_MIX_ERROR("Mix_OpenAudio");
        return false;
    }

    return true;
}

bool Game::create_window()
{
    INFO("Create Window (" << m_name << ", " << m_window_size.first << ", " <<
         m_window_size.second << ")");

    m_window = SDL_CreateWindow(
        m_name.c_str(),         // Title
        SDL_WINDOWPOS_CENTERED, // Position x. SDL_WINDOWPOS_UNDEFINED
        SDL_WINDOWPOS_CENTERED, // Position y. SDL_WINDOWPOS_UNDEFINED
        m_window_size.first,    // width
        m_window_size.second,   // height
        SDL_WINDOW_SHOWN        // Window flags, SDL_WindowFlags for more
    );

    if (m_window == NULL)
    {
        SDL_ERROR("SDL_CreateWindow");
        return false;
    }

    INFO("Create canvas");
    m_canvas = SDL_CreateRenderer(
        m_window,
        -1, // Render driver. -1 to the first one that support the flags
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (m_canvas == NULL)
    {
        SDL_ERROR("SDL_CreateRenderer");
        return false;
    }

    SDL_SetRenderDrawColor(m_canvas,
                           m_background_color.r, m_background_color.b,
                           m_background_color.g, m_background_color.a);

    return true;
}

bool teardown_sdl()
{
    INFO("Teardown SDL");

    INFO("Quit SDL Mix");
    Mix_Quit();

    INFO("Quit SDL TTF");
    TTF_Quit();

    INFO("Quit SDL IMG");
    IMG_Quit();

    INFO("Quit SDL");
    SDL_Quit();

    return true;
}

bool Game::destroy_window()
{
    INFO("Destroy canvas");
    SDL_DestroyRenderer(m_canvas);
    m_canvas = NULL;

    INFO("Destroy window");
    SDL_DestroyWindow(m_window);
    m_window = NULL;

    return true;
}

void Game::run()
{
    INFO("Game " << m_name << "Setup");

    m_state = State::init;

    if (setup_sdl() && create_window())
    {
        INFO("Start game loop");
        m_state = State::main_loop;

        if (m_scene == NULL)
        {
            WARN("No scenes to run!");
            m_state = State::exit_loop;
        }
        else m_state = State::main_loop_change_scene;

        double frame_time = 1000.0 / static_cast<double>(m_fps);
        m_timer.start();

        while(m_state != State::exit_loop)
        {
            if(handle_scene_changes() == false) break;

            SDL_Event evt;
            while(SDL_PollEvent(&evt) != 0)
            {
                switch(evt.type)
                {
                    case SDL_QUIT:
                        m_state = State::exit_loop;
                        break;
                    default:
                        m_input_manager.gather_input(evt);
                        break;
                }
            }

            m_scene->update();

            SDL_RenderClear(m_canvas);
            m_scene->draw();
            SDL_RenderPresent(m_canvas);

            m_input_manager.clear_input();

            // Frame capping
            if (frame_time > m_elapsed_time)
            {
                SDL_Delay(frame_time - m_elapsed_time);
            }

            m_elapsed_time = m_timer.elapsed_time();
            m_timer.step();
        }

        m_timer.stop();

        INFO("Cleaning up resources...");
        if(m_scene) m_scene->shutdown();
    }

    INFO("Game Shutdown");
    m_state = State::shutdown;
    destroy_window();
    teardown_sdl();
}

void Game::set_background_color(int r, int g, int b, int a)
{
    m_background_color.r = r;
    m_background_color.g = g;
    m_background_color.b = b;
    m_background_color.a = a;

    if (m_canvas != NULL)
    {
        SDL_SetRenderDrawColor(m_canvas,
                               m_background_color.r, m_background_color.b,
                               m_background_color.g, m_background_color.a);
    }
}

bool Game::add_scenes(SceneSetup scene_setup){
    for(auto scene_path: scene_setup.m_paths){
        auto scene = scene_path.second;

        VisualNovelScene vn_scene(std::to_string(scene.id));

        auto text = GameObject("Text", 3, 0);
        auto box = GameObject("Box", 2, 0);
        auto npc = GameObject("NPC", 1, 0);
        auto bg = GameObject("Background", 0, 0);

        text.set_position(150, 200);
        box.set_position(0, 0);
        bg.set_position(0,0);
        npc.set_position(90, 175);

        auto scene_text = TextComponent(scene.text_path, "font.ttf", 30,
                                        Color(0x00, 0x00, 0x00), 700);

        auto bg_music = AudioComponent(scene.sound_path, true);

        auto text_box = ImageComponent(scene.image_path[0]);
        
        auto background = ImageComponent(scene.image_path[1]);


        text.add_component(scene_text);
        box.add_component(bg_music); 
        box.add_component(text_box);
        bg.add_component(background);

        vn_scene.add_text(text);
        vn_scene.add_game_object(box);
        vn_scene.add_background(bg);
        vn_scene.add_character(npc);

        add_scene(vn_scene);

    }
    return true;

}

bool Game::add_scene(VisualNovelScene & scene)
{
    auto id = scene.name();
    INFO("Add scene " << id);

    if (m_scenes.find(id) != m_scenes.end())
    {
        WARN("Scene " << id << " already exists!");
        return false;
    }

    m_scenes[id] = &scene;

    if (m_scene == NULL) m_scene = &scene;

    return true;
}

bool Game::change_scene(const std::string & id)
{
    INFO("Change scene to " << id);

    if (m_scenes.find(id) == m_scenes.end())
    {
        WARN("Scene " << id << " not found!");
        return false;
    }

    m_last_scene = m_scene;
    m_scene = m_scenes[id];
    m_state = State::main_loop_change_scene;
    return true;
}

bool Game::handle_scene_changes()
{
    if (m_state == State::main_loop_change_scene)
    {
        if (m_scene == NULL)
        {
            WARN("No scenes to run!");
            return false;
        }
        else
        {
            INFO("Scenes changing from " <<
                 (m_last_scene ? m_last_scene->name() : "NULL") << " to " <<
                 m_scene->name() << "...");

            if(m_last_scene)
            {
                m_last_scene->shutdown();
                m_last_scene->assets_manager().shutdown();
            }

            m_scene->init();
            m_scene->setup();

            m_state = State::main_loop;
        }
    }

    return true;
}