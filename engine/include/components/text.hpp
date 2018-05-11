#ifndef __ENGINE_COMPONENTS_TEXT__
#define __ENGINE_COMPONENTS_TEXT__

#include <string>
#include <utility>

#include "sdl2include.h"

#include "color.hpp"
#include "components/component.hpp"

namespace engine{

    class TextComponent: public Component{
    public:
        TextComponent(
            std::string  text_path="",
            std::string  font_path="",
            int          font_size=42,
            Color        color=Color(),
            Color        background_color=Color(0x0, 0x0, 0x0, 0x00)
        ) : Component(), m_text(""), m_text_path(text_path),
            m_font_path(font_path), m_font_size(font_size), m_color(color),
            m_background_color(background_color), m_texture(NULL), m_font(NULL),
            m_w(0), m_h(0) {}

        virtual ~TextComponent() {}

        virtual bool init();
        virtual bool shutdown();
        virtual void draw();

        inline void enable_high_quality()  { m_high_quality = true; }
        inline void disable_high_quality() { m_high_quality = false; }

    protected:
        std::string m_text;
        std::string m_text_path;
        std::string m_font_path;
        int         m_font_size;
        bool        m_high_quality;
        Color       m_color;
        Color       m_background_color;

        SDL_Texture * m_texture;
        TTF_Font    * m_font;

        int m_w;
        int m_h;
    };
}


#endif