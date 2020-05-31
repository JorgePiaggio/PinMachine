#ifndef JUGABILIDAD_H_INCLUDED
#define JUGABILIDAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "Arboles.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#define ANCHO 800
#define ALTO 600
#define RADIOP 10
#define ANCHOREBOTADOR 70
#define FPS 150.0
#define ANCHORESORTE 18
#define CANTOBJETOSANIMADOS 2
#define CANTMAPAS 2
#define CANTSOUNDS 13
#define CANTMSJs 9


typedef struct
{

    nodo* lista; //lista con scores de usuarios
    // el indice del arreglo indica el numero de mapa

} scoreMapas;

typedef struct
{
    float x;
    float y;
    float velocidad;
    float dx;
    float dy;
} pelota;

typedef struct
{
    int x;
    int y;
    int region;
} rebotadores;

typedef struct
{
    int x;
    int y;
    int region;
} reaccionarios;

typedef struct
{
    int x;
    int y;
    float angulo;
    int derecha;    ///0 izquierda, 1 derecha
} paletas;

typedef struct
{
    int xtope;
    int ytope;
    float anguloTope;
    int fuerza;
    int x;
    int y;
    float angulo;
} lanzador;

typedef struct
{
    int x;
    int y;
    int region;
} target;

typedef struct
{
    int x;
    int y;
    float region;
    int huecox;
    int huecoy;
    int salidax;
    int saliday;
} spin;

typedef struct
{
    int x;
    int y;
    float angulo;
    int limiteMaX;
    int limiteMin;
    int velocidad;
} bloque;

typedef struct
{
    int  cantidadRebotadores;
    rebotadores rebotador[5];
    int cantidadReaccionarios;
    reaccionarios reaccionario[5];
    int cantidadPaletas;
    paletas paleta[5];
    bloque barreras[5];
    int cantidadBarreras;
    target Blancos[5];
    int cantidadBlancos;
    spin Ruleta;
    pelota bola;
    int score;
    lanzador resorte;
    ALLEGRO_BITMAP *fondo;
    ALLEGRO_BITMAP *fondoBonus;
    ALLEGRO_BITMAP *paredes;
    ALLEGRO_BITMAP *paredesBonus;
    int limiteInferior;
    int limiteSuperior;
} mapaFlipper;


nodoArbol* sesion (scoreMapas ADS[],nodoArbol* arbolUser);
bool Inicializar();
void juegoNuevo(mapaFlipper *actual,nodoArbol** arbolUsers, int, ALLEGRO_DISPLAY *buffer, ALLEGRO_BITMAP *pantalla, ALLEGRO_EVENT_QUEUE *colaeventos, ALLEGRO_EVENT *evento, ALLEGRO_FONT *metal1,ALLEGRO_FONT *metal2,ALLEGRO_MIXER *musicMixer,ALLEGRO_VOICE *voice, nodoArbol*, scoreMapas ADS[], char nameusr[],ALLEGRO_SAMPLE_INSTANCE*eff[],ALLEGRO_SAMPLE_INSTANCE*,ALLEGRO_MONITOR_INFO info);
void CargarMapas(mapaFlipper *actual, int flagmapas,ALLEGRO_MONITOR_INFO info);
void DireccionBola(mapaFlipper *actual, float, float);
int Colision(ALLEGRO_BITMAP* pelota,ALLEGRO_BITMAP* buffer,mapaFlipper *actual,ALLEGRO_COLOR* colorbuffer,float* xchoque, float* ychoque, int a[],ALLEGRO_SAMPLE_INSTANCE *eff[],int flagmapas);
int detectarObjetoColisionado (mapaFlipper *actual, float xcolision, float ycolision, int a[],ALLEGRO_SAMPLE_INSTANCE *eff[]);
int AnimarRebotador(mapaFlipper *actual, int contarAnimado[],int a[],int);
int AnimarReactor(mapaFlipper *actual, int contarAnimado[], int indice[], int validos);
int AgregarColaAnimacion( int objeto,int elemento,int a[],int cont[],int validos);
void acercaDeLasColisionesEntrePelotaYPaleta(mapaFlipper *actual,float xcolision,float ycolision,int numPaleta);
void FuerzaResorte(mapaFlipper *actual);
void RestaurarPosicionBola(mapaFlipper* actual,int, int,int,int flagmapas);
void scratch(ALLEGRO_BITMAP*img, int i,ALLEGRO_MONITOR_INFO info);
void Tilt(mapaFlipper* actual);
void MostrarTilt(ALLEGRO_FONT*,ALLEGRO_BITMAP*,ALLEGRO_MONITOR_INFO info);
void mostrarMapa(mapaFlipper *actual, ALLEGRO_BITMAP* bola, ALLEGRO_BITMAP*resorte[8],ALLEGRO_BITMAP* rebotador,ALLEGRO_BITMAP*tope,ALLEGRO_BITMAP*tope2,ALLEGRO_BITMAP*reaccionario,ALLEGRO_BITMAP*reaccionario2,ALLEGRO_BITMAP*paleta, ALLEGRO_FONT* metal1, ALLEGRO_FONT* metal2, int indiceResorte, char scoreString[],int vidas, int flag,ALLEGRO_BITMAP* barrera,ALLEGRO_BITMAP* target,ALLEGRO_BITMAP* ruleta, ALLEGRO_BITMAP* salida,int, ALLEGRO_BITMAP*,ALLEGRO_BITMAP* msj[],int,ALLEGRO_MONITOR_INFO info );
void AgregarScoresUsuario(char nameUser[30],scoreMapas ADS[],int score, int flagmap);
void MoverBarrera(mapaFlipper *actual, int i, int orientacion, int*) ;
void cortarSample(ALLEGRO_SAMPLE_INSTANCE* f[]);

#endif // JUGABILIDAD_H_INCLUDED
