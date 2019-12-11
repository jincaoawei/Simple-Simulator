#pragma once


#include "../include/gfx/vec2.h"
#include <iostream>

#define PI 3.14159

class Kernel{
public:

    Kernel(float h);
    //kernel interface
    virtual float W(const Vec2f& r) = 0;
    virtual Vec2f dW(const Vec2f& r) = 0;
    virtual float lW(const Vec2f& r) = 0;

    float h;

};