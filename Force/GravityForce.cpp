

#include "GravityForce.h"

GravityForce::GravityForce(std::vector<Particle*> particles) :
    Force(particles) 
{
}

GravityForce::~GravityForce()
{
}
//compute gravity force: m_G*m_mass
void GravityForce::update() { 
    for (Particle* particle : m_Particles) {
        Vec2f force = Vec2f(0, - m_G * particle->m_Mass);
        particle->addForce(force);
    }
}

void GravityForce::draw(){}
