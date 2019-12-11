#include "AngularSpringForce.h"
#include <GL/glut.h>

AngularSpringForce::AngularSpringForce(Particle* p1, Particle* p2, Particle* p3, double angle, double ks, double kd) :
  m_p1(p1), m_p2(p2), m_p3(p3), m_angle(angle), m_ks(ks), m_kd(kd) , Force({p1, p2, p3}){ 

  }

void AngularSpringForce::draw()
{

}
//compute angular spring force: fa = −(ks*√a^2+b^2−2abcosα −c + kd*ċ*c\c) =−fc
void AngularSpringForce::update()
{

    Vec2f vec_a = m_p1->m_Position - m_p2->m_Position;
    Vec2f vec_b = m_p3->m_Position - m_p2->m_Position;

    Vec2f vec_c = m_p3->m_Position - m_p1->m_Position;
    Vec2f vec_cd = m_p3->m_Velocity - m_p1->m_Velocity;

    float a = norm(vec_a);
    float b = norm(vec_b);
    float c = norm(vec_c);

    Vec2f f_a = (- m_ks * (sqrt(a * a + b * b - 2 * a * b * cos(m_angle)) - c) 
        + m_kd * (vec_c * vec_cd) / c) * (vec_c / c);

    m_p1->addForce(f_a);
    m_p2->addForce(-f_a);
}
