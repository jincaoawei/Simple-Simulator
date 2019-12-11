#pragma once

#include "Constraint.h"

class CircularWireConstraint : public Constraint{
    public: 
        CircularWireConstraint(Particle* p, const Vec2f &center, float radius);
        float computeC() override;
        float computeCd() override;
        std::vector<Vec2f> computeJ() override;
        std::vector<Vec2f> computeJd() override;
        void draw() override;


    protected: 
        Particle* m_p;
        const Vec2f &center;
        float radius;
};