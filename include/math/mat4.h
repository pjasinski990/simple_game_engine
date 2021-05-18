#ifndef MRLD_ENGINE_MAT4_H
#define MRLD_ENGINE_MAT4_H

#include <iostream>

namespace mrld
{
    struct vec2;
    struct vec3;
    struct vec4;

    struct mat4
    {
        float* operator[] (int i);
        const float* operator[] (int i) const;

        mat4();

        mat4& operator+=(const mat4& o);
        mat4& operator-=(const mat4& o);
        mat4& operator*=(const mat4& o);
        mat4& operator*=(float f);

        friend mat4 operator+(mat4 o1, const mat4 &o2);
        friend mat4 operator-(mat4 o1, const mat4 &o2);
        friend mat4 operator*(mat4 o1, const mat4 &o2);
        friend mat4 operator*(mat4 o1, float f);
        vec4 operator*(const vec4 &v) const;

        friend std::ostream& operator<<(std::ostream& out, const mat4 &o);

        static mat4 identity();
        // static mat4 rotation(float angle_x, float angle_y, float angle_z);    //TODO implement quaternions and rotation
        static mat4 translation(const vec2 &v);
        static mat4 translation(const vec3 &v);
        static mat4 translation(const vec4 &v);
        static mat4 projection(float aspect_ratio, float fov, float z_near, float z_far);

        float data[16];
    };
}

#endif //MRLD_ENGINE_MAT4_H
