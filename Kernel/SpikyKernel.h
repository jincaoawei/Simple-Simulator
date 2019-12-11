#pragma once
#include "Kernel.h"

class SpikyKernel:public Kernel{
    public:
    //for Spiky w(r,h) in paper
    SpikyKernel(float h);
    float W(const Vec2f& r) override;
    Vec2f dW(const Vec2f& r) override;
    float lW(const Vec2f& r) override;
};