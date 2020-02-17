
/*
Fredy Marin F POOE

g++ main.c `sdl-config --cflags --libs` -o main


Para compilar en terminal

g++ main.c `sdl-config --cflags --libs` -o main -lSDL_ttf (para la fuente)
./main

UAEM

desonses@gmail.com

*/

#include<stdio.h>
#include<stdlib.h>
#include<SDL.h>
//#include <SDL/SDL.h> 
#include"csprite.cpp"
#include"util.cpp"


int main(int argc, char *argv[]) {

    SDL_Event event;
    Uint8 *keys;
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0) {
        //printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
        fprintf(stderr, "No se pudo iniciar SDL: %s\n",SDL_GetError());
        return 1;
    }

    screen = SDL_SetVideoMode(640,480,24,SDL_HWSURFACE);
    if (screen == NULL) {
        fprintf(stderr,"No se puede inicializar el modo gráfico:%s \n",SDL_GetError());
        return 1;
    }
    
    atexit(SDL_Quit);
    Inicializa();
    InitSprites();
    
    while (done == 0) {

        // movemos el avion enemiga
        Muevenave();
        // movemos los disparos
        Muevebalas();
        // dibujamos el frame
        ResetTimeBase();
        //puntuacion();
        ciclos++;
        if(!(ciclos%50)){// frecuencia de creacion de las naves enemigas
            Creaenemigo();
        }
        
        
        DrawScene(screen);

        // consultamos el estado del teclado
        keys=SDL_GetKeyState(NULL);
        // consultamos el estado del joystick
        if((keys[SDLK_UP] || joyy < -10) && (jugador.gety() > 0)){
           jugador.addy(-5);
        }
        
        if((keys[SDLK_DOWN] || joyy > 10) && (jugador.gety() < 460)){
            jugador.addy(5);
        }
        
        if((keys[SDLK_LEFT] || joyx < -10) && (jugador.getx() > 0)) {
            jugador.addx(-5);
        }
        
        if((keys[SDLK_RIGHT] || joyx > 10) && (jugador.getx() < 620)) {
            jugador.addx(5);
        }
        if (keys[SDLK_LSHIFT]) {
            Creadisparo();
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {done=1;}
            if (event.type == SDL_KEYDOWN || event.type == SDL_JOYBUTTONDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    done=1;
                }
            }
        
        do{// control del tiempo ms
            frametime = CurrentTime();
        }while(frametime < 30);
            
        }
    }
    
    Finaliza();
    return 0;

}//:~



