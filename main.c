#include "mostrar.h"

void InicializarADS(scoreMapas ADS[]);
void PasarArchivosToADS(scoreMapas ADS[]);
void PasarADStoArchivo(scoreMapas ADS[]);
nodoArbol* PasarDeArchiToArbol(char nombre[]);
void preorder(nodoArbol * arbolito);

int main()
{

    char nameArchivo[]="usuariosArbol.dat";
    nodoArbol* arbolito=PasarDeArchiToArbol(nameArchivo);
    nodoArbol* encontrado=BuscarArbol(arbolito,"theboss");
    if(!encontrado)
    {
        usuarioArbol admin;
        strcpy(admin.nombre,"theboss");
        EncriptarPass("admin1234",admin.MatrizPassword,admin.MatrizAsignada);
        arbolito=InsertarArbol(arbolito,admin);
    }

    scoreMapas ADS[CANTMAPAS];
    InicializarADS(ADS);
    PasarArchivosToADS(ADS);
    arbolito=sesion(ADS,arbolito);
    PasarADStoArchivo(ADS);
    PasarDeArbolToArchivo(arbolito,nameArchivo);

    return 0;
}

///Persistencia +ADS

void PasarArchivosToADS(scoreMapas ADS[])
{
    usuarioLista aux;
    nodo* nuevo;
    char nombreMapa[]="Mapa1.dat";
    for(int i=0 ; i<CANTMAPAS; i++)
    {
        nombreMapa[4]=(char) i+'0';

        FILE* archivo=fopen(nombreMapa,"rb");
        if(archivo)
        {

            while(fread(&aux,sizeof(usuarioLista),1,archivo)>0)
            {

                nuevo=crearnodo(aux);
                ADS[i].lista=agregarEnOrden(ADS[i].lista,nuevo);



            }


        }
        fclose(archivo);

    }

}


void PasarADStoArchivo(scoreMapas ADS[])
{
    nodo* seg;
    char nombreMapa[]="Mapa1.dat";

    for(int i=0 ; i<CANTMAPAS; i++)
    {
        nombreMapa[4]=(char) i+'0';
        FILE* archivo=fopen(nombreMapa,"wb");
        if(archivo)
        {

            seg=ADS[i].lista;
            while(seg!=NULL)
            {

                fwrite(&seg->dato,sizeof(usuarioLista),1,archivo);
                seg=seg->siguiente;



            }


        }
        fclose(archivo);

    }

}

void InicializarADS(scoreMapas ADS[])
{

    for(int i=0; i<CANTMAPAS; i++)
    {

        ADS[i].lista=iniclista(ADS[i].lista);


    }



}

void preorder(nodoArbol * arbolito)
{

    if(arbolito!=NULL)
    {

        printf("%s\n",arbolito->dato.nombre);
        preorder(arbolito->izq);
        preorder(arbolito->der);


    }



}

nodoArbol* PasarDeArchiToArbol(char nombre[])
{

    FILE* archivo=fopen(nombre,"rb");
    usuarioArbol aux;
    int cantidad=0;
    int i=-1;
    nodoArbol* arbolito=inicArbol();
    if(archivo)
    {

        fseek(archivo,0,SEEK_END);
        cantidad= ftell(archivo)/sizeof(usuarioArbol);
        fseek(archivo,0,SEEK_SET);
        usuarioArbol users[cantidad];
        while(fread(&aux,sizeof(usuarioArbol),1,archivo)>0)
        {

            InsertarOrdenado(users,i,aux);
            i++;
        }

        arbolito=CrearArbolNivelado(users,cantidad);
    }
    fclose(archivo);


    return arbolito;
}
