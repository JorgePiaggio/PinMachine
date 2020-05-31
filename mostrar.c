#include "mostrar.h"



int menuJuego (mapaFlipper *actual,char usr[],char usrpass[],nodoArbol** arbolUsuarios, scoreMapas ADS[],int *usrLogueado,ALLEGRO_MONITOR_INFO info)
{
    ALLEGRO_FONT *m1, *m2,*letra;
    m1=al_load_font ("fonts/Metal3.ttf",20,0);
    m2=al_load_font ("fonts/Metal2.otf",50,0);
    letra=al_load_font ("fonts/Metal3.ttf",18,0);
    ALLEGRO_BITMAP *ayuda=al_load_bitmap("img/ayuda2.bmp");
    ALLEGRO_BITMAP *mapa1=al_load_bitmap("img/Captura1.bmp");
    ALLEGRO_BITMAP *mapa2=al_load_bitmap("img/Captura2.bmp");
    ALLEGRO_BITMAP *logo=al_load_bitmap("img/PinMachine.bmp");
    al_convert_mask_to_alpha(ayuda,al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(logo,al_map_rgb(22,0,102));
    ALLEGRO_BITMAP *bestTeacherEver=al_load_bitmap("img/prof.bmp");
    al_convert_mask_to_alpha(bestTeacherEver,al_map_rgb(0,0,0));
    ALLEGRO_EVENT_QUEUE *fila=al_create_event_queue();
    al_register_event_source(fila,al_get_mouse_event_source());
    al_register_event_source(fila,al_get_keyboard_event_source());
    ALLEGRO_EVENT eve;
    ALLEGRO_MOUSE_STATE estadoMouse;
    nodoArbol* encontrado=NULL;
    ALLEGRO_COLOR ColorObjetivos[CANTOBJETIVOs];
    int sumaObjetivos=0;
    if(*usrLogueado==0)
    {
        for(int i=0; i<CANTOBJETIVOs; i++)
            ColorObjetivos[i]=al_map_rgb(155,155,155);


    }

    // Reviso Objetivos de usuario para Habilitar


    int nx=1;
    int ny=1;
    int c=0;
    int uno=1;
    int dos=1;
    int tres=1;
    float r=1;
    int exit=0;
    int menu=0;
    int aleatorio=1;
    int color[3]= {255,255,255};
    int teclaenter=0;
    char d[20];
    char e[20];
    char f[20];
    char g[20];
    char h[20];
    char i[20];
    char j[20];
    char k[20];
    char pass2[14];
    char pass[14];
    char passOculto[14];
    char passOculto2[14];
    char passNuevo[14];
    char nombre[21];
    char nombreNuevo[21];
    char nombreNuevoNuevo[21];
    strcpy(nombreNuevoNuevo,"");
    strcpy(pass,"");
    strcpy(passNuevo,"");
    strcpy(nombreNuevo,"");
    strcpy(pass2,"");
    strcpy(nombre,"");
    strcpy(passOculto2,"");
    strcpy(passOculto,"");
    nodo* listaUser=NULL;
    listaUser= PasarArbolLista(*arbolUsuarios,listaUser);
    int login=0;        ///resultado de intento de logueo o registro
    usuarioArbol senior;///usr auxiliar para copiar logueado

/// SWITCH MENUS ///

    while(!exit)
    {
        locomotion(&aleatorio,&ny,&nx,&c,&uno,&dos,&tres,&r,info);  ///animar fondo

        strcpy(d," ");
        strcpy(e," ");
        strcpy(f," ");
        strcpy(g," ");
        strcpy(h," ");
        strcpy(j," ");
        strcpy(k," ");

        if(menu!=0 && *usrLogueado!=2)
            strcpy(i,"MAIN MENU");

        if(*usrLogueado==1 || *usrLogueado==2)
        {
            login=VerificarLogeo(*arbolUsuarios,usr,usrpass,senior);
            strcpy(senior.nombre,usr);
        }
        else
            strcpy(senior.nombre,"GUEST 255");


        switch(menu)
        {
        case 0:
            mainScreen(d,e,f,g,h,i,*usrLogueado,info);
            al_draw_bitmap(logo,(info.x2-ANCHO)/2+400,(info.y2-ALTO)/2+150,0); ///Poner imagen logo aca

            break;
        case 1:
            elegirMapa(d,j);
            if(menu>10 && menu<15)
                exit=menu;
            al_draw_tinted_scaled_bitmap(mapa1,al_map_rgba_f(0,0,1.0,0.5),0,0,ANCHO,ALTO,(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+200,ANCHO*0.4,ALTO*0.4,0); ///Poner imagenes mapas aca
            al_draw_tinted_scaled_bitmap(mapa2,al_map_rgba_f(1.0,0,0,0.5),0,0,ANCHO,ALTO,(info.x2-ANCHO)/2+430,(info.y2-ALTO)/2+200,ANCHO*0.4,ALTO*0.4,0);
            break;
        case 2:
            reg_logIn(d,e,*usrLogueado);
            break;
        case 3:
            if(*usrLogueado==1)
            {
                nodoArbol* encontradoOb=BuscarArbol(*arbolUsuarios,usr);

                if(encontradoOb)
                {
                    for(int i=0; i<CANTOBJETIVOs; i++)
                    {
                        if(encontradoOb->dato.objetivos[i]==CANTMAPAS)
                            ColorObjetivos[i]=al_map_rgb(255,255,0);
                        else
                            ColorObjetivos[i]=al_map_rgb(155,155,155);

                        sumaObjetivos+=encontradoOb->dato.objetivos[i];
                    }
                    if(sumaObjetivos==(CANTOBJETIVOs-1)*2)
                        ColorObjetivos[CANTOBJETIVOs-1]=al_map_rgb(255,255,0);
                }
            }
            MostrarScoreMapas(ADS,30,senior.nombre,m1,20,1,info);
            al_draw_text(m1,al_map_rgb(0,255,255),(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+350,0,"---OBJECTIVES---");
            al_draw_text(m1,al_map_rgb(0,255,255),(info.x2-ANCHO)/2+50,(info.y2-ALTO)/2+200,0,"---THE WALL---");
            al_draw_text(m1,al_map_rgb(0,255,255),(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+200,0,"---STRINGS---");
            al_draw_text(m1,ColorObjetivos[0],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+380,0,"*Exceed 1000 points twice");
            al_draw_text(m1,ColorObjetivos[1],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+400,0,"*Exceed 3000 points twice");
            al_draw_text(m1,ColorObjetivos[2],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+420,0,"*Get an extraball twice");
            al_draw_text(m1,ColorObjetivos[3],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+440,0,"*Get 2X bonus twice");
            al_draw_text(m1,ColorObjetivos[4],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+460,0,"*Get 3X bonus twice");
            al_draw_text(m1,ColorObjetivos[5],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+480,0,"*Get +500 twice");
            al_draw_text(m1,ColorObjetivos[6],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+500,0,"*Exceed 10000 points");
            al_draw_text(m1,ColorObjetivos[7],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+520,0,"*Exceed 20000 points");
            al_draw_text(m1,ColorObjetivos[8],(info.x2-ANCHO)/2+280,(info.y2-ALTO)/2+540,0,"*Get all the goals");
            perfil(d,senior);
            break;
        case 4:
            MostrarScoreMapas(ADS,30,"",m1,20,0,info);
            highscores(d,m1,info);
            if(nx>849 && nx<951)
            {
                al_draw_filled_rectangle((info.x2-ANCHO)/2+0,(info.y2-ALTO)/2+450,(info.x2-ANCHO)/2+230,(info.y2-ALTO)/2+600,(al_map_rgb(0,0,0)));
            }
            if(nx>850 && nx<950)
            {
                al_draw_bitmap(bestTeacherEver,(info.x2-ANCHO)/2+0-c*2,(info.y2-ALTO)/2+0+c*2,0);
            }
            break;
        case 5:
            al_draw_bitmap(ayuda,(info.x2-ANCHO)/2+0,(info.y2-ALTO)/2+0,0);
            break;
        case 6:
            entroElAdmin(d,e,i);
            break;
        case 7:
            verListaUsuarios(d,i);
            VerUsuarios(listaUser,letra,(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+170,18);
            break;
        case 8:                                                 /// ADMIN EDITAR USR cual usr
            editarUsuario(d,i);
            teclaenter=0;
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+190,(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+240,0,0,al_map_rgb(255,255,color[0]),1);//e
            if(color[0]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)         /// registrar teclado
            {
                teclaenter=EscribirTeclado(21,nombreNuevoNuevo,0,"",0,info);
                if(teclaenter==1)
                {
                    encontrado=BuscarArbol(*arbolUsuarios,nombreNuevoNuevo);
                    if(encontrado!=NULL && strcmp("theboss",nombreNuevoNuevo)!=0)
                    {
                        menu=12;  ///preg si edita o borra usr
                    }
                    else
                    {
                        al_clear_to_color(al_map_rgb(0,0,0));
                        al_draw_text(m2,al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,"USER NOT FOUND");
                        al_flip_display();
                        al_rest(1.5);
                        al_clear_to_color(al_map_rgb(0,0,0));
                        al_flip_display();
                        menu=6;
                    }
                    strcpy(d,"");
                    strcpy(i,"");
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_flip_display();
                    strcpy(nombre,nombreNuevoNuevo);
                    strcpy(nombreNuevoNuevo,"");
                }
            }
            teclaenter=0;
            break;
        case 9:                                              ///ADMIN cambiar datos usr
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+190,(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+240,0,0,al_map_rgb(255,255,color[0]),1);//e
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+330,(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+380,0,0,al_map_rgb(255,255,color[1]),1);//g
            editarUsuario3(d,f);
            if(color[0]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                teclaenter=EscribirTeclado(21,nombreNuevo,0,"",0,info);
                if(teclaenter==1)  ///enter == pasar a pass
                {
                    color[0]=255;
                    color[1]=0;
                    color[2]=255;
                    teclaenter=0;
                    break;
                }
            }
            if(color[1]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                teclaenter=EscribirTeclado(14,pass,1,"",0,info);
                if(teclaenter==1) ///enter == cambiar datos
                {
                    color[0]=255;
                    color[1]=255;
                    color[2]=0;
                    teclaenter=0;
                    nodoArbol* nombreOtroUser=BuscarArbol(*arbolUsuarios,nombreNuevo); //evitar que coincida con el nombre de otro user
                    if(strlen(nombreNuevo)<5 || strlen(pass)<5 || nombreOtroUser!=NULL)
                    {
                        al_clear_to_color(al_map_rgb(0,0,0));
                        al_draw_text(m2,al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,"INVALID NAME OR PASS");
                        al_flip_display();
                        al_rest(1.5);
                    }
                    else
                    {
                        bool validar=FALSE;
                        strcpy(nombre,encontrado->dato.nombre);
                        validar=ModificarNombreUser(arbolUsuarios,ADS,encontrado->dato.nombre,nombreNuevo);

                        validar=ModificarPassUser(arbolUsuarios,nombreNuevo,pass);
                        if(validar==TRUE)
                        {
                            nodo* buscado=buscarNodo(nombre,listaUser); //modifico lista
                            if(buscado)
                                strcpy(buscado->dato.nombre,nombreNuevo);
                            al_clear_to_color(al_map_rgb(0,0,0));
                            al_draw_text(m2,al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,"USER UPDATED");
                            al_flip_display();
                            al_rest(1.5);
                        }
                    }
                    strcpy(nombreNuevo,"");
                    strcpy(nombre,"");
                    strcpy(pass,"");
                    strcpy(passOculto,"");
                    strcpy(d,"");
                    strcpy(f,"");
                    strcpy(i,"");
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_flip_display();
                    menu=6;
                    color[0]=255;
                    color[1]=255;
                }
                teclaenter=0;


            }
            break;
        case 10:                                            /// USUARIO registrar
            strcpy(d,"TYPE YOUR NAME");
            strcpy(f,"TYPE YOUR PASS");
            strcpy(k,"RETYPE YOUR PASS");
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+190,(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+240,0,0,al_map_rgb(255,255,color[0]),1);//e
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+330,(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+380,0,0,al_map_rgb(255,255,color[1]),1);//g
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+360,(info.y2-ALTO)/2+330,(info.x2-ANCHO)/2+630,(info.y2-ALTO)/2+380,0,0,al_map_rgb(255,255,color[2]),1);//l

            if(color[0]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                teclaenter=EscribirTeclado(21,nombre,0,"",0,info);
                if(teclaenter==1)
                {
                    color[0]=255;
                    color[1]=0;
                    color[2]=255;
                    teclaenter=0;
                    break;  ///enter == pasar a pass
                }
            }
            if(color[1]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                teclaenter=EscribirTeclado(14,pass,1,passOculto,1,info);
                if(teclaenter==1)
                {
                    color[0]=255;
                    color[1]=255;
                    color[2]=0;
                    teclaenter=0;
                    break;  ///enter == pasar a pass2
                }
            }
            if(color[2]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                teclaenter=EscribirTeclado(14,pass2,2,passOculto2,1,info);
                if(teclaenter==1)///enter == enviar datos a registrar
                {
                    login=RegistrarUsuario(&*arbolUsuarios,nombre,pass,pass2,senior);
                    usuarioLista nuevoUser;
                    strcpy(nuevoUser.nombre,nombre);
                    nodo* nuevo=crearnodo(nuevoUser);
                    listaUser=agregarPrin(listaUser,nuevo);                          ///funcion q registra usr
                    checklog(login,d,menu);                                         ///funcion q muestra ok o q error cometio
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_text(m2,al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,d);
                    al_flip_display();
                    al_rest(1.5);
                    al_clear_to_color(al_map_rgb(0,0,0));
                    strcpy(d," ");
                    strcpy(f," ");
                    strcpy(k," ");
                    al_flip_display();
                    teclaenter=0;
                    if(login==4)
                    {
                        *usrLogueado=1;
                        strcpy(usrpass,pass);
                        strcpy(senior.nombre,nombre);
                        strcpy(usr,nombre);

                        strcpy(i,"");
                        menu=0;
                        teclaenter=0;

                    }
                    strcpy(pass,"");
                    strcpy(pass2,"");
                    strcpy(passOculto,"");
                    strcpy(passOculto2,"");

                }
            }
            break;
        case 11:                                            ///usuario loguearse
            strcpy(d,"TYPE YOUR NAME");
            strcpy(f,"TYPE YOUR PASS");
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+190,(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+240,0,0,al_map_rgb(255,255,color[0]),1);//e
            al_draw_rounded_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+330,(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+380,0,0,al_map_rgb(255,255,color[1]),1);//g
            if(color[0]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)         ///teclado
            {
                teclaenter=EscribirTeclado(21,nombre,0,"",0,info);
                if(teclaenter==1)
                {
                    color[0]=255;
                    color[1]=0;
                    teclaenter=0;
                    break;
                }
            }
            if(color[1]==0 && eve.type==ALLEGRO_EVENT_KEY_DOWN)
            {
                teclaenter=EscribirTeclado(14,pass,1,passOculto,1,info);
                if(teclaenter==1)
                {
                    login=VerificarLogeo(*arbolUsuarios,nombre,pass,senior);                ///funcion q loguea usr
                    checklog(login,d,menu);                                          ///funcion q muestra ok o q error cometio
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_text(m2,al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,d);
                    al_flip_display();
                    al_rest(1.5);
                    al_clear_to_color(al_map_rgb(0,0,0));
                    strcpy(d," ");
                    strcpy(f," ");
                    al_flip_display();
                    teclaenter=0;
                    if(login==6)
                    {
                        al_clear_to_color(al_map_rgb(0,0,0));
                        al_flip_display();
                        if(strcmp(nombre,"theboss")==0) ///si login admin
                        {
                            *usrLogueado=2;
                            strcpy(i,"");
                            strcpy(usr,"theboss");
                            strcpy(senior.nombre,"theboss");
                            menu=6;
                        }
                        else
                        {
                            *usrLogueado=1;
                            strcpy(i,"");
                            strcpy(usr,nombre);
                            strcpy(senior.nombre,nombre);
                            strcpy(usrpass,pass);
                            menu=0;
                        }

                        strcpy(senior.nombre,nombre);
                        color[1]=255;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        al_flip_display();
                    }
                    strcpy(pass,"");
                    strcpy(passOculto,"");

                }
            }
            break;
        case 12:
            editarUsuario2(d,e,i);              ///preg si edita o borra usr
            break;
        case 13:                            /// ADMIN borrar usr
            *arbolUsuarios=BorrarUsuario(*arbolUsuarios,ADS,nombre);
            listaUser=borrarNodo(nombre,listaUser);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_text(m2,al_map_rgb(255,255,255),(info.x2-ANCHO)/2+(info.y2-ALTO)/2+30,120,0,"USER DELETED");
            al_flip_display();
            al_rest(1.5);
            strcpy(nombre,"");
            strcpy(i,"");
            al_clear_to_color(al_map_rgb(0,0,0));
            al_flip_display();
            menu=6;
            break;
        }


        dibujarPalabras(menu,m2,m1,d,e,f,g,h,i,j,k,usr,nombre,passOculto,pass,passOculto2,nombreNuevoNuevo,nombreNuevo,passNuevo,info);        ///palabras a buffer

        al_wait_for_event_timed(fila,&eve,0.02);    ///RETRASO ANIMACION... ESPERAR CLIC
        al_get_mouse_state(&estadoMouse);

        pintarPalabras(estadoMouse,menu,m2,m1,d,e,f,g,h,i,j,info);       ///pintar palabras bajo puntero mouse

        mouseClic(&menu,&exit,usrLogueado,&senior,usr,nombre,passOculto,passOculto2,usrpass,i,color,&login,&aleatorio,info); /// evaluar si hace clic

        al_flip_display();

        if(eve.type==ALLEGRO_EVENT_KEY_CHAR) /// ESC == CERRAR CONSOLA
        {
            if(eve.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
            {
                exit=30;
            }
        }
    }

    return exit;
}







/// DIBUJAR PALABRAS EN MENUS ///
void dibujarPalabras(int menu,ALLEGRO_FONT*m2,ALLEGRO_FONT*m1,char d[],char e[],char f[],char g[],char h[],char i[],char j[],char k[],char user[],char nombre[],char pass[],char passAdmin[],char pass2[],char nombreNuevoNuevo[],char nombreNuevo[],char passNuevo[],ALLEGRO_MONITOR_INFO info)
{

    ///palabras comunes
    if(menu!=4)                                                                                 ///CADA PALABRA ES UNA POSICION FIJA EN PANTALLA,
        al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,d);
    if(menu==3)
    {
        al_draw_text(m2, al_map_rgb(255,255,0),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,d);
        al_draw_text(m2, al_map_rgb(255,0,0),(info.x2-ANCHO)/2+31,(info.y2-ALTO)/2+120,0,d);
    }
    if(menu==4)
    {
        al_draw_text(m2, al_map_rgb(255,255,0),(info.x2-ANCHO)/2+301,(info.y2-ALTO)/2+120,0,d);
        al_draw_text(m2, al_map_rgb(255,0,0),(info.x2-ANCHO)/2+300,(info.y2-ALTO)/2+120,0,d);
    }
    al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+190,0,e);
    al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+260,0,f);
    if(menu!=3)
        al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+330,0,g);
    else
        al_draw_text(m2, al_map_rgb(55,0,55),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+330,0,g);
    al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+400,0,h);
    al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+470,0,i);
    al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+600,(info.y2-ALTO)/2+120,0,j);
    al_draw_text(m2, al_map_rgb(255,255,255),(info.x2-ANCHO)/2+360,(info.y2-ALTO)/2+260,0,k);
    al_draw_text(m1, al_map_rgb(255,0,0),(info.x2-ANCHO)/2+375,(info.y2-ALTO)/2+570,0,user);
    if(menu==10)    ///regist
    {
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+40,(info.y2-ALTO)/2+205,0,nombre);
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+40,(info.y2-ALTO)/2+345,0,pass);
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+370,(info.y2-ALTO)/2+345,0,pass2);
    }
    if(menu==11)    ///login
    {
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+40,(info.y2-ALTO)/2+205,0,nombre);
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+40,(info.y2-ALTO)/2+345,0,pass);
    }
    if(menu==8)    ///admin
    {
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+40,(info.y2-ALTO)/2+205,0,nombreNuevoNuevo);
    }
    if(menu==9)    ///admin
    {
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+40,(info.y2-ALTO)/2+205,0,nombreNuevo);
        al_draw_text(m1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+40,(info.y2-ALTO)/2+345,0,passAdmin);
    }
    if(menu==0) ///menu principal
    {
        al_draw_text(m1, al_map_rgb(1,1,111),(info.x2-ANCHO)/2+740,(info.y2-ALTO)/2+565,0,"O");
        al_draw_text(m1, al_map_rgb(1,1,111),(info.x2-ANCHO)/2+760,(info.y2-ALTO)/2+565,0,"O");
    }
}


