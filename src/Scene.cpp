#include "Scene.hpp"
#include "Adapter.hpp"

void Graphic::Scene::bind (const Camera2D& camera) const {
    // NOTE: Begin scissor mode (define screen area for following drawing)
    Graphic::Adapter::beginScissorMode(static_cast<int>((canvas_.pos()).x()), static_cast<int>((canvas_.pos()).y()), canvas_.width(), canvas_.height());
    Graphic::Adapter::clearBackground(canvas_.color());
    camera.begin();
}

void Graphic::Scene::unbind (const Camera2D& camera) const {
    camera.end();
    Graphic::Adapter::endScissorMode();
}