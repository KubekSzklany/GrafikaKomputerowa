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

#define tytul "GK2022 - Lab 2 - Maciaszek Damian"


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void linia1(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);
void linia2(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);
void linia3(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);
void okrag(int x, int y, int r, Uint8 R, Uint8 G, Uint8 B);
void elipsa(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B);

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();
void Funkcja6();
void Funkcja7();
void Funkcja8();
void Funkcja9();


void Funkcja1() {
    int R,G,B,C,M,Y,c,m,y,k;

    for(int yy=0;yy<wysokosc/2;yy++){
        for(int xx=0;xx<szerokosc/2;xx++){
            R = getPixel(xx,yy).r;
            G = getPixel(xx,yy).g;
            B = getPixel(xx,yy).b;

            C = 255 - R;
            M = 255 - G;
            Y = 255 - B;

            k = min(min(C,M), Y);
            c = C - k;
            m = M - k;
            y = Y - k;

            //zmiany
            setPixel(xx+szerokosc/2, yy+wysokosc/2, 255-k,255-k,255-k);
            k = 0;

            C = c + k;
            M = m + k;
            Y = y + k;

            R = 255 - C;
            G = 255 - M;
            B = 255 - Y;

            setPixel(xx+szerokosc/2, yy, R,G,B);
        }
    }

    SDL_UpdateWindowSurface(window);
}

//Funkcja9 -> Funkcja2 przed próbą konwersji YUV->RGB
void Funkcja2() {
    int R,G,B,Y, Cb,Cr;

    for(int yy=0;yy<wysokosc/2;yy++){
        for(int xx=0;xx<szerokosc/2;xx++){
            R = getPixel(xx,yy).r;
            G = getPixel(xx,yy).g;
            B = getPixel(xx,yy).b;

            Y = 0.299*R + 0.587*G + 0.114*B;
            Cb = -0.169*R - 0.331*G + 0.499*B + 128; // 0.499 i +128 (przesuniecie zeby było miedzy 0 a 128) żeby nie wychodzic poza zakresy (-)
            Cr = 0.499*R - 0.418*G - 0.0813*B + 128;


            //int BB, YY;
            //if(Cb>150)
            //    BB = 255;
            //else
            //    BB = 0;

            setPixel(xx+szerokosc/2,yy,Y,Y,Y);
            setPixel(xx,yy+wysokosc/2, 255-Cb,255-Cb,Cb);
            setPixel(xx+szerokosc/2, yy+wysokosc/2,Cr,255-Cr,255-Cr);

        }
    }
    SDL_UpdateWindowSurface(window);
}

void Funkcja3() {

    linia1(0,0,rand()%szerokosc, rand()%wysokosc,255,255,0);

    SDL_UpdateWindowSurface(window);
}

void Funkcja4() {

    int x = rand()%(szerokosc-100);
    int y = rand()%(wysokosc-100);
    linia2(x,y,x+rand()%100,y+rand()%100,255,255,0);


    SDL_UpdateWindowSurface(window);
}

void Funkcja5() {

    linia3(rand()%szerokosc,rand()%wysokosc,rand()%szerokosc,rand()%wysokosc,255,255,0);

    SDL_UpdateWindowSurface(window);
}

void Funkcja6() {

    okrag(rand()%szerokosc,rand()%wysokosc,rand()%100,255,255,255);

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

    int R,G,B,Y, Cb,Cr;

    for(int yy=0;yy<wysokosc/2;yy++){
        for(int xx=0;xx<szerokosc/2;xx++){
            R = getPixel(xx,yy).r;
            G = getPixel(xx,yy).g;
            B = getPixel(xx,yy).b;

            Y = 0.299*R + 0.587*G + 0.114*B;
            Cb = -0.169*R - 0.331*G + 0.499*B + 128; // 0.499 i +128 (przesuniecie zeby było miedzy 0 a 128) żeby nie wychodzic poza zakresy (-)
            Cr = 0.499*R - 0.418*G - 0.0813*B + 128;

            setPixel(xx+szerokosc/2,yy,Y,Y,Y);
            setPixel(xx,yy+wysokosc/2, Cb,Cb,Cb);
            setPixel(xx+szerokosc/2, yy+wysokosc/2,Cr,Cr,Cr);

        }
    }
    SDL_UpdateWindowSurface(window);
}

