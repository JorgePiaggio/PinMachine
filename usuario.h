#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define CANTOBJETIVOs 9


typedef struct
{
    char nombre[30];
    float MatrizPassword[2][7]; // Matriz generada por el password a desencriptar
    float MatrizAsignada[2][2]; // Matriz asignada aleatoriamente al usuario
    int objetivos[CANTOBJETIVOs]; // Arreglo de objetivos cumplidos
} usuarioArbol;


typedef struct
{
    char nombre[30];
    int Score; // Score por mapa
    char Fecha[70]; // fecha de la partida
} usuarioLista;


void InsertarOrdenado(usuarioArbol users[],int upos, usuarioArbol dato);
float Determinante2x2(float M[2][2]);
int VerificaInvsersa(float M[2][2]);
void MultiplicaMatrix(float M[2][2],float M2[2][7],float MR[2][7]);
void MatrizInversa(float M[2][2],float MI[2][2]);
int ConvertirLetraNumero(char letra);
void CodificarMatriz(char pass[14], float MEncriptada[2][7]);
void EncriptarPass(char pass[14],float MResultado[2][7], float MRandom[2][2]);
void DesencriptarPass(float M1[2][2],float MEncrip[2][7],float Mresult[2][7]);
int CompararMatrices(float M1[2][7],float M2[2][7]);



#endif // USUARIO_H_INCLUDED
