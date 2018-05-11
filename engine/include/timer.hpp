#ifndef __ENGINE_TIMER__
#define __ENGINE_TIMER__

namespace engine {

class Timer {
public:

    enum class State {
        running,
        stopped
    };

    Timer() : m_state(State::stopped), m_ticks(0), m_step_ticks(0) {}

    void start();
    void stop();
    void step();

    unsigned int elapsed_time();
    unsigned int total_elapsed_time();

private:
    State m_state;

    unsigned int m_ticks;
    unsigned int m_step_ticks;
};

}

#endif
