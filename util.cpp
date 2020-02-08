
#include"util.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include <SDL/SDL_ttf.h>

    SDL_Surface *texto;
    TTF_Font *fuente;
    SDL_Color bgcolor,fgcolor;
    SDL_Rect rectangulo;


/* ******************************************************************************* */
/*se realiza el movimiento de los tipos de nave 1 y 0, y se realiza la reactivacion de nuestra nave principal una vez que ha perdido una vida*/

void Muevenave() {

    if( (jugador.getactivo()) == 2){
        jugador.addtime(-1);
        if(jugador.gettime() <= 0){
            jugador.settime(0);
            SDL_Delay( 50 );
            jugador.setactivo(1);
        }
    }
    
    if(jugador.getactivo() == 0){
        jugador.addtime(-1);
        if(jugador.gettime() <= 0){
            jugador.settime(50);
            if(jugador.getvidas() == 0) {
                jugador.setactivo(0);
            }
            else{
                jugador.setactivo(2);
                jugador.setx(320);
                jugador.sety(400);
            }
        }
    }


   
    /*se realiza el movimiendo de nuestras naves enemigas segun el tipo 0 ó 1 */
    for (int i=0; i<=3; i++){

        if(enemy[i].getactivo() == 1){
            enemy[i].setx(enemy[i].getx() + enemy[i].getdx());
            enemy[i].sety(enemy[i].gety() + enemy[i].getdy());
            
            //mov de tipo 0
            if(enemy[i].gettipo() == 0){
                if( (enemy[i].getestado() == 0) && (enemy[i].gety() > 240) ){
                    Creadispenemigo(i);
                    enemy[i].setdy(-3);
                    enemy[i].setdx(0);
                    enemy[i].setestado(1);
                }
            }
            /* desactivamos la nave enemiga si ya no esta visible o salio de la pantalla*/
            if( (enemy[i].gety() > 480) || (enemy[i].gety() < -50) ){
                enemy[i].setactivo(0);
            }
        }
    }
    
    
    // dibuja(movimiendo) los disparos enemigos
    for(int i=0; i <= 7; i++){
        if(disp[i].getactivo() == 1){
            disp[i].setx(disp[i].getx() + disp[i].getdx());
            disp[i].sety(disp[i].gety() + disp[i].getdy());
            if(disp[i].gety() > 480 ){/* desactivamos el disparo si salio de la pantalla*/
                disp[i].setactivo(0);
            }
        }
    }
    
      
}

/* ******************************************************************************* */
/*se realiza el desplazamiento de nuestros disparos a traves de la pantalla y se desactiva una vez que ha salido de la pantalla*/
void Muevebalas() {
    int i;
    for (i = 0; i <= MAXBALAS; i++) {
        // si la pos.X del desparo no es 0,
        // es una bala activa.
        if (bala[i].getx() != 0) {
            bala[i].addy(-5);
            // si el disparo sale de la pantalla la desactivamos
            if (bala[i].gety() < 0) {
                bala[i].setx(0);
            }
        }
    }
}

/* ******************************************************************************* */
/*se realiza el dibuja del mapa y nuestra naave principal, así mismo, se realiza la deteccion de colision entre nuestra nave principal y alguna nave enemiga del tipo 0 y 1, ademas de la deteccion de colision de los disparon, tanto enemigos como disparos de nuestra nave principal*/