///MOUSE

///PINTAR PALABRAS BAJO EL PUNTERO
void pintarPalabras(ALLEGRO_MOUSE_STATE estadoMouse,int menu,ALLEGRO_FONT*m2,ALLEGRO_FONT*m1,char d[],char e[],char f[],char g[],char h[],char i[],char j[],ALLEGRO_MONITOR_INFO info)
{

    if(estadoMouse.more_axes)    ///si no son menus 'clickeables' no se pintan
    {
        if((estadoMouse.y > (info.y2-ALTO)/2+120) && (estadoMouse.y < (info.y2-ALTO)/2+160) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))///palabra d
        {
            if(menu!=3 && menu!=4 && menu!=10 && menu!=11 && menu!=7 && menu!=8 && menu!=-8 && menu!=9)
                al_draw_text(m2, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+120,0,d);
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+190) && (estadoMouse.y < (info.y2-ALTO)/2+230) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))///e
        {
            al_draw_text(m2, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+190,0,e);
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+260) && (estadoMouse.y < (info.y2-ALTO)/2+300) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))///f
        {
            if(menu!=10 && menu !=11 && menu!=-8)
                al_draw_text(m2, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+260,0,f);
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+330) && (estadoMouse.y < (info.y2-ALTO)/2+370) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))///g
        {
            al_draw_text(m2, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+330,0,g);
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+400) && (estadoMouse.y < (info.y2-ALTO)/2+440) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))///h
        {
            al_draw_text(m2, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+400,0,h);
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+470) && (estadoMouse.y < (info.y2-ALTO)/2+510) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))///i
        {
            al_draw_text(m2, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+470,0,i);
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+120) && (estadoMouse.y < (info.y2-ALTO)/2+300) && (estadoMouse.x > (info.x2-ANCHO)/2+600) && (estadoMouse.x < (info.x2-ANCHO)/2+780))///j
        {
            al_draw_text(m2, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+600,(info.y2-ALTO)/2+120,0,j);
        }
        if(menu==0)
        {
            if((estadoMouse.y > (info.y2-ALTO)/2+565) && (estadoMouse.y < (info.y2-ALTO)/2+595) && (estadoMouse.x > (info.x2-ANCHO)/2+740) && (estadoMouse.x < (info.x2-ANCHO)/2+760))
            {
                al_draw_text(m1, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+740,(info.y2-ALTO)/2+565,0,"O");
            }
            else if((estadoMouse.y > (info.y2-ALTO)/2+565) && (estadoMouse.y < (info.y2-ALTO)/2+595) && (estadoMouse.x > (info.x2-ANCHO)/2+760) && (estadoMouse.x < (info.x2-ANCHO)/2+780))
            {
                al_draw_text(m1, al_map_rgb(111,0,0),(info.x2-ANCHO)/2+760,(info.y2-ALTO)/2+565,0,"O");
            }
        }
    }

}


