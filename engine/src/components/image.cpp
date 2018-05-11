#include "components/image.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;

bool ImageComponent::init()
{
    INFO("Init ImageComponent");

    if (m_path == "")
    {
        WARN("Invalid path for image!");
        return false;
    }

    auto image = Game::instance.assets_manager().load_image(m_path);

    m_texture = image->texture;
    m_w = image->w;
    m_h = image->h;

    m_game_object->set_size(m_w, m_h);
    update_canvas_rect();

    m_image_rect.x = 0;
    m_image_rect.y = 0;
    m_image_rect.w = m_w;
    m_image_rect.h = m_h;

    return true;
}

bool ImageComponent::shutdown()
{
    INFO("Shutdown ImageComponent");

    m_texture = NULL;

    return true;
}

void ImageComponent::draw()
{
    update_canvas_rect();

    SDL_RenderCopy(Game::instance.canvas(), m_texture,
                   &m_image_rect, &m_canvas_rect);
}



void ImageComponent::update_canvas_rect()
{
    auto position = m_game_object->get_position();

    m_canvas_rect.x = position.first;
    m_canvas_rect.y = position.second;
    m_canvas_rect.w = m_game_object->w;
    m_canvas_rect.h = m_game_object->h;
}