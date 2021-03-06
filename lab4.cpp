#include <exception>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 512
#define wysokosc 340

#define tytul "GKiM2021 - Lab 4 - Kaczyński Łukasz"


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B) {

    int dx{x2-x1},dy{y2-y1},d{0},x{x1},y{y1},kx{1},ky{1};

    if(dx<0){
        dx=x1-x2;
        kx=-1;
    }
    if(dy<0){
        dy=y1-y2;
        ky=-1;
    }
    setPixel(x,y,R,G,B);

    if(dx>=dy){
        d=2*dy-dx;
        while(x!=x2){
            if(d>=0){
                d=d+2*(dy-dx);
                x+=kx;
                y+=ky;
            }
            else{
                d=d+2*dy;
                x+=kx;
            }
            setPixel(x,y,R,G,B);
        }
    }
    else{
        d=2*dx-dy;
        while(y!=y2){
            if(d>=0){
                d=d+2*(dx-dy);
                y+=ky;
                x+=kx;
            }
            else{
                d=d+2*dx;
                y+=ky;
            }
            setPixel(x,y,R,G,B);
        }
    }
}

void okrag(int x, int y, int r, Uint8 R, Uint8 G, Uint8 B) {

    setPixel(x, y, R,G,B);
    setPixel(x+r, y,  R,G,B);
    setPixel(x-r, y,  R,G,B);
    setPixel(x, y+r,  R,G,B);
    setPixel(x, y-r,  R,G,B);

    int xx{0},yy{r},d{3-2*r};

    setPixel(x+xx,y+yy,R,G,B);
    linia(x,y,x+xx,y+yy,R,G,B);

    while(xx<=yy){
        if(d<0){
            d=d+4*xx+6;
        }
        else{
            d=d+4*(xx-yy)+10;
        }
        setPixel(x+xx,y+yy,R,G,B);
        linia(x,y,x+xx,y+yy,R,G,B);
        setPixel(x-xx,y+yy,R,G,B);
        linia(x,y,x-xx,y+yy,R,G,B);
        setPixel(x+xx,y-yy,R,G,B);
        linia(x,y,x+xx,y-yy,R,G,B);
        setPixel(x-xx,y-yy,R,G,B);
        linia(x,y,x-xx,y-yy,R,G,B);

        setPixel(x+yy,y+xx,R,G,B);
        linia(x,y,x+yy,y+xx,R,G,B);
        setPixel(x-yy,y+xx,R,G,B);
        linia(x,y,x-yy,y+xx,R,G,B);
        setPixel(x+yy,y-xx,R,G,B);
        linia(x,y,x+yy,y-xx,R,G,B);
        setPixel(x-yy,y-xx,R,G,B);
        linia(x,y,x-yy,y-xx,R,G,B);
        if(d<0){
           xx++;
        }
        else{
           xx++;
           yy--;
        }
    }
}

void Funkcja1() {

    int R,G,B;
    for(int x=0;x<szerokosc/6+1;x++){
        for(int y=0;y<wysokosc;y++){
            G=0+x/2;
            setPixel(x,y,255,G*6,0);
        }
    }
    for(int x=szerokosc/6+1;x<szerokosc/6*2+1;x++){
        for(int y=0;y<wysokosc;y++){
            R=255-x/2;
            setPixel(x,y,R*6,255,0);
        }
    }
    for(int x=szerokosc/6*2+1;x<szerokosc/6*3+2;x++){
        for(int y=0;y<wysokosc;y++){
            B=0+x/2;
            setPixel(x,y,0,255,B*6);
        }
    }
    for(int x=szerokosc/6*3;x<szerokosc/6*4;x++){
        for(int y=0;y<wysokosc;y++){
            G=255-x/2;
            setPixel(x,y,0,G*6,255);
        }
    }
    for(int x=szerokosc/6*4;x<szerokosc/6*5;x++){
        for(int y=0;y<wysokosc;y++){
            R=0+x/2;
            setPixel(x,y,R*6,0,255);
        }
    }
    for(int x=szerokosc/6*5;x<szerokosc;x++){
        for(int y=0;y<wysokosc;y++){
            B=255-x/2;
            setPixel(x,y,255,0,B*6);
        }
    }


    SDL_UpdateWindowSurface(window);
}

