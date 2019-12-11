// ParticleToy.cpp : Defines the entry point for the console application.
//

#include "Particle/Particle.h"
#include "Particle/FixedParticle.h"
#include "Force/SpringForce.h"
#include "Force/GravityForce.h"
#include "Force/PressureForce.h"
#include "Force/ViscosityForce.h"
#include "Force/TensionForce.h"
#include "Constraint/RodConstraint.h"
#include "Solver/ConstraintSolver.h"
#include "Solver/SPHsolver.h"
#include "RigidBody.h"
#include "imageio.h"

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

/* macros */

/* external definitions (from solver) */
extern void simulation_step( std::vector<Particle*> pVector, 
                             std::vector<Force*> fVector, 
							 std::vector<RigidBody*> rVector,
							 ConstraintSolver* cSolver, SPHsolver* sphSolver, float dt, int solver_number, 
							 std::vector<Constraint*> constraints);

/* global variables */

static int N;
static float dt, d;
static int dsim;
static int dump_frames;
static int frame_number;

static int pIndex = 0;

// static Particle *pList;
static std::vector<Particle*> pVector;
static std::vector<Force*> fVector;
static std::vector<Constraint*> cVector;
static std::vector<RigidBody*> rVector;

static ConstraintSolver cSolver;
static SPHsolver* sphSolver;
static int solver_number = 3;

static int win_id;
static int win_x, win_y;
static int mouse_down[3];
static int mouse_release[3];
static int mouse_shiftclick[3];
static int omx, omy, mx, my;
static int hmx, hmy;




/*
----------------------------------------------------------------------
free/clear/allocate simulation data
----------------------------------------------------------------------
*/

static void free_data ( void )
{
	pVector.clear();
	fVector.clear();
}

static void clear_force ( void )
{
	for(Particle* p : pVector){
		p->resetForce();
	}
}

static void clear_data ( void )
{
	int ii, size = pVector.size();

	for(ii=0; ii<size; ii++){
		pVector[ii]->reset();
		pVector[ii]->resetForce();
		pVector[ii]->resetDensity();
	}
}

static void init_system(void)
{
	const double dist = 0.08;

	// pVector.push_back(new Particle(Vec2f(0, 0),pIndex));
	for(float y = -.8; y <= -0.3f; y+= dist)
	{
		for(float x = -0.9; x<= 0.9; x+=dist){
			pVector.push_back(new Particle(Vec2f(x, y),pIndex, 10.f));
			pIndex++;
		}
	}

	float rigid_mass = 100.f;
	int nrXp_rigid = 15;
	int nrYp_rigid = 15;
	float lenX_rigid = 0.3f;
	float lenY_rigid = 0.3f;
	float originX_rigid = 0.f;
	float originY_rigid = 0.f;
	rVector.push_back(new RigidBody(Vec2f(originX_rigid, originY_rigid),
									Vec2f(lenX_rigid, lenY_rigid),
									{nrXp_rigid, nrYp_rigid},
									rigid_mass));
	

	// add border

	float mass = 10.f;
	float dSpace = .05f;

	for(float x = -1; x <= 1; x += dSpace) {
		pVector.push_back(new FixedParticle(Vec2f(x, -1),pIndex, mass));
		pVector.push_back(new FixedParticle(Vec2f(x, -1.1),pIndex, mass));
		pIndex++;
	}
	for(float x = -1; x <= 1; x += dSpace) {
		pVector.push_back(new FixedParticle(Vec2f(x, 1),pIndex, mass));
		pVector.push_back(new FixedParticle(Vec2f(x, 1.1),pIndex, mass));
		pIndex++;
	}

	for(float y = -1; y <= 1; y += dSpace) {
		pVector.push_back(new FixedParticle(Vec2f(-1, y),pIndex, mass));
		pVector.push_back(new FixedParticle(Vec2f(-1.1, y),pIndex, mass));
		pIndex++;
	}
	for(float y = -1; y <= 1; y += dSpace) {
		pVector.push_back(new FixedParticle(Vec2f(1, y),pIndex, mass));
		pVector.push_back(new FixedParticle(Vec2f(1.1, y),pIndex, mass));
		pIndex++;
	}

	float h = .15f;
	float mu = 100;
	float sg = 12.f;
	float restDensity = 10000.f;
	float k = 5.f;


	std::vector<Particle*> tVector;
	tVector.insert(tVector.end(), pVector.begin(), pVector.end());
	tVector.insert(tVector.end(), rVector[0]->particles.begin(), rVector[0]->particles.end());

	fVector.push_back(new GravityForce(pVector));

	fVector.push_back(new GravityForce(rVector[0]->particles));
	fVector.push_back(new PressureForce(tVector, h));
	fVector.push_back(new ViscosityForce(pVector, h, mu));
	fVector.push_back(new TensionForce(pVector, sg));

	//pVector.push_back(new Vec2f(x,y));
	
	// You shoud replace these with a vector generalized forces and one of
	// constraints...
	cSolver = ConstraintSolver();

	sphSolver = new SPHsolver(k, restDensity, h);
}

/*
----------------------------------------------------------------------
OpenGL specific drawing routines
----------------------------------------------------------------------
*/

static void pre_display ( void )
{
	glViewport ( 0, 0, win_x, win_y );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	gluOrtho2D ( -1.0, 1.0, -1.0, 1.0 );
	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
}

