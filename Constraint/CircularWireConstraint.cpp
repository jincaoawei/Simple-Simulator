#include "CircularWireConstraint.h"
#include <GL/glut.h>


#define PI 3.1415926535897932384626433832795

static void draw_circle(const Vec2f &vect, float radius)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0,1.0,0.0); 
	for (int i=0; i<360; i=i+18)
	{
		float degInRad = i*PI/180;
		glVertex2f(vect[0]+cos(degInRad)*radius,vect[1]+sin(degInRad)*radius);
	}
	glEnd();
}


CircularWireConstraint::CircularWireConstraint(Particle* p, const Vec2f &center, float radius) :
	Constraint({p}), m_p(p), center(center), radius(radius){}



void CircularWireConstraint::draw()
{
    draw_circle(center, radius);
}

//compute constraint: (x-xc, y-yc)^2-r^2
float CircularWireConstraint::computeC()
{
    Vec2f diff = particles[0]->m_Position - center;
    float diff_sq = diff * diff;
    float radius_sq = radius * radius;
    return diff_sq - radius_sq;
}
//compute devariation of constraint: 2*(x-xc, y-yc) * v
float CircularWireConstraint::computeCd()
{
    Vec2f diffPosition = particles[0]->m_Position - center;
    Vec2f diffVelocity = particles[0]->m_Velocity;
    return 2.0 * diffPosition * diffVelocity;
}
//compute jacobians: j + 2*(x-xc, y-yc) + 2*(x-xc, y-yc)
std::vector<Vec2f> CircularWireConstraint::computeJ() 
{
    std::vector<Vec2f> j;
    j.push_back(2 * (particles[0]->m_Position - center));
    j.push_back(2 * (particles[0]->m_Position - center));
    return j;
}
//compute devariation of jacohians: j + 2 * v + 2 * v
std::vector<Vec2f> CircularWireConstraint::computeJd() 
{
    std::vector<Vec2f> jd;
    jd.push_back(particles[0]->m_Velocity * 2);
    jd.push_back(particles[0]->m_Velocity * 2);
    return jd;
}


