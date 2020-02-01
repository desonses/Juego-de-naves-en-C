//{o}

//#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "csprite.h"



void CFrame::Load(char *path) {
    img=SDL_LoadBMP(path);// caraga la superficie desde un archivo BMP
    
/* se establece la clave de color en una superficie (pixel transparente) */
    SDL_SetColorKey(img,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(img->format,0,255,255));
    img=SDL_DisplayFormat(img);
}

/*util para eliminar los sprites de memoria*/
void CFrame::Unload(){
    SDL_FreeSurface(img);// se libera los sprites
}

/*constructor para varios sprites y obtener una aminacion */
CSprite::CSprite(int nf) {

    sprite=new CFrame[nf];// crea un sprite que contendra varios frames
    nframes=nf;
    cont=0;
}

/*constructor para animacion de varios sprites*/
CSprite::CSprite() {
int nf=1;
    sprite=new CFrame[nf];// crea un sprite con un solo frame
    nframes=nf;
    cont=0;
}

/* eliminamos los sprites que se hayan cargado*/
void CSprite::Finalize() {
    for (int i=0 ; i<=nframes-1 ; i++) sprite[i].Unload();
}


/* anadimos frames y llevamos un conteo*/
void CSprite::Addframe(CFrame frame) {
    if (cont<nframes) {
        sprite[cont]=frame;
        cont++;
    }
}

/*selecciona el sprite actual*/
void CSprite::Selframe(int nf) {
    if (nf<=nframes) {
        estado=nf;
    }
}

/*carga los sprites en pantalla*/
void CSprite::Draw(SDL_Surface *superficie) {
    SDL_Rect dest;
    dest.x=posx;
    dest.y=posy;
    
    /* Vamos a usarla para copiar el grafico que hemos cargado anteriormente en la superficie image en la superficie visible (screen), es decir, para mostrar el grafico en la pantalla. */
    SDL_BlitSurface(sprite[estado].img,NULL,superficie,&dest);
}


/*se realiza la deteccion de colisiones entre los sprites, el tipo de deteccion es por rectagulo*/
int CSprite::Colision(CSprite sp) {
int w1,h1,w2,h2,x1,y1,x2,y2;

    w1=getw();// ancho del sprite1
    h1=geth();// alto del sprite1
    x1=getx();// ancho del sprite2
    y1=gety();// alto del sprite2
    w2=sp.getw(); // pos.x del sprite1
    h2=sp.geth(); // pos.y del sprite1
    x2=sp.getx(); // pos.x del sprite2
    y2=sp.gety(); // pos.y del sprite2

    if (((x1+w1)>x2)&&((y1+h1)>y2)&&((x2+w2)>x1)&&((y2+h2)>y1)) {
        return TRUE;
    } 
    else {
        return FALSE;
    }

}








