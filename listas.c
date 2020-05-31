#include "listas.h"
nodo * iniclista(nodo * lista)
{

    lista=NULL;

    return lista;
}

nodo * crearnodo(usuarioLista dato )
{
//crea la variable en memoria de tamaño nodo
    nodo * aux=(nodo *) malloc(sizeof(nodo));
//asigna dato
    aux->dato=dato;
//asigna direccion nula a siguiente
    aux->siguiente=NULL;


    return aux;
}


nodo * agregarPrin(nodo *lista, nodo *nuevo)
{

    if(lista==NULL)
    {
        lista=nuevo; //si esta vacia asigno la nueva directamente
    }
    else
    {
        nuevo->siguiente=lista; //sino esta vacia lo asigno a siguiente
        lista=nuevo;


    }

    return lista;
}

nodo * buscarNodo(char nombre[], nodo * lista)

{
    nodo * seg;
    seg = lista;

    while ((seg != NULL) && strcmp (seg->dato.nombre,nombre)!=0)
    {
        seg=seg->siguiente;
    }

    return seg;
}

nodo * buscarUltimo(nodo * lista)
{

    nodo * seg=lista;
    if(seg!=NULL)  // me aseguro que no sea nulo
    {
        while(seg->siguiente!=NULL)
        {

            seg=seg->siguiente; // se mueve al siguiente


        }


    }
    return seg;

}




nodo * agregarFinal(nodo * lista, nodo * nuevo)
{

    if(lista==NULL)
    {

        lista=nuevo;

    }
    else
    {

        nodo *ultimo=buscarUltimo(lista); // busca la ultima posicion de memoeria en la lista
        ultimo->siguiente=nuevo; // le asigna a siguiente el nuevo nodo

    }


    return lista;

}


nodo * borrarNodo(char nombre[30], nodo * lista)
{
    nodo * seg;
    nodo * ant;

    if(lista!=NULL && (strcmp(nombre,lista->dato.nombre)==0))
    {
        nodo * aux=lista;

        lista=lista->siguiente;
        free(aux);

    }
    else
    {


        seg=lista;

        while( seg!=NULL && (strcmp(seg->dato.nombre,nombre)!=0))
        {
            ant=seg;
            seg=seg->siguiente;
        }

        if(seg!=NULL)
        {

            ant->siguiente=seg->siguiente;
            free(seg);
        }



    }


    return lista;

}



nodo * agregarEnOrden(nodo * lista, nodo * nuevoNodo) // Agrega en orden por Score
{

    nodo * ant;
    nodo * seg;

    if(lista==NULL)
    {

        lista=nuevoNodo;

    }
    else
    {

        if(lista->dato.Score<nuevoNodo->dato.Score)
        {

            lista=agregarPrin(lista,nuevoNodo);

        }
        else
        {

            ant=lista;
            seg=lista->siguiente;

            while(seg!=NULL && (seg->dato.Score>nuevoNodo->dato.Score))
            {

                ant=seg;
                seg=seg->siguiente;


            }


            ant->siguiente=nuevoNodo;
            nuevoNodo->siguiente=seg;


        }





    }




    return lista;

}



nodo * borrarTodaLaLista(nodo * lista)
{

    nodo* proximo;
    nodo* seg=lista;

    while(seg!=NULL)
    {

        proximo=seg->siguiente;
        free(seg);
        seg=proximo;


    }


    return seg;
}




//FUNCIONES AVANZADAS



nodo * subprogramaBusquedaDeUnNodo(nodo * lista)
{

    usuarioLista aux;
    nodo * seg=lista;


    printf("ingrese el nombre de la usuario ");
    scanf("%s",aux.nombre);

    while(seg!=NULL && (strcmp(aux.nombre,seg->dato.nombre)!=0))
    {

        seg=seg->siguiente;


    }



    return seg;

}


nodo *  subprogramaBorrarNodo(nodo * lista)
{

    nodo * aBorrar;
    aBorrar=subprogramaBusquedaDeUnNodo(lista);

    lista=borrarNodo(aBorrar->dato.nombre,aBorrar);

    return lista;
}

///Funciones Recursivas
//
//void recorrerYmostrarRecursivo(nodo* lista)
//{
//    nodo* nuevo=lista;
//    if(lista!=NULL)
//    {
//
//        recorrerYmostrarRecursivo(lista->siguiente);
//        mostrarUnNodo(nuevo);
//
//    }
//
//}






nodo* BorrarNodoRecursivo(nodo* lista, char nombre[])
{
    nodo* aux;




    if(lista!=NULL)
    {

        if((strcmp(nombre,lista->dato.nombre)!=0))
        {


            lista->siguiente=BorrarNodoRecursivo(lista->siguiente,nombre);










        }
        else
        {



            aux=lista;
            lista=lista->siguiente;
            free(aux);




        }

    }

    return lista;

}


nodo* InsertarNodoRecursivo(nodo* lista, nodo* nuevo)
{

    if(lista!=NULL)
    {

        if((strcmp(nuevo->dato.nombre,lista->dato.nombre)<0))
        {


            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else
        {


            lista->siguiente=InsertarNodoRecursivo(lista->siguiente,nuevo);
        }

    }
    else
    {

        lista=nuevo;
    }

    return lista;

}







