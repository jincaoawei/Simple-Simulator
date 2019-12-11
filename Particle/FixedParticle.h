#pragma once

#include "Particle.h"

class FixedParticle : public Particle {
    public: 
        FixedParticle(const Vec2f & ConstructPos, int index, float mass);
        void addForce(Vec2f force);
};