#include "LightManager.hpp"

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Graphic::LightManager::addLight(const Math::Vector3D& pos, Graphic::Color color) {
    lights_.push_back({pos, true, color});
}

void Graphic::LightManager::clear() {
    lights_.clear();
}

void Graphic::LightManager::setAllEnabled(bool state) {
    for (auto& light : lights_) {
        light.enabled = state;
    }
}

Graphic::Light& Graphic::LightManager::getLightRef(size_t index) {
    return lights_[index];
}