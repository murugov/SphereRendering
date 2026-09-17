#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Colors.hpp"
#include "Vector.hpp"

namespace Graphic {

class Canvas {
private:
    Math::Vector2D pos_;
    int width_;
    int height_;
    Color color_;
    float scale_;

public:
    // -------------------------------------------------------------------------------
    // --- Сonstructor ---

    Canvas(const Math::Vector2D& pos, int width, int height, Color color, float scale = 1.0)
        : pos_(pos), width_(width), height_(height), color_(color), scale_(scale) {}

    // --- Destructor ---

    ~Canvas() = default;

    // -------------------------------------------------------------------------------
    // --- Getters ---

    Math::Vector2D pos()    const { return pos_; }
    float          x()      const { return pos_.x(); }
    float          y()      const { return pos_.y(); }
    int            width()  const { return width_; }
    int            height() const { return height_; }
    Color          color()  const { return color_; }
    float          scale()  const { return scale_; }
};

}

#endif
