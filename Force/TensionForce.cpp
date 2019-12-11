#include "TensionForce.h"

TensionForce::TensionForce(std::vector<Particle*> particles, float sg) :
    Force(particles), sigma(sg)
{

}

void TensionForce::draw()
{

}

void TensionForce::update()
{
    for (Particle* p : m_Particles) 
    {
        if(norm(p->m_ColourG) > 0.001f)
        {
            Vec2f tensionForce = - sigma * p->m_ColourL * p->m_ColourG / norm(p->m_ColourG);
            p->addForce(tensionForce);
        }
    }
}