///EVALUAR CLICS
void mouseClic(int*menu,int*exit,int*usrLogueado,usuarioArbol*senior,char usr[],char nombre[],char pass[],char pass2[],char usrpass[],char i[],int color[],int*login,int*aleatorio,ALLEGRO_MONITOR_INFO info)
{
    ALLEGRO_MOUSE_STATE estadoMouse;
    al_get_mouse_state(&estadoMouse);

    if(estadoMouse.buttons & 1)       ///SI HACE CLIC DEVOLVER MENU AL QUE IR
    {
        if((estadoMouse.y > (info.y2-ALTO)/2+120) && (estadoMouse.y < (info.y2-ALTO)/2+160) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))   ///1er palabra (d)
        {
            switch(*menu)
            {
            case 0:
                al_clear_to_color(al_map_rgb(0,0,0));
                *menu=1;                                         ///ir a pantalla juego nuevo
                al_rest(0.2);
                break;
            case 1:
                *exit=11;                                        ///eligio mapa 1, devolver int
                strcpy(usr,senior->nombre);
                break;
            case 2:                                             ///quiere registrarse
                if(*usrLogueado==0)
                {
                    strcpy(nombre,"");
                    strcpy(pass,"");
                    strcpy(pass2,"");
                    al_clear_to_color(al_map_rgb(0,0,0));
                    *menu=10;
                }
                break;
            case 6:
                al_clear_to_color(al_map_rgb(0,0,0));           /// admin -> menu
                *menu=7;
                break;
            case 12:                                            ///admin editar usr
                al_clear_to_color(al_map_rgb(0,0,0));
                al_flip_display();
                al_rest(0.2);
                *menu=9;
                break;
            }
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+190) && (estadoMouse.y < (info.y2-ALTO)/2+240) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+300))    ///2da palabra (e)
        {
            switch(*menu)
            {
            case 0:
                al_clear_to_color(al_map_rgb(0,0,0));           ///ir a menu registro-login
                if(*usrLogueado==0)
                {
                    strcpy(pass,"");
                    strcpy(pass2,"");
                    *menu=2;
                    al_rest(0.2);
                }
                else if(*usrLogueado==1 || *usrLogueado==2)
                {
                    *login=0;                                     ///desloguearse
                    *usrLogueado=0;
                    strcpy(senior->nombre,"GUEST 255");
                    strcpy(usr,senior->nombre);
                    strcpy(nombre,"");
                    strcpy(pass,"");
                    strcpy(pass2,"");
                    strcpy(usrpass,"");
                    *menu=0;
                    ///vaciar matriz objetivos??
                }
                break;
            case 2:                                             /// ir a menu loguearse
                strcpy(nombre,"");
                strcpy(pass,"");
                al_clear_to_color(al_map_rgb(0,0,0));
                *menu=11;
                break;
            case 6:
                al_clear_to_color(al_map_rgb(0,0,0));
                *menu=8;
            case 9 ... 10:                                            ///palabra nombre en regist
                color[0]=0;
                color[1]=255;
                color[2]=255;
                break;
            case 11:                                            ///palabra nombre en login
                color[0]=0;
                color[1]=255;
                break;
            case 12:                                            ///admin borrar usr
                al_clear_to_color(al_map_rgb(0,0,0));
                al_flip_display();
                al_rest(0.2);
                *menu=13;
                break;
            }
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+260) && (estadoMouse.y < (info.y2-ALTO)/2+300) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))     ///3er palabra f
        {
            switch(*menu)
            {
            case 0:
                al_clear_to_color(al_map_rgb(0,0,0));
                *menu=3;
                al_rest(0.2);
                break;
            }
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+330) && (estadoMouse.y < (info.y2-ALTO)/2+380) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+300))    ///4ta palabra g
        {
            switch(*menu)
            {
            case 0:
                al_clear_to_color(al_map_rgb(0,0,0));
                *menu=4;
                al_rest(0.2);
                break;
            case 9 ... 10:        ///palabra pass en regist
                color[0]=255;
                color[1]=0;
                color[2]=255;
                break;
            case 11:        ///palabra pass en login
                color[0]=255;
                color[1]=0;
                break;
            }
        }
        else if((estadoMouse.y >(info.y2-ALTO)/2+ 400) && (estadoMouse.y < (info.y2-ALTO)/2+440) && (estadoMouse.x >(info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))    ///5ta palabra h
        {
            switch(*menu)
            {
            case 0:
                al_clear_to_color(al_map_rgb(0,0,0));
                *menu=5;
                al_rest(0.2);
            }
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+470) && (estadoMouse.y < (info.y2-ALTO)/2+510) && (estadoMouse.x > (info.x2-ANCHO)/2+30) && (estadoMouse.x < (info.x2-ANCHO)/2+180))    ///6ta palabra i = ir a main menu o salir
        {

            switch(*menu)
            {
            case 0:
                *exit=30;                ///EXIT GAME
                break;
            case 1 ... 5:
                al_clear_to_color(al_map_rgb(0,0,0));
                color[0]=255;
                color[1]=255;
                color[2]=255;
                if(*menu==10)
                {
                    strcpy(nombre,"");
                    strcpy(pass,"");
                    strcpy(pass2,"");
                }
                *menu=0;               ///IR A MENU PRINCIPAL
                al_rest(0.3);
                break;
            case 6 :
                al_clear_to_color(al_map_rgb(0,0,0));
                *login=0;
                *usrLogueado=0;
                *menu=0;               ///admin logout
                al_rest(0.3);
                strcpy(i,"");
                strcpy(pass,"");
                strcpy(pass2,"");
                strcpy(usr,"GUEST 255");
                strcpy(senior->nombre,"GUEST 255");
                break;

            case 7 ... 9:
                al_clear_to_color(al_map_rgb(0,0,0));
                *menu=6;               ///admin volver a su menu
                al_rest(0.3);
                strcpy(i,"");
                break;

            case 10 ... 11:
                al_clear_to_color(al_map_rgb(0,0,0));
                color[0]=255;
                color[1]=255;
                color[2]=255;
                if(*menu==10)
                {
                    strcpy(nombre,"");
                    strcpy(pass,"");
                    strcpy(pass2,"");
                }
                *menu=0;               ///IR A MENU PRINCIPAL
                al_rest(0.3);
                break;
            }
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+120) && (estadoMouse.y < (info.y2-ALTO)/2+160) && (estadoMouse.x > (info.x2-ANCHO)/2+600) && (estadoMouse.x < (info.x2-ANCHO)/2+770))       ///palabra j ///MAPA2
        {
            switch(*menu)
            {
            case 1:
                *exit=12;
                strcpy(usr,senior->nombre);
                break;
            }
        }
        else if((estadoMouse.y > (info.y2-ALTO)/2+330) && (estadoMouse.y < (info.y2-ALTO)/2+380) && (estadoMouse.x > (info.x2-ANCHO)/2+360) && (estadoMouse.x < (info.x2-ANCHO)/2+630))       ///palabra pass2
        {
            switch(*menu)
            {
            case 10:
                color[0]=255;
                color[1]=255;
                color[2]=0;
                break;
            }
        }

        if(*menu==0)
        {
            if((estadoMouse.y > (info.y2-ALTO)/2+565) && (estadoMouse.y < (info.y2-ALTO)/2+595) && (estadoMouse.x > (info.x2-ANCHO)/2+740) && (estadoMouse.x < (info.x2-ANCHO)/2+760))
            {
                *aleatorio*=-1;
            }
            else if((estadoMouse.y > (info.y2-ALTO)/2+565) && (estadoMouse.y < (info.y2-ALTO)/2+595) && (estadoMouse.x > (info.x2-ANCHO)/2+760) && (estadoMouse.x < (info.x2-ANCHO)/2+780))
            {
                int o=rand()%105;
                al_clear_to_color(al_map_rgb(o,0,22));
            }
        }
    }
}