void DrawScene(SDL_Surface *screen) {
    char msg[30], vidas[30];
    int i,j,x,y,t;
    // movimiento del scenario (scroll)
    indice_in += 2;
    if (indice_in>=64) {
        indice_in=0;
        indice-=10;
    }
    if (indice <= 0) {
        indice=MAXMAP-100; // si llegamos al final, empezamos de nuevo.
        indice_in=0;
    }
    //dibujar escenario
    for (i=0 ; i<10 ; i++) {
        for (j=0 ; j<10 ; j++) {
            t=mapa[indice+(i*10+j)];
            // calculo de la posición del tile
            x=j*64;
            y=(i-1)*64+indice_in;
            // dibujamos el tile
            suelo[t].setx(x);
            suelo[t].sety(y);
            suelo[t].Draw(screen);
        }
    }
    // dibuja avión
    if(jugador.getactivo() == 1){
        nave.setx(jugador.getx());
        nave.sety(jugador.gety());
        nave.Draw(screen);

    }
    
    /*nos ayuda para reactivar nuestraa nave una vez que ha perdido alguna vida*/
    if( (jugador.getactivo() == 2) && ( (jugador.gettime() % 2) == 0) ){
        nave.setx(jugador.getx());
        nave.sety(jugador.gety());
        nave.Draw(screen);
    }
    
    
    // dibuja a las naves enemigas
    for(i = 0; i <= 3; i++){
        if(enemy[i].getactivo() == 1){
            if(enemy[i].gettipo() == 0){// enemigo de tipo 0
                malo1.setx(enemy[i].getx());
                malo1.sety(enemy[i].gety());
                malo1.Selframe(enemy[i].getnframe());
                malo1.Draw(screen);
                if( (malo1.Colision(nave) == TRUE) && (jugador.getactivo() == 1)){
                    jugador.addvidas(-1);
                    //Creaexplosion(255);
                    jugador.settime(30);
                    
                    //exp.setactivo(1);
                    //Creaexplosion(255);
                    Creaexplosion(i);
                    Creaexplosion(255);
                    jugador.setactivo(0); // desactivar nuestra nave
                    SDL_Delay( 50 );
                    enemy[i].setactivo(0);
                    
                }
            }
            
            if(enemy[i].gettipo() == 1){// enemigos de tipo 1
                malo.setx(enemy[i].getx());
                malo.sety(enemy[i].gety());
                malo.Draw(screen);
                if( (malo.Colision(nave) == TRUE) && (jugador.getactivo() == 1) ){
                    jugador.addvidas(-1);
                    jugador.settime(30);
                    Creaexplosion(i);  // explosion para la nave enemiga
                    Creaexplosion(255);// explosion para nuestra nave
                    //
                    jugador.setactivo(0);
                    SDL_Delay( 50 );
                    enemy[i].setactivo(0);
                }
            }
        }
    }
        
    // dibuja nuestros disparos solo si nuestra nave esta activa

    for (i = 0; i <= MAXBALAS; i++) {
        if (bala[i].getx() != 0 && jugador.getactivo() == 1) {
            mibala.setx(bala[i].getx());
            mibala.sety(bala[i].gety());
            mibala.Draw(screen);
            
            for(int j=0; j <= 7; j++){
                if(enemy[j].getactivo() == 1){
                    switch(enemy[j].gettipo()){
                        case 0:
                            //comprobamos el impacto con la nave de tipo 1
                            malo1.setx(enemy[j].getx());
                            malo1.sety(enemy[j].gety());
                            if((mibala.Colision(malo1) == TRUE) && enemy[i].getactivo()==0){
                                Creaexplosion(j);
                                enemy[j].setactivo(0);
                                score += 10;
                                //mibala.setestado(0);
                            }
                            break;
                        case 1:
                            //comprobamos el impacto con la nave de tipo 1
                            malo.setx(enemy[j].getx());
                            malo.sety(enemy[j].gety());
                            if((mibala.Colision(malo) == TRUE) && (enemy[i].getactivo()==0)){
                                Creaexplosion(j);
                                enemy[j].setactivo(0);
                                score += 10;
                            }
                            break;    
                    }
                }
            }
        }
    }
    
   // dibujamos los dispparos enemigos
    for(i=0; i<=7; i++){
        if(disp[i].getactivo() == 1){
            dispene.setx(disp[i].getx());
            dispene.sety(disp[i].gety());
            disp[i].addtime(1);
            
            if(disp[i].gettime() >= 5){
                disp[i].settime(0);
                if(disp[i].getestado() == 0){
                    //dispene.Selframe(1);
                    disp[i].setestado(1);
                }else{
                    dispene.Selframe(0);
                    disp[i].setestado(0);
                }
            }
            dispene.Draw(screen);
            
            // revisamos si nos han dado
            if(dispene.Colision(nave) && jugador.getactivo() == 1){
                jugador.addvidas(-1);
                Creaexplosion(255);
                jugador.settime(30);
                jugador.setactivo(0);
            }   
        }
    }
    
    // dibujamos el score
    
    sprintf(msg, "Life: %d \t\t\tScore: %d",jugador.getvidas() ,score);
    texto = TTF_RenderText_Shaded(fuente,msg,fgcolor,bgcolor);
    rectangulo.y=5;
    rectangulo.x=210;
    rectangulo.w = texto->w;
    rectangulo.h = texto->h;
    SDL_SetColorKey(texto,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(texto->format,255,0,0));
    SDL_BlitSurface(texto,NULL,screen,&rectangulo);
    
    // dibuja las explosiones
    for(i=0; i <= 7; i++){
        if(explod[i].getactivo() == 1){
            explode.Selframe(explod[i].getnframe());
            explode.setx(explod[i].getx());
            explode.sety(explod[i].gety());
            explod[i].addnframe(1);
            explode.Draw(screen);
            if(explod[i].getnframe() > 7){
                explod[i].setactivo(0);
            }
        }
    }
    
    SDL_Flip(screen);
}

