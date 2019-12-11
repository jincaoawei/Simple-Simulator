#pragma once

#include "Constraint.h"

class RodConstraint : public Constraint{
    public: 
        RodConstraint(Particle* p1, Particle* p2, float distance);
        float computeC() override;
        float computeCd() override;
        std::vector<Vec2f> computeJ() override;
        std::vector<Vec2f> computeJd() override;
        void draw() override;


    protected: 
        Particle* m_p1;
        Particle* m_p2;
        float distance;
        

};