static void post_display ( void )
{
	// Write frames if necessary.
	if (dump_frames) {
		const int FRAME_INTERVAL = 4;
		if ((frame_number % FRAME_INTERVAL) == 0) {
			const unsigned int w = glutGet(GLUT_WINDOW_WIDTH);
			const unsigned int h = glutGet(GLUT_WINDOW_HEIGHT);
			unsigned char * buffer = (unsigned char *) malloc(w * h * 4 * sizeof(unsigned char));
			if (!buffer)
				exit(-1);
			// glRasterPos2i(0, 0);
			glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			static char filename[80];
			sprintf(filename, "snapshots/img%.5i.png", frame_number / FRAME_INTERVAL);
			printf("Dumped %s.\n", filename);
			saveImageRGBA(filename, buffer, w, h);
			
			free(buffer);
		}
	}
	frame_number++;
	
	glutSwapBuffers ();
}

static void draw_particles ( void )
{
	int size = pVector.size();

	for(int ii=0; ii< size; ii++)
	{
		pVector[ii]->draw();
	}

	for (RigidBody* r : rVector) {
		r->draw();
	}
}

static void draw_forces ( void )
{
	// change this to iteration over full set
    for (Force* force : fVector) {
		force->draw();
	}
}

static void draw_constraints ( void )
{
	// change this to iteration over full set
	for (Constraint* cons : cVector)
	{
		cons->draw();
	}
}

/*
----------------------------------------------------------------------
relates mouse movements to particle toy construction
----------------------------------------------------------------------
*/

static void get_from_UI ()
{
	int i, j;
	// int size, flag;
	int hi, hj;
	// float x, y;
	if ( !mouse_down[0] && !mouse_down[2] && !mouse_release[0] 
	&& !mouse_shiftclick[0] && !mouse_shiftclick[2] ) return;

	i = (int)((       mx /(float)win_x)*N);
	j = (int)(((win_y-my)/(float)win_y)*N);

	if ( i<1 || i>N || j<1 || j>N ) return;

	if ( mouse_down[0] ) {

	}

	if ( mouse_down[2] ) {
	}

	hi = (int)((       hmx /(float)win_x)*N);
	hj = (int)(((win_y-hmy)/(float)win_y)*N);

	if( mouse_release[0] ) {
	}

	omx = mx;
	omy = my;
}

static void remap_GUI()
{
	int ii, size = pVector.size();
	for(ii=0; ii<size; ii++)
	{
		pVector[ii]->m_Position[0] = pVector[ii]->m_ConstructPos[0];
		pVector[ii]->m_Position[1] = pVector[ii]->m_ConstructPos[1];
	}
}

/*
----------------------------------------------------------------------
GLUT callback routines
----------------------------------------------------------------------
*/

static void key_func ( unsigned char key, int x, int y )
{
	switch ( key )
	{
	case 'c':
	case 'C':
		clear_data ();
		break;

	case 'd':
	case 'D':
		dump_frames = !dump_frames;
		break;

	case 'q':
	case 'Q':
		free_data ();
		exit ( 0 );
		break;

	case ' ':
		dsim = !dsim;
		break;
	}
}

static void mouse_func ( int button, int state, int x, int y )
{
	omx = mx = x;
	omx = my = y;

	if(!mouse_down[0]){hmx=x; hmy=y;}
	if(mouse_down[button]) mouse_release[button] = state == GLUT_UP;
	if(mouse_down[button]) mouse_shiftclick[button] = glutGetModifiers()==GLUT_ACTIVE_SHIFT;
	mouse_down[button] = state == GLUT_DOWN;
}

static void motion_func ( int x, int y )
{
	mx = x;
	my = y;
}

static void reshape_func ( int width, int height )
{
	glutSetWindow ( win_id );
	glutReshapeWindow ( width, height );

	win_x = width;
	win_y = height;
}

static void idle_func ( void )
{
	if ( dsim ) simulation_step( pVector, fVector, rVector, &cSolver, sphSolver, dt, solver_number, cVector);
	else        {get_from_UI();remap_GUI();}

	glutSetWindow ( win_id );
	glutPostRedisplay ();
}

static void display_func ( void )
{
	pre_display ();

	draw_forces();
	draw_constraints();
	draw_particles();

	post_display ();
}


/*
----------------------------------------------------------------------
open_glut_window --- open a glut compatible window and set callbacks
----------------------------------------------------------------------
*/

static void open_glut_window ( void )
{
	glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE );

	glutInitWindowPosition ( 0, 0 );
	glutInitWindowSize ( win_x, win_y );
	win_id = glutCreateWindow ( "Particletoys!" );

	glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear ( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers ();
	glClear ( GL_COLOR_BUFFER_BIT );
	glutSwapBuffers ();

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	pre_display ();

	glutKeyboardFunc ( key_func );
	glutMouseFunc ( mouse_func );
	glutMotionFunc ( motion_func );
	glutReshapeFunc ( reshape_func );
	glutIdleFunc ( idle_func );
	glutDisplayFunc ( display_func );
}


/*
----------------------------------------------------------------------
main --- main routine
----------------------------------------------------------------------
*/

int main ( int argc, char ** argv )
{
	glutInit ( &argc, argv );

	if ( argc == 1 ) {
		N = 64;
		dt = 0.1f;
		d = 5.f;
		fprintf ( stderr, "Using defaults : N=%d dt=%g d=%g\n",
			N, dt, d );
	} else {
		N = atoi(argv[1]);
		dt = atof(argv[2]);
		d = atof(argv[3]);
	}

	printf ( "\n\nHow to use this application:\n\n" );
	printf ( "\t Toggle construction/simulation display with the spacebar key\n" );
	printf ( "\t Dump frames by pressing the 'd' key\n" );
	printf ( "\t Quit by pressing the 'q' key\n" );

	dsim = 0;
	dump_frames = 0;
	frame_number = 0;
	
	init_system();
	
	win_x = 512;
	win_y = 512;
	open_glut_window ();

	glutMainLoop ();

	exit ( 0 );
}

