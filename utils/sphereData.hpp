#ifndef SPHEREDATA_HPP
#define SPHEREDATA_HPP
#include "../glm/glm.hpp"

namespace sp{
    struct sphereData{
        float raio;
        glm::vec3 positions;
        int stacks;
        int sectors;
    };
}

#endif
