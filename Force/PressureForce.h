#pragma once

#include "Force.h"
#include "../Kernel/SpikyKernel.h"

class PressureForce : public Force{
 public:
  PressureForce(std::vector<Particle*> particles, float h);

  void draw() override;
  void update() override;

 private:
  SpikyKernel m_Kernel;

};
