#pragma once
#include "Color.h"
struct Particle {
    float x, y, z;
    float vx, vy, vz;
    Color color;
    int type;// Type 0 or Type 1 (can be extended)

};

