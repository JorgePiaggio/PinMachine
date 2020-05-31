#include "Arboles.h"

///FUNCIONES BASICAS ARBOLES usuario

nodoArbol* inicArbol(void)
{

    return NULL;
}

nodoArbol* crearArbol(usuarioArbol usuario )
{

    nodoArbol* nuevo= (nodoArbol*) malloc(sizeof(nodoArbol));
    nuevo->izq=NULL;
    nuevo->der=NULL;
    nuevo->dato=usuario;

    return nuevo;
}

nodoArbol* InsertarArbol(nodoArbol* arbolito, usuarioArbol user)
{


    if(arbolito==NULL)
    {

        arbolito=crearArbol(user);
    }
    else
    {
        if(strcmp(user.nombre,arbolito->dato.nombre)>0)
        {

            arbolito->der=InsertarArbol(arbolito->der,user);
        }
        else
        {

            arbolito->izq=InsertarArbol(arbolito->izq,user);
        }
    }

    return arbolito;
}

nodoArbol* BuscarArbol(nodoArbol* arbolito,char usuario[])
{
    nodoArbol* rta=NULL;
    if(arbolito!=NULL)
    {
        if(strcmp(usuario,arbolito->dato.nombre)==0)
        {
            rta=arbolito;
        }
        else
        {

            if(strcmp(usuario,arbolito->dato.nombre)>0)
            {
                rta=BuscarArbol(arbolito->der,usuario);
            }
            else
            {
                rta=BuscarArbol(arbolito->izq,usuario);
            }
        }

    }

    return rta;

}


nodoArbol* CrearArbolNivelado(usuarioArbol users[],int validos)
{


    nodoArbol* arbolito=inicArbol();

    if(validos!=0)
    {

        int indiceInicio= (validos/2);
        int i=indiceInicio;
        int j=indiceInicio;
        arbolito=InsertarArbol(arbolito,users[i]);
        i--;
        j++;
        if(validos%2==0)
        {


            while(i>0)
            {

                arbolito=InsertarArbol(arbolito,users[i]);
                arbolito=InsertarArbol(arbolito,users[j]);
                i--;
                j++;


            }

            if(i==0)
                arbolito=InsertarArbol(arbolito,users[i]);
        }
        else
        {
            while(i>=0)
            {

                arbolito=InsertarArbol(arbolito,users[i]);
                arbolito=InsertarArbol(arbolito,users[j]);
                i--;
                j++;
            }

        }

    }



    return arbolito;

}



void PasarDeArbolToArchivo(nodoArbol* arbolito, char nombre[])
{

    FILE* archivo=fopen(nombre,"wb");
    if(archivo && arbolito)
    {


        EscribirArbolEnArchivo(arbolito,archivo);



    }

    fclose(archivo);

}

void EscribirArbolEnArchivo(nodoArbol* arbolito, FILE* archivo)
{

    if(arbolito)
    {

        fwrite(&arbolito->dato,sizeof(usuarioArbol),1,archivo);
        EscribirArbolEnArchivo(arbolito->izq,archivo);
        EscribirArbolEnArchivo(arbolito->der,archivo);


    }

}

nodoArbol* BorrarNodoArbol(nodoArbol* arbol,char nombre[])
{

    if(arbol!=NULL)
    {
        nodoArbol* masDerecho;
        nodoArbol* masIzquiedo;

        if(strcmp(nombre,arbol->dato.nombre)==0)
        {

            if(arbol->izq==NULL && arbol->der==NULL)
            {

                free(arbol);
                arbol=NULL;

            }
            else
            {

                if(arbol->izq!=NULL)
                {
                    masDerecho=NodoMasDerecho(arbol->izq);
                    arbol->dato=masDerecho->dato;
                    arbol->izq=BorrarNodoArbol(arbol->izq,masDerecho->dato.nombre);

                }
                else
                {
                    if(arbol->der!=NULL)
                    {
                        masIzquiedo=NodoMasIzquierdo(arbol->der);
                        arbol->dato=masIzquiedo->dato;
                        arbol->der=BorrarNodoArbol(arbol->der,masIzquiedo->dato.nombre);
                    }
                }


            }

        }
        else
        {

            if(strcmp(nombre,arbol->dato.nombre)>0)
            {

                arbol->der=BorrarNodoArbol(arbol->der,nombre);

            }
            else
            {

                if(strcmp(nombre,arbol->dato.nombre)<0)
                {

                    arbol->izq=BorrarNodoArbol(arbol->izq,nombre);

                }

            }

        }





    }





    return arbol;

}

nodoArbol* NodoMasDerecho(nodoArbol* arbol)
{
    nodoArbol* rta;
    if(arbol->der!=NULL)
    {

        rta=NodoMasDerecho(arbol->der);

    }
    else
    {


        rta=arbol;

    }



    return rta;

}

nodoArbol* NodoMasIzquierdo(nodoArbol* arbol)
{
    nodoArbol* rta;
    if(arbol->izq!=NULL)
    {

        rta=NodoMasIzquierdo(arbol->izq);

    }
    else
    {


        rta=arbol;

    }



    return rta;

}



nodo* PasarArbolLista(nodoArbol* arbol,nodo* lista)
{
    usuarioLista nuevoUser;
    nodo* nuevo;

    if(arbol!=NULL)
    {
        strcpy(nuevoUser.nombre,arbol->dato.nombre);

        nuevo=crearnodo(nuevoUser);
        lista=agregarPrin(lista,nuevo);
        lista=PasarArbolLista(arbol->izq,lista);
        lista=PasarArbolLista(arbol->der,lista);

    }


    return lista;
}