///ANIMACION FONDO

void locomotion(int*aleatorio,int*ny,int*nx,int*c,int*uno,int*dos,int*tres,float*r,ALLEGRO_MONITOR_INFO info)
{
    switch(*aleatorio)
    {
    case 1:

        if(*nx==0)
            *uno=1;
        if(*nx==1400)
            *uno=-1;
        if(*c==0)
            *tres=1;
        if(*c==50)
            *tres=-1;
        *r+=*uno;
        al_draw_circle((info.x2-ANCHO)/2+(400+*r),(info.y2-ALTO)/2+(300+*r),*r,al_map_rgb(*c,0,0),7);///circulo
        al_draw_circle((info.x2-ANCHO)/2+400+*r,(info.y2-ALTO)/2+300+*r,*r+*c,al_map_rgb(*c,0,40),7);///sombra
        al_draw_circle((info.x2-ANCHO)/2+(400-*r),(info.y2-ALTO)/2+(300-*r),*r,al_map_rgb(*c,0,0),7);///circulo
        al_draw_circle((info.x2-ANCHO)/2+400-*r,(info.y2-ALTO)/2+300-*r,*r+*c,al_map_rgb(*c,0,40),7);///sombra
        al_draw_circle((info.x2-ANCHO)/2+(400+*r),(info.y2-ALTO)/2+(300-*r),*r,al_map_rgb(*c,0,0),7);
        al_draw_circle((info.x2-ANCHO)/2+400+*r,(info.y2-ALTO)/2+300-*r,*r+*c,al_map_rgb(*c,0,40),7);
        al_draw_circle((info.x2-ANCHO)/2+(400-*r),(info.y2-ALTO)/2+(300+*r),*r,al_map_rgb(*c,0,0),7);
        al_draw_circle((info.x2-ANCHO)/2+400-*r,(info.y2-ALTO)/2+300+*r,*r+*c,al_map_rgb(*c,0,40),7);
        al_draw_circle((info.x2-ANCHO)/2+(0+*c),(info.y2-ALTO)/2+(0+*c),*r+20,al_map_rgb(*c,0,0),7);
        al_draw_circle((info.x2-ANCHO)/2+0+*c,(info.y2-ALTO)/2+0+*c,*r+*c+20,al_map_rgb(*c,0,40),7);
        al_draw_circle((info.x2-ANCHO)/2+(800-*c),(info.y2-ALTO)/2+(600-*c),*r+20,al_map_rgb(*c,0,0),7);
        al_draw_circle((info.x2-ANCHO)/2+800-*c,(info.y2-ALTO)/2+600-*c,*r+*c+20,al_map_rgb(*c,0,40),7);
        al_draw_circle((info.x2-ANCHO)/2+(0+*c),(info.y2-ALTO)/2+(600-*c),*r+20,al_map_rgb(*c,0,0),7);
        al_draw_circle((info.x2-ANCHO)/2+0+*c,(info.y2-ALTO)/2+600-*c,*r+*c+20,al_map_rgb(*c,0,40),7);
        al_draw_circle((info.x2-ANCHO)/2+(800-*c),(info.y2-ALTO)/2+(0+*c),*r+20,al_map_rgb(*c,0,0),7);
        al_draw_circle((info.x2-ANCHO)/2+800-*c,(info.y2-ALTO)/2+0+*c,*r+*c+20,al_map_rgb(*c,0,40),7);
        *c+=*tres;
//        *ny+=*dos;
        *nx+=*uno;
        break;
    case -1:
        if(*nx==0)
            *uno=2;
        if(*nx==810)
            *uno=-2;
        if(*ny==0)
            *dos=1;
        if(*ny==610)
            *dos=-1;
        if(*c==0)
            *tres=1;
        if(*c==50)
            *tres=-1;
        al_draw_circle((info.x2-ANCHO)/2+(800-*nx),(info.y2-ALTO)/2+(600-*ny),*nx,al_map_rgb(*c,0,30),7);
        *nx+=*uno;
        *ny+=*dos;
        *c+=*tres;
        *r+=*dos;
        break;
      }
}