/* ******************************************************************************* */
/* se realiza la activacion de la explosion, puede suceder tanto para las naves enemigas y nuestra nave principal al cual le damos las coordenanas y el enemigo i que colisiona*/

void Creaexplosion(int j){
    int libre = -1;
    
    for(int i=0 ; i <= 7; i++){
        if(explod[i].getactivo() == 0) libre=i;
    }

    explod[libre].setactivo(1);
    explod[libre].setnframe(1);    
    if(libre >= 0){
        if(j != 255){
//            explod[libre].setactivo(1);
//            explod[libre].setnframe(0);
            explod[libre].setx(enemy[j].getx());
            explod[libre].sety(enemy[j].gety());
        }else{    
//            explod[libre].setactivo(1);
//            explod[libre].setnframe(0);
            explod[libre].setx(jugador.getx());
            explod[libre].sety(jugador.gety());
        }
    }  
}

/* ******************************************************************************* */

/*se crean los disparos de nuestra nave principal y se le da la coordenada segun la posicion de nuestra nave principal*/

void Creadisparo() {
    int libre = -1;
    // ¿Hay alguna bala libre?
    for (int i=0 ; i<=1 ; i++) {
        if (bala[i].getx() == 0) libre=i;
    }
    // Hay una bala
    if (libre>=0) {
        bala[libre].setx(nave.getx());
        bala[libre].sety(nave.gety()-15);
    }
}

/* ******************************************************************************* */

/* se crean las naves enemigas, suceden de dos tipos 1 y 0, kamikase y nave caza, ademas, se les da una coordenada aleatoria dentro de la pantalla, el numero de enemigos creados es de 7 */

void Creaenemigo(){
    int libre = -1;

    for(int i = 0; i <= nmalos; i++){
        if (enemy[i].getactivo() == 0) libre = i;
    }
    
    if(libre >= 0){
        enemy[libre].setactivo(1);
        enemy[libre].setnframe(0);
        enemy[libre].setx(rand());
        if(enemy[libre].getx() > 600){
            enemy[libre].setx( (int)enemy[libre].getx() % 600 );
        }
        enemy[libre].settipo(rand());
        if(enemy[libre].gettipo() >= 2){
            enemy[libre].settipo( (int)enemy[libre].gettipo() % 2 );
        }
        
        // avion tipo caza
        if(enemy[libre].gettipo() == 0){
            enemy[libre].sety(-30);
            enemy[libre].setdx(0);
            enemy[libre].setdy(5);
            enemy[libre].setestado(0);
        }
        
        
        //avion tipo kamikase
        if(enemy[libre].gettipo() == 1){
            enemy[libre].sety(-30);
            if(enemy[libre].getx() > nave.getx()){
                enemy[libre].setdx(-3);
            }else{
                enemy[libre].setdx(3);    
            }
            enemy[libre].setdy(5);
            enemy[libre].setestado(0);
        }
        
    }


}

/* ******************************************************************************* */

/*se realiza la creacion de los disparos enemigos, solo ocurre en la nave de tipo caza, ademas se le da la coordenada de la nave i que creara el disparo*/
void Creadispenemigo(int j){
    int libre = -1;
    
    for(int i=0; i <= 7; i++){
        if(disp[i].getactivo() == 0) libre=i;
    }
    
    if(libre >= 0){
        disp[libre].setactivo(1);
        if(enemy[j].getx() > nave.getx()){
            disp[libre].setdx(-3);
            
        }else{
            disp[libre].setdx(3);
        
        }
        disp[libre].setdy(3);
        disp[libre].setx(enemy[j].getx() + 30);
        disp[libre].sety(enemy[j].gety() + 20);
        disp[libre].setestado(0);
        disp[libre].settime(0);   
    }

}

/* ******************************************************************************* */

/*se realiza la activacion de nuestra nave principal(coordenadas y vidas), naves enemigas, tipo 0 y 1, se activan los disparos de nuestra nave principal y los disparos de nuestra nave enemiga tipo caza. Se inicializa el puntaje y mapa */

