#ifndef UTIL_H_
#define UTIL_H_

#define MAXBALAS 8
#define MAXMAP 400


class Jugador {
    
    private:
        int activo,
        x, y,
        vidas, time;

    public:
//        Jugador jugador();
        int getx() { return x; }
        int gety() { return y; }
        int getactivo() { return activo; }
        int gettime() { return time; }
        int getvidas() { return vidas; }
        
        void setx (int c) { x = c;} 
        void sety (int c) { y = c;} 
        void addx (int c) { x += c;}//despl del sprite en pantalla ref actual
        void addy (int c) { y += c;}        
        
        void setactivo (int x) { activo = x;} 
        void settime (int x) { time = x;}
        void addtime (int x) { time += x;}
        void setvidas (int x) { vidas = x;}
        void addvidas (int x) { vidas += x;}
};


class NaveEnemiga {
    
    private:
        int activo, x, y, dx, dy, tipo, estado, impactos, nframe;
        
    public:
//        NaveEnemiga enemigo(); // constructor
        
        int getx() { return x; }
        int gety() { return y; }
        int getactivo() { return activo; }
        int getdx(){return dx;}
        int getdy(){return dy;}
        int getestado(){return estado;}
        int gettipo(){return tipo;}
        int getimpactos(){return impactos;}
        int getnframe(){return nframe;}

        
        void setx(int c){x = c; }
        void sety(int c){y = c; }
        void addx(int c){x += c; }
        void addy(int c){y += c; }        
        
        void setactivo(int c){activo = c; }
        void setdx(int c){dx = c; }
        void setdy(int c){dy = c; }
        void setestado(int c){estado = c; }
        void addestado(int c){estado += c; }
        
        void settipo(int c){tipo = c;}
        void setimpactos(int c){impactos = c;}
        void setnframe(int c){nframe = c;}

};

class Disparo : public NaveEnemiga {

    private:
        int time;
    public:
        int gettime(){return time; }
        void settime(int c){ time = c; }
        void addtime(int c){ time += c;}
        
};

class Explosion{
    private:
        int activo, x, y, nframe;
    public:
        int getx() { return x; }
        int gety() { return y; }
        int getactivo() { return activo; }   
        int getnframe(){return nframe;} 
        
        void setx(int c){x = c; }
        void sety(int c){y = c; }
        void addx(int c){x += c; }
        void addy(int c){y += c; }
        void addactivo(int c){activo += c; }
        void setactivo(int c){activo = c; }
        void addnframe(int i){nframe += i; }
        void setnframe(int c){nframe = c;}
        
        // var globales
        

};


/* variables globales */

SDL_Surface *screen;
SDL_Rect rect;
CFrame fnave;
CFrame fmalo;
CFrame tile1;
CFrame tile2;
CFrame tile3;
CFrame tile4;

CFrame labala;
CFrame ex[6];
CFrame dis;
CFrame dis2;

CFrame fmalo1_1;

Jugador jugador;
NaveEnemiga enemigo;
NaveEnemiga enemy[7];

Disparo bala[MAXBALAS];
Disparo disp[MAXBALAS];
Explosion exp;
Explosion explod[7];

CSprite nave(1);
CSprite malo(1);
CSprite dispene(2);
CSprite malo1(5);
CSprite suelo[3];
CSprite mibala(1);
CSprite explode(8);

SDL_Joystick *joystick;

char mapa[401];
int joyx, joyy, estado=0;
int done=0, score=0;;
int indice, indice_in;
FILE *f;


Uint32 ini_milisegundos, fin_milisegundos, frametime;
int nmalos = 7, ciclos;
void Finaliza();
void Creaexplosion(int j);
void Creadispenemigo(int j);


#endif//:~
