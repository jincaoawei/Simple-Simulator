#include "FixedParticle.h"

FixedParticle::FixedParticle(const Vec2f & ConstructPos, int index, float mass) : Particle(ConstructPos, index, mass) {
    m_Mass = mass;
}

void FixedParticle::addForce(Vec2f force) {
    // don't apply the force
}


