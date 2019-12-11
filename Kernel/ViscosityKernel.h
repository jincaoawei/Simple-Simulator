#pragma once

#include "Kernel.h"

class ViscosityKernel:public Kernel{
    public:
    //for viscosity w(r,h) in paper
    ViscosityKernel(float h);
    float W(const Vec2f& r) override;
    Vec2f dW(const Vec2f& r) override;
    float lW(const Vec2f& r) override;


};