/// ""FUNCIONES"" AUX
void mainScreen (char d[],char e[],char f[],char g[],char h[],char i[],int login,ALLEGRO_MONITOR_INFO info)
{
    strcpy(d,"NEW GAME");
    if(login==0)
        strcpy(e,"REGISTER / LOG IN");
    else
        strcpy(e,"LOG OUT");
    strcpy(f,"PROFILE");
    strcpy(g,"HIGHSCORES");
    strcpy(h,"ABOUT");
    strcpy(i,"EXIT");
}
void elegirMapa (char d[],char j[])
{
    strcpy(d,"THE WALL");
    strcpy(j,"STRINGS");
}
void reg_logIn(char d[],char e[],int login)
{
    if(login==0)
    {
        strcpy(d,"REGISTER");
        strcpy(e,"LOGIN");
    }
    else
        strcpy(d,"LOGOUT");
}
void perfil(char d[],usuarioArbol senior)
{
    strcat(d,senior.nombre);
}
void highscores(char d[],ALLEGRO_FONT*m1,ALLEGRO_MONITOR_INFO info)
{
    strcpy(d,"HIGHSCORES");
    al_draw_text(m1, al_map_rgb(255,0,55),(info.x2-ANCHO)/2+150,(info.y2-ALTO)/2+180,0,"THE WALL");
    al_draw_text(m1, al_map_rgb(255,0,55),(info.x2-ANCHO)/2+150,(info.y2-ALTO)/2+190,0,"--------");
    al_draw_text(m1, al_map_rgb(255,0,55),(info.x2-ANCHO)/2+550,(info.y2-ALTO)/2+180,0,"STRINGS");
    al_draw_text(m1, al_map_rgb(255,0,55),(info.x2-ANCHO)/2+550,(info.y2-ALTO)/2+190,0,"-------");
}
void entroElAdmin(char d[],char e[],char i[])
{
    strcpy(d,"USER LIST");
    strcpy(e,"EDIT USER");
    strcpy(i,"LOGOUT");
}
void verListaUsuarios(char d[],char i[])       /// menu 7
{
    strcpy(d,"USER LIST");
    strcpy(i,"BACK TO MENU");
}
void editarUsuario(char d[],char i[])              /// 8
{
    strcpy(d,"USER TO EDIT:");
    strcpy(i,"BACK TO MENU");
}
void editarUsuario2(char d[],char e[],char i[])    /// 12
{
    strcpy(d,"EDIT NAME AND PASS");
    strcpy(e,"DELETE USER");
    strcpy(i,"BACK TO MENU");
}
void editarUsuario3(char d[],char f[])    /// 9
{
    strcpy(d,"ENTER NEW NAME:");
    strcpy(f,"ENTER NEW PASS:");
}
void borrarUsuario(char d[])              /// 13
{
    strcpy(d,"USER TO DELETE:");
}
void checklog(int log, char d[20], int menu)    ///mensaje cuando se registra o loguea o lo intenta
{
    if(menu==10)
    {
        switch(log)                     ///menu de registro
        {
        case 0:
            strcpy(d,"ENTER YOUR NAME (6-14 CHARS)");
            break;
        case 1:
            strcpy(d,"INVALID PASS");
            break;
        case 2:
            strcpy(d,"PASSES DO NOT MATCH");
            break;
        case 4:
            strcpy(d,"REGISTERED CORRECTLY - LOGGING IN...");
            break;
        }
    }
    else if(menu==11)               ///menu de logueo
    {
        switch(log)
        {
        case 0:
            strcpy(d,"USER NOT FOUND");
            break;
        case 6:
            strcpy(d,"LOGGING IN...");
            break;
        case 7:
            strcpy(d,"INCORRECT PASS");
            break;
        }
    }
}


