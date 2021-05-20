#include <cmath>

#include <math/constants.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>

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
                    temp.at(i, j) += at(i, k) * o.at(k, j);
                }
            }
        }
        *this = std::move(temp);
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
                temp[i] += at(i, j) * v[i];
            }
        }
        return temp;
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

    mat4 mat4::translation(const vec3 &v)
    {
        mat4 res = mat4::identity();
        res.at(0, 3) = v.x;
        res.at(1, 3) = v.y;
        res.at(2, 3) = v.z;
        return res;
    }
//    mat4 mat4::rotation(float angle)  // TODO rotation implementation
//    {
//        return mat4();
//    }
    mat4 mat4::scale(const vec3 &scale)
    {
        mat4 res;
        res.data[0 + 0 * 4] = scale.x;
        res.data[1 + 1 * 4] = scale.y;
        res.data[2 + 2 * 4] = scale.z;
        res.data[3 + 3 * 4] = 1.0f;
        return res;
    }

    mat4 mat4::projection(float aspect_ratio, float fov_degrees, float z_near, float z_far)
    {
        mat4 res;
        float fov_rads = fov_degrees / 180.0f * constants::pi;
        float atan_fov_half = std::atan(fov_rads / 2.0f);
        res.at(0, 0) = aspect_ratio * atan_fov_half;
        res.at(1, 1) = atan_fov_half;
        res.at(2, 2) = z_far / (z_far - z_near);
        res.at(2, 3) = 1.0f;
        res.at(3, 2) = -1.0f * z_far * z_near / (z_far - z_near);
        return res;
    }
}
