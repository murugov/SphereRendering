#include "Camera2D.hpp"

// -------------------------------------------------------------------------------
// --- Implementation Of Methods ---

void Graphic::Camera2D::begin () const {
    BeginMode2D(camera_);
}

void Graphic::Camera2D::end () const {
    EndMode2D();
}

void Graphic::Camera2D::look_at (const Math::Vector2D& world_pos) {
    camera_.target = ::Vector2{ world_pos.x(), world_pos.y() };
}