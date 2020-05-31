#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "listas.h"




typedef struct _nodoArbol
{
    usuarioArbol dato;
    struct _nodoArbol * izq;
    struct _nodoArbol * der;
} nodoArbol;






///FUNCIONES BASICAS ARBOLES usuario
nodoArbol* inicArbol(void);
nodoArbol* crearArbol(usuarioArbol );
nodoArbol* InsertarArbol(nodoArbol*,usuarioArbol);
nodoArbol* BuscarArbol(nodoArbol*,char name[]);
nodoArbol* CrearArbolNivelado(usuarioArbol users[],int validos);
nodoArbol* BorrarNodoArbol(nodoArbol* arbol,char nombre[]);
nodoArbol* NodoMasDerecho(nodoArbol* arbol);
nodoArbol* NodoMasIzquierdo(nodoArbol* arbol);
nodo* PasarArbolLista(nodoArbol* arbol,nodo* lista);
void PasarDeArbolToArchivo(nodoArbol* arbolito, char nombre[]);
void EscribirArbolEnArchivo(nodoArbol* arbolito, FILE* archivo);







#endif // ARBOLES_H_INCLUDED
