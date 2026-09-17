#ifndef SCENE_HPP
#define SCENE_HPP

#include "Canvas.hpp"
#include "LightManager.hpp"
#include "Camera2D.hpp"

namespace Graphic {

class Scene {
private:
    Canvas& canvas_;
    LightManager lightManager_;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Scene(Canvas& canvas) : canvas_(canvas), lightManager_() {}
    
    // --- Destructor ---

    ~Scene() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---
    
    const Canvas& canvas() const { return canvas_; }
    Canvas& canvas()             { return canvas_; }
    
    const LightManager& lightManager() const { return lightManager_; }
    LightManager& lightManager()             { return lightManager_; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---
    
    void bind (const Camera2D& camera) const;
    void unbind (const Camera2D& camera) const;
};

}

#endif