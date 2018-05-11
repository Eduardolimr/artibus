#include "components/animation.hpp"

#include <cmath>

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;

bool AnimationComponent::init()
{
    INFO("Init AnimationComponent");

    if (ImageComponent::init() == false) return false;

    if (m_duration == 0)
    {
        WARN("Can't create animation with duration 0");
        return false;
    }

    if (m_n_columns == 0 || m_n_rows == 0)
    {
        WARN("Can't create animation with 0 rows (" << m_n_rows <<
             ") or columns (" << m_n_columns << ")");
        return false;
    }

    if (m_start_frame > m_end_frame)
    {
        WARN("Ciclic animation");
        return false;
    }
    else m_n_frames = m_end_frame - m_start_frame + 1;

    m_sprite_w = m_w / m_n_columns;
    m_sprite_h = m_h / m_n_rows;

    m_image_rect.w = m_sprite_w;
    m_image_rect.h = m_sprite_h;

    INFO("Animation (" << m_path << ") sprite size "
         << m_sprite_w << "x" << m_sprite_h);

    m_frame_time = (unsigned int) std::ceil(double(m_duration) /
                                            double(m_n_frames));

    return true;
}

void AnimationComponent::setup()
{
    m_game_object->set_size(m_sprite_w, m_sprite_h);
}

bool AnimationComponent::shutdown()
{
    INFO("Shutdown AnimationComponent");

    if (ImageComponent::shutdown() == false) return false;
    return true;
}

void AnimationComponent::draw()
{
    m_finished = false;

    m_playing_duration += Game::instance.elapsed_time();

    if (m_playing_duration >= m_duration) {
        m_finished = true;
        if (m_loop) m_playing_duration -= m_duration;
        else m_playing_duration = m_duration;
    }

    m_current_frame = (m_playing_duration / m_frame_time) + m_start_frame;

    int current_row = m_current_frame / m_n_columns;
    int current_col = m_current_frame % m_n_columns;

    m_image_rect.x = current_col * m_sprite_w;
    m_image_rect.y = current_row * m_sprite_h;

    ImageComponent::draw();
}
