#pragma once

#include "Force.h"

class GravityForce : public Force {
 public:
  GravityForce(std::vector<Particle*> particles);
  ~GravityForce();

  void update() override;
  void draw() override;

 private:
    
    float const m_G = 9.81;
};