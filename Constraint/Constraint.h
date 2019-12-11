#pragma once

#include "../Particle/Particle.h"
#include <vector>
#include <GL/glut.h>

class Constraint {
    public: 
        Constraint(std::vector<Particle*> particles);
        virtual float computeC() = 0;
        virtual float computeCd() = 0;
        virtual std::vector<Vec2f> computeJ() = 0;
        virtual std::vector<Vec2f> computeJd() = 0;
        std::vector<int> getParticleIndeces();
        //int getnrParticles();
        virtual void draw() = 0;


    protected: 
        std::vector<Particle*> particles;
        std::vector<int> indices;
};