/// FUNCIONES LOGUEO Y REGISTRO

int RegistrarUsuario(nodoArbol** arbolito,char nombre[30], char pass[14], char pass2[14],usuarioArbol senior)
{

    int verifica=0;
    nodoArbol* encontrado=BuscarArbol(*arbolito,nombre);
    if(strlen(nombre)>5 && encontrado==NULL)
    {
        verifica=1;
    }
    if(strlen(pass)>5 && verifica==1)
    {
        verifica=2;
    }
    if(strcmp(pass,pass2)==0 && verifica==2)
    {
        verifica=3;
    }
    if(verifica==3)
    {
        usuarioArbol nuevo;
        strcpy(nuevo.nombre,nombre);
        strcpy(senior.nombre,nombre);//MAXI SE LA COME
        EncriptarPass(pass,nuevo.MatrizPassword,nuevo.MatrizAsignada);
        *arbolito=InsertarArbol(*arbolito,nuevo);
        verifica=4;
        encontrado=BuscarArbol(*arbolito,nombre);
        ///Inicializo Objetivos
        for(int i=0 ; i<CANTOBJETIVOs ; i++)
            encontrado->dato.objetivos[i]=0;
        encontrado->dato.objetivos[6]+=1;
        encontrado->dato.objetivos[7]+=1;

    }


    return verifica;

}

