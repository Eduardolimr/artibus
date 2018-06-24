#ifndef __ENGINE_GAME_OBJECT__
#define __ENGINE_GAME_OBJECT__

#include <string>
#include <list>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

namespace engine {

class Component;

class GameObject {
public:
    enum class State {
        enabled,
        disabled,
        invalid
    };

    GameObject() : GameObject("", 0, 0, State::invalid) {}
    GameObject(std::string name,
               unsigned int layer=0, unsigned int layer_order=0,
               State state=State::enabled)
         : x(0), y(0), w(0), h(0), rotation(0), m_name(name),
           m_state(state), m_parent(NULL), m_layer(layer),
           m_layer_order(layer_order) {}

    virtual ~GameObject() {}

    virtual bool init();
    virtual void setup();
    virtual bool shutdown();

    virtual void update();
    virtual void draw();

    bool add_component(Component & component);

    template<typename T>
    T * get_component()
    {
        return dynamic_cast<T *>(m_components[std::type_index(typeid(T))].front());
    }

    template<typename T>
    std::list<Component *> get_components();

    inline std::string name()  const { return m_name; }
    inline State       state() const { return m_state; }

    inline std::pair<double, double> get_position() const {
        auto position = std::make_pair(x, y);

        if (m_parent) {
            auto parent_position = m_parent->get_position();
            position.first  += parent_position.first;
            position.second += parent_position.second;
        }
        return position;
    }

    inline void set_parent(GameObject & parent) { m_parent = &parent; }
    inline void set_position(double _x, double _y) { x = _x; y = _y; }
    inline void set_size(double _w, double _h) { w = _w; h = _h; }
    inline unsigned int get_layer() const { return m_layer; }
    inline unsigned int get_layer_order() const { return m_layer_order; }
 
    double x, y;
    double w, h;
    double rotation;
    GameObject * m_parent;

protected:
    std::string m_name;
    State       m_state;
    std::unordered_map<std::type_index, std::list<Component *> > m_components;
    
private:
    unsigned int m_layer;
    unsigned int m_layer_order;
};

}

#endif
