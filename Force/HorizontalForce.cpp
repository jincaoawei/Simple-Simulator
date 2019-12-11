

#include "HorizontalForce.h"

HorizontalForce::HorizontalForce(std::vector<Particle*> particles) :
    Force(particles) 
{
}

HorizontalForce::~HorizontalForce()
{
}

void HorizontalForce::update() { 
    if(m_dir == 1){
        for (Particle* particle : m_Particles) {
            Vec2f force = Vec2f(m_f * particle->m_Mass, 0);
            particle->addForce(force);
        }
    }
    if(m_dir == 0){
        for (Particle* particle : m_Particles) {
            Vec2f force = Vec2f(- m_f * particle->m_Mass, 0);
            //std::cout<<"good"<<std::endl;
            particle->addForce(force);
        }
    }
    
}

// void HorizontalForce::changeFDirection(){
//     if(m_dir == 1){
//         //m_dir = 0;
//         std::cout << "change horizontal force to left" << std::endl;
//     }
//     if(m_dir == 0){
//         //m_dir = 1;
//         std::cout << "change horizontal force to right" << std::endl;
//     }
// }

void HorizontalForce::draw(){

}

int HorizontalForce::showDir(){
    return m_dir;
}
