#include "RodConstraint.h"


RodConstraint::RodConstraint(Particle* p1, Particle* p2, float distance) :
    m_p1(p1), m_p2(p2), Constraint({p1, p2}), distance(distance) {};

//compute constraint: (x1-x2, y1-y2)^2-r^2
float RodConstraint::computeC()
{
    Vec2f pos1 = particles[0]->m_Position;
    Vec2f pos2 = particles[1]->m_Position;
    Vec2f pos3 = pos1 - pos2;

    float C = pos3 * pos3 - distance * distance;

    return C;
}
//compute devariation of constraint: 4*(x1-x2, y1-y2) * (v1 - v2)
float RodConstraint::computeCd(){
    Vec2f pos1 = particles[0]->m_Position;
    Vec2f pos2 = particles[1]->m_Position;
    Vec2f pos3 = pos1 - pos2;

    Vec2f vel1 = particles[0]->m_Velocity;
    Vec2f vel2 = particles[1]->m_Velocity;
    Vec2f vel3 = vel1 - vel2;

    float Cd = 4.0 * pos3 * vel3;
    return Cd;
}

//compute jacobians: j + 2*(x1-x2, y1-y2) + 2*(x1-x2, y1-y2)
std::vector<Vec2f> RodConstraint::computeJ() {
    std::vector<Vec2f> J;
    J.push_back(2 * (particles[0]->m_Position - particles[1]->m_Position));
    J.push_back(2 * (particles[1]->m_Position - particles[0]->m_Position));
    
    return J;
}
//compute devariation of jacohians: j + 2 * (v1 - v2) + 2 * (v1 - v2)
std::vector<Vec2f> RodConstraint::computeJd() {
    std::vector<Vec2f> J;
    J.push_back(2 * (particles[0]->m_Velocity - particles[1]->m_Velocity));
    J.push_back(2 * (particles[1]->m_Velocity - particles[0]->m_Velocity));
    
    return J;
}

void RodConstraint::draw()
{
  glBegin( GL_LINES );
  glColor3f(0.8, 0.7, 0.6);
  glVertex2f( m_p1->m_Position[0], m_p1->m_Position[1] );
  glColor3f(0.8, 0.7, 0.6);
  glVertex2f( m_p2->m_Position[0], m_p2->m_Position[1] );
  glEnd();
}


