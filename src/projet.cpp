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

    glutInit(&argc, argv);

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
        "VisuAppartImac",
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
    maCamera.axeVertical=createVector(0, 0, 1);
    maCamera.sensibilite=0.5;
    maCamera.vitesse=0.25;
    maCamera.position=createVector(30, 100, 60);
    maCamera=setPosition(maCamera, maCamera.position);
    maCamera.pointCible=createVector(30, 0, 0);
    maCamera = setPointCible(maCamera, maCamera.pointCible);
    
    bool modePerso=false;
    bool modeAuto=false;

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
        gluPerspective(70.0, (double) WINDOW_WIDTH/WINDOW_HEIGHT, 1.0, 200.0);
        if(modeAuto)
        {
            maCamera=visiteAuto(maCamera);
        }

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
                            if(modePerso==true){                      
                                modePerso=false;
                                cout<<"Caméra freefly"<<endl;
                            }
                            else{                      
                                modePerso=true;
                                cout<<"Caméra à hauteur fixe"<<endl;
                            }
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
                        case SDL_SCANCODE_RETURN :
                        {
                             if(modeAuto==true){                      
                                modeAuto=false;
                                maCamera.compteur=0;
                                cout<<"Caméra libre"<<endl;
                            }
                            else{                      
                                modeAuto=true;
                                cout<<"Caméra automatique"<<endl;
                            }
                            break;
                        }  
                        // Avancée de la caméra
                        case SDL_SCANCODE_UP :
                            if(modePerso==true){
                                maCamera.position = createVector(maCamera.position.x, maCamera.position.y, 12);
                            }
                            maCamera=deplacementAvant(maCamera);
			                break;
                        // Recul de la caméra
		                case SDL_SCANCODE_DOWN :
                            if(modePerso==true){
                                maCamera.position = createVector(maCamera.position.x, maCamera.position.y, 12);
                            }
			                maCamera=deplacementArriere(maCamera);
			                break;
                        // Déplacement vers la gauche
		                case SDL_SCANCODE_LEFT :
                            if(modePerso==true){
                                maCamera.position = createVector(maCamera.position.x, maCamera.position.y, 12);
                            }
			                maCamera=deplacementGauche(maCamera);
			                break;
                        // Déplacement vers la droite
		                case SDL_SCANCODE_RIGHT :
                            if(modePerso==true){
                                maCamera.position = createVector(maCamera.position.x, maCamera.position.y, 12);
                            }
			                maCamera=deplacementDroite(maCamera);
			                break;
                        case SDL_SCANCODE_PAGEUP :
			                maCamera=deplacementMonter(maCamera);
			                break;
                        case SDL_SCANCODE_PAGEDOWN :
			                maCamera=deplacementDescendre(maCamera);
			                break;
                        case SDL_SCANCODE_KP_1 :
                              maCamera=inEntree(maCamera);
                            break;
                        case SDL_SCANCODE_KP_2 :
                              maCamera=inSdb(maCamera);
                            break;
                        case SDL_SCANCODE_KP_3 :
                              maCamera=inSejour(maCamera);
                            break;
                        case SDL_SCANCODE_KP_4 :
                              maCamera=inCuisine(maCamera);
                            break;
                        case SDL_SCANCODE_KP_5 :
                              maCamera=inChambre(maCamera);
                            break;
                        case SDL_SCANCODE_KP_6 :
                              maCamera=inBalcon(maCamera);
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