void Funkcja2() {

    SDL_Color kolor;
    int R{},G{},B{},bladR{},bladG{},bladB{},R2{},G2{},B2{},przes{1};
    float bledyR[(szerokosc/2)+2][(wysokosc/2)+1];
    float bledyG[(szerokosc/2)+2][(wysokosc/2)+1];
    float bledyB[(szerokosc/2)+2][(wysokosc/2)+1];
    memset(bledyR,0,sizeof(bledyR));
    memset(bledyG,0,sizeof(bledyG));
    memset(bledyB,0,sizeof(bledyB));
    for(int x=0;x<szerokosc/2;x++){
        for(int y=0;y<wysokosc/2;y++){
            kolor=getPixel(x,y);
            R=kolor.r;
            G=kolor.g;
            B=kolor.b;

            R2=kolor.r;
            G2=kolor.g;
            B2=kolor.b;

            R2+=bledyR[x+przes][y];
            G2+=bledyG[x+przes][y];
            B2+=bledyB[x+przes][y];

            setPixel(x,y+wysokosc/2,R,G,B);

            if(R>127){
                R=255;
            }else{
                R=0;
            }
            if(G>127){
                G=255;
            }else{
                G=0;
            }
            if(B>127){
                B=255;
            }else{
                B=0;
            }
            setPixel(x+szerokosc/2,y,R,G,B);

            if(R2>127){
                bladR=R2-255;
                R2=255;
            }else{
               bladR=R2;
                R2=0;
            }
            if(G2>127){
                bladG=G2-255;
                G2=255;

            }else{
                bladG=G2;
                G2=0;

            }
            if(B2>127){
                bladB=B2-255;
                B2=255;

            }else{
                bladB=B2;
                B2=0;

            }
            setPixel(x+szerokosc/2,y+wysokosc/2,R2,G2,B2);

            bledyR[x+przes+1][y]+=(bladR*7.0/16.0);
            bledyR[x+przes-1][y+1]+=(bladR*3.0/16.0);
            bledyR[x+przes][y+1]+=(bladR*5.0/16.0);
            bledyR[x+przes+1][y+1]+=(bladR*1.0/16.0);

            bledyG[x+przes+1][y]+=(bladG*7.0/16.0);
            bledyG[x+przes-1][y+1]+=(bladG*3.0/16.0);
            bledyG[x+przes][y+1]+=(bladG*5.0/16.0);
            bledyG[x+przes+1][y+1]+=(bladG*1.0/16.0);

            bledyB[x+przes+1][y]+=(bladB*7.0/16.0);
            bledyB[x+przes-1][y+1]+=(bladB*3.0/16.0);
            bledyB[x+przes][y+1]+=(bladB*5.0/16.0);
            bledyB[x+przes+1][y+1]+=(bladB*1.0/16.0);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    int y1{},x1{},x2{},y2{340};
    for(y1=0;y1<szerokosc;){
        linia(x1,y1,x2,y2,255,255,255);
        y1+=10;
        x2+=15;
    }
    y1=0;
    x1=512;
    y2=340;
    x2=512;
    for(y1=0;y1<szerokosc;){
        linia(x1,y1,x2,y2,255,255,0);
        y1+=10;
        x2-=15;
    }
    y1=340;
    x1=512;
    y2=0;
    x2=512;
    for(y1=340;y1>0;){
        linia(x1,y1,x2,y2,255,0,255);
        y1-=10;
        x2-=15;
    }
    y1=340;
    x1=0;
    y2=0;
    x2=0;
    for(y1=340;y1>0;){
        linia(x1,y1,x2,y2,0,0,255);
        y1-=10;
        x2+=15;
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {
    int ile = 1;
    for (int i=0; i<ile; i++) {
        okrag(rand()%szerokosc, rand()%wysokosc, rand()%50+10,  rand()%255, rand()%255, rand()%255);
        }

    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

    //...

    SDL_UpdateWindowSurface(window);
}

void Funkcja9() {

    //...

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
    while (SDL_WaitEvent(&event)) {
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
                if (event.key.keysym.sym == SDLK_b)
                    czyscEkran(0, 0, 10);
                else
                    break;
               }
        }
        if (done) break;
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
