#include "SpikyKernel.h"


SpikyKernel::SpikyKernel(float h):Kernel(h){}

float SpikyKernel::W(const Vec2f& r){
     //float nr = r->norm();
     float nr = norm(r);
     if(nr>=0 && nr<=h){
         return 15 / (PI * pow(h, 6)) * pow(h - nr, 3);
     }
     return 0; 
}

Vec2f SpikyKernel::dW(const Vec2f& r) {
    //float nr = r->norm();
    float nr = norm(r);
    if (nr > 0 && nr <= h) {
        float scalar = - 45 * pow(h - nr, 2) / (PI * pow(h, 6) * nr);
        return scalar * r;
        //return Vec2f(0.0f, 0.0f);    
    }
    return Vec2f(0.0f, 0.0f);
}

float SpikyKernel::lW(const Vec2f& r) {
    //float nr = r->norm();
    float nr = norm(r);
    if (nr >= 0 && nr <= h) {
        return  45 / (PI * pow(h, 6)) * (- h * h / nr + 4 * h - 3 * nr);
    }
    return 0;
}