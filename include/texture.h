#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <iostream>
#include <string>

using namespace std;


// Structure Texture
typedef struct {    
    GLuint id=0;
    string fichierImage;
}Texture;

bool charger(Texture texture);
//void setFichierImage(string fichierImage);
GLuint getID(Texture texture);

#endif