#pragma once

#include <vector>
#include "../Particle/Particle.h"

class Force {
 public:
  Force(std::vector<Particle*> particles);
  virtual ~Force();
  virtual void update() = 0;
  virtual void draw();

 protected:
    std::vector<Particle*> m_Particles;
};