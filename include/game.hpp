#ifndef __ENGINE_GAME__
#define __ENGINE_GAME__

#include <string>
#include <map>
#include <utility>
#include "assets_manager.hpp"
#include "input.hpp"
#include "scene_setup.hpp"
#include "vn_scene.hpp"
#include "sdl2include.h"
#include "timer.hpp"

namespace engine {

#define DEFAULT_GAME_NAME "Game"
#define DEFAULT_WINDOW_SIZE std::pair<int,int>(100,100)

class Game {
public:
    enum class State {
        created,
        init,
        main_loop,
        main_loop_change_scene,
        exit_loop,
        paused,
        shutdown
    };

	static Game& GetInstance(void){
		static Game instance;
		return instance;
	};

    void set_properties(std::string name, std::pair<int, int> window_size,
                        unsigned int fps=60);

    void run();
    void set_background_color(int r, int g, int b, int a);

    bool add_scene(VisualNovelScene & scene);
    bool add_scenes(SceneSetup scene_setup);
    bool change_scene(const std::string & id);

    inline std::pair<int, int> window_size() { return m_window_size; }
    inline SDL_Renderer * canvas() { return m_canvas; }
    inline const InputManager & input_manager() const { return m_input_manager; }
    inline AssetsManager & assets_manager() { return m_scene->assets_manager(); }

    inline unsigned int elapsed_time() { return m_elapsed_time; }
    inline double elapsed_time_seconds() { return m_elapsed_time / 1000.0; }
    inline const SceneSetup & scene_setup() const { return m_scene_setup; }
private:
    Game()
        : m_name(DEFAULT_GAME_NAME), m_window_size(DEFAULT_WINDOW_SIZE), m_fps(60),
          m_state(State::created), m_window(NULL), m_canvas(NULL),
          m_background_color({0xff, 0xff, 0xff, 0xff}),
          m_scene(NULL), m_last_scene(NULL), m_elapsed_time(0),
          m_scene_setup(0) {}

    std::string         m_name;
    std::pair<int, int> m_window_size;
    unsigned int        m_fps;
    State               m_state;

    SDL_Window   * m_window;
    SDL_Renderer * m_canvas;
    SDL_Color      m_background_color;

    std::map<std::string, VisualNovelScene *> m_scenes;
    VisualNovelScene * m_scene;       // Current Scene
    VisualNovelScene * m_last_scene;  // Last Scene Playedz

    Timer m_timer;
    unsigned int m_elapsed_time;

    InputManager m_input_manager;
    SceneSetup m_scene_setup;
    
    bool create_window();
    bool destroy_window();

    bool handle_scene_changes();
};

}

#endif
