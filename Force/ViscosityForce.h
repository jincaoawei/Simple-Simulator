#pragma once

#include "Force.h"
#include "../Kernel/ViscosityKernel.h"

class ViscosityForce : public Force{
 public:
  ViscosityForce(std::vector<Particle*> particles, float h, float mu);

  void draw() override;
  void update() override;

 private:
    ViscosityKernel m_Kernel;
    float m_Mu;

};