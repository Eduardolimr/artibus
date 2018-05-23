#include "components/text.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

#include <string>

using namespace engine;

bool TextComponent::init()
{
    INFO("Init TextComponent");

    if (m_font_path == "")
    {
        WARN("Invalid path for font!");
        return false;
    }
    
    if(m_text_path == ""){
        WARN("Invalid path for text!");
        return false;
    }

    m_font = Game::instance.assets_manager().load_font(m_font_path, m_font_size);
    m_text = Game::instance.assets_manager().load_text(m_text_path);

    if(m_font == NULL) return false;

    SDL_Color color = {m_color.r, m_color.g, m_color.b, m_color.a};

    SDL_Surface * surface = NULL;

    auto text = get_line(0);
    surface = TTF_RenderUTF8_Blended_Wrapped(
        m_font, text.c_str(), color, 500
    );

    if(surface == NULL)
    {
        SDL_TTF_ERROR("Could not render text " << text << " with font "
                      << m_font_path);
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(Game::instance.canvas(), surface);

    if (m_texture == NULL)
    {
        SDL_ERROR("Could not create texture from rendered text surface!");
        return false;
    }

    m_w = surface->w;
    m_h = surface->h;

    SDL_FreeSurface(surface);

    return true;
}

bool TextComponent::shutdown()
{
    INFO("Shutdown TextComponent");

    SDL_DestroyTexture(m_texture);
    m_texture = NULL;

    m_font = NULL;

    return true;
}

void TextComponent::draw()
{
    auto position = m_game_object->get_position();

    SDL_Rect renderQuad = {
        static_cast<int>(position.first),
        static_cast<int>(position.second),
        m_w,
        m_h
    };
    SDL_RenderCopy(Game::instance.canvas(), m_texture, NULL, &renderQuad);
}


bool TextComponent::next_line(int num){
    SDL_DestroyTexture(m_texture);
    m_texture = NULL;
    SDL_Surface * surface = NULL;


    SDL_Color color = {m_color.r, m_color.g, m_color.b, m_color.a};

    auto text = get_line(num);
    surface = TTF_RenderUTF8_Blended_Wrapped(
        m_font, text.c_str(), color, 500
    );

    if(surface == NULL)
    {
        SDL_TTF_ERROR("Could not render text " << text << " with font "
                      << m_font_path);
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(Game::instance.canvas(), surface);

    if (m_texture == NULL)
    {
        SDL_ERROR("Could not create texture from rendered text surface!");
        return false;
    }

    m_w = surface->w;
    m_h = surface->h;

    SDL_FreeSurface(surface);

    return true;
}

std::string TextComponent::get_line(int num){
    if(m_text.find(std::to_string(num)) != m_text.end()){
        auto text = m_text[std::to_string(num)];
        return text;
    }
    else{
        return "";
    }
}