void Inicializa() {
    srand( (unsigned)time( NULL ) );
    int i,c;
    //TTF_Font *Font=NULL;
    
    
    jugador.setactivo(1);
    jugador.setvidas(3);// vidass al inicio del juego
    jugador.setx(300);
    jugador.sety(300);
        
    indice=MAXMAP-100;
    indice_in=0;
    
    // inicializamos el array de explociones
    for(i = 0; i <= 7; i++){
        explod[i].setactivo(0);
    }
    
    // incializamo el array de enemigos
    for (i=0; i <= nmalos; i++) {
        enemy[i].setactivo(0);
    }
    // Inicializamos el array de balas(nuetro jugador)
    for (i=0 ; i<=MAXBALAS ; i++) {
        bala[i].addx(0);
        bala[i].addy(0);
        //bala[i].setactivo(0);
    }
    
    // inicializamos el array de disparos enemigos
    for(i=0; i <= 7; i++){
        disp[i].setactivo(0);
    }
    /*para el color del msg de score*/    
    fgcolor.r=200; bgcolor.r=255;
    fgcolor.g=200; bgcolor.g=0;
    fgcolor.b=10;  bgcolor.b=0;

   
    if(TTF_Init() == 0) {
	    atexit(TTF_Quit);
    }
    fuente = TTF_OpenFont("ep.ttf", 20);// cargamos la fuente
    
    // Carga del mapa
    if((f=fopen("mapa3.MAP","r")) != NULL) {
        c=fread(mapa,MAXMAP,1,f);
        fclose(f);
    }
}

/* ******************************************************************************* */
/*se encarga de finalizar los sprites y eliminar*/
void Finaliza() {
    // finalizamos los sprites
    nave.Finalize();
    malo.Finalize();
    mibala.Finalize();
    suelo[0].Finalize();
    suelo[1].Finalize();
    suelo[2].Finalize();
    // cerramos el joystick
    if (SDL_JoystickOpened(0)) {
        SDL_JoystickClose(joystick);
    }
    explode.Finalize();
}

/* ******************************************************************************* */
/*se realiza la inicializacion de los sprites, se cargan los tiles de nuestra nave principal, nave enemiga y los tiles de disparo, asi como los tiles que dibujan la explosion*/

int InitSprites() {

    fnave.Load((char*)"imagen/nave.bmp");
    nave.Addframe(fnave);
    
    fmalo.Load((char*)"imagen/enemigo.bmp");// avion de tipo caza
    malo.Addframe(fmalo);
   
    fmalo1_1.Load((char*)"imagen/enemigo2.bmp");// avion de tipo kamikase
    malo1.Addframe(fmalo1_1);
   
    dis.Load((char*)"imagen/dotenemy.bmp");
    dispene.Addframe(dis);
    
    tile1.Load((char*)"imagen/tile0.bmp");// fondo principal
    suelo[0].Addframe(tile1);
    tile2.Load((char*)"imagen/planet3.bmp");
    suelo[1].Addframe(tile2);
    
    tile3.Load((char*)"imagen/planet11.bmp");
    suelo[2].Addframe(tile3);
    
    //tile4.Load((char*)"imagen/planet4.bmp");
    //suelo[3].Addframe(tile4);
    
    labala.Load((char*)"imagen/dot.bmp");
    mibala.Addframe(labala);
    
    ex[0].Load((char*)"imagen/explode1.bmp");
    explode.Addframe(ex[0]);
    ex[1].Load((char*)"imagen/explode2.bmp");
    explode.Addframe(ex[1]);
    ex[2].Load((char*)"imagen/explode3.bmp");
    explode.Addframe(ex[2]);
    ex[3].Load((char*)"imagen/explode4.bmp");
    explode.Addframe(ex[3]);
    ex[4].Load((char*)"imagen/explode5.bmp");
    explode.Addframe(ex[4]);
    ex[5].Load((char*)"imagen/explode6.bmp");
    explode.Addframe(ex[5]);
    ex[6].Load((char*)"imagen/explode7.bmp");
    explode.Addframe(ex[6]);
    
    return 0;
}

/* ******************************************************************************* */
/*util para que nuestro juego no se acelere o se ralentice en sistemas distintos, es decir, la velocidad del juego sera la misma en distintos equipos*/
void ResetTimeBase() {
    ini_milisegundos = SDL_GetTicks();
}

/* ******************************************************************************* */

/*igual que la de arriba (resettimebase)*/
int CurrentTime() {
    fin_milisegundos = SDL_GetTicks();
    return fin_milisegundos-ini_milisegundos;
}







