#pragma once

#include "Kernel.h"

class Poly6Kernel:public Kernel{
    public:
    //for poly6 w(r,h) in paper
    Poly6Kernel(float h);
    float W(const Vec2f& r) override;
    Vec2f dW(const Vec2f& r) override;
    float lW(const Vec2f& r) override;

};