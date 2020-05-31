#include "usuario.h"






void InsertarOrdenado(usuarioArbol users[],int upos, usuarioArbol dato)    //Inserta de forma ordenada por nombre
{


    int i=upos;
    while(i>=0 && strcmp(dato.nombre,users[i].nombre)<0)
    {

        users[i+1]=users[i];
        i--;



    }

    users[i+1]=dato;


}


/// FUNCIONES DE ENCRIPTACION

float Determinante2x2(float M[2][2])
{
    int resultado=0;

    resultado= (M[0][0]*M[1][1])-(M[0][1]*M[1][0]);

    return resultado;

}

int VerificaInvsersa(float M[2][2])
{
    int verifica=0;
    if(Determinante2x2(M)!=0)
    {
        verifica=1;
    }

    return verifica;
}
void MultiplicaMatrix(float M[2][2],float M2[2][7],float MR[2][7])
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<7; j++)
        {
            MR[i][j]=0;
        }


    }
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<7; j++)
        {
            for(int h=0; h<2; h++)
            {
                MR[i][j]+=(float)round(M[i][h]*M2[h][j]);

            }


        }



    }




}
void MatrizInversa(float M[2][2],float MI[2][2])
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            MI[i][j]=0;
        }
    }

    if(Determinante2x2(M)!=0)
    {

        MI[0][0]=M[1][1];
        MI[1][1]=M[0][0];
        MI[0][1]=(-1)*M[0][1];
        MI[1][0]=(-1)*M[1][0] ;

        for(int i=0; i<2; i++)
        {
            for(int j=0; j<2; j++)
            {
                MI[i][j]=(float)(1.0/Determinante2x2(M))*MI[i][j];

            }

        }
    }



}


void EncriptarPass(char pass[14],float MResultado[2][7], float MRandom[2][2])
{
    srand(clock());
    float MEncriptada[2][7];
    // inicializo Mrandom
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            MRandom[i][j]=0;


// Cargo con valores random la matriz
    while(Determinante2x2(MRandom)==0)  // evito que no tenga inversa con esta condicion
    {
        for(int i=0; i<2; i++)
        {

            for(int j=0; j<2; j++)
            {

                MRandom[i][j]=rand()%5+1;

            }


        }
    }
// Cargo la Meencriptada teniendo en cuenta el pass

    CodificarMatriz(pass,MEncriptada);

//Multiplico ambas y guardo en Mresultado

    MultiplicaMatrix(MRandom,MEncriptada,MResultado);

}

void CodificarMatriz(char pass[14], float MEncriptada[2][7])
{
    int k=0;
    for(int j=0; j<7; j++)
    {
        for(int i=0; i<2; i++)
        {
            if(k<strlen(pass))
                MEncriptada[i][j]=ConvertirLetraNumero(pass[k]);
            else
                MEncriptada[i][j]=0;
            k++;

        }
    }


}

void DesencriptarPass(float M1[2][2],float MEncrip[2][7],float Mresult[2][7])
{

    float Minversa[2][2];

    MatrizInversa(M1,Minversa);
    MultiplicaMatrix(Minversa,MEncrip,Mresult);
}


int ConvertirLetraNumero(char letra)
{
    int numero=0;
    switch(letra)
    {

    case 'a':
        numero=1;
        break;
    case 'b':
        numero=2;
        break;
    case 'c':
        numero=3;
        break;
    case 'd':
        numero=4;
        break;
    case 'e':
        numero=5;
        break;
    case 'f':
        numero=6;
        break;
    case 'g':
        numero=7;
        break;
    case 'h':
        numero=8;
        break;
    case 'i':
        numero=9;
        break;
    case 'j':
        numero=10;
        break;
    case 'k':
        numero=11;
        break;
    case 'l':
        numero=12;
        break;
    case 'm':
        numero=13;
        break;
    case 'n':
        numero=14;
        break;
    case 'o':
        numero=15;
        break;
    case 'p':
        numero=16;
        break;
    case 'q':
        numero=17;
        break;
    case 'r':
        numero=18;
        break;
    case 's':
        numero=19;
        break;
    case 't':
        numero=20;
        break;
    case 'u':
        numero=21;
        break;
    case 'v':
        numero=22;
        break;
    case 'w':
        numero=23;
        break;
    case 'x':
        numero=24;
        break;
    case 'y':
        numero=25;
        break;
    case 'z':
        numero=26;
        break;
    case '0':
        numero=27;
        break;
    case '1':
        numero=28;
        break;
    case '2':
        numero=29;
        break;
    case '3':
        numero=30;
        break;
    case '4':
        numero=31;
        break;
    case '5':
        numero=32;
        break;
    case '6':
        numero=33;
        break;
    case '7':
        numero=34;
        break;
    case '8':
        numero=35;
        break;
    case '9':
        numero=36;
        break;

    default:
        numero=0;
        break;
    }



    return numero;

}

int CompararMatrices(float M1[2][7],float M2[2][7])
{

    int rta=6;              ///contraseña correcta
    int i=0;
    int j=0;
    while(i<2 && rta==6)
    {
        while(j<7 && rta==6)
        {
            if(M1[i][j]!=M2[i][j])
                rta=7;          ///contraseña incorrecta
            j++;
        }
        i++;
    }


    return rta;
}

