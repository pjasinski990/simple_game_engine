#include <cmath>

#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>

namespace mrld
{
    float* mat4::operator[] (int i)
    {
        return &(*data) + 4 * i;
    }
    const float* mat4::operator[] (int i) const
    {
        return &(*data) + 4 * i;
    }

    mat4& mat4::operator+=(const mat4 &o)
    {
        for (int i = 0; i < 16; ++i) {
            (*this).data[i] += o.data[i];
        }
        return *this;
    }
    mat4& mat4::operator-=(const mat4 &o)
    {
        for (int i = 0; i < 16; ++i) {
            (*this).data[i] -= o.data[i];
        }
        return *this;
    }
    mat4& mat4::operator*=(const mat4 &o)
    {
        mat4 temp;
        for (int i = 0; i < 4; ++i) {
            for (int k = 0; k < 4; ++k) {
                for (int j = 0; j < 4; ++j) {
                    temp[i][j] += (*this)[i][k] * o[k][j];
                }
            }
        }
        *this = std::move(temp);
        return *this;
    }
    mat4& mat4::operator*=(float f)
    {
        for (int i = 0; i < 16; ++i) {
            (*this).data[i] *= f;
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
                temp[i] += (*this)[i][j] * v[i];
            }
        }
        return temp;
    }

    std::ostream &operator<<(std::ostream &out, const mat4 &o)
    {
        int i = 0;
        while (i < 16) {
            out << o.data[i] << " ";
            if (!(++i % 4)) { out << std::endl; }
        }
        return out;
    }

    mat4 mat4::zero()
    {
        mat4 temp;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                temp[i][j] = 0.0f;
            }
        }
        return temp;
    }
    mat4 mat4::identity()
    {
        mat4 temp = mat4::zero();
        for (int i = 0; i < 4; ++i) {
            temp[i][i] = 1.0f;
        }
        return temp;
    }
//    mat4 mat4::rotation(float angle)  // TODO rotation implementation
//    {
//        return mat4();
//    }
    mat4 mat4::translation(const vec2 &v)
    {
        mat4 res = mat4::identity();
        res[0][3] = v.x;
        res[1][3] = v.y;
        return res;
    }
    mat4 mat4::translation(const vec3 &v)
    {
        mat4 res = mat4::identity();
        res[0][3] = v.x;
        res[1][3] = v.y;
        res[2][3] = v.z;
        return res;
    }
    mat4 mat4::translation(const vec4 &v)
    {
        mat4 res = mat4::identity();
        res[0][3] = v.x;
        res[1][3] = v.y;
        res[2][3] = v.z;
        return res;
    }
    mat4 mat4::projection(float aspect_ratio, float fov, float z_near, float z_far)
    {
        mat4 res = mat4::zero();
        float atan_fov = std::atan(fov / 2.0f);
        res[0][0] = aspect_ratio * atan_fov;
        res[1][1] = atan_fov;
        res[2][2] = z_far / (z_far - z_near);
        res[2][3] = 1.0f;
        res[3][2] = -1.0f * z_far * z_near / (z_far - z_near);
        return res;
    }
}
