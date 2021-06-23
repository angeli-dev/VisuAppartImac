#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "../include/geometry.h"
#include "../include/camera.h"
#include "../include/draw.h"

/* Dimensions de la fenetre */
static const unsigned int WINDOW_WIDTH = 1600;
static const unsigned int WINDOW_HEIGHT = 1200;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/*********************************************************/

///// MAIN /////

int main(int argc, char** argv) 
{
    /* Initialisation de la SDL */

   if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr, 
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }   

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */

    SDL_Window* window;
    {
        window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if(NULL == window) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation de la fenetre : %s\n", error);

            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    
    SDL_GLContext context;
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        context = SDL_GL_CreateContext(window);
    
        if(NULL == context) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    
    // Caméra mobile
    Camera maCamera;
    maCamera.position=createVector(5, 5, 1);
    maCamera.pointCible=createVector(50, 50, 1);
    maCamera.axeVertical=createVector(0, 0, 1);
    maCamera.sensibilite=0.5;
    maCamera.vitesse=0.2;
    maCamera = setPointcible(maCamera, maCamera.pointCible);

    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {   
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

         /* construction de la matrice de projection */
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();

	    /* définition de la camera */
        gluPerspective(70.0, (double) WINDOW_WIDTH/WINDOW_HEIGHT, 1.0, 100.0);

        /* reinitialisation des buffers : couleur et ZBuffer */
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	    /* modification de la matrice de la scène */
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();   
        
        /* Placer ici le code de dessin */
        drawScene(maCamera);
        
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
           if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Clic souris*/
                case SDL_MOUSEBUTTONUP: 
                    switch(e.button.button) 
                        case SDL_BUTTON_MIDDLE:
                        break;
                default:
                     break;

                /* Mouvement souris */
               case SDL_MOUSEMOTION:
                    maCamera = orienter(maCamera, e.motion.xrel, e.motion.yrel);

                    break;
                
                /* Touche clavier */
               case SDL_KEYDOWN:
                    switch(e.key.keysym.scancode) 
                    {   
                        case SDL_SCANCODE_ESCAPE :
                        {
                            loop = 0;
                            break;
                        }    
                        // Avancée de la caméra
                        case SDL_SCANCODE_UP :
                            maCamera.position = addVectors(maCamera.position, multVector(maCamera.orientation, maCamera.vitesse));
                            maCamera.pointCible = addVectors(maCamera.position, maCamera.orientation);
                  
			            break;
                        // Recul de la caméra
		                case SDL_SCANCODE_DOWN :
			                maCamera.position = subVectors(maCamera.position, multVector(maCamera.orientation, maCamera.vitesse));
                            maCamera.pointCible = addVectors(maCamera.position, maCamera.orientation);
                  
			            break;
                        // Déplacement vers la gauche
		                case SDL_SCANCODE_LEFT :
			                maCamera.position = addVectors(maCamera.position, multVector(maCamera.deplacementLateral, maCamera.vitesse));
                            maCamera.pointCible = addVectors(maCamera.position, maCamera.orientation);
                      
			            break;
                        // Déplacement vers la droite
		                case SDL_SCANCODE_RIGHT :
			                maCamera.position = subVectors(maCamera.position, multVector(maCamera.deplacementLateral, maCamera.vitesse));
                            maCamera.pointCible = addVectors(maCamera.position, maCamera.orientation);
                      
			            break;
                          case SDL_SCANCODE_Z :
                            maCamera = orienter(maCamera, 1, 0);
                        break;
                        case SDL_SCANCODE_S :
                            maCamera = orienter(maCamera, -1, 0);
                        break;
                        case SDL_SCANCODE_Q :
                            maCamera = orienter(maCamera, 0, 1);
                        break;
                        case SDL_SCANCODE_D :
                            maCamera = orienter(maCamera, 0, -1);
                        break;
                        default:
                            break;
                    }
                }
                break;
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
            /* Si trop peu de temps s'est ecoule, on met en pause le programme */
            if(elapsedTime < FRAMERATE_MILLISECONDS) 
            {
                SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
            }
    }

        /* Liberation des ressources associees a la SDL */
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    
        return EXIT_SUCCESS;
}