int VerificarLogeo(nodoArbol* arbolito,char nombre[30],char pass[14],usuarioArbol senior)
{
    int verifica=0;
    nodoArbol* encontrado=BuscarArbol(arbolito,nombre);
    if(encontrado!=NULL)
    {
        verifica=5;
        float Resultado[2][7];
        float MCodificada[2][7];
        DesencriptarPass(encontrado->dato.MatrizAsignada,encontrado->dato.MatrizPassword,Resultado);
        CodificarMatriz(pass,MCodificada);
        verifica=CompararMatrices(MCodificada,Resultado);
        if(verifica==6)
            strcpy(senior.nombre,nombre);
    }

    return verifica;
}


///FUNCIONALIDAD DE LOS MENUS PRINCIPALES ----------------------------------------------------------------------------
// FUNCIONES ADMIN

nodoArbol* BorrarUsuario(nodoArbol* arbolito,scoreMapas ADS[], char nombre[30])
{
    nodo *seg;
    arbolito=BorrarNodoArbol(arbolito,nombre);
    for(int i=0; i<CANTMAPAS; i++)
    {
        seg=ADS[i].lista;
        while(seg!=NULL)
        {

            if(strcmp(seg->dato.nombre,nombre)==0)
                ADS[i].lista=borrarNodo(nombre,ADS[i].lista);

            seg=seg->siguiente;

        }
    }


    return arbolito;
}

bool ModificarNombreUser(nodoArbol** arbolito,scoreMapas ADS[],char nombreAbuscar[30],char nombreMod[30])
{


    nodoArbol *encontrado=BuscarArbol(*arbolito,nombreAbuscar);
    bool valida=FALSE;
    if(encontrado && strlen(nombreMod)>5)
    {
        nodo *seg;
        valida=TRUE;
        strcpy(encontrado->dato.nombre,nombreMod);
        for(int i=0; i<CANTMAPAS; i++)
        {
            seg=ADS[i].lista;
            while(seg!=NULL)
            {

                if(strcmp(seg->dato.nombre,nombreAbuscar)==0)
                    strcpy(seg->dato.nombre,nombreMod);

                seg=seg->siguiente;

            }
        }


    }
    return valida;
}

bool ModificarPassUser(nodoArbol** arbolito,char nombreUser[30], char passNew[14])
{
    nodoArbol *encontrado=BuscarArbol(*arbolito,nombreUser);
    bool valida=FALSE;
    if(encontrado && strlen(passNew)>5)
    {
        valida=TRUE;

        EncriptarPass(passNew,encontrado->dato.MatrizPassword,encontrado->dato.MatrizAsignada);

    }
    return valida;
}

void VerUsuarios(nodo* listaUser, ALLEGRO_FONT* letra, int xini, int yini,int tam)
{


    nodo * seg=listaUser;
    int i=0;
    int total=0;
    while(seg!=NULL && total<60)
    {
        while(seg!=NULL && i<15)
        {
            al_draw_text(letra,al_map_rgb(255,255,0),xini,yini,0,seg->dato.nombre);
            yini+=(tam+2);
            i++;
            total++;
            seg=seg->siguiente;
        }
        i=0;
        xini+=200;
        yini=170;


    }


}

