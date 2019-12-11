#include "include/Eigen/Dense"
#include "include/gfx/vec3.h"
#include "Particle/Particle.h"
#include <vector>

using namespace Eigen;

class RigidBody {
    public: 
        RigidBody(Vec2f initX, Vec2f size, std::vector<int> nrParticles, float mass);

        // constant
        float mass;
        Matrix3f Ibody, Ibodyinv;

        // state variables
        Vector3f x_construct;
        Vector3f x; 
        Quaternionf q;
        Vector3f P, L;

        // Derived quantities
        Matrix3f Iinv, R;
        Vector3f v, omega;

        // Computed quantities
        Vector3f force, torque;
        
        std::vector<Particle*> particles;
        Vec2f size;

        void updateForce();
        void updateTorque();
        void computeAuxVars();
        void resetForce();
        void draw();
            

};