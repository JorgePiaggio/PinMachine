#ifndef MOSTRAR_H_INCLUDED
#define MOSTRAR_H_INCLUDED
#include "jugabilidad.h"

///FUNCIONALIDAD DE LOS MENUS (FRONT)
int menuJuego(mapaFlipper *actual,char i[],char usrpass[],nodoArbol** arbolUsuarios,scoreMapas ADS[], int*,ALLEGRO_MONITOR_INFO info);
void locomotion(int*aleatorio,int*ny,int*nx,int*c,int*uno,int*dos,int*tres,float*r,ALLEGRO_MONITOR_INFO info);
void mouseClic(int*menu,int*exit,int*usrLogueado,usuarioArbol*senior,char usr[],char nombre[],char pass[],char pass2[],char usrpass[],char i[],int color[],int*login,int*al,ALLEGRO_MONITOR_INFO info);
void dibujarPalabras(int menu,ALLEGRO_FONT*m2,ALLEGRO_FONT*m1,char d[],char e[],char f[],char g[],char h[],char i[],char j[],char k[],char guest[],char nombre[],char pass[],char p[],char pass2[],char nombreNuevoNuevo[],char nombreNuevo[],char passNuevo[],ALLEGRO_MONITOR_INFO info);
void pintarPalabras(ALLEGRO_MOUSE_STATE estadoMouse,int menu,ALLEGRO_FONT*m2,ALLEGRO_FONT*m1,char d[],char e[],char f[],char g[],char h[],char i[],char j[],ALLEGRO_MONITOR_INFO info);
void mainScreen (char d[],char e[],char f[],char g[],char h[],char i[],int login,ALLEGRO_MONITOR_INFO info);
void elegirMapa (char d[],char j[]);
void reg_logIn(char d[],char e[],int login);
void checklog(int i,char log[],int menu);
void perfil(char d[],usuarioArbol senior);
void highscores(char d[],ALLEGRO_FONT*m1,ALLEGRO_MONITOR_INFO info);
void entroElAdmin(char d[],char e[],char i[]);
void verListaUsuarios(char d[],char i[]);
void editarUsuario(char d[],char i[]);
void editarUsuario2(char d[],char f[],char i[]);
void editarUsuario3(char d[],char f[]);
void borrarUsuario(char d[]);
void MostrarHighscores(scoreMapas ADS[],int i,int x,ALLEGRO_FONT* fuente, int tam,ALLEGRO_MONITOR_INFO info);
void MostrarScoresUsuario(scoreMapas ADS[],int i,char nombre[],int x,ALLEGRO_FONT* fuente, int tam,ALLEGRO_MONITOR_INFO info);
void mostrarUnUsuario(usuarioLista aux,int x, int y, ALLEGRO_FONT* fuente,int tam, int flag,ALLEGRO_MONITOR_INFO info);
void MostrarScoreMapas(scoreMapas ADS[], int xini,char nombre[],ALLEGRO_FONT* fuente, int tam, int flag,ALLEGRO_MONITOR_INFO info);
///FUNCIONALIDAD DE LOS MENUS (BACK)
//ADMIN
nodoArbol* BorrarUsuario(nodoArbol* arbolito,scoreMapas ADS[], char nombre[30]);
bool ModificarNombreUser(nodoArbol** arbolito,scoreMapas ADS[],char nombreAbuscar[30],char nombreMod[30]);
bool ModificarPassUser(nodoArbol** arbolito,char nombreUser[30], char passNew[14]);
void VerUsuarios(nodo*,ALLEGRO_FONT*,int,int,int);
//REGISTRO Y LOGUEO
int VerificarLogeo(nodoArbol* arbolito,char nombre[30],char pass[14],usuarioArbol s);
int RegistrarUsuario(nodoArbol** arbolito,char nombre[30], char pass[14], char pass2[14],usuarioArbol s);
//TECLADO
int EscribirTeclado(int cantidad,char palabra[cantidad], int flagRegion,char passOculto[], int flagOculto,ALLEGRO_MONITOR_INFO info); //flag region para las cajas de escritura // flag oculto para ocultar pass



#endif // MOSTRAR_H_INCLUDED
