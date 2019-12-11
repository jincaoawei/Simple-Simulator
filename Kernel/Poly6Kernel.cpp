#include "Poly6Kernel.h"


Poly6Kernel::Poly6Kernel(float h):Kernel(h){}


float Poly6Kernel::W(const Vec2f& r){
     float nr = norm(r);
    //  float nr = sqrt(r*r);
     if(nr>=0 && nr<=h){
         return 315 / (64 * PI * pow(h, 9)) * pow(h * h - nr * nr, 3);
     }
     return 0; 
}

Vec2f Poly6Kernel::dW(const Vec2f& r) {
    float nr = norm(r);
    // float nr = sqrt(r*r);
    if (nr >= 0 && nr <= h) {
        float scalar = -945 / (32 * PI * pow(h, 9)) * pow(- h * h + nr * nr, 2);
        return scalar * r;
    }
    return Vec2f(0.0f, 0.0f);
}

float Poly6Kernel::lW(const Vec2f& r) {
    float nr = norm(r);
    // float nr = sqrt(r*r);
    if (nr >= 0 && nr <= h) {
        return - 945 / (16 * PI * pow(h, 9)) * (pow(h, 4) - 4 * h * h * nr * nr + 3 * pow(nr, 4));
    }
    return 0;
}