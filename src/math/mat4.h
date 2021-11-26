#pragma once

#include <iostream>

namespace mrld
{
    struct vec2;
    struct vec3;
    struct vec4;
    struct quat;

    struct mat4
    {
        mat4();

        float& at(int i, int j);
        float at(int i, int j) const;

        mat4& operator+=(const mat4& o);
        mat4& operator-=(const mat4& o);
        mat4& operator*=(const mat4& o);
        mat4& operator*=(float f);

        friend mat4 operator+(mat4 o1, const mat4 &o2);
        friend mat4 operator-(mat4 o1, const mat4 &o2);
        friend mat4 operator*(mat4 o1, const mat4 &o2);
        friend mat4 operator*(mat4 o1, float f);
        vec4 operator*(const vec4 &v) const;
        vec3 operator*(const vec3 &v) const;
        mat4 transposed() const;

        friend std::ostream& operator<<(std::ostream& out, const mat4 &o);

        static mat4 identity();
        static mat4 diagonal(float f);

        static mat4 translate(const vec3 &v);
        static mat4 rotate(const quat &q);
        static mat4 rotate_x(float angle_rads);
        static mat4 rotate_y(float angle_rads);
        static mat4 rotate_z(float angle_rads);
        static mat4 scale(const vec3 &scale);

        static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
        static mat4 perspective(float aspect_ratio, float fov_degrees, float z_near, float z_far);

        float data[16];
    };
}
