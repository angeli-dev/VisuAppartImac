#include "texture.h"

/*Texture createTexture(Texture tex, string fichierImage)
{

}*/

bool charger(Texture tex)
{
     // Chargement de l'image dans une surface SDL
    SDL_Surface *imageSDL = IMG_Load(tex.fichierImage.c_str());

    if(imageSDL == 0)
    {
        cout << "Erreur : " << SDL_GetError() << endl;
        return false;
    }

    // Génération de l'ID
    glGenTextures(1, &tex.id);

    // Verrouillage
    glBindTexture(GL_TEXTURE_2D, tex.id);


    // Déverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);

    
    // Format de l'image
    GLenum formatInterne(0);
    GLenum format(0);

    // Détermination du format et du format interne pour les images à 3 composantes
    if(imageSDL->format->BytesPerPixel == 3)
    {
        // Format interne
        formatInterne = GL_RGB;

        // Format pour 3 couleurs
        if(imageSDL->format->Rmask == 0xff)
            format = GL_RGB;
        else
            format = GL_BGR;
    }

    // Détermination du format et du format interne pour les images à 4 composantes
    else if(imageSDL->format->BytesPerPixel == 4)
    {
        formatInterne = GL_RGBA;

        // Format pour 4 couleurs
        if(imageSDL->format->Rmask == 0xff)
            format = GL_RGBA;   
        else
            format = GL_BGRA;
    }

    // Dans les autres cas, on arrête le chargement
    else
    {
        cout << "Erreur, format de l'image inconnu" << endl;
        SDL_FreeSurface(imageSDL);

        return false;
    }

    // Copie des pixels
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, imageSDL->w, imageSDL->h, 0, format, GL_UNSIGNED_BYTE, imageSDL->pixels);

    // Application des filtres
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Déverrouillage
    glBindTexture(GL_TEXTURE_2D, 0);

    // Fin de la fonction
    SDL_FreeSurface(imageSDL);
    return true;
}

GLuint getID(Texture tex) 
{
    return tex.id;
}

/*
void setFichierImage(Texture tex, string fichierImage)
{
    tex.fichierImage = fichierImage;
}*/