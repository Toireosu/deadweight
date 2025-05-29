#pragma once

#include <list>

class RenderableBase;
class RenderableUI;
class RenderStack {
private: 
    std::list<RenderableBase*> _perspective;
    std::list<RenderableUI*> _orthographic;
public:
    void add(RenderableBase*);
    void remove(RenderableBase*);
    std::list<RenderableBase*> getPerspective();
    std::list<RenderableUI*> getOrthographic();
};