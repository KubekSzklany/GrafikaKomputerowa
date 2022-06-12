#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 512
#define wysokosc 340

#define tytul "GK2022 - Lab 3 - Maciaszek Damian"


struct krawedz{
    float x1;
    float y1;
    float x2;
    float y2;
};

krawedz wzorzec[] = {
    {30,10,10,30}, //AB
    {10,30,30,30}, //BC
    {30,30,30,60}, //CD
    {30,60,50,60}, //DE
    {50,60,50,30}, //EF
    {50,30,60,30}, //FG
    {60,30,60,10}, //GH
    {60,10,30,10}, //HA
};

krawedz mlotek[8];

void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);
void okrag(int x, int y, int r, Uint8 R, Uint8 G, Uint8 B);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

void inicjalizacja(){
    for(int i=0;i<8;i++){
        mlotek[i] = wzorzec[i];
    }
}

void rysuj(Uint8 R, Uint8 G, Uint8 B){
    for(int i=0;i<8;i++){
        linia(mlotek[i].x1, mlotek[i].y1,mlotek[i].x2, mlotek[i].y2, R,G,B);
    }

}

void przesuniecie(int px, int py){
    for(int i=0;i<8;i++){
        mlotek[i].x1 += px;
        mlotek[i].x2 += px;
        mlotek[i].y1 += py;
        mlotek[i].y2 += py;
    }
}

void skalowanie(float sx, float sy){
    for(int i=0;i<8;i++){
        mlotek[i].x1 *= sx;
        mlotek[i].x2 *= sx;
        mlotek[i].y1 *= sy;
        mlotek[i].y2 *= sy;
    }
}

void obrot(float kat){
    float rad = (kat*2*3.14159265358979323846)/360;

    for(int i=0;i<8;i++){
        float tempx1, tempx2, tempy1, tempy2;
        tempx1 = mlotek[i].x1;
        tempx2 = mlotek[i].x2;
        tempy1 = mlotek[i].y1;
        tempy2 = mlotek[i].y2;

        mlotek[i].x1 = tempx1*cos(rad) - tempy1*sin(rad);
        mlotek[i].x2 = tempx2*cos(rad) - tempy2*sin(rad);
        mlotek[i].y1 = tempy1*cos(rad) + tempx1*sin(rad);
        mlotek[i].y2 = tempy2*cos(rad) + tempx2*sin(rad);
    }
}

void scinanie(float SHx, float SHy=0){
    float tempX1, tempX2;

    for(int i=0;i<8;i++){
        tempX1 = mlotek[i].x1;
        tempX2 = mlotek[i].x2;

        mlotek[i].x1 += SHx * mlotek[i].y1;
        mlotek[i].y1 += SHy * tempX1;
        mlotek[i].x2 += SHx * mlotek[i].y2;
        mlotek[i].y2 += SHy * tempX2;
    }
}

bool porownajKolory(SDL_Color k1, SDL_Color k2){
    if(k1.r != k2.r)
        return false;
    if(k1.g != k2.g)
        return false;
    if(k1.b != k2.b)
        return false;

    return true;
}

void sianie(int x, int y, SDL_Color kK, SDL_Color kW){
    setPixel(x,y,kW.r, kW.g, kW.b);
    SDL_UpdateWindowSurface(window);
    SDL_Color kolor;

    kolor = getPixel(x-1, y);
    if ((!porownajKolory(kolor, kK) && (!porownajKolory(kolor,kW)))){
        sianie(x-1,y,kK,kW);
    }

    kolor = getPixel(x, y-1);
    if ((!porownajKolory(kolor, kK) && (!porownajKolory(kolor,kW)))){
        sianie(x,y-1,kK,kW);
    }

    kolor = getPixel(x+1, y);
    if ((!porownajKolory(kolor, kK) && (!porownajKolory(kolor,kW)))){
        sianie(x+1,y,kK,kW);
    }

    kolor = getPixel(x, y+1);
    if ((!porownajKolory(kolor, kK) && (!porownajKolory(kolor,kW)))){
        sianie(x,y+1,kK,kW);
    }

}

void sianie2(int x, int y, SDL_Color kB, SDL_Color kW){
    setPixel(x,y,kW.r, kW.g, kW.b);
    SDL_UpdateWindowSurface(window);
    SDL_Color kolor;

    kolor = getPixel(x-1, y);
    if (porownajKolory(kolor, kB)){
        sianie2(x-1,y,kB,kW);
    }

    kolor = getPixel(x, y-1);
    if (porownajKolory(kolor, kB)){
        sianie2(x,y-1,kB,kW);
    }

    kolor = getPixel(x+1, y);
    if (porownajKolory(kolor, kB)){
        sianie2(x+1,y,kB,kW);
    }

    kolor = getPixel(x, y+1);
    if (porownajKolory(kolor, kB)){
        sianie2(x,y+1,kB,kW);
    }

}

