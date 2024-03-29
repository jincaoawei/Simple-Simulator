#include "Particle.h"
#include <GL/glut.h>

Particle::Particle(const Vec2f & ConstructPos, int index, float mass) :
	m_ConstructPos(ConstructPos), m_Position(Vec2f(0.0, 0.0)), 
	m_Velocity(Vec2f(0.0, 0.0)), m_Mass(mass), m_Density(0.0f), 
	m_Force(Vec2f(0.0, 0.0)), m_Pressure(0.0f), index(index)
{
}

Particle::~Particle(void)
{
}

void Particle::reset()
{
	m_Position = m_ConstructPos;
	m_Velocity = Vec2f(0.0, 0.0);
}
void Particle::draw()
{
	const double h = 0.03;
	glColor3f(1.f, 1.f, 1.f); 
	glBegin(GL_QUADS);
	glVertex2f(m_Position[0]-h/2.0, m_Position[1]-h/2.0);
	glVertex2f(m_Position[0]+h/2.0, m_Position[1]-h/2.0);
	glVertex2f(m_Position[0]+h/2.0, m_Position[1]+h/2.0);
	glVertex2f(m_Position[0]-h/2.0, m_Position[1]+h/2.0);
	glEnd();
}

void Particle::addForce(Vec2f force)
{
	m_Force += force;
}

void Particle::resetForce()
{
	m_Force = Vec2f(0.0, 0.0);
}

void Particle::resetDensity()
{
	m_Density = 0.0f;
}
