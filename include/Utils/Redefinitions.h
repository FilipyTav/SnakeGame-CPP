#include "Vector2.hpp"
#include <raylib.h>

template <typename T> //
class Shy : public raylib::Vector2 {
  public:
    Shy(T x, T y) : Vector2{static_cast<float>(x), static_cast<float>(y)} {}
    Shy(T x) : Vector2{x, 0} {}
    Shy(const Vector2& vec)
        : Shy{static_cast<T>(vec.x), static_cast<T>(vec.y)} {}

    GETTERSETTER(T, X, x)
    GETTERSETTER(T, Y, y)

  private:
};
