#include "drawable.h"

namespace mrld
{
    void Drawable::assign_material(const material &m)
    {
        _materials.clear();
        _materials.push_back(m);
        for (auto &vd : _vertices) {
            vd.material_slot = 0.0f;
        }
    }
}
