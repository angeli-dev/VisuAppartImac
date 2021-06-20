#pragma once

#include "../include/globject.hpp"
#include "../include/Program.hpp"
#include "../include/scene.hpp"

#define STEP_TIME	0.32f
#define STEP_ANGLE	M_PI/90.0
#define STEP_PROF	M_PI/90.0

/* variables globales pour la gestion de la caméra */
extern float profondeur;
extern float latitude;
extern float longitude;

/* variables globales pour la gestion de la scene */
extern float global_time;
extern float global_light;
extern bool use_shader;
extern bool animate_world;
extern bool animate_light;
extern Program* my_shader;
extern Scene* my_scene;
extern GLUquadric *quadric;

/* Déclaration des fonctions */
void idle(void);
void init();

