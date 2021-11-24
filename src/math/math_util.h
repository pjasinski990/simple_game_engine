#pragma once

namespace mrld
{
    namespace math_constants
    {
        constexpr float epsilon = 1e-6f;
        constexpr float pi = 3.14159265f;
        constexpr float pi2 = pi / 2.0f;
        constexpr float pi4 = pi / 4.0f;
        constexpr float pi6 = pi / 6.0f;
        constexpr float pi8 = pi / 8.0f;
    }

    inline float rad_to_deg(float theta) {
        return theta * 180.0f / math_constants::pi;
    }

    inline float deg_to_rad(float deg) {
        return deg * math_constants::pi / 180.0f;
    }

}
