#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"


typedef struct _nodo
{
    usuarioLista dato;
    struct _nodo * siguiente;
} nodo;



// FUNCIONES ELEMENTALES

nodo * iniclista(nodo *);
nodo * crearnodo(usuarioLista );
nodo * agregarPrin(nodo *, nodo *);
nodo * agregarFinal(nodo * lista, nodo * nuevoNodo);
nodo * buscarUltimo(nodo * lista);
nodo * borrarNodo(char nombre[30], nodo * lista);
nodo * agregarEnOrden(nodo * lista, nodo * nuevoNodo);
nodo * borrarTodaLaLista(nodo * lista) ;
nodo * subprogramaBusquedaDeUnNodo(nodo * lista);
nodo * buscarNodo(char nombre[], nodo * lista);

//FUNCIONES RECURSIVAS

void recorrerYmostrarRecursivo(nodo * lista);
void MostrarParesRecursivo(nodo* lista);
nodo* InvertirListaRecursivo(nodo *lista);
nodo* BorrarNodoRecursivo(nodo* lista, char nombre[]);
nodo* InsertarNodoRecursivo(nodo* lista, nodo* nuevo);



#endif // LISTAS_H_INCLUDED
