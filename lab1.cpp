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

#define tytul "GK2022 - Lab 1 - Łukasz Pawlik"


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


// generuje losow kropki na całym ekranie
void Funkcja1() {

    for(int i = 0; i<10000; i++){
        setPixel(rand()%szerokosc, rand()%wysokosc, rand()%255, rand()%255, rand()%255);
    }

    SDL_UpdateWindowSurface(window);
}

// robi gradient góra dół
void Funkcja2() {

    for(int x=0;x<szerokosc; x++){
        for(int y=0; y<wysokosc; y++){
            setPixel(x,y,x/2,x/2,x/2);
        }
    }
    SDL_UpdateWindowSurface(window);

}

// wyciąga kolor z każdego pixela i rysuje w tym kolorze obrazek
void Funkcja3() {

    SDL_Color kolor;
    int R,G,B;

    for(int x=0; x<szerokosc/2;x++){
        for(int y=0; y<wysokosc/2; y++){
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            setPixel(x+szerokosc/2, y, R,0,0);
            setPixel(x, y+wysokosc/2, 0,G,0);
            setPixel(x+szerokosc/2, y+wysokosc/2, 0,0,B);
        }
    }

    SDL_UpdateWindowSurface(window);
}

// zamienia kolory miejscami
void Funkcja4() {

    SDL_Color kolor;
    int R,G,B;

    for(int x=0; x<szerokosc/2;x++){
        for(int y=0; y<wysokosc/2; y++){
            kolor = getPixel(x,y);
            R = getPixel(x,y).r;
            G = kolor.g;
            B = kolor.b;

            setPixel(x+szerokosc/2, y, R,B,G);
            setPixel(x, y+wysokosc/2, B,G,R);
            setPixel(x+szerokosc/2, y+wysokosc/2, G,R,B);
        }
    }

    SDL_UpdateWindowSurface(window);
}

// Robi jakieś szarosci
void Funkcja5() {

    SDL_Color kolor;
    int R,G,B;

    int BW1, BW2;

    for(int x=0; x<szerokosc/2;x++){
        for(int y=0; y<wysokosc/2; y++){
            kolor = getPixel(x,y);
            R = getPixel(x,y).r;
            G = kolor.g;
            B = kolor.b;
            BW1 = (R + G + B) / 3;
            BW2 = 0.299*R + 0.587*G + 0.114*B;  //nie odczuwamy każdego z tych kolorów tak samo!!
            setPixel(x+szerokosc/2, y, BW1,BW1,BW2);
            //setPixel(x, y+wysokosc/2, 0,BW,0);
            setPixel(x+szerokosc/2, y+wysokosc/2, BW2,BW2,BW2);
        }
    }

    SDL_UpdateWindowSurface(window);
}

#
void Funkcja6() {

    SDL_Color kolor;
    int R,G,B;

    int BW;

    for(int x=0; x<szerokosc/2;x++){
        for(int y=0; y<wysokosc/2; y++){
            kolor = getPixel(x,y);
            BW = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;

            setPixel(x+szerokosc/2, y, BW,BW,BW);

            if (BW>127)
            {
                setPixel(x+szerokosc/2, y+wysokosc/2, 255, 255, 255);
            }
            else{
                setPixel(x+szerokosc/2, y+wysokosc/2, 0, 0, 0);
            }
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja7() {

    SDL_Color kolor;

    float bledy[(szerokosc/2)+2][(wysokosc/2)+2];
    memset(bledy, 0, sizeof(bledy));

    int blad = 0;
    int przesuniecie = 1;
    int BW;

    for(int x=0; x<szerokosc/2;x++){
        for(int y=0; y<wysokosc/2; y++){
            kolor = getPixel(x,y);
            BW = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            setPixel(x+szerokosc/2, y, BW,BW,BW);

            BW += bledy[x+przesuniecie][y];

            if (BW>127)
            {
                setPixel(x+szerokosc/2, y+wysokosc/2, 255, 255, 255);
                blad = BW - 255;
            }
            else{
                setPixel(x+szerokosc/2, y+wysokosc/2, 0, 0, 0);
                blad = BW - 0;
            }

            if (BW>255) BW=255;
            if (BW<0) BW=0;
            setPixel(x,y+wysokosc/2, BW,BW,BW);

            bledy[x+przesuniecie+1][y  ] += (blad*7.0/16.0);
            bledy[x+przesuniecie+1][y+1] += (blad*1.0/16.0);
            bledy[x+przesuniecie  ][y+1] += (blad*5.0/16.0);
            bledy[x+przesuniecie-1][y+1] += (blad*3.0/16.0);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void Funkcja8() {

    SDL_Color kolor;

    float bledy[(szerokosc/2)+2][(wysokosc/2)+2];
    memset(bledy, 0, sizeof(bledy));

    int blad = 0;
    int przesuniecie = 1;
    int BW;

    for(int y=0; y<wysokosc/2;y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x,y);
            BW = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            setPixel(x+szerokosc/2, y, BW,BW,BW);

            BW += bledy[x+przesuniecie][y];

            if (BW>127)
            {
                setPixel(x+szerokosc/2, y+wysokosc/2, 255, 255, 255);
                blad = BW - 255;
            }
            else{
                setPixel(x+szerokosc/2, y+wysokosc/2, 0, 0, 0);
                blad = BW - 0;
            }

            if (BW>255) BW=255;
            if (BW<0) BW=0;
            setPixel(x,y+wysokosc/2, BW,BW,BW);

            bledy[x+przesuniecie+1][y  ] += (blad*7.0/16.0);
            bledy[x+przesuniecie+1][y+1] += (blad*1.0/16.0);
            bledy[x+przesuniecie  ][y+1] += (blad*5.0/16.0);
            bledy[x+przesuniecie-1][y+1] += (blad*3.0/16.0);
        }
    }
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
