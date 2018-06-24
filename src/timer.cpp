#include "timer.hpp"

#include "sdl2include.h"
#include "log.h"

using namespace engine;

void Timer::start()
{
    INFO("Start Timer");

    m_state = State::running;
    m_ticks = m_step_ticks = SDL_GetTicks();
}

void Timer::stop()
{
    INFO("Stop Timer");

    m_state = State::stopped;
    m_ticks = 0;
    m_step_ticks = 0;
}

void Timer::step()
{
    if (m_state == State::stopped) return;

    m_step_ticks = SDL_GetTicks();
}

unsigned int Timer::elapsed_time()
{
    if (m_state == State::stopped) return 0;

    return SDL_GetTicks() - m_step_ticks;
}

unsigned int Timer::total_elapsed_time()
{
    if (m_state == State::stopped) return 0;

    return SDL_GetTicks() - m_ticks;
}
