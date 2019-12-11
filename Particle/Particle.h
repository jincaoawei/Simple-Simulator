#pragma once

#include <gfx/vec2.h>

class Particle
{
public:

	Particle(const Vec2f & ConstructPos, int index, float mass);
	virtual ~Particle(void);

	void reset();
	void draw();

	void resetForce();
	void resetDensity();
	virtual void addForce(Vec2f force);

	Vec2f m_ConstructPos;
	Vec2f m_Position;
	Vec2f m_Velocity;

	float m_Density;
	float m_Pressure;
	float m_ColourL;
	Vec2f m_ColourG;
	 
	Vec2f m_Force;
	float m_Mass;
	int index;
	bool isRigidParticle = false;
};
