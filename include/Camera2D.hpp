#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <raylib.h>
#include "Vector.hpp"

namespace Graphic {

class Camera2D {
private:
    ::Camera2D camera_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---

    Camera2D(Math::Vector2D world_target, Math::Vector2D screen_offset, float zoom = 1.0, float rotation = 0.0) {
        camera_.target   = ::Vector2{ world_target.x(),  world_target.y() };
        camera_.offset   = ::Vector2{ screen_offset.x(), screen_offset.y() };
        camera_.zoom     = zoom;
        camera_.rotation = rotation;
    }

    // --- Destructor ---

    ~Camera2D() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    ::Camera2D get_native () const { return camera_; }

    Math::Vector2D target() const { return Math::Vector2D{ camera_.target.x, camera_.target.y }; }
    float zoom() const { return camera_.zoom; }

    // -------------------------------------------------------------------------------
    // --- Setters ---

    void set_target(const Math::Vector2D& new_target) { camera_.target = ::Vector2{ new_target.x(), new_target.y() }; }
    void set_zoom (float zoom) { camera_.zoom = zoom; }

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---

    void begin () const;
    void end () const;
    void look_at (const Math::Vector2D& world_pos);
};

}

#endif
