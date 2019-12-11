#include "RigidBody.h"
#include <GL/glut.h>

RigidBody::RigidBody(Vec2f initX, Vec2f size, std::vector<int> nrParticles, float mass):size(size), mass(mass) {
   
    float stepSizeX = size[0] / (nrParticles[0] - 1);
    float stepSizeY = size[1] / (nrParticles[1] - 1);

    float totalNrParticles = nrParticles[0] * nrParticles[1];
    
    Particle* particle;

    // create particles
    for (float x = initX[0] - size[0] / 2; x <= initX[0] + size[0] / 2; x += stepSizeX) {
        for (float y = initX[1] - size[1] / 2; y <= initX[1] + size[1] / 2; y += stepSizeY) {
            particle = new Particle(Vec2f(x, y), 0, mass / totalNrParticles);
            particle->isRigidParticle = true;
            particles.push_back(particle);
            // std::cout << particle->m_ConstructPos << " ";
        }
        // std::cout << "\n";
    }

    // compute total density
    float density = mass / (size[0] * size[1]);

    // calculate Ibody
    Ibody = Matrix3f::Zero();
    Ibody(0, 0) = pow(size[1], 2);
    Ibody(1, 1) = pow(size[0], 2);
    Ibody(2, 2) = pow(size[1], 2) + pow(size[0], 2);
    // Ibody(0, 0) = pow(size[1], 2);
    // Ibody(1, 1) = pow(size[0], 2);
    // Ibody(2, 2) = pow(size[0], 2) + pow(size[1], 2);
    Ibody *= mass / 12;

    Ibodyinv = Ibody.inverse();

    x_construct = Vector3f(initX[0], initX[1], 0);
    x = x_construct;
    R = Matrix3f::Identity();
    P = Vector3f(0, 0, 0);
    L = Vector3f(0, 0, 0);
    q = Quaternionf(1,0,0,0);


    v = Vector3f(0, 0, 0);
    omega = Vector3f(0, 0, 0);
    force = Vector3f(0, 0, 0);
    torque = Vector3f(0, 0, 0);

    Iinv = Ibodyinv;


}

void RigidBody::updateForce() {
    force = Vector3f(0, 0, 0);
    for (Particle* p : particles) {
        force += Vector3f(p->m_Force[0], p->m_Force[1], 0);
    }
}

void RigidBody::resetForce() {
    for (Particle* p : particles) {
        p->resetForce();
    }
}

void RigidBody::updateTorque() {
    torque = Vector3f(0, 0, 0);
    Vector3f dist;
    for (Particle* p : particles) {
        dist = Vector3f(p->m_Position[0], p->m_Position[1], 0) - x;
        torque += dist.cross(Vector3f(p->m_Force[0], p->m_Force[1], 0));
    }
}

void RigidBody::computeAuxVars() {
    R = q.normalized().toRotationMatrix();
    // std::cout << Ibody << std::endl;
    // std::cout << Ibody.inverse() << std::endl;
    v = P / mass;
    Iinv = R * Ibodyinv * R.transpose();
    omega = Iinv * L;
    // std::cout << Iinv << std::endl;
}

void RigidBody::draw(){
    Vector3f v1 = R * Vector3f(-size[0]/2, -size[1]/2, 0) + x;
    Vector3f v2 = R * Vector3f(size[0]/2, -size[1]/2, 0) + x;
    Vector3f v3 = R * Vector3f(-size[0]/2, size[1]/2, 0) + x;
    Vector3f v4 = R * Vector3f(size[0]/2, size[1]/2, 0) + x;
    
	glBegin( GL_LINES );
    glColor3f(0.6, 0.7, 0.8);
	glVertex2f(v1[0], v1[1]);
    glColor3f(0.6, 0.7, 0.8);
    glVertex2f(v2[0], v2[1]);
    glColor3f(0.6, 0.7, 0.8);
    glVertex2f(v1[0], v1[1]);
    glVertex2f(v3[0], v3[1]);
    glColor3f(0.6, 0.7, 0.8);
    glVertex2f(v2[0], v2[1]);
    glVertex2f(v4[0], v4[1]);
    glColor3f(0.6, 0.7, 0.8);
    glVertex2f(v3[0], v3[1]);
    glVertex2f(v4[0], v4[1]);
	glEnd();

    // for (Particle* p : particles) {
    //     p->draw();
    // }
}




