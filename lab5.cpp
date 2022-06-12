#include <exception>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
using namespace std;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

#define szerokosc 512
#define wysokosc 340

#define tytul "GK2022 - Lab 5 - Szklarczyk Jakub"


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

void linia(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B);
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


void Funkcja1()
{
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    char identyfikator[] = "JS";

    cout << "Zapisujemy plik 'obraz1.bin' uzywajac operatora <<" << endl;

    ofstream wyjscie("obraz1.bin");

    wyjscie << identyfikator;
    wyjscie << (Uint8)szerokoscObrazka;
    wyjscie << (Uint8)(szerokoscObrazka>>8);
    wyjscie << (Uint8)wysokoscObrazka;
    wyjscie << (Uint8)(wysokoscObrazka>>8);

    for(int y = 0; y < wysokoscObrazka; y++)
    {
        for(int x = 0; x < szerokoscObrazka; x++)
        {
            kolor = getPixel(x, y);
            wyjscie << kolor.r << kolor.g << kolor.b;
        }
    }
    wyjscie.close();

    SDL_UpdateWindowSurface(window);
}

void Funkcja2()
{
    SDL_Color kolor;

    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    char identyfikator[] = "JS";

    cout << "Zapisujemy plik 'obraz1.bin' uzywajac metody write()" << endl;

    ofstream wyjscie("obraz1.bin", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    for(int y = 0; y < wysokoscObrazka; y++)
    {
        for(int x = 0; x < szerokoscObrazka; x++)
        {
            kolor = getPixel(x, y);
            //wyjscie.write((char*)&kolor, sizeof(SDL_Color));
            wyjscie.write((char*)&kolor.r, sizeof(Uint8));
            wyjscie.write((char*)&kolor.g, sizeof(Uint8));
            wyjscie.write((char*)&kolor.b, sizeof(Uint8));
        }
    }

    wyjscie.close();

    SDL_UpdateWindowSurface(window);
}

void Funkcja3()
{
    SDL_Color kolor;

    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    char identyfikator[] = "  ";

    cout << "odczytujemy plik 'obraz1.bin' uzywajac metody read()" << endl;

    ifstream wejscie("obraz1.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;

    for(int y = 0; y < wysokoscObrazka; y++)
    {
        for(int x = 0; x < szerokoscObrazka; x++)
        {
            //wejscie.read((char*)&kolor, sizeof(Uint8)*3);
            wejscie.read((char*)&kolor.r, sizeof(Uint8));
            wejscie.read((char*)&kolor.g, sizeof(Uint8));
            wejscie.read((char*)&kolor.b, sizeof(Uint8));
            setPixel(x + szerokosc/2, y, kolor.r, kolor.g, kolor.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}

void Funkcja4()
{
    SDL_Color kolor;
    Uint8 Bw = 0;

    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    char identyfikator[] = "JS";

    cout << "Zapisujemy plik 'obraz2.bin' uzywajac metody write() - binarnie" << endl;

    ofstream wyjscie("obraz2.bin", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    for(int y = 0; y < wysokoscObrazka; y++)
    {
        for(int x = 0; x < szerokoscObrazka; x++)
        {
            kolor = getPixel(x, y);
            Bw = kolor.r*0.299+kolor.g*0.587+kolor.b*0.114;
            wyjscie.write((char*)&Bw, sizeof(Uint8));
        }
    }

    wyjscie.close();

    SDL_UpdateWindowSurface(window);
}

void Funkcja5()
{
    SDL_Color kolor;
    Uint8 Bw = 0;

    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    char identyfikator[] = "  ";

    cout << "odczytujemy plik 'obraz2.bin' uzywajac metody read() - binarnie" << endl;

    ifstream wejscie("obraz2.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;

    for(int y = 0; y < wysokoscObrazka; y++)
    {
        for(int x = 0; x < szerokoscObrazka; x++)
        {
            wejscie.read((char*)&Bw, sizeof(Uint8));
            setPixel(x + szerokosc/2, y, Bw, Bw, Bw);
        }
    }

    SDL_UpdateWindowSurface(window);
}

SDL_Color paleta[256];
int ileKolorow = 0;

int dodajKolor(SDL_Color kolor)
{
    if(ileKolorow > 255)
    {
        return -1;
    }

    int aktualnyKolor = ileKolorow;
    paleta[aktualnyKolor] = kolor;
    cout << aktualnyKolor << ": " << (int)kolor.r << ", " << (int)kolor.g << ", " << (int)kolor.b << endl;

    ileKolorow++;
    return aktualnyKolor;
}

bool porownajKolory(SDL_Color k1, SDL_Color k2)
{
    return (k1.r == k2.r) && (k1.g == k2.g) && (k1.b == k2.b);
}

int sprawdzKolor(SDL_Color kolor)
{
    if(ileKolorow > 0)
    {
        for(int i = 0; i < ileKolorow; i++)
        {
            if(porownajKolory(kolor, paleta[i]))
            {
                return i;
            }
        }
    }
    return dodajKolor(kolor);
}

void Funkcja6()
{
    SDL_Color kolor;
    ileKolorow = 0;

    for(int y = 0; y < wysokosc/2; y++)
    {
        for(int x = 0; x < szerokosc/2; x++)
        {
            kolor = getPixel(x, y);
            sprawdzKolor(kolor);
        }
    }

    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    char identyfikator[] = "JS";
    Uint8 kolory = ileKolorow;
    Uint8 wartosc = 0;

    cout << "Zapisujemy 8-bitowy plik 'obraz8.bin' uzywajac metody write()" << endl;

    ofstream wyjscie("obraz8.bin", ios::binary);

    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));

    wyjscie.write((char*)&kolory, sizeof(Uint8));

    for(int i = 0; i < kolory; i++)
    {
        wyjscie.write((char*)&paleta[i].r, sizeof(Uint8));
        wyjscie.write((char*)&paleta[i].g, sizeof(Uint8));
        wyjscie.write((char*)&paleta[i].b, sizeof(Uint8));
    }

    for(int y = 0; y < wysokoscObrazka; y++)
    {
        for(int x = 0; x < szerokoscObrazka; x++)
        {
            kolor = getPixel(x, y);
            wartosc = sprawdzKolor(kolor);
            wyjscie.write((char*)&wartosc, sizeof(Uint8));
        }
    }

    wyjscie.close();

    SDL_UpdateWindowSurface(window);
}

void Funkcja7()
{
    SDL_Color kolor;
    Uint8 wartosc = 0;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 kolory = 0;
    char identyfikator[] = "  ";

    cout << "Odczytujemy 8-bitowy plik 'obraz8.bin' uzywajac metody read()" << endl;

    ifstream wejscie("obraz8.bin");

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));

    wejscie.read((char*)&kolory, sizeof(Uint8));

    for(int i = 0; i < kolory; i++)
    {
        wejscie.read((char*)&paleta[i].r, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].g, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].b, sizeof(Uint8));
    }

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << szerokoscObrazka << endl;
    cout << "wysokosc: " << wysokoscObrazka << endl;
    cout << "ile kolorow: " << (int)kolory << endl;

    for(int y = 0; y < wysokoscObrazka; y++)
    {
        for(int x = 0; x < szerokoscObrazka; x++)
        {
            wejscie.read((char*)&wartosc, sizeof(Uint8));
            kolor = paleta[wartosc];
            setPixel(x + szerokosc/2, y, kolor.r, kolor.g, kolor.b);
        }
    }

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


void elipsa(int x, int y, int a, int b, Uint8 R, Uint8 G, Uint8 B) {

	int xx = 0;
    int yy = b;
    setPixel(x, y+yy, R, G, B);
    setPixel(x, y-yy, R, G, B);
    int d = 4*b*b - 4*a*a*b + a*a;

    while ( (xx*xx)<=(a*a*a*a/(a*a+b*b)) ) {
        if(d < 0) {
            d = d + 8*b*b*xx + 12*b*b;
            xx++;
        }
        else {
            d = d + 8*b*b*xx + 12*b*b - 8*a*a*yy + 8*a*a;
            xx++;
            yy--;
        }

        setPixel(x+xx, y+yy, R, G, B);
        setPixel(x-xx, y+yy, R, G, B);
        setPixel(x+xx, y-yy, R, G, B);
        setPixel(x-xx, y-yy, R, G, B);


    }

    d = 4*a*a - 4*b*b*a + b*b;
    yy = 0;
    xx = a;
    setPixel(x+xx, y, R, G, B);
    setPixel(x-xx, y, R, G, B);
    while ( (yy*yy)<=(b*b*b*b/(b*b+a*a)) ) {
        if(d < 0) {
            d = d + 8*a*a*yy + 12*a*a;
            yy++;
        }
        else {
            d = d + 8*a*a*yy + 12*a*a - 8*b*b*xx + 8*b*b;
            yy++;
            xx--;
        }

        setPixel(x+xx, y+yy, R, G, B);
        setPixel(x-xx, y+yy, R, G, B);
        setPixel(x+xx, y-yy, R, G, B);
        setPixel(x-xx, y-yy, R, G, B);


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
                    if (event.key.keysym.sym == SDLK_k)
                        ladujBMP("obrazek8.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_l)
                        linia(rand()%szerokosc, rand()%wysokosc, rand()%szerokosc, rand()%wysokosc, 255, 128, 255);
                    if (event.key.keysym.sym == SDLK_o)
                        okrag(rand()%szerokosc, rand()%wysokosc, 10+rand()%200, 0, 255, 255);
                    if (event.key.keysym.sym == SDLK_e)
                        elipsa(rand()%szerokosc, rand()%wysokosc, 10+rand()%200, 10+rand()%200, 255, 255, 128);


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
