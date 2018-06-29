#include "assets_manager.hpp"
#include "log.h"
#include "sdl_log.h"
#include "game.hpp"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace engine;

bool AssetsManager::shutdown()
{
    INFO("Dealocate AssetsManager");

    INFO("Dealocate images");
    for(auto id_image: m_images)
    {
        SDL_DestroyTexture(id_image.second->texture);
        delete id_image.second;
    }
    m_images.clear();

    INFO("Dealocate fonts");
    for(auto id_font: m_fonts)
    {
        TTF_CloseFont(id_font.second);
    }
    m_fonts.clear();

    INFO("Dealocate musics");
    for(auto id_music: m_musics)
    {
        Mix_FreeMusic(id_music.second);
    }
    m_musics.clear();

    INFO("Dealocate sounds");
    for(auto id_sound: m_sounds)
    {
        Mix_FreeChunk(id_sound.second);
    }
    m_sounds.clear();

    INFO("Dealocate texts");
    for(auto id_text: m_text){
        id_text.second = "";
    }
    m_text.clear();

    return true;
}

Image * AssetsManager::load_image(std::string path, bool use_base)
{
    if(use_base)
        path = m_base_path + "sprites/" + path;

    if (m_images.find(path) == m_images.end())
    {
        INFO("Loading new image...");

        SDL_Surface * image = IMG_Load(path.c_str());

        if (image == NULL)
        {
            SDL_IMG_ERROR("Could not load image from path " << path);
            return NULL;
        }

        auto m_texture = SDL_CreateTextureFromSurface(Game::GetInstance().canvas(),
                                                      image);

        if (m_texture == NULL)
        {
            SDL_ERROR("Could not create texture from image!");
            return NULL;
        }

        Image * img = new Image;
        img->texture = m_texture;
        img->w = image->w;
        img->h = image->h;

        m_images[path] = img;

        SDL_FreeSurface(image);
    }

    return m_images[path];
}

std::map<std::string, std::string> AssetsManager::load_text(std::string path, bool use_base){
    std::string data;
    std::string text = "";
    int num_breaks = 0;
    int num_line = -1;

    if(use_base)
        path = m_base_path + "text/" + path;

    if(m_text.find(path) == m_text.end()){
        ifstream input;
        input.open(path);
        if(input.is_open()){
            while(!input.eof()){
                if(num_breaks >=3){
                    num_breaks = 0;
                }
                while(num_breaks < 3){
                    getline(input, data);
                    text += data;
                    ++num_breaks;
                    if(num_breaks < 3){
                        text += '\n';
                    }
                    data = "";
                }
                num_line++;
                INFO(std::to_string(num_line));
                m_text.insert(std::pair<std::string, std::string>(std::to_string(num_line), text));
                text = "";
            }
        }
        input.close();
    }
    INFO(m_text["0"]);
    return m_text;
}

TTF_Font * AssetsManager::load_font(std::string path, int size, bool use_base)
{
    if(use_base)
        path = m_base_path + "fonts/" + path;

    auto path_size = std::make_pair(path, size);

    if (m_fonts.find(path_size) == m_fonts.end())
    {
        INFO("Loading new font...");

        auto m_font = TTF_OpenFont(path.c_str(), size);

        if(m_font == NULL)
        {
            SDL_TTF_ERROR("Could not load font from path " << path);
            return NULL;
        }
    auto path_size = std::make_pair(path, size);
        m_fonts[path_size] = m_font;
    }

    return m_fonts[path_size];
}

Mix_Music * AssetsManager::load_music(std::string path, bool use_base)
{
    if(use_base)
        path = m_base_path + "sounds/" + path;

    if (m_musics.find(path) == m_musics.end())
    {
        Mix_Music * music = Mix_LoadMUS(path.c_str());
        if (music == NULL)
        {
            SDL_MIX_ERROR("Could not load music from path " << path);
            return NULL;
        }

        m_musics[path] = music;
    }

    return m_musics[path];
}

Mix_Chunk * AssetsManager::load_sound(std::string path, bool use_base)
{
    if(use_base)
        path = m_base_path + "sounds/" + path;

    if (m_sounds.find(path) == m_sounds.end())
    {
        Mix_Chunk * sound = Mix_LoadWAV(path.c_str());
        if (sound == NULL)
        {
            SDL_MIX_ERROR("Could not load sound from path " << path);
            return NULL;
        }

        m_sounds[path] = sound;
    }

    return m_sounds[path];
}

