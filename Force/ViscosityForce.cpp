#include "ViscosityForce.h"

ViscosityForce::ViscosityForce(std::vector<Particle*> particles, float h, float mu) :
    Force(particles), m_Kernel(ViscosityKernel(h)), m_Mu(mu)
{

}

void ViscosityForce::draw()
{

}

void ViscosityForce::update()
{
    Vec2f dist;
    for (Particle* p : m_Particles) {
        for (Particle* q : m_Particles) {

            dist = p->m_Position - q->m_Position;

            Vec2f viscosityForce = m_Mu * q->m_Mass * (q->m_Velocity - p->m_Velocity) / q->m_Density * m_Kernel.lW(dist);

            p->addForce(viscosityForce);
        }
    }
}