#include "ViscosityKernel.h"

ViscosityKernel::ViscosityKernel(float h):Kernel(h){}

float ViscosityKernel::W(const Vec2f& r){
     //float nr = r->norm();
     float nr = norm(r);
     if(nr>=0 && nr<=h){
         return 15 / (2 * PI * pow(h, 3)) * (-pow(nr, 3) / (2 * pow(h, 3)) + (nr * nr) / (h * h) + h / (2 * nr) - 1);
     }
     return 0; 
}

Vec2f ViscosityKernel::dW(const Vec2f& r) {
    //float nr = r->norm();
    float nr = norm(r);
    if (nr >= 0 && nr <= h) {
        float scalar = -15 / (4 * PI * pow(h, 6) * pow(nr, 3)) * (pow(h, 4) - 4 * h * pow(nr,3) + 3 * pow(nr, 4));
        return scalar * r;
    }
    return Vec2f(0.0f, 0.0f);
}

float ViscosityKernel::lW(const Vec2f& r) {
    //float nr = r->norm();
    float nr = norm(r);
    if (nr >= 0 && nr <= h) {
        return (45  / (PI * pow(h, 6))) * (h - nr) ;
    }
    return 0;
}