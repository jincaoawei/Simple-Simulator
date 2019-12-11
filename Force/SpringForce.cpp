#include "SpringForce.h"
#include <GL/glut.h>

SpringForce::SpringForce(Particle *p1, Particle * p2, double dist, double ks, double kd) :
  m_p1(p1), m_p2(p2), m_dist(dist), m_ks(ks), m_kd(kd) , Force({p1, p2}){ 

  }

void SpringForce::draw()
{
  glBegin( GL_LINES );
  glColor3f(0.6, 0.7, 0.8);
  glVertex2f( m_p1->m_Position[0], m_p1->m_Position[1] );
  glColor3f(0.6, 0.7, 0.8);
  glVertex2f( m_p2->m_Position[0], m_p2->m_Position[1] );
  glEnd();
}
//computing spring force: -(ks * (diffpos - distance) + kd * (|diffpos| * vec_l_deriv) / l) * (vec_l / l);
void SpringForce::update()
{
  Vec2f vec_l = m_Particles[0]->m_Position - m_Particles[1]->m_Position;
  float l = norm(vec_l);
  Vec2f vec_l_deriv = m_Particles[0]->m_Velocity - m_Particles[1]->m_Velocity;
  Vec2f f_a = -(m_ks * (l - m_dist) + m_kd * (vec_l * vec_l_deriv) / l) * (vec_l / l);
  Vec2f f_b = -f_a;
  m_Particles[0]->addForce(f_a);
  m_Particles[1]->addForce(f_b);

}