void linia1(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B) {

    setPixel(x1, y1, 255, 0, 0);
    setPixel(x2, y2, 255, 0, 192);

    int dx = x2;
    int dy = y2;

    int d = 0;

    int x = 0;
    int y = 0;

    setPixel(x,y,R,G,B);
    if (dx >= dy){
        d = 2*dy - dx;

        while(x<x2){
            if (d>=0){
                x++;
                y++;
                d = d+2*(dy-dx);
            }
            else{
                x++;
                d = d + 2*dy;
            }
            setPixel(x,y,R,G,B);
        }
    }
    else{
        d = 2*dx - dy;
        while (y < y2){
            if (d >= 0){
                y++;
                x++;
                d = d+2*(dx-dy);
            }
            else{
                y++;
                d = d + 2*dx;
            }
            setPixel(x,y,B,G,R);
        }
    }

    SDL_UpdateWindowSurface(window);
}


void linia2(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B) {

    setPixel(x1, y1, 255, 0, 0);
    setPixel(x2, y2, 255, 0, 192);

    int dx = x2-x1; //
    int dy = y2-y1; //

    int d = 0;

    int x = x1; //
    int y = y1; //

    setPixel(x,y,R,G,B);
    if (dx >= dy){
        d = 2*dy - dx;

        while(x<x2){
            if (d>=0){
                x++;
                y++;
                d = d+2*(dy-dx);
            }
            else{
                x++;
                d = d + 2*dy;
            }
            setPixel(x,y,R,G,B);
        }
    }
    else{
        d = 2*dx - dy;
        while (y < y2){
            if (d >= 0){
                y++;
                x++;
                d = d+2*(dx-dy);
            }
            else{
                y++;
                d = d + 2*dx;
            }
            setPixel(x,y,B,G,R);
        }
    }

    SDL_UpdateWindowSurface(window);
}


void linia3(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B) {

    setPixel(x1, y1, 255, 0, 0);
    setPixel(x2, y2, 255, 0, 192);

    int kx = 1;
    int ky = 1;

    int dx = x2-x1; //
    int dy = y2-y1; //

    if(dx<0){
        dx = x1-x2;
        kx = -1;
    }
    if (dy<0){
        dy = y1-y2;
        ky = -1;
    }

    int d = 0;

    int x = x1; //
    int y = y1; //

    setPixel(x,y,R,G,B);
    if (dx >= dy){
        d = 2*dy - dx;

        while(x != x2){
            if (d>=0){
                x+=kx;
                y+=ky;
                d = d+2*(dy-dx);
            }
            else{
                x+=kx;
                d = d + 2*dy;
            }
            setPixel(x,y,R,G,B);
        }
    }
    else{
        d = 2*dx - dy;
        while (y < y2){
            if (d >= 0){
                y+=ky;
                x+=kx;
                d = d+2*(dx-dy);
            }
            else{
                y+=ky;
                d = d + 2*dx;
            }
            setPixel(x,y,B,G,R);
        }
    }

    SDL_UpdateWindowSurface(window);
}


void okrag(int x, int y, int r, Uint8 R, Uint8 G, Uint8 B) {

    setPixel(x, y, 255, 0, 0);
    setPixel(x+r, y, 255, 0, 192);
    setPixel(x-r, y, 255, 0, 192);
    setPixel(x, y+r, 255, 0, 192);
    setPixel(x, y-r, 255, 0, 192);

    int xx = 0;
    int yy = r;

    int d = 0;

    setPixel(xx,yy,R,G,B);
    d = 3 - 2*r;

    while(xx<=yy){
        if(d<0){
            d = d+4*xx + 6;
            xx++;
        }
        else{
            d = d+4*(xx-yy) + 10;
            xx++;
            yy--;
        }
        setPixel(x+xx,y+yy,R,G,B);
        setPixel(x-xx,y+yy,R,G,B);
        setPixel(x+xx,y-yy,R,G,B);
        setPixel(x-xx,y-yy,R,G,B);

        setPixel(x+yy,y+xx,R,G,B);
        setPixel(x-yy,y+xx,R,G,B);
        setPixel(x+yy,y-xx,R,G,B);
        setPixel(x-yy,y-xx,R,G,B);
    }

    SDL_UpdateWindowSurface(window);
}


void elipsa(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B) {

    setPixel(x, y, 0, 255, 0);
    setPixel(x+a, y, 0, 255, 192);
    setPixel(x-a, y, 0, 255, 192);
    setPixel(x, y+b, 0, 255, 192);
    setPixel(x, y-b, 0, 255, 192);

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
