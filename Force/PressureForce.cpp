#include "PressureForce.h"

PressureForce::PressureForce(std::vector<Particle*> particles, float h) :
    Force(particles), m_Kernel(SpikyKernel(h))
{

} 

void PressureForce::update() 
{
    Vec2f dis;

    for(Particle* p : m_Particles){
        for(Particle* q : m_Particles){
            if (p->isRigidParticle && !q->isRigidParticle) {
                dis = p->m_Position - q->m_Position;            

            
                Vec2f pressure_force = - q->m_Mass * (p->m_Pressure + q->m_Pressure) / (2 * q->m_Density) * 
                                    m_Kernel.dW(dis);
            
                p->addForce(pressure_force * 0.0002f);
            } else if (!p->isRigidParticle) {
                dis = p->m_Position - q->m_Position;            

            
                Vec2f pressure_force = - q->m_Mass * (p->m_Pressure + q->m_Pressure) / (2 * q->m_Density) * 
                                    m_Kernel.dW(dis);
            
                p->addForce(pressure_force);
            }
        }
    }
}

void PressureForce::draw()
{
    
}