void Funkcja1() {
    inicjalizacja();
    rysuj(255,255,0);
    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {
    rysuj(0,0,0);
    przesuniecie(5,5);
    rysuj(rand()%255,rand()%255,rand()%255);

    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {
    rysuj(0,0,0);
    skalowanie(2.0,2.0);
    rysuj(rand()%255,rand()%255,rand()%255);

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {
    rysuj(0,0,0);
    obrot(30);
    rysuj(rand()%255,rand()%255,rand()%255);
    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {
    rysuj(0,0,0);
    scinanie(0.3);
    rysuj(rand()%255,rand()%255,rand()%255);

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {

    SDL_Color kolorKrawedzi = {255,255,0};
    SDL_Color kolorWypelnienia = {0,255,255};

    okrag(100,100,30,kolorKrawedzi.r, kolorKrawedzi.g, kolorKrawedzi.b);
    sianie(100,100, kolorKrawedzi, kolorWypelnienia);
    SDL_UpdateWindowSurface(window);
}

//Nowe funkcje w 8 i 9
void Funkcja7() {
    SDL_Color kolorWypelnienia = {255,255,255};

    okrag(100,100,30,128,128,128);

    SDL_Color kolorBazowy = getPixel(100,100);

    sianie2(100,100, kolorBazowy, kolorWypelnienia);

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {
    SDL_Color kolorKrawedzi = {255,255,0};
    SDL_Color kolorWypelnienia = {0,255,255};

    rysuj(kolorKrawedzi.r, kolorKrawedzi.g, kolorKrawedzi.b);
    float x_start = (mlotek[0].x1 + mlotek[6].x1)/2;
    float y_start = (mlotek[0].y1 + mlotek[6].y1)/2;
    sianie(x_start, y_start, kolorKrawedzi, kolorWypelnienia);

    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {
    SDL_Color kolorWypelnienia = {255,255,255};
    SDL_Color kolorKrawedzi = {255,255,0};

    rysuj(kolorKrawedzi.r, kolorKrawedzi.g, kolorKrawedzi.b);
    float x_start = (mlotek[0].x1 + mlotek[6].x1)/2;
    float y_start = (mlotek[0].y1 + mlotek[6].y1)/2;

    SDL_Color kolorBazowy = getPixel(x_start, y_start);

    sianie2(x_start, y_start, kolorBazowy, kolorWypelnienia);

    SDL_UpdateWindowSurface(window);
}

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B) {

    int d;

    int x = x1;
    int y = y1;

    int kx = 1;
    int ky = 1;

    int dx = x2-x1;
    int dy = y2-y1;

    if(dx<0) {
        kx = -1;
        dx  =x1-x2;
    }

    if(dy<0) {
        ky = -1;
        dy = y1-y2;
    }

    setPixel(x, y, R, G, B);

    if(dx >= dy) {
        d = 2*dy - dx;
        while (x != x2) {
            if (d >= 0) {
                d = d + 2*(dy-dx);
                x += kx;
                y += ky;
            }
            else {
                d = d + 2*dy;
                x+=kx;
            }
            setPixel(x, y, R, G, B);
        }
    }
    else {
        d= 2*dx - dy;
        while (y != y2) {
            if (d >= 0) {
                d = d + 2*(dx-dy);
                y += ky;
                x += kx;
            }
            else {
                d= d + 2*dx;
                y+=ky;
            }
            setPixel(x, y, R, G, B);
        }
    }

    SDL_UpdateWindowSurface(window);
}


void okrag(int x, int y, int r, Uint8 R, Uint8 G, Uint8 B) {

    int xx = 0;
    int yy = r;
    int d = 3 - 2*r;

    setPixel(x+xx, y+yy, R, G, B);
    setPixel(x-xx, y+yy, R, G, B);
    setPixel(x+xx, y-yy, R, G, B);
    setPixel(x-xx, y-yy, R, G, B);

    setPixel(x+yy, y+xx, R, G, B);
    setPixel(x-yy, y+xx, R, G, B);
    setPixel(x+yy, y-xx, R, G, B);
    setPixel(x-yy, y-xx, R, G, B);

    while (xx<=yy) {
        if(d < 0) {
            d = d + 4*xx + 6;
            xx++;
        }
        else {
            d = d + 4*(xx-yy) + 10;
            xx++;
            yy--;
        }
        setPixel(x+xx, y+yy, R, G, B);
        setPixel(x-xx, y+yy, R, G, B);
        setPixel(x+xx, y-yy, R, G, B);
        setPixel(x-xx, y-yy, R, G, B);

        setPixel(x+yy, y+xx, R, G, B);
        setPixel(x-yy, y+xx, R, G, B);
        setPixel(x+yy, y-xx, R, G, B);
        setPixel(x-yy, y-xx, R, G, B);
    }

    SDL_UpdateWindowSurface(window);
}



void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p1 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2) * bpp;
    Uint8 *p2 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2) * bpp;
    Uint8 *p3 = (Uint8 *)screen->pixels + (y*2) * screen->pitch + (x*2+1) * bpp;
    Uint8 *p4 = (Uint8 *)screen->pixels + (y*2+1) * screen->pitch + (x*2+1) * bpp;

    /* Ustawiamy wartość piksela, w zależnoœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p1 = pixel;
            *p2 = pixel;
            *p3 = pixel;
            *p4 = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p1 = pixel;
            *(Uint16 *)p2 = pixel;
            *(Uint16 *)p3 = pixel;
            *(Uint16 *)p4 = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p1[0] = (pixel >> 16) & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = pixel & 0xff;
                p2[0] = (pixel >> 16) & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = pixel & 0xff;
                p3[0] = (pixel >> 16) & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = pixel & 0xff;
                p4[0] = (pixel >> 16) & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = pixel & 0xff;
            } else {
                p1[0] = pixel & 0xff;
                p1[1] = (pixel >> 8) & 0xff;
                p1[2] = (pixel >> 16) & 0xff;
                p2[0] = pixel & 0xff;
                p2[1] = (pixel >> 8) & 0xff;
                p2[2] = (pixel >> 16) & 0xff;
                p3[0] = pixel & 0xff;
                p3[1] = (pixel >> 8) & 0xff;
                p3[2] = (pixel >> 16) & 0xff;
                p4[0] = pixel & 0xff;
                p4[1] = (pixel >> 8) & 0xff;
                p4[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p1 = pixel;
            *(Uint32 *)p2 = pixel;
            *(Uint32 *)p3 = pixel;
            *(Uint32 *)p4 = pixel;
            break;

        }
    }
}

void setPixelSurface(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<szerokosc*2) && (y>=0) && (y<wysokosc*2))
  {
    /* Zamieniamy poszczególne składowe koloru na format koloru piksela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informację ile bajtów zajmuje jeden piksel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres piksela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartość piksela, w zależności od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;
        }
    }
}

SDL_Color getPixel(int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)screen->pixels ;

        //przesunięcie względem y
        pPosition+=(screen->pitch*y*2) ;

        //przesunięcie względem x
        pPosition+=(screen->format->BytesPerPixel*x*2);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, screen->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}

SDL_Color getPixelSurface(int x, int y, SDL_Surface *surface) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<szerokosc) && (y>=0) && (y<wysokosc)) {
        //określamy pozycję
        char* pPosition=(char*)surface->pixels ;

        //przesunięcie względem y
        pPosition+=(surface->pitch*y) ;

        //przesunięcie względem x
        pPosition+=(surface->format->BytesPerPixel*x);

        //kopiujemy dane piksela
        memcpy(&col, pPosition, surface->format->BytesPerPixel);

        //konwertujemy kolor
        SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


void ladujBMP(char const* nazwa, int x, int y)
{
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Color kolor;
        for (int yy=0; yy<bmp->h; yy++) {
			for (int xx=0; xx<bmp->w; xx++) {
				kolor = getPixelSurface(xx, yy, bmp);
				setPixel(xx, yy, kolor.r, kolor.g, kolor.b);
			}
        }
		SDL_FreeSurface(bmp);
        SDL_UpdateWindowSurface(window);
    }

}


void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_UpdateWindowSurface(window);
}



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(tytul, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szerokosc*2, wysokosc*2, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
    return false;
    }
    SDL_UpdateWindowSurface(window);


    bool done = false;
    SDL_Event event;
    // główna pętla programu
    while (!done) {
        while (SDL_PollEvent(&event)) {
            // sprawdzamy czy pojawiło się zdarzenie
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;

                    // sprawdzamy czy został wciśnięty klawisz
                case SDL_KEYDOWN: {
                    // wychodzimy, gdy wciśnięto ESC
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    if (event.key.keysym.sym == SDLK_1)
                        Funkcja1();
                    if (event.key.keysym.sym == SDLK_2)
                        Funkcja2();
                    if (event.key.keysym.sym == SDLK_3)
                        Funkcja3();
                    if (event.key.keysym.sym == SDLK_4)
                        Funkcja4();
                    if (event.key.keysym.sym == SDLK_5)
                        Funkcja5();
                    if (event.key.keysym.sym == SDLK_6)
                        Funkcja6();
                    if (event.key.keysym.sym == SDLK_7)
                        Funkcja7();
                    if (event.key.keysym.sym == SDLK_8)
                        Funkcja8();
                    if (event.key.keysym.sym == SDLK_9)
                        Funkcja9();
                    if (event.key.keysym.sym == SDLK_a)
                        ladujBMP("obrazek1.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_s)
                        ladujBMP("obrazek2.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_d)
                        ladujBMP("obrazek3.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_f)
                        ladujBMP("obrazek4.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_g)
                        ladujBMP("obrazek5.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_h)
                        ladujBMP("obrazek6.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_j)
                        ladujBMP("obrazek7.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_l)
                        linia(rand()%szerokosc, rand()%wysokosc, rand()%szerokosc, rand()%wysokosc, 255, 128, 255);
                    if (event.key.keysym.sym == SDLK_o)
                        okrag(rand()%szerokosc, rand()%wysokosc, 10+rand()%200, 0, 255, 255);
                    if (event.key.keysym.sym == SDLK_b)
                        czyscEkran(0, 0, 10);
                    else
                        break;
                   }
            }
            if (done) break;
        }
    }

    if (screen) {
        SDL_FreeSurface(screen);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }


    SDL_Quit();
    return 0;
}
