#pragma once

#include "Force.h"

class HorizontalForce : public Force {
 public:
  HorizontalForce(std::vector<Particle*> particles);
  ~HorizontalForce();

  

  void update() override;
  void draw() override;
  void changeFDirection();
  int showDir();
  int m_dir = 1;


 private:
    
    float const m_f = 500;
    //int m_dir = 1;
};