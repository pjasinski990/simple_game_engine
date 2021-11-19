#include <cmath>

#include "math_util.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace mrld
{
    mat4::mat4()
    {
        for (int i = 0; i < 16; ++i) {
            data[i] = 0.0f;
        }
    }

    float& mat4::at(int i, int j)
    {
        return data[i + j * 4];
    }
    float mat4::at(int i, int j) const
    {
        return data[i + j * 4];
    }

    mat4& mat4::operator+=(const mat4 &o)
    {
        for (int i = 0; i < 16; ++i) {
            data[i] += o.data[i];
        }
        return *this;
    }
    mat4& mat4::operator-=(const mat4 &o)
    {
        for (int i = 0; i < 16; ++i) {
            data[i] -= o.data[i];
        }
        return *this;
    }
    mat4& mat4::operator*=(const mat4 &o)
    {
        mat4 temp;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    temp.data[i + j * 4] += data[i + k * 4] * o.data[k + j * 4];
                }
            }
        }
        *this = temp;
        return *this;
    }
    mat4& mat4::operator*=(float f)
    {
        for (int i = 0; i < 16; ++i) {
            data[i] *= f;
        }
        return *this;
    }

    mat4 operator+(mat4 o1, const mat4 &o2)
    {
        return o1 += o2;
    }
    mat4 operator-(mat4 o1, const mat4& o2)
    {
        return o1 -= o2;
    }
    mat4 operator*(mat4 o1, const mat4& o2)
    {
        return o1 *= o2;
    }
    mat4 operator*(mat4 o1, float f)
    {
        return o1 *= f;
    }
    vec4 mat4::operator*(const vec4 &v) const
    {
        vec4 temp;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                temp[i] += data[i + j * 4] * v[j];
            }
        }
        return temp;
    }
    vec3 mat4::operator*(const vec3 &v) const
    {
        vec3 temp;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                temp[i] += data[i + j * 4] * v[j];
            }
            temp[i] += data[i + 3 * 4];
        }
        return temp;
    }

    mat4 mat4::transposed() const
    {
        mat4 res;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res.at(i, j) = at(j, i);
            }
        }
        return res;
    }

    std::ostream &operator<<(std::ostream &out, const mat4 &o)
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                out << o.at(i, j) << " ";
            }
            out << std::endl;
        }
        return out;
    }

    mat4 mat4::identity()
    {
        mat4 res;
        res.data[0 + 0 * 4] = 1.0f;
        res.data[1 + 1 * 4] = 1.0f;
        res.data[2 + 2 * 4] = 1.0f;
        res.data[3 + 3 * 4] = 1.0f;
        return res;
    }
    mat4 mat4::diagonal(float f)
    {
        mat4 res;
        res.data[0 + 0 * 4] = f;
        res.data[1 + 1 * 4] = f;
        res.data[2 + 2 * 4] = f;
        res.data[3 + 3 * 4] = f;
        return res;
    }

    mat4 mat4::translate(const vec3 &v)
    {
        mat4 res = mat4::identity();
        res.data[0 + 3 * 4] = v.x;
        res.data[1 + 3 * 4] = v.y;
        res.data[2 + 3 * 4] = v.z;
        return res;
    }
    mat4 mat4::rotate_x(float angle_rads)
    {
        mat4 res;
        float s = sin(angle_rads);
        float c = cos(angle_rads);
        res.data[0 + 0 * 4] = 1.0f;
        res.data[1 + 1 * 4] = c;
        res.data[2 + 2 * 4] = c;
        res.data[1 + 2 * 4] = -s;
        res.data[2 + 1 * 4] = s;
        res.data[3 + 3 * 4] = 1.0f;
        return res;
    }
    mat4 mat4::rotate_y(float angle_rads)
    {
        mat4 res;
        float s = sin(angle_rads);
        float c = cos(angle_rads);
        res.data[0 + 0 * 4] = c;
        res.data[1 + 1 * 4] = 1.0f;
        res.data[2 + 2 * 4] = c;
        res.data[0 + 2 * 4] = s;
        res.data[2 + 0 * 4] = -s;
        res.data[3 + 3 * 4] = 1.0f;
        return res;
    }
    mat4 mat4::rotate_z(float angle_rads)
    {
        mat4 res;
        float s = sin(angle_rads);
        float c = cos(angle_rads);
        res.data[0 + 0 * 4] = c;
        res.data[1 + 1 * 4] = c;
        res.data[2 + 2 * 4] = 1.0f;
        res.data[0 + 1 * 4] = -s;
        res.data[1 + 0 * 4] = s;
        res.data[3 + 3 * 4] = 1.0f;
        return res;
    }
    mat4 mat4::scale(const vec3 &scale)
    {
        mat4 res;
        res.data[0 + 0 * 4] = scale.x;
        res.data[1 + 1 * 4] = scale.y;
        res.data[2 + 2 * 4] = scale.z;
        res.data[3 + 3 * 4] = 1.0f;
        return res;
    }

    mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
    {
        mat4 res;
        res.data[0 + 0 * 4] = 2.0f / (right - left);
        res.data[1 + 1 * 4] = 2.0f / (top - bottom);
        res.data[2 + 2 * 4] = -2.0f / (far - near);
        res.data[3 + 3 * 4] = 1.0f;

        res.data[0 + 3 * 4] = -1.0f * (right + left) / (right - left);
        res.data[1 + 3 * 4] = -1.0f * (top + bottom) / (top - bottom);
        res.data[2 + 3 * 4] = -1.0f * (far + near) / (far - near);
        return res;
    }

    mat4 mat4::perspective(float aspect_ratio, float fov_degrees, float z_near, float z_far)
    {
        mat4 res;
        const float fov_rads = deg_to_rad(fov_degrees);
        const float tan_fov_half = std::tan(fov_rads / 2.0f);
        res.data[0 + 0 * 4] = 1.0f / (aspect_ratio * tan_fov_half);
        res.data[1 + 1 * 4] = 1.0f / tan_fov_half;
        res.data[2 + 2 * 4] = z_far / (z_far - z_near);
        res.data[3 + 2 * 4] = -z_far * z_near / (z_far - z_near);
        res.data[2 + 3 * 4] = 1.0f;
        return res;
    }
}
