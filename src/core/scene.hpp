#pragma once

#include <list>

#include "core/render_stack.hpp"
class Updatable;
class Scene {
private:
    std::list<Updatable*> _updatables;
    RenderStack _renderStack;
    void destroyAll();  
public:
    void init();
    ~Scene();
    void spawn(Updatable*); 
    void destroy(Updatable*);
    void updateAll();
    RenderStack* getRenderStack() { return &_renderStack; }
};