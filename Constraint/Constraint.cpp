#include "Constraint.h"

Constraint::Constraint(std::vector<Particle*> particles) : 
    particles(particles)
{
    //get all index value in constraint particles
    for(int i = 0; i < particles.size(); i++) {
        indices.push_back(particles[i]->index);
    }
}

std::vector<int> Constraint::getParticleIndeces() 
{
    return indices;
}

void Constraint::draw(){}
