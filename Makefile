CXX = g++
CXXFLAGS = -g -O2 -Wall -Wno-sign-compare -Iinclude -DHAVE_CONFIG_H 
OBJS = RigidBody.o Force/TensionForce.o Force/ViscosityForce.o Force/PressureForce.o Solver/Solver.o Solver/SPHsolver.o ParticleToy.o Constraint/RodConstraint.o Force/SpringForce.o Constraint/CircularWireConstraint.o imageio.o Force/Force.o Force/GravityForce.o Force/HorizontalForce.o Constraint/Constraint.o Solver/ConstraintSolver.o Force/AngularSpringForce.o Kernel/Kernel.o Kernel/Poly6Kernel.o Kernel/SpikyKernel.o Kernel/ViscosityKernel.o Particle/Particle.o Particle/FixedParticle.o 
project1: $(OBJS)
	$(CXX) -o $@ $^ -L/usr/lib/x86_64-linux-gnu/mesa/ -l:libGL.so.1 -lglut -lpng -lGLU
clean:
	rm $(OBJS) project1
