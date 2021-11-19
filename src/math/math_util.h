#pragma once

namespace mrld
{
    namespace math_constants
    {
        constexpr float epsilon = 1e-6f;
        constexpr float pi = 3.14159265f;
    }

    inline float rad_to_deg(float theta) {
        return theta * 180.0f / math_constants::pi;
    }

    inline float deg_to_rad(float deg) {
        return deg * math_constants::pi / 180.0f;
    }

}