void mostrarUnUsuario(usuarioLista aux,int x, int y, ALLEGRO_FONT* fuente,int tam, int flag,ALLEGRO_MONITOR_INFO info) //flag para ocultar nombre
{
    char Score[10];
    strcpy(Score,itoa(aux.Score,Score,10));

    al_draw_text(fuente,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+x,(info.y2-ALTO)/2+y,0,Score);
    al_draw_text(fuente,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+x+(tam*4),(info.y2-ALTO)/2+y,0,aux.Fecha);
    if(flag==1)
        al_draw_text(fuente,al_map_rgb(255,0,0),(info.x2-ANCHO)/2+x+(tam*10),(info.y2-ALTO)/2+y,0,aux.nombre);


}

void MostrarScoresUsuario(scoreMapas ADS[],int i,char nombre[],int x,ALLEGRO_FONT* fuente, int tam,ALLEGRO_MONITOR_INFO info)
{

    nodo *seg=ADS[i].lista;
    int y=220;
    int contar=0;
    while(seg!=NULL)
    {

        if(strcmp(seg->dato.nombre,nombre)==0 && contar<5)
        {
            mostrarUnUsuario(seg->dato,x,y,fuente,tam,0,info);
            y+=(tam+2);
            contar++;
        }
        seg=seg->siguiente;
    }



}


void MostrarHighscores(scoreMapas ADS[],int i,int x,ALLEGRO_FONT* fuente, int tam,ALLEGRO_MONITOR_INFO info)
{

    nodo *seg=ADS[i].lista;
    int y=220;
    int contar=0;
    while(seg!=NULL)
    {
        if( contar<10)
        {
            mostrarUnUsuario(seg->dato,x,y,fuente,tam,1,info);
            y+=(tam+2);
            contar++;
        }
        seg=seg->siguiente;
    }
}


void MostrarScoreMapas(scoreMapas ADS[], int xini,char nombre[],ALLEGRO_FONT* fuente, int tam, int flag,ALLEGRO_MONITOR_INFO info) //Bandera para Highscores 0 o ScoresUsuario 1
{

    for(int i=0; i<CANTMAPAS; i++)
    {
        switch(flag)
        {
        case 0:
            MostrarHighscores(ADS,i,xini,fuente,tam,info);
            xini+=350;
            break;
        case 1:
            MostrarScoresUsuario(ADS,i,nombre,xini,fuente,tam,info);
            xini+=250;
            break;

        }
    }
}

///OBJETIVOS




//TECLADO
// Funcion Escritura Teclado


int EscribirTeclado(int cantidad,char palabra[cantidad], int flagRegion,char passOculto[], int flagOculto,ALLEGRO_MONITOR_INFO info) //flag region para las cajas de escritura // flag oculto para ocultar pass
{

    ALLEGRO_KEYBOARD_STATE estado;
    al_get_keyboard_state(&estado);
    int enter=0;

    if(strlen(palabra)<cantidad-1)
    {
        if(al_key_down(&estado,ALLEGRO_KEY_A) )
        {
            strcat(palabra,"a");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_B) )
        {
            strcat(palabra,"b");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_C) )
        {
            strcat(palabra,"c");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_D) )
        {
            strcat(palabra,"d");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_E) )
        {
            strcat(palabra,"e");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_F) )
        {
            strcat(palabra,"f");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_G) )
        {
            strcat(palabra,"g");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_H) )
        {
            strcat(palabra,"h");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_I) )
        {
            strcat(palabra,"i");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_J) )
        {
            strcat(palabra,"j");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_K) )
        {
            strcat(palabra,"k");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_L) )
        {
            strcat(palabra,"l");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_M) )
        {
            strcat(palabra,"m");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_N) )
        {
            strcat(palabra,"n");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_O) )
        {
            strcat(palabra,"o");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_P) )
        {
            strcat(palabra,"p");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_Q) )
        {
            strcat(palabra,"q");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_R) )
        {
            strcat(palabra,"r");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_S) )
        {
            strcat(palabra,"s");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_T) )
        {
            strcat(palabra,"t");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_U) )
        {
            strcat(palabra,"u");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_V) )
        {
            strcat(palabra,"v");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_W) )
        {
            strcat(palabra,"w");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_X) )
        {
            strcat(palabra,"x");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_Y) )
        {
            strcat(palabra,"y");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_Z) )
        {
            strcat(palabra,"z");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_0) )
        {
            strcat(palabra,"0");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_1) )
        {
            strcat(palabra,"1");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_2) )
        {
            strcat(palabra,"2");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_3) )
        {
            strcat(palabra,"3");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_4) )
        {
            strcat(palabra,"4");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_5) )
        {
            strcat(palabra,"5");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_6) )
        {
            strcat(palabra,"6");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_7) )
        {
            strcat(palabra,"7");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_8) )
        {
            strcat(palabra,"8");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_9) )
        {
            strcat(palabra,"9");
        }
        if(al_key_down(&estado,ALLEGRO_KEY_ENTER) )
        {
            enter=1;
        }
    }

    if(al_key_down(&estado,ALLEGRO_KEY_BACKSPACE) && strlen(palabra)>0)
    {
        palabra[strlen(palabra)-1]='\0';
        if(flagOculto==1 && strlen(passOculto)>0)
            passOculto[strlen(passOculto)-1]='\0';
        switch(flagRegion)
        {
        case 0:
            al_set_clipping_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+190,(info.x2-ANCHO)/2+265,(info.y2-ALTO)/2+45);
            break;
        case 1:
            al_set_clipping_rectangle((info.x2-ANCHO)/2+30,(info.y2-ALTO)/2+330,(info.x2-ANCHO)/2+265,(info.y2-ALTO)/2+45);
            break;
        case 2:
            al_set_clipping_rectangle((info.x2-ANCHO)/2+360,(info.y2-ALTO)/2+330,(info.x2-ANCHO)/2+265,(info.y2-ALTO)/2+45);
            break;
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        al_set_clipping_rectangle(0,0,info.x2,info.y2);
    }
    else
    {

        if(flagOculto==1 && strlen(passOculto)<cantidad-1 && strlen(passOculto)>=0 && strlen(palabra)>0 && !al_key_down(&estado,ALLEGRO_KEY_ENTER))
            strcat(passOculto,"*");


    }
    return enter;
}


