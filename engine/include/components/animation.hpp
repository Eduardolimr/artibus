#ifndef __ENGINE_COMPONENTS_ANIMATION__
#define __ENGINE_COMPONENTS_ANIMATION__

#include <string>
#include "components/image.hpp"

namespace engine {

class AnimationComponent : public ImageComponent {
public:
    AnimationComponent(std::string path="",
                       unsigned int n_columns=1, unsigned int n_rows=1,
                       double duration=1.0, bool loop=true)
        : ImageComponent(path), m_n_columns(n_columns), m_n_rows(n_rows),
          m_duration(static_cast<unsigned int>(duration * 1000)),
          m_loop(loop), m_n_frames(n_columns * n_rows), m_playing_duration(0),
          m_start_frame(0), m_end_frame(m_n_frames - 1),
          m_current_frame(m_start_frame), m_finished(false) {}

    virtual ~AnimationComponent() {}

    virtual bool init();
    virtual void setup();
    virtual bool shutdown();
    virtual void draw();


    inline void set_frame_range(unsigned int start_frame,
                                unsigned int end_frame)
    {
        m_start_frame = start_frame;
        m_end_frame = end_frame;
    }
    inline void set_start_frame(unsigned int start_frame)
    {
        m_start_frame = start_frame;
    }
    inline void set_end_frame(unsigned int end_frame)
    {
        m_end_frame = end_frame;
    }

    inline bool has_finished() const { return m_finished; }

protected:
    unsigned int m_n_columns, m_n_rows;
    unsigned int m_duration;
    bool m_loop;
    unsigned int m_n_frames;

    unsigned int m_playing_duration;  // Elapsed time since animation start
    unsigned int m_frame_time;        // Millisecons that a frame should play
    unsigned int m_start_frame, m_end_frame, m_current_frame;
    unsigned int m_sprite_w, m_sprite_h;

    bool m_finished;
};

}

#endif
