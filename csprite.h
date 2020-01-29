
#ifndef CSPRITE_H_
#define CSPRITE_H_

#define TRUE 1
#define FALSE 0
// CFrame representa un frame independiente de un sprite.
class CFrame{
    public:
        SDL_Surface *img; // para almacenar la superficie
        void Load(char *path); // cargar el grafico
        void Unload();// liberamos lo que se utiliz0 (recursos)
};
// La clase CSprite esta formada por un array de frames;
class CSprite{
    private:
        int posx, posy;
        int estado; // estado del frame actual
        int nframes; //num de frames
        int cont;
        
    public: //           SDL_Rect();  
        CFrame *sprite;
        CSprite(int nf); // constructor
        CSprite();       // constructor
        void Finalize(); // llama a unload para eliminar c/u de los frames del sprite
        void Addframe(CFrame frame);// anadimos frames a un sprite
        void Selframe(int nf);// seleccionamos el frame actual o el que queremos dibujar
        int frames() {return cont;}// nos regresa el num de frames del sprite actualmente
        void setx (int x) { posx = x;} // mover el sprite en x
        void sety (int y) { posy = y;} // mover el sprite en y
        void addx (int c) { posx += c;}// indicamos el desplazamiento del sprite en pantalla tomando como ref la situacion actual
        void addy (int c) { posy += c;}
        
        int getx() { return posx; }// posicion del sprite 
        int gety() { return posy; }
        int getw() { return sprite[estado].img->w; }// tam del sprite 
        int geth() { return sprite[estado].img->h; }
       
        void Draw(SDL_Surface *superficie);// dibujamos el sprite con la posicion y frame actual
        int Colision (CSprite sp);// nos permite conocer si el sprite hace contato o ha colisionado con otro sprite
};
#endif//:~



