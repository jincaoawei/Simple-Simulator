#pragma once

#include "Force.h"

class TensionForce : public Force{
 public:
  TensionForce(std::vector<Particle*> particles, float sg);

  float sigma;
  void draw() override;
  void update() override;

};