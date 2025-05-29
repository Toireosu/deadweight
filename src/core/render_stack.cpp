#include "core/render_stack.hpp"

#include "core/renderable_base.hpp"
#include "core/renderable_UI.hpp"

void RenderStack::add(RenderableBase* renderable) {
    auto ui = dynamic_cast<RenderableUI*>(renderable);

    if (ui)
        _orthographic.push_back(ui);
    else
        _perspective.push_back(renderable);
}
void RenderStack::remove(RenderableBase* renderable) {
    auto ui = dynamic_cast<RenderableUI*>(renderable);

    if (ui)
        _orthographic.remove(ui);
    else
        _perspective.remove(renderable);
}

std::list<RenderableBase*> RenderStack::getPerspective() { return _perspective; }
std::list<RenderableUI*> RenderStack::getOrthographic() { return _orthographic; }