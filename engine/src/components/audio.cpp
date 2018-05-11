#include "components/audio.hpp"

#include "game.hpp"
#include "log.h"
#include "sdl_log.h"

using namespace engine;


bool AudioComponent::init(){
    INFO("Initializing audio component");

    if(m_is_music){
        m_music = Game::instance.assets_manager().load_music(m_path);
        if(m_music == NULL){
            return false;
        }
    }
    else{
        m_sound = Game::instance.assets_manager().load_sound(m_path);
        if(m_sound == NULL){
            return false;
        }
    }
    return true;
}

bool AudioComponent::shutdown(){
    INFO("Shutdown audio component"); 
    return true;
}

void AudioComponent::update(){
    if(m_play_on_start){
        play();
        m_play_on_start = false;
    }
}

void AudioComponent::play(int loops, int channel){
    if(m_is_music)
    {
        if(m_audio_state == State::stopped) Mix_PlayMusic(m_music, loops);
        else if (m_audio_state == State::paused) Mix_ResumeMusic();
    }
    else
    {
        if(m_audio_state == State::stopped)
            Mix_PlayChannel(channel, m_sound, loops);
        else if (m_audio_state == State::paused)
            Mix_Resume(channel);
    }

    m_audio_state = State::playing;
} 

void AudioComponent::stop(int channel)
{
    if(m_is_music) Mix_HaltMusic();
    else Mix_HaltChannel(channel);

    m_audio_state = State::stopped;
}

void AudioComponent::pause(int channel)
{
    if(m_is_music) Mix_PauseMusic();
    else Mix_Pause(channel);

    m_audio_state = State::paused;
}