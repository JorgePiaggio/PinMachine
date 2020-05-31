#include "jugabilidad.h"
#include "mostrar.h"



bool Inicializar()
{
    bool validar;
    if(al_init())
    {
        validar=al_init_image_addon();
        if(validar)
        {
            al_init_font_addon();
            {
                validar=al_init_ttf_addon();
                {
                    if(validar)
                    {
                        validar=al_init_primitives_addon();
                        if(validar)
                        {
                            validar=al_install_keyboard();
                            if(validar)
                            {
                                validar=al_install_mouse();
                                if(validar)
                                {
                                    validar=al_install_audio();
                                    if(validar)
                                    {
                                        validar=al_init_acodec_addon();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(validar==FALSE)
        printf("Error al inicializar\n");

    return validar;

}



nodoArbol* sesion(scoreMapas ADS[],nodoArbol* arbolUsuarios)
{
    if(Inicializar())
    {
        ALLEGRO_DISPLAY *buffer=NULL;
        ALLEGRO_MONITOR_INFO info;
        al_get_monitor_info(0,&info);

        ALLEGRO_EVENT_QUEUE *colaeventos=NULL;
        ALLEGRO_FONT *metal1, *metal2/*,*metal3*/;
        ALLEGRO_EVENT evento;
        ALLEGRO_BITMAP *pantalla=NULL;
        ALLEGRO_BITMAP *icon=al_load_bitmap("img/icon.bmp");
//        buffer=al_create_display(ANCHO,ALTO);
        buffer=al_create_display(info.x2,info.y2);
        al_set_target_bitmap(al_get_backbuffer(buffer));
        al_set_window_title(buffer,"PINMACHINE");
        al_set_display_icon(buffer,icon);
        colaeventos=al_create_event_queue();
        al_register_event_source(colaeventos, al_get_display_event_source(buffer));
        al_register_event_source(colaeventos, al_get_keyboard_event_source());

        ///SONIDO
        ALLEGRO_MIXER *musicMixer=NULL;
        ALLEGRO_VOICE *voice=NULL;
        voice=al_create_voice(44100,ALLEGRO_AUDIO_DEPTH_INT16,ALLEGRO_CHANNEL_CONF_2);          ///CREAR VOZ
        musicMixer=al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,ALLEGRO_CHANNEL_CONF_2);  ///CREAR MIXER
        al_attach_mixer_to_voice(musicMixer,voice);                                             ///VINCULAR MIXER A VOZ
        ///STREAMS
        ALLEGRO_AUDIO_STREAM *song=al_load_audio_stream("audio/Arcadia.wav",4,2048);
        ALLEGRO_AUDIO_STREAM *song1=al_load_audio_stream("audio/SeDicePinball,NoFlipper.wav",4,2048);
        ALLEGRO_AUDIO_STREAM *song2=al_load_audio_stream("audio/AguaEnPolvo.wav",4,2048);
        al_attach_audio_stream_to_mixer(song,musicMixer);
        al_attach_audio_stream_to_mixer(song1,musicMixer);
        al_attach_audio_stream_to_mixer(song2,musicMixer);
        al_set_audio_stream_playmode(song,ALLEGRO_PLAYMODE_LOOP);
        al_set_audio_stream_playmode(song1,ALLEGRO_PLAYMODE_LOOP);
        al_set_audio_stream_playmode(song2,ALLEGRO_PLAYMODE_LOOP);
        al_set_audio_stream_playing(song1,false);
        al_set_audio_stream_playing(song2,false);
        al_set_mixer_gain(musicMixer,1.0);
        ///SAMPLES
        ALLEGRO_SAMPLE *sample[CANTSOUNDS]= {NULL};
        ALLEGRO_SAMPLE_INSTANCE *eff[CANTSOUNDS]= {NULL};
        ALLEGRO_SAMPLE *over=al_load_sample("audio/efectos/GameOver.wav");
        ALLEGRO_SAMPLE_INSTANCE *gameOver=al_create_sample_instance(over);

        ALLEGRO_MIXER *sfxMixer=al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,ALLEGRO_CHANNEL_CONF_2);
        al_attach_sample_instance_to_mixer(gameOver,sfxMixer);
        al_attach_mixer_to_mixer(sfxMixer,musicMixer);
        al_set_mixer_gain(sfxMixer,0.7);
        al_reserve_samples(CANTSOUNDS);
        sample[0]=al_load_sample("audio/efectos/palI.wav");
        sample[1]=al_load_sample("audio/efectos/palD.wav");
        sample[2]=al_load_sample("audio/efectos/rebo.wav");
        sample[3]=al_load_sample("audio/efectos/lanzador.wav");
        sample[4]=al_load_sample("audio/efectos/lanzadorCarga.wav");
        sample[5]=al_load_sample("audio/efectos/roulette.wav");
        sample[6]=al_load_sample("audio/efectos/reacc.wav");
        sample[7]=al_load_sample("audio/efectos/target.wav");
        sample[8]=al_load_sample("audio/efectos/target2.wav");
        sample[9]=al_load_sample("audio/efectos/tilt.wav");
        sample[12]=al_load_sample("audio/efectos/+500.wav");
        sample[10]=al_load_sample("audio/efectos/bonus.wav");
        sample[11]=al_load_sample("audio/efectos/extraBall.wav");

        for(int w=0; w<CANTSOUNDS; w++)
        {
            eff[w]=al_create_sample_instance(sample[w]);
        }
        for(int z=0; z<CANTSOUNDS; z++)
        {
            al_attach_sample_instance_to_mixer(eff[z],sfxMixer);
        }

        ///FUENTES
        metal1=al_load_font ("fonts/Metal1.ttf",20,0);
        metal2=al_load_font ("fonts/Metal2.otf",50,0);
//        metal3=al_load_font ("fonts/Metal3.ttf",10,0);

        ///MAPAS IMG
        ALLEGRO_BITMAP *map1=al_load_bitmap("img/fondohexa.bmp");
        ALLEGRO_BITMAP *map1b=al_load_bitmap("img/mapahexacontorno.bmp");
        ALLEGRO_BITMAP *map2=al_load_bitmap("img/guitar1.bmp");
        ALLEGRO_BITMAP *map2b=al_load_bitmap("img/guitarb1.bmp");

        ///MAPAS TRANSPARENCIAS
        al_convert_mask_to_alpha(map1b, al_map_rgb(0,0,0));
        al_convert_mask_to_alpha(map2b, al_map_rgb(0,0,0));

        ///ARREGLO DE MAPAS
        mapaFlipper mapas[4];
        mapas[0].fondo=map1;
        mapas[0].paredes=map1b; ///CARGAR FONDOS
        mapas[1].fondo=map2;
        mapas[1].paredes=map2b;
        mapaFlipper *actual=NULL;
        int flagmapas=0;
        ///USER
        char usr[30];
        char usrpass[30];
        int usrLogueado=0;  /// == 1 usuario logueado en el juego
        bool playing=false;
        strcpy(usr,"GUEST 255");

        ///MENU
        while(flagmapas!=30)
        {
            flagmapas=menuJuego(actual,usr,usrpass,&arbolUsuarios,ADS,&usrLogueado,info);

            switch(flagmapas)
            {
            case 11:    ///MAPA1
                actual=&mapas[0];
                flagmapas=1;
                al_set_audio_stream_playing(song,false);
                playing=false;
                al_set_audio_stream_playing(song1,true);
                al_clear_to_color(al_map_rgb(0,0,0));
                al_flip_display();
                juegoNuevo(actual,&arbolUsuarios, flagmapas, buffer, pantalla, colaeventos, &evento, metal1,metal2,musicMixer,voice,arbolUsuarios,ADS,usr,eff,gameOver,info);
                al_set_audio_stream_playing(song1,false);
                break;
            case 12:    ///MAPA2
                actual=&mapas[1];
                flagmapas=2;
                al_set_audio_stream_playing(song,false);
                playing=false;
                al_set_audio_stream_playing(song2,true);
                al_clear_to_color(al_map_rgb(0,0,0));
                al_flip_display();
                juegoNuevo(actual,&arbolUsuarios, flagmapas, buffer, pantalla, colaeventos, &evento, metal1,metal2,musicMixer,voice,arbolUsuarios,ADS,usr,eff,gameOver,info);
                al_set_audio_stream_playing(song2,false);
                break;
            }

            playing=al_get_audio_stream_playing(song);
            if(!playing)
                al_set_audio_stream_playing(song,true);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_flip_display();
        }
    }

//    al_destroy_mixer(musicMixer);
//    al_destroy_voice(voice);
//    al_destroy_display(buffer);
//    al_destroy_bitmap(mapa1);
//    al_destroy_bitmap(hexa);
//    al_destroy_bitmap(bola);
//    al_destroy_bitmap(paleta);
//    al_destroy_timer(timerJuego);

    return arbolUsuarios;
}




void juegoNuevo(mapaFlipper *actual,nodoArbol** arbolUsuarios, int flagmapas, ALLEGRO_DISPLAY *buffer, ALLEGRO_BITMAP *pantalla, ALLEGRO_EVENT_QUEUE *colaeventos, ALLEGRO_EVENT *evento, ALLEGRO_FONT *metal1,ALLEGRO_FONT *metal2,ALLEGRO_MIXER *musicMixer,ALLEGRO_VOICE *voice, nodoArbol* arbolUser, scoreMapas ADS[], char usr[30],ALLEGRO_SAMPLE_INSTANCE*eff[],ALLEGRO_SAMPLE_INSTANCE* gameOver,ALLEGRO_MONITOR_INFO info)
{

    int salir=0;
    bool presionado=FALSE;
    int colisiono=0;
    int gameover=0;
    int score=0;
    char scoreString[30]= {'0'};
    float xchoque=0;
    float ychoque=0;
    int contarAnimado[CANTOBJETOSANIMADOS]= {0};
    int objetoColision[2]= {0}; // indica que objeto y cual de ellos.
    int indiceResorte=1;
    int finAnimacion[CANTOBJETOSANIMADOS]= {0};
    int validos[CANTOBJETOSANIMADOS]= {0}; // arreglo de inidices de rebotadores para animacion
    int contarTilt=0;
    int vidas=3;
    int BarreraMov=1;
    int BarreraMovY=1;
    int contarTarget=0;
    int ocultarBola=0;
    int giroRuleta=30;
    int finRuleta=0;
    int regionElegida=0; //utilizada para ver donde frena la ruleta
    int bonus=1; // bonus de la ruleta
    int indiceMsj=0; //inicializo mensajes
    int tiempoMsj=5000;
    nodoArbol* encontrado=BuscarArbol(*arbolUsuarios,usr); ///Para Objetivo

    /// COMUNES A TODOS LOS MAPAS
    ALLEGRO_BITMAP* bola=al_load_bitmap("img/bola5.bmp");
    ALLEGRO_BITMAP* paleta=al_load_bitmap("img/paletaI.bmp");
    ALLEGRO_BITMAP* rebotador=al_load_bitmap("img/rebotador.bmp");
    ALLEGRO_BITMAP* reaccionario1=al_load_bitmap("img/reaccionario1.bmp");
    ALLEGRO_BITMAP* reaccionario2=al_load_bitmap("img/reaccionario2.bmp");
    ALLEGRO_BITMAP* tope=al_load_bitmap("img/tope.bmp");
    ALLEGRO_BITMAP* tope2=al_load_bitmap("img/tope3.bmp");
    ALLEGRO_BITMAP* tilt=al_load_bitmap("img/tilt.bmp");
    ALLEGRO_BITMAP* Spin=al_load_bitmap("img/spin/spinmask45x3.bmp");
    ALLEGRO_BITMAP* SpinSalida=al_load_bitmap("img/spin/salida.bmp");
    ALLEGRO_BITMAP* target=al_load_bitmap("img/target.bmp");
    ALLEGRO_BITMAP* barrera=al_load_bitmap("img/barrera.bmp");
    ALLEGRO_BITMAP* GameOver=al_load_bitmap("img/gameover.bmp");
    ALLEGRO_BITMAP* visor=al_load_bitmap("img/Visor.bmp");
    ALLEGRO_BITMAP* reb=al_load_bitmap("img/reb.bmp");
    ALLEGRO_BITMAP* reac=al_load_bitmap("img/reac.bmp");


    ALLEGRO_BITMAP* Msj[CANTMSJs]; ///Cargo los mensajes del visor
    Msj[8]=al_load_bitmap("img/500Msj.bmp");
    Msj[7]=al_load_bitmap("img/upsMsj.bmp");
    Msj[6]=al_load_bitmap("img/extraBallMsj.bmp");
    Msj[5]=al_load_bitmap("img/bonusMsj.bmp");
    Msj[4]=al_load_bitmap("img/bonus3Msj.bmp");
    Msj[3]=al_load_bitmap("img/Msj1.bmp");
    Msj[2]=al_load_bitmap("img/Msj2.bmp");
    Msj[1]=al_load_bitmap("img/Msj3.bmp");
    Msj[0]=al_load_bitmap("img/Msj4.bmp");
    for(int i=0; i<CANTMSJs ; i++)
        al_convert_mask_to_alpha(Msj[i], al_map_rgb(0,0,0));
    ALLEGRO_BITMAP* resorte[8];
    resorte[0]=al_load_bitmap("img/resorte1.bmp");
    resorte[1]=al_load_bitmap("img/resorte2.bmp");
    resorte[2]=al_load_bitmap("img/resorte3.bmp");
    resorte[3]=al_load_bitmap("img/resorte4.bmp");
    resorte[4]=al_load_bitmap("img/resorte5.bmp");
    resorte[5]=al_load_bitmap("img/resorte6.bmp");
    resorte[6]=al_load_bitmap("img/resorte7.bmp");
    resorte[7]=al_load_bitmap("img/resorte8.bmp");
//    al_convert_mask_to_alpha(bola, al_map_rgb(255,0,255));
    al_convert_mask_to_alpha(bola, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(target, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(Spin, al_map_rgb(45,45,45));
    al_convert_mask_to_alpha(SpinSalida, al_map_rgb(22,0,102));
    al_convert_mask_to_alpha(paleta, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(rebotador, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(reaccionario1, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(reaccionario2, al_map_rgb(0,0,0));

    for(int i=0 ; i<8; i++)
        al_convert_mask_to_alpha(resorte[i], al_map_rgb(255,255,255));
    ALLEGRO_COLOR colorbuffer;
    ALLEGRO_TIMER *timerJuego=NULL;
    ALLEGRO_TIMER *timerChoque=NULL;
    ALLEGRO_TIMER *timerAnimacion[CANTOBJETOSANIMADOS];
    ALLEGRO_TIMER *timerResorte=NULL;
    ALLEGRO_TIMER *timerTilt=al_create_timer(1.0/1000);
    ALLEGRO_TIMER *timerBarrera=al_create_timer(1.0/1000);
    ALLEGRO_TIMER *timerRuleta=al_create_timer(1.0/1000);
    ALLEGRO_TIMER *timerBonusRuleta=al_create_timer(1.0/1000);
    ALLEGRO_TIMER *timerGameOver=al_create_timer(1.0/1000);
    ALLEGRO_TIMER *timerMsjs=al_create_timer(1.0/1000);
    for(int i=0; i<CANTOBJETOSANIMADOS; i++)
        timerAnimacion[i]=al_create_timer(1.0/1000);
    timerResorte=al_create_timer(1.0/1000);
    timerJuego=al_create_timer(1.0/FPS);
    timerChoque=al_create_timer(1.0/1000);
    al_start_timer(timerJuego);
    al_start_timer(timerChoque);
    al_start_timer(timerTilt);
    al_start_timer(timerBarrera);
    al_start_timer(timerMsjs);
    al_register_event_source(colaeventos, al_get_timer_event_source(timerJuego));
    ALLEGRO_KEYBOARD_STATE state;

    ///

    CargarMapas(actual, flagmapas,info);
    int xinicial=actual->bola.x;
    int yinicial=actual->bola.y;
    int indiceRebotador[actual->cantidadRebotadores]; /// Cantidad De objetos para animar por tipo
    int indiceReactor[actual->cantidadReaccionarios];
    for(int i=0; i<actual->cantidadRebotadores; i++)  /// Inicializo dichos objetos
        indiceRebotador[i]=0;
    for(int i=0; i<actual->cantidadReaccionarios; i++)
        indiceReactor[i]=0;


    ///INICIO JUEGO

    while(salir==0 && gameover==0)
    {
        al_wait_for_event(colaeventos, evento);

        if(vidas==0)
            gameover=1;

        if(al_get_timer_count(timerJuego)>1/FPS) /// dibujo frame a frame de los objetos
        {
            mostrarMapa(actual,bola,resorte,rebotador,tope,tope2,reaccionario1,reaccionario2,paleta,metal1,metal2,indiceResorte,scoreString,vidas, flagmapas,barrera,target,Spin,SpinSalida,ocultarBola,visor,Msj,indiceMsj,info);

            if(contarTilt>0 && al_get_timer_count(timerTilt)>500)
                MostrarTilt(metal2,tilt,info);
            pantalla=al_get_backbuffer(buffer); /// toma el buffer de la pantalla y lo convierte en un BITMAP

            ///ESPACIO RESERVADO PARA PUBLICIDAD.

            al_flip_display();

            if(actual->bola.y+RADIOP < actual->limiteInferior)
            {
                colisiono=Colision(bola,pantalla,actual,&colorbuffer,&xchoque,&ychoque,objetoColision,eff,flagmapas); ///BUSCAR COLISION COMPARANDO PIXELES
            }
            else
            {
                actual->bola.y=700;
                actual->bola.x=0;
                actual->bola.velocidad=0;
                mostrarMapa(actual,bola,resorte,rebotador,tope,tope2,reaccionario1,reaccionario2,paleta,metal1,metal2,indiceResorte,scoreString,vidas, flagmapas,barrera,target,Spin,SpinSalida,ocultarBola,visor,Msj,indiceMsj,info);
                al_flip_display();
                al_rest(0.5);
                actual->bola.y=yinicial;
                actual->bola.x=xinicial;
                actual->bola.velocidad=0;
                vidas--;
                indiceResorte=1;
                if(contarTarget==actual->cantidadBlancos) // reinicio targets si los rompio todos y perdio una bola
                {
                    for(int i=0; i<actual->cantidadBlancos; i++)
                        actual->Blancos[i].region=60;
                    contarTarget=0;
                }

                RestaurarPosicionBola(actual,xinicial,yinicial,0,flagmapas);
            }


            if(colisiono==1)  // si hay colision cambia la direccion
            {
                DireccionBola(actual,xchoque,ychoque);
                indiceResorte=1;
            }
            else
            {
                actual->bola.velocidad*=0.999995;             ///FRICCION
                actual->bola.dy+=0.012;                          ///GRAVEDAD
            }

            actual->bola.x+=actual->bola.dx*actual->bola.velocidad;     ///ACTUALIZAR VELOCIDAD
            actual->bola.y+=actual->bola.dy*actual->bola.velocidad;
            if(actual->bola.velocidad<1)
                actual->bola.velocidad=1;

        al_set_timer_count(timerJuego,0);
        }



        ///EVENTOS TECLADO, ANIMACIONES, SONIDOS

        if(evento->type==ALLEGRO_EVENT_KEY_CHAR) /// Animacion del resorte + funcionalidad
        {
            if(evento->keyboard.keycode==ALLEGRO_KEY_SPACE)
            {
                presionado=TRUE;

                al_start_timer(timerResorte);
                if(al_get_timer_count(timerResorte)>70)
                {

                    if(indiceResorte<7)
                    {
                        indiceResorte++;
                        actual->resorte.fuerza=indiceResorte;
                        cortarSample(eff);
                        al_play_sample_instance(eff[4]);
                    }
                    al_set_timer_count(timerResorte,0);
                }
            }
        }


        if(presionado==FALSE)  /// Resorte si la tecla espacio no esta pulsada
        {
            if(al_get_timer_count(timerResorte)>10)
            {
                if(indiceResorte>0)
                {
                    indiceResorte--;
                }
                else
                {
                    al_stop_timer(timerResorte);
                }
                al_set_timer_count(timerResorte,0);
                cortarSample(eff);
                al_play_sample_instance(eff[3]);
            }
        }

        RestaurarPosicionBola(actual,xinicial,yinicial,colisiono,flagmapas);

        al_get_keyboard_state(&state);
        bool KEY_RIGHT=al_key_down(&state,ALLEGRO_KEY_RIGHT);           ///ROTACION GRADUAL DE FLIPPERS (PALETAS)
        if(KEY_RIGHT==TRUE)                                                     ///DERECHA
        {
            if(actual->paleta[1].angulo<0.5)
                actual->paleta[1].angulo+=0.06;
            if((actual->cantidadPaletas == 3) && (actual->paleta[2].angulo<0.3))
                actual->paleta[2].angulo+=0.06;
            if((actual->paleta[1].angulo<-0.1) && (actual->paleta[1].angulo>-0.3))
            {
                cortarSample(eff);
                al_set_sample_instance_playing(eff[0],true);
            }
        }

        al_get_keyboard_state(&state);
        bool KEY_LEFT=al_key_down(&state,ALLEGRO_KEY_LEFT);

        if(KEY_LEFT==TRUE)                                                      ///IZQUIERDA
        {
            if(actual->paleta[0].angulo>-0.5)
            {
                actual->paleta[0].angulo-=0.06;
            }
            if((actual->paleta[0].angulo>0.1) && (actual->paleta[0].angulo<0.3))
            {
                cortarSample(eff);
                al_set_sample_instance_playing(eff[1],true);
            }
        }


        if(evento->type==ALLEGRO_EVENT_KEY_UP)   ///RESTAURAR PALETAS
        {
            actual->paleta[1].angulo=-0.3;
            actual->paleta[0].angulo=0.3;
            if(actual->cantidadPaletas == 3)
                actual->paleta[2].angulo=-0.5;
            presionado=FALSE;
        }

        /// FUNCIONES DEL TILT

        if(evento->type==ALLEGRO_EVENT_KEY_DOWN)
        {
            if(evento->keyboard.keycode==ALLEGRO_KEY_UP)  /// Funciones TILT
            {
                al_start_timer(timerTilt);
                cortarSample(eff);
                al_set_sample_instance_playing(eff[9],true);
            }
        }

        if(al_get_timer_count(timerTilt)>1000)
        {
            contarTilt++;
            al_stop_timer(timerTilt);
            al_set_timer_count(timerTilt,0);
            Tilt(actual);
        }

        if(contarTilt==4)
        {
            contarTilt=0;
            vidas--;
            if(vidas==0)
                gameover=1;
            actual->bola.x=xinicial;
            actual->bola.y=yinicial;
            actual->bola.velocidad=0;
        }


        al_get_keyboard_state(&state);
        if(al_key_down(&state,ALLEGRO_KEY_ESCAPE))
            salir=1;

        /// SCORE Y ANIMACIONES /// Indice 0-Rebotadores , 1-Reactores , 2- etc....
        if(objetoColision[0]>2 && colisiono==1 && al_get_timer_count(timerChoque)>30 ) /// Si colisiono con un Rebotador, reactor, etc....
        {
            switch(objetoColision[0])
            {
            case 3:
                score+=(50*bonus);
                scratch(reb,0,info);
                al_start_timer(timerAnimacion[0]);
                validos[0]=AgregarColaAnimacion(objetoColision[0],objetoColision[1],contarAnimado,indiceRebotador,validos[0]); /// agregar rebotadores a la cola para animar
                break;
            case 4:
                score+=(30*bonus);
                scratch(reac,1,info);
                al_start_timer(timerAnimacion[1]);
                validos[1]=AgregarColaAnimacion(objetoColision[0],objetoColision[1],contarAnimado,indiceReactor,validos[1]);
                break;
            case 5:  // control de targets
                actual->Blancos[objetoColision[1]].region-=60;
                if(actual->Blancos[objetoColision[1]].region<0)
                {
                    score+=(100*bonus);
                    contarTarget++;
                    cortarSample(eff);
                    al_set_sample_instance_playing(eff[8],true);
                }
                else
                {
                    if(actual->Blancos[objetoColision[1]].region==0)
                    {
                        cortarSample(eff);
                        al_set_sample_instance_playing(eff[7],true);
                    }
                }
                if(contarTarget==actual->cantidadBlancos)
                    score+=(500*bonus);
                break;
            }

            itoa(score,scoreString,10);
            al_set_timer_count(timerChoque,0);

        }

        ///Animo los objetos de la cola

        for(int i=0; i<CANTOBJETOSANIMADOS; i++)
        {
            if(al_get_timer_count(timerAnimacion[i])>200 && finAnimacion[i]==0/*&& objetoColision[0]==4*/)
                finAnimacion[i]=AnimarReactor(actual,contarAnimado,indiceReactor,validos[i]);
            if(al_get_timer_count(timerAnimacion[i])>500 && finAnimacion[i]==0)
            {
                finAnimacion[i]=AnimarRebotador(actual,contarAnimado,indiceRebotador,validos[i]);
                al_set_timer_count(timerAnimacion[i],0);
            }
            else
            {
                if(finAnimacion[i]==1)
                {
                    al_stop_timer(timerAnimacion[i]);
                    al_set_timer_count(timerAnimacion[i],0);
                    finAnimacion[i]=0;

                    for(int j=0; j<validos[i] ; j++)
                    {
                        switch(i)
                        {
                        case 0:
                            actual->rebotador[indiceRebotador[j]].region=ANCHOREBOTADOR*2; ///reinicia la imagen correspondiente en todos los rebotadores apagados
                            break;

                        case 1:
                            actual->reaccionario[indiceReactor[j]].region=ANCHOREBOTADOR*2; ///reinicia la imagen correspondiente en todos los reactores apagados
                            break;
                        }
                    }
                    validos[i]=0;
                }
            }
        }

        ///Mover Barreras

        if(al_get_timer_count(timerBarrera)>actual->barreras[0].velocidad)
        {
            for(int i=0; i<actual->cantidadBarreras; i++)
            {
                if(actual->barreras[i].angulo==0)
                    MoverBarrera(actual,i,0,&BarreraMov);
                else
                    MoverBarrera(actual,i,1,&BarreraMovY);
            }
            al_set_timer_count(timerBarrera,0);
        }
        /// COLISION RULETA


        if((actual->bola.y >= actual->Ruleta.huecoy-35) && (actual->bola.y <= actual->Ruleta.huecoy-10))
        {
            if((actual->bola.x >= actual->Ruleta.huecox+12) && (actual->bola.x <= actual->Ruleta.huecox+32))
            {
                al_start_timer(timerRuleta);
                ocultarBola=1;
                giroRuleta=30;
                srand(time(NULL));
                finRuleta= rand()%100;
            }
        }

        if(ocultarBola==1)
        {
            actual->bola.x=0;
            actual->bola.y=0;
            actual->bola.velocidad=0;
            actual->bola.dx=0;
            actual->bola.dy=0;
        }

        /// Giro aleatorio ruleta

        if(al_get_timer_count(timerRuleta)>giroRuleta)
        {
            al_set_timer_count(timerRuleta,0);
            actual->Ruleta.region+=66.66;
            if(actual->Ruleta.region>339)
                actual->Ruleta.region=0;
            giroRuleta+=5;
            cortarSample(eff);
            al_play_sample_instance(eff[5]);

            if(giroRuleta>200+finRuleta)
            {
                al_stop_timer(timerRuleta);
                al_set_timer_count(timerRuleta,0);
                giroRuleta=30;
                ocultarBola=0;
                actual->bola.x=actual->Ruleta.salidax;
                actual->bola.y=actual->Ruleta.saliday;
                actual->bola.velocidad=5;
                actual->bola.dx=1;
                actual->bola.dy=1;
                regionElegida=(int) actual->Ruleta.region;
                switch(regionElegida)
                {

                case 0:
                    al_start_timer(timerBonusRuleta);
                    bonus=2;
                    indiceMsj=5;
                    tiempoMsj=15000;
                    al_set_timer_count(timerMsjs,0);
                    cortarSample(eff);
                    al_play_sample_instance(eff[10]);
                    if(encontrado)
                    {
                        if(encontrado->dato.objetivos[4]<CANTMAPAS)
                            encontrado->dato.objetivos[4]+=1;
                    }
                    break;
                case 66 ... 100:
                    vidas+=1;
                    indiceMsj=6;
                    if(encontrado)
                    {
                        if(encontrado->dato.objetivos[2]<CANTMAPAS)
                            encontrado->dato.objetivos[2]+=1;
                    }
                    al_set_timer_count(timerMsjs,0);
                    al_play_sample_instance(eff[11]);
                    break;
                case 198 ... 263:
                    al_start_timer(timerBonusRuleta);
                    bonus=2;
                    indiceMsj=5;
                    tiempoMsj=15000;
                    if(encontrado)
                    {
                        if(encontrado->dato.objetivos[4]<CANTMAPAS)
                            encontrado->dato.objetivos[4]+=1;
                    }
                    al_set_timer_count(timerMsjs,0);
                    cortarSample(eff);
                    al_play_sample_instance(eff[10]);
                    break;
                case 264 ... 332:
                    score+=500;
                    itoa(score,scoreString,10);
                    indiceMsj=8;
                    al_set_timer_count(timerMsjs,0);
                    if(encontrado)
                    {
                        if(encontrado->dato.objetivos[3]<CANTMAPAS)
                            encontrado->dato.objetivos[3]+=1;
                    }
                    cortarSample(eff);
                    al_play_sample_instance(eff[12]);
                    break;
                case 333 ... 334:
                    al_start_timer(timerBonusRuleta);
                    bonus=3;
                    indiceMsj=4;
                    tiempoMsj=15000;
                    al_set_timer_count(timerMsjs,0);
                    if(encontrado)
                    {
                        if(encontrado->dato.objetivos[5]<CANTMAPAS)
                            encontrado->dato.objetivos[5]+=1;
                    }
                    cortarSample(eff);
                    al_play_sample_instance(eff[10]);
                    break;

                default:
                    indiceMsj=7;
                    al_set_timer_count(timerMsjs,0);
                    break;



                }
            }
        }

/// tiempo de Bonus cuando toca la opcion
        if(al_get_timer_count(timerBonusRuleta)>15000)
        {

            al_set_timer_count(timerBonusRuleta,0);
            al_stop_timer(timerBonusRuleta);
            bonus=1;
        }

        srand(clock());
/// Tiempo de Mensajes
        if(al_get_timer_count(timerMsjs)>tiempoMsj)
        {
            if(indiceMsj<3)  //Para mensajes Casuales
            {
                indiceMsj++;
            }
            else
            {
                indiceMsj=rand()%4;
            }
            tiempoMsj=5000;
            al_set_timer_count(timerMsjs,0);


        }




    }
    if(gameover==1 )
    {
        AgregarScoresUsuario(usr,ADS,score,flagmapas);
        al_start_timer(timerGameOver);
        cortarSample(eff);
        al_play_sample_instance(gameOver);
        int contar=0;
        int RegionGameOver=0;

        /// Cuenta para habilitar Objetivos o logros del usuario

        if(encontrado)
        {
            switch(score)
            {
            case 1000 ... 2999:
                if(encontrado->dato.objetivos[0]<CANTMAPAS)
                    encontrado->dato.objetivos[0]=encontrado->dato.objetivos[0]+1;
                break;
            case 3000 ... 9999:
                if(encontrado->dato.objetivos[0]<CANTMAPAS)
                    encontrado->dato.objetivos[0]+=1;
                if(encontrado->dato.objetivos[1]<CANTMAPAS)
                    encontrado->dato.objetivos[1]+=1;
                break;
            case 10000 ... 19999:
                if(encontrado->dato.objetivos[0]<CANTMAPAS)
                    encontrado->dato.objetivos[0]+=1;
                if(encontrado->dato.objetivos[1]<CANTMAPAS)
                    encontrado->dato.objetivos[1]+=1;
                if(encontrado->dato.objetivos[6]<CANTMAPAS)
                    encontrado->dato.objetivos[6]+=1;
                break;
            case 20000 ... 999999:
                if(encontrado->dato.objetivos[0]<CANTMAPAS)
                    encontrado->dato.objetivos[0]+=1;
                if(encontrado->dato.objetivos[1]<CANTMAPAS)
                    encontrado->dato.objetivos[1]+=1;
                if(encontrado->dato.objetivos[6]<CANTMAPAS)
                    encontrado->dato.objetivos[6]+=1;
                if(encontrado->dato.objetivos[7]<CANTMAPAS)
                    encontrado->dato.objetivos[7]+=1;
                break;
            }
        }
        while(contar<10) ///Pantalla game over
        {
            al_draw_bitmap_region(GameOver,RegionGameOver,0,(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0,0,0);
            al_draw_text(metal1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+443,(info.y2-ALTO)/2+320,0,scoreString);
            al_draw_text(metal1,al_map_rgb(255,0,0),(info.x2-ANCHO)/2+520,(info.y2-ALTO)/2+275,0,usr);
            if(al_get_timer_count(timerGameOver)>150)
            {
                RegionGameOver+=ANCHO;
                al_set_timer_count(timerGameOver,0);
            }
            if(RegionGameOver>=ANCHO*5)
            {
                RegionGameOver=0;
                contar++;
            }
            al_flip_display();
        }

        al_stop_timer(timerGameOver);
        al_set_timer_count(timerGameOver,0);

    }

}




void mostrarMapa(mapaFlipper *actual, ALLEGRO_BITMAP* bola, ALLEGRO_BITMAP*resorte[8],ALLEGRO_BITMAP* rebotador,ALLEGRO_BITMAP*tope,ALLEGRO_BITMAP*tope2,ALLEGRO_BITMAP*reaccionario1,ALLEGRO_BITMAP*reaccionario2,ALLEGRO_BITMAP*paleta,
ALLEGRO_FONT* metal1, ALLEGRO_FONT* metal2, int indiceResorte, char scoreString[], int vidas, int flag,ALLEGRO_BITMAP* barrera,ALLEGRO_BITMAP* target,ALLEGRO_BITMAP* ruleta, ALLEGRO_BITMAP* salida,int OcultarBola, ALLEGRO_BITMAP* visor, ALLEGRO_BITMAP* Msj[],int indiceMsj,ALLEGRO_MONITOR_INFO info)
{

    int i=0;
    char Vidas[2];
    strcpy(Vidas,itoa(vidas,Vidas,10));
    srand(clock());

    al_draw_bitmap(actual->fondo,(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0);
    al_draw_bitmap_region(ruleta,actual->Ruleta.region,0,66.66,68,actual->Ruleta.x,actual->Ruleta.y,0);
    al_draw_bitmap(salida,actual->Ruleta.salidax,actual->Ruleta.saliday,0);
    al_draw_bitmap(salida,actual->Ruleta.huecox,actual->Ruleta.huecoy,0);
    switch(flag)
    {
    case 1:
        al_draw_rotated_bitmap(tope,0,0,actual->resorte.xtope,actual->resorte.ytope,actual->resorte.anguloTope,0);
        break;
    case 2:
        al_draw_rotated_bitmap(tope2,0,0,actual->resorte.xtope,actual->resorte.ytope,actual->resorte.anguloTope,0);
        break;
    }
    if(!OcultarBola)
        al_draw_bitmap(bola,actual->bola.x,actual->bola.y,0);
    al_draw_rotated_bitmap(resorte[indiceResorte],ANCHORESORTE-4,100,actual->resorte.x,actual->resorte.y,actual->resorte.angulo,0);

    while(i<actual->cantidadRebotadores)
    {
        al_draw_bitmap_region(rebotador,actual->rebotador[i].region,0,70,70,actual->rebotador[i].x,actual->rebotador[i].y,0);
        i++;
    }
    i=0;
    while(i<actual->cantidadReaccionarios)
    {
        if(i==2 || i==3)
            al_draw_bitmap_region(reaccionario1,actual->reaccionario[i].region,0,70,40,actual->reaccionario[i].x,actual->reaccionario[i].y,0);
        else
            al_draw_bitmap_region(reaccionario2,actual->reaccionario[i].region,0,70,40,actual->reaccionario[i].x,actual->reaccionario[i].y,0);
        i++;
    }
    i=0;
    while(i<actual->cantidadBarreras)
    {
        al_draw_rotated_bitmap(barrera,0,0,actual->barreras[i].x,actual->barreras[i].y,actual->barreras[i].angulo,0);
        i++;
    }
    i=0;
    while(i<actual->cantidadBlancos)
    {
        if(actual->Blancos[i].region>=0)
            al_draw_bitmap_region(target,actual->Blancos[i].region,0,60,30,actual->Blancos[i].x,actual->Blancos[i].y,0);
        i++;
    }
    i=0;
    al_draw_scaled_rotated_bitmap(paleta,0,0,actual->paleta[0].x,actual->paleta[0].y,0.1,0.1,actual->paleta[0].angulo,0);
    al_draw_scaled_rotated_bitmap(paleta,800,0,actual->paleta[1].x,actual->paleta[1].y,0.1,0.1,actual->paleta[1].angulo,ALLEGRO_FLIP_HORIZONTAL);
    if(actual->cantidadPaletas > 2)
        al_draw_scaled_rotated_bitmap(paleta,800,0,actual->paleta[2].x,actual->paleta[2].y,0.1,0.1,actual->paleta[2].angulo,ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(actual->paredes,(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0);
    switch(flag)
    {
    case 1:
        al_draw_bitmap(actual->fondoBonus,(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0);
        al_draw_text (metal1,al_map_rgb(255,0,0),(info.x2-ANCHO)/2+700,(info.y2-ALTO)/2+10,0,"Score");
        al_draw_text (metal1,al_map_rgb(255,0,0),(info.x2-ANCHO)/2+700,(info.y2-ALTO)/2+70,0,"Ball");
        al_draw_text (metal1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+700,(info.y2-ALTO)/2+30,0,scoreString);
        al_draw_text (metal1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+700,(info.y2-ALTO)/2+90,0,Vidas);
        al_draw_bitmap(visor,(info.x2-ANCHO)/2+ANCHO-160,(info.y2-ALTO)/2+ALTO-100,0); ///modificar segun mapa
        al_draw_tinted_bitmap(Msj[indiceMsj],al_map_rgba_f(1,1,1,(rand()%9+1)*0.1),(info.x2-ANCHO)/2+ANCHO-160,(info.y2-ALTO)/2+ALTO-100,0);

        break;
    case 2:
        al_draw_text (metal1,al_map_rgb(255,0,0),(info.x2-ANCHO)/2+730,(info.y2-ALTO)/2+370,0,"Score");
        al_draw_text (metal1,al_map_rgb(255,0,0),(info.x2-ANCHO)/2+730,(info.y2-ALTO)/2+430,0,"Ball");
        al_draw_text (metal1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+730,(info.y2-ALTO)/2+390,0,scoreString);
        al_draw_text (metal1,al_map_rgb(255,255,0),(info.x2-ANCHO)/2+730,(info.y2-ALTO)/2+450,0,Vidas);
        al_draw_bitmap(visor,(info.x2-ANCHO)/2+10,(info.y2-ALTO)/2+20,0);
        al_draw_tinted_bitmap(Msj[indiceMsj],al_map_rgba_f(1,1,1,(rand()%9+1)*0.1),(info.x2-ANCHO)/2+10,(info.y2-ALTO)/2+20,0);
        break;
    }

}



void DireccionBola(mapaFlipper *actual, float xchoque, float ychoque)
{

    actual->bola.dx = ((actual->bola.x+RADIOP)-xchoque);
    actual->bola.dy = (ychoque-(actual->bola.y+RADIOP));

    float norma=sqrt(pow(actual->bola.dx,2)+pow(actual->bola.dy,2));

    if(actual->bola.dx!=0 || actual->bola.dy!=0)
    {
        actual->bola.dx=(actual->bola.dx)/norma;
        actual->bola.dy=(actual->bola.dy)/norma;
    }


    if(actual->bola.y > actual->limiteSuperior || actual->bola.y < actual->limiteInferior )
    {
        actual->bola.dy*=-1;
    }

}



int Colision(ALLEGRO_BITMAP* pelota,ALLEGRO_BITMAP* buffer,mapaFlipper *actual,ALLEGRO_COLOR* colorbuffer,float* xchoque, float* ychoque,int objetoDecolision[],ALLEGRO_SAMPLE_INSTANCE *eff[],int flagmapas)
{
    ALLEGRO_COLOR colorpelota;
    int px;
    int py;
    float xcolision[16]= {0};
    float ycolision[16]= {0};
    int i=0;/// representa la variacion de angulo en allegro 256 son 360 grados
    int validos=0;
    int choque=0;
    int xbola=(int) round(actual->bola.x);
    int ybola=(int) round(actual->bola.y);

    switch(flagmapas)
    {
    case 0:
        while((i<256))
        {
            px=(RADIOP)+ (int)((RADIOP-2.5)*al_fixtof(al_fixcos(al_itofix(i)))); /// obtengo las posicion de los bordes de la pelota
            py=(RADIOP)+ (int)((RADIOP-2.5)*al_fixtof(al_fixsin(al_itofix(i))));
            if(px!=0) /// restamos uno porque la matriz de pixeles arranca en (0,0)
                px--;
            if(py!=0)
                py--;
            colorpelota=al_get_pixel(pelota,px,py);
            *colorbuffer=al_get_pixel(buffer,px+xbola,py+ybola);

            if(colorbuffer->b!=colorpelota.b || colorbuffer->g!=colorpelota.g || colorbuffer->r!=colorpelota.r ) /// comparo color pelota con el color del buffer actual, si son distintos hay choque
            {
                xcolision[validos]=px+xbola;
                ycolision[validos]=py+ybola;
                objetoDecolision[0]=detectarObjetoColisionado(actual, px+actual->bola.x,py+actual->bola.y,objetoDecolision,eff); /// arreglo que me devuelve en que objeto colisiona y en el indice de objeto
                validos++;
                choque=1;
            }
            i+=16;
        }
        i=0;
        break;
    case 1 ... 2:
        i=64;
        while((i<256))
        {
            px=(RADIOP)+ (int)((RADIOP-2.5)*al_fixtof(al_fixcos(al_itofix(i))));
            py=(RADIOP)+ (int)((RADIOP-2.5)*al_fixtof(al_fixsin(al_itofix(i))));
            if(px!=0)
                px--;
            if(py!=0)
                py--;
            colorpelota=al_get_pixel(pelota,px,py);
            *colorbuffer=al_get_pixel(buffer,px+xbola,py+ybola);

            if(colorbuffer->b!=colorpelota.b || colorbuffer->g!=colorpelota.g || colorbuffer->r!=colorpelota.r )
            {
                xcolision[validos]=px+xbola;
                ycolision[validos]=py+ybola;
                objetoDecolision[0]=detectarObjetoColisionado(actual, px+actual->bola.x,py+actual->bola.y,objetoDecolision,eff);
                validos++;
                choque=1;
            }
            i+=32;
        }
        i=0;
        while((i<64))
        {
            px=(RADIOP)+ (int)((RADIOP-2.5)*al_fixtof(al_fixcos(al_itofix(i))));
            py=(RADIOP)+ (int)((RADIOP-2.5)*al_fixtof(al_fixsin(al_itofix(i))));
            if(px!=0)
                px--;
            if(py!=0)
                py--;
            colorpelota=al_get_pixel(pelota,px,py);
            *colorbuffer=al_get_pixel(buffer,px+xbola,py+ybola);

            if(colorbuffer->b!=colorpelota.b || colorbuffer->g!=colorpelota.g || colorbuffer->r!=colorpelota.r )
            {
                xcolision[validos]=px+xbola;
                ycolision[validos]=py+ybola;
                objetoDecolision[0]=detectarObjetoColisionado(actual, px+actual->bola.x,py+actual->bola.y,objetoDecolision,eff);
                validos++;
                choque=1;
            }
            i+=16;
        }
    default:
        break;
    }

    *xchoque=(int)((xcolision[0]+xcolision[validos-1])/2);
    *ychoque=(int)((ycolision[0]+ycolision[validos-1])/2);


    return choque;

}


int detectarObjetoColisionado (mapaFlipper *actual, float xcolision, float ycolision, int objetoDecolision[],ALLEGRO_SAMPLE_INSTANCE *eff[])
{
    int m=0;
    int found=0;


    while(m < actual->cantidadPaletas && found==0)                   ///CHEQUEAR SI ALGUN X,Y DE COLISION ESTA EN ZONA DE PALETAS
    {

        if((ycolision >= actual->paleta[m].y-50) && (ycolision <= actual->paleta[m].y+40))
        {
            if((xcolision >= actual->paleta[m].x) && (xcolision <= actual->paleta[m].x+80) && (actual->paleta[m].derecha == 0))
            {
                acercaDeLasColisionesEntrePelotaYPaleta(actual,xcolision,ycolision,m);///PALETA IZQ
                found=1;
            }
            else if((xcolision >= actual->paleta[m].x-80) && (xcolision <= actual->paleta[m].x)&& (actual->paleta[m].derecha == 1))
            {
                acercaDeLasColisionesEntrePelotaYPaleta(actual,xcolision,ycolision,m);///PALETA DER
                found=2;
            }
        }
        m++;
    }
    m=0;

    /// ZONA LANZADOR

    if(ycolision >= actual->resorte.y-80 && found==0)
    {
        if((xcolision >= actual->resorte.x-50) && (xcolision <= actual->resorte.x+10))
        {
            FuerzaResorte(actual);
            found=1;
        }
    }

    /// ZONA DE REBOTADORES

    while(m < actual->cantidadRebotadores && found==0)
    {
        if((ycolision >= actual->rebotador[m].y-10) && (ycolision <= actual->rebotador[m].y+80))
        {
            if((xcolision >= actual->rebotador[m].x-10) && (xcolision <= actual->rebotador[m].x+80))
            {
                actual->bola.velocidad=8;
                found=3;
                objetoDecolision[1]=m;
                ///Le paso que rebotador es para animarlo
                cortarSample(eff);
                al_play_sample_instance(eff[2]);
            }
        }
        m++;
    }
    m=0;

    /// ZONA DE REACCIONARIOS

    while(m < actual->cantidadReaccionarios && found==0)
    {
        ///REACC MIRANDO PARA ABAJO
        switch(m)
        {
        case 0 ... 1:
            if((ycolision >= actual->reaccionario[m].y-5) && (ycolision <= actual->reaccionario[m].y+45))
            {
                if((xcolision >= actual->reaccionario[m].x-5) && (xcolision <= actual->reaccionario[m].x+75))
                {
                    actual->bola.velocidad=7;
                    found=4;
                    objetoDecolision[1]=m;
                    cortarSample(eff);
                    al_play_sample_instance(eff[6]);
                }
            }
            break;
        case 2 ... 4:
            ///REACC MIRANDO PARA ARRIBA
            if((ycolision >= actual->reaccionario[m].y-5) && (ycolision <= actual->reaccionario[m].y+45))
            {
                if((xcolision >= actual->reaccionario[m].x-5) && (xcolision <= actual->reaccionario[m].x+75))
                {
                    actual->bola.velocidad=7;
                    found=4;
                    objetoDecolision[1]=m;
                    cortarSample(eff);
                    al_play_sample_instance(eff[6]);
                }
            }
            break;
        }
        m++;
    }
    m=0;


    /// ZONA DE TARGETS

    while(m < actual->cantidadBlancos && found==0)
    {
        if((ycolision >= actual->Blancos[m].y-5) && (ycolision <= actual->Blancos[m].y+30))
        {
            if((xcolision >= actual->Blancos[m].x) && (xcolision <= actual->Blancos[m].x+60))
            {
                found=5;
                objetoDecolision[1]=m;
            }
        }
        m++;
    }
    m=0;

    if(found==0)    ///    COLISION PAREDES
    {
        actual->bola.velocidad*=0.95;
    }


    return found;

}



void acercaDeLasColisionesEntrePelotaYPaleta(mapaFlipper *actual,float xcolision,float ycolision,int numPaleta)
{

    int distancia=0;
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);
    bool KEY_LEFT=al_key_down(&state,ALLEGRO_KEY_LEFT);
    bool KEY_RIGHT=al_key_down(&state,ALLEGRO_KEY_RIGHT);

    ///DISTANCIA ENTRE PUNTO DE IMPACTO Y PIVOTE
    distancia= abs (xcolision - actual->paleta[numPaleta].x);


    switch(distancia)                   /// SI LA TECLA ESTA APRETADA (Y PALETA SUBIENDO) Y COINCIDE PALETA DE COLISION CON PALETA PULSADA..
    {
    case 0 ... 20:
        if((KEY_RIGHT==TRUE) && (actual->paleta[numPaleta].angulo>-0.3 )&& (actual->paleta[numPaleta].angulo<0.5)&&((numPaleta == 1) ||  (numPaleta == 2 )))
            actual->bola.velocidad=0.5;
        if((KEY_LEFT==TRUE)&& (actual->paleta[numPaleta].angulo<0.3 ) && (actual->paleta[numPaleta].angulo>-0.5)&& (numPaleta == 0 ))
            actual->bola.velocidad=0.5;
        break;
    case 21 ... 40:
        if((KEY_RIGHT==TRUE) && (actual->paleta[numPaleta].angulo>-0.3 )&& (actual->paleta[numPaleta].angulo<0.5)&&((numPaleta == 1) ||  (numPaleta == 2 )))
            actual->bola.velocidad=5;
        if((KEY_LEFT==TRUE)&& (actual->paleta[numPaleta].angulo<0.3 ) && (actual->paleta[numPaleta].angulo>-0.5)&& (numPaleta == 0 ))
            actual->bola.velocidad=5;
        break;
    case 41 ... 60:
        if((KEY_RIGHT==TRUE) && (actual->paleta[numPaleta].angulo>-0.3 )&& (actual->paleta[numPaleta].angulo<0.5)&&((numPaleta == 1) ||  (numPaleta == 2 )))
            actual->bola.velocidad=7.5;
        if((KEY_LEFT==TRUE)&& (actual->paleta[numPaleta].angulo<0.3 ) && (actual->paleta[numPaleta].angulo>-0.5)&& (numPaleta == 0 ))
            actual->bola.velocidad=7.5;
        break;
    case 61 ... 70:
        if((KEY_RIGHT==TRUE) && (actual->paleta[numPaleta].angulo>-0.3 )&& (actual->paleta[numPaleta].angulo<0.5)&&((numPaleta == 1) ||  (numPaleta == 2 )))
            actual->bola.velocidad=9.5;
        if((KEY_LEFT==TRUE)&& (actual->paleta[numPaleta].angulo<0.3 ) && (actual->paleta[numPaleta].angulo>-0.5)&& (numPaleta == 0 ))
            actual->bola.velocidad=9.5;
        break;
    case 71 ... 85:
        if((KEY_RIGHT==TRUE) && (actual->paleta[numPaleta].angulo>-0.3 )&& (actual->paleta[numPaleta].angulo<0.5)&&((numPaleta == 1) ||  (numPaleta == 2 )))
            actual->bola.velocidad=12;
        if((KEY_LEFT==TRUE)&& (actual->paleta[numPaleta].angulo<0.3 ) && (actual->paleta[numPaleta].angulo>-0.5)&& (numPaleta == 0 ))
            actual->bola.velocidad=12;
        break;
    default:
        break;
    }

}


void CargarMapas(mapaFlipper *actual, int flagmapas,ALLEGRO_MONITOR_INFO info)
{

    switch(flagmapas)
    {
    case 1:
        actual->bola.x=(info.x2-ANCHO)/2+198;
        actual->bola.y=(info.y2-ALTO)/2+492;
        actual->bola.velocidad=0;
        actual->bola.dx=0;
        actual->bola.dy=0;
        actual->cantidadRebotadores=3;
        actual->rebotador[0].x=(info.x2-ANCHO)/2+550;
        actual->rebotador[0].y=(info.y2-ALTO)/2+200;
        actual->rebotador[0].region=ANCHOREBOTADOR*2;
        actual->rebotador[1].x=(info.x2-ANCHO)/2+390;
        actual->rebotador[1].y=(info.y2-ALTO)/2+250;
        actual->rebotador[1].region=ANCHOREBOTADOR*2;
        actual->rebotador[2].x=(info.x2-ANCHO)/2+550;
        actual->rebotador[2].y=(info.y2-ALTO)/2+370;
        actual->rebotador[2].region=ANCHOREBOTADOR*2;
        actual->cantidadReaccionarios=1;
        actual->reaccionario[0].x=(info.x2-ANCHO)/2+490;
        actual->reaccionario[0].y=(info.y2-ALTO)/2+12;
        actual->reaccionario[0].region=ANCHOREBOTADOR*2;
        actual->cantidadPaletas=2;
        actual->paleta[0].x=(info.x2-ANCHO)/2+300;
        actual->paleta[0].y=(info.y2-ALTO)/2+515;
        actual->paleta[0].angulo=0.3;
        actual->paleta[0].derecha=0;
        actual->paleta[1].x=(info.x2-ANCHO)/2+490;
        actual->paleta[1].y=(info.y2-ALTO)/2+515;
        actual->paleta[1].angulo=-0.3;
        actual->paleta[1].derecha=1;
        actual->limiteInferior=(info.y2-ALTO)/2+570;
        actual->limiteSuperior=(info.y2-ALTO)/2+30;
        actual->score=0;
        actual->resorte.x=(info.x2-ANCHO)/2+257;
        actual->resorte.y=(info.y2-ALTO)/2+566;
        actual->resorte.angulo=-0.58;
        actual->resorte.xtope=(info.x2-ANCHO)/2+196;
        actual->resorte.ytope=(info.y2-ALTO)/2+518;
        actual->resorte.anguloTope=-0.6;
        actual->resorte.fuerza=0;
        actual->cantidadBarreras=2;
        actual->barreras[0].x=(info.x2-ANCHO)/2+220;
        actual->barreras[0].y=(info.y2-ALTO)/2+200;
        actual->barreras[0].angulo=ALLEGRO_PI/2;
        actual->barreras[0].limiteMin=(info.y2-ALTO)/2+90;
        actual->barreras[0].limiteMaX=(info.y2-ALTO)/2+270;
        actual->barreras[0].velocidad=5;
        actual->barreras[1].x=(info.x2-ANCHO)/2+320;
        actual->barreras[1].y=(info.y2-ALTO)/2+570;
        actual->barreras[1].angulo=0;
        actual->barreras[1].limiteMin=(info.x2-ANCHO)/2+300;
        actual->barreras[1].limiteMaX=(info.x2-ANCHO)/2+470;
        actual->cantidadBlancos=4;
        actual->Blancos[0].x=(info.x2-ANCHO)/2+400;
        actual->Blancos[0].y=(info.y2-ALTO)/2+139;
        actual->Blancos[0].region=60;
        actual->Blancos[1].x=(info.x2-ANCHO)/2+460;
        actual->Blancos[1].y=(info.y2-ALTO)/2+139;
        actual->Blancos[1].region=60;
        actual->Blancos[2].x=(info.x2-ANCHO)/2+520;
        actual->Blancos[2].y=(info.y2-ALTO)/2+139;
        actual->Blancos[2].region=60;
        actual->Blancos[3].x=(info.x2-ANCHO)/2+340;
        actual->Blancos[3].y=(info.y2-ALTO)/2+139;
        actual->Blancos[3].region=60;
        actual->Ruleta.x=(info.x2-ANCHO)/2+270;
        actual->Ruleta.y=(info.y2-ALTO)/2+310;
        actual->Ruleta.region=0;
        actual->Ruleta.huecox=actual->Ruleta.x+22;
        actual->Ruleta.huecoy=actual->Ruleta.y-25;
        actual->Ruleta.salidax=(info.x2-ANCHO)/2+331;
        actual->Ruleta.saliday=(info.y2-ALTO)/2+45;
        actual->fondoBonus=al_load_bitmap("img/contornomapa1.bmp");
        al_convert_mask_to_alpha(actual->fondoBonus, al_map_rgb(0,0,0));
        actual->paredesBonus=NULL;
        break;
    case 2:
//        actual->bola.x=545;
//        actual->bola.y=512;
        actual->bola.x=(info.x2-ANCHO)/2+545;
        actual->bola.y=(info.y2-ALTO)/2+522;
        actual->bola.velocidad=0;
        actual->bola.dx=0;
        actual->bola.dy=0;
        actual->cantidadRebotadores=4;
        actual->rebotador[0].x=(info.x2-ANCHO)/2+445;
        actual->rebotador[0].y=(info.y2-ALTO)/2+68;
        actual->rebotador[0].region=ANCHOREBOTADOR*2;
        actual->rebotador[1].x=(info.x2-ANCHO)/2+132;
        actual->rebotador[1].y=(info.y2-ALTO)/2+185;
        actual->rebotador[1].region=ANCHOREBOTADOR*2;
        actual->rebotador[2].x=(info.x2-ANCHO)/2+295;
        actual->rebotador[2].y=(info.y2-ALTO)/2+185;
        actual->rebotador[2].region=ANCHOREBOTADOR*2;
        actual->rebotador[3].x=(info.x2-ANCHO)/2+665;
        actual->rebotador[3].y=(info.y2-ALTO)/2+68;
        actual->rebotador[3].region=ANCHOREBOTADOR*2;
        actual->cantidadReaccionarios=4;
        actual->reaccionario[0].x=(info.x2-ANCHO)/2+510;
        actual->reaccionario[0].y=(info.y2-ALTO)/2+0;
        actual->reaccionario[0].region=ANCHOREBOTADOR*2;
        actual->reaccionario[1].x=(info.x2-ANCHO)/2+2570;
        actual->reaccionario[1].y=(info.y2-ALTO)/2+880;
        actual->reaccionario[1].region=ANCHOREBOTADOR*2;
        actual->reaccionario[2].x=(info.x2-ANCHO)/2+75;
        actual->reaccionario[2].y=(info.y2-ALTO)/2+500;
        actual->reaccionario[2].region=ANCHOREBOTADOR*2;
        actual->reaccionario[3].x=(info.x2-ANCHO)/2+666;
        actual->reaccionario[3].y=(info.y2-ALTO)/2+495;
        actual->reaccionario[3].region=ANCHOREBOTADOR*2;
        actual->cantidadBarreras=2;
        actual->barreras[0].x=(info.x2-ANCHO)/2+410;
        actual->barreras[0].y=(info.y2-ALTO)/2+210;
        actual->barreras[0].angulo=0;
        actual->barreras[0].limiteMin=(info.x2-ANCHO)/2+400;
        actual->barreras[0].limiteMaX=(info.x2-ANCHO)/2+570;
        actual->barreras[0].velocidad=5;
        actual->barreras[1].x=(info.x2-ANCHO)/2+710;
        actual->barreras[1].y=(info.y2-ALTO)/2+260;
        actual->barreras[1].angulo=ALLEGRO_PI/2;
        actual->barreras[1].limiteMin=(info.y2-ALTO)/2+150;
        actual->barreras[1].limiteMaX=(info.y2-ALTO)/2+271;
        actual->barreras[1].velocidad=12000;
        actual->cantidadBlancos=3;
        actual->Blancos[0].x=(info.x2-ANCHO)/2+190;
        actual->Blancos[0].y=(info.y2-ALTO)/2+105;
        actual->Blancos[0].region=60;
        actual->Blancos[1].x=(info.x2-ANCHO)/2+250;
        actual->Blancos[1].y=(info.y2-ALTO)/2+105;
        actual->Blancos[1].region=60;
        actual->Blancos[2].x=(info.x2-ANCHO)/2+435;
        actual->Blancos[2].y=(info.y2-ALTO)/2+402;
        actual->Blancos[2].region=60;
        actual->Ruleta.x=(info.x2-ANCHO)/2+560;
        actual->Ruleta.y=(info.y2-ALTO)/2+67;
        actual->Ruleta.region=0;
        actual->Ruleta.huecox=actual->Ruleta.x+22;
        actual->Ruleta.huecoy=actual->Ruleta.y-25;
        actual->Ruleta.salidax=(info.x2-ANCHO)/2+106;
        actual->Ruleta.saliday=(info.y2-ALTO)/2+137;
        actual->cantidadPaletas=3;
        actual->paleta[0].x=(info.x2-ANCHO)/2+213;
        actual->paleta[0].y=(info.y2-ALTO)/2+503;
        actual->paleta[0].angulo=0.3;
        actual->paleta[0].derecha=0;
        actual->paleta[1].x=(info.x2-ANCHO)/2+427;
        actual->paleta[1].y=(info.y2-ALTO)/2+470;
        actual->paleta[1].angulo=-0.3;
        actual->paleta[1].derecha=1;
        actual->paleta[2].x=(info.x2-ANCHO)/2+695;
        actual->paleta[2].y=(info.y2-ALTO)/2+390;
        actual->paleta[2].angulo=-0.5;
        actual->paleta[2].derecha=1;
        actual->limiteInferior=(info.y2-ALTO)/2+580; ///  dejar q caiga la bolaaa
        actual->limiteSuperior=(info.y2-ALTO)/2+30;
        actual->score=0;
        actual->resorte.x=(info.x2-ANCHO)/2+561;
        actual->resorte.y=(info.y2-ALTO)/2+612;
        actual->resorte.angulo=0;
//        actual->resorte.xtope=515;
//        actual->resorte.ytope=530;
        actual->resorte.xtope=(info.x2-ANCHO)/2+515;
        actual->resorte.ytope=(info.y2-ALTO)/2+540;
        actual->resorte.anguloTope=0;
        actual->resorte.fuerza=0;
        actual->fondoBonus=NULL;
        actual->paredesBonus=NULL;

        break;
    default:
        break;
    }

}





void FuerzaResorte(mapaFlipper *actual)
{
    switch(actual->resorte.fuerza)
    {
    case 1:
        actual->bola.velocidad=0.5;
        break;
    case 2:
        actual->bola.velocidad=1;
        break;
    case 3:
        actual->bola.velocidad=2;
        break;
    case 4:
        actual->bola.velocidad=4;
        break;
    case 5:
        actual->bola.velocidad=5;
        break;
    case 6:
        actual->bola.velocidad=8;
        break;
    case 7:
        actual->bola.velocidad=12;
        break;
    default:
        break;

    }

    actual->resorte.fuerza=0;

}



void RestaurarPosicionBola(mapaFlipper* actual,int xinicial, int yinicial,int colisiono,int flagmapas)
{

    switch(flagmapas)
    {
    case 1:
        if((actual->bola.y+20 > actual->resorte.ytope-15) && colisiono==0)
        {
            if((actual->bola.x > actual->resorte.xtope) && (actual->bola.x < actual->resorte.xtope+35))
            {
                actual->bola.x=xinicial;
                actual->bola.y=yinicial;
                actual->bola.velocidad=0;
                actual->bola.dx=0;
                actual->bola.dy=0;
            }
        }
        break;
    case 2:
        if((actual->bola.y+20 > actual->resorte.ytope-10) && colisiono==0)
        {
            if((actual->bola.x > actual->resorte.xtope) && (actual->bola.x < actual->resorte.xtope+100))
            {
                actual->bola.x=xinicial;
                actual->bola.y=yinicial;
                actual->bola.velocidad=0;
                actual->bola.dx=0;
                actual->bola.dy=0;

            }
        }
        break;


    }
}





int AgregarColaAnimacion( int objeto,int elemento,int contaranimado[],int a[],int validos)
{
    int repetido=0;
    int i=0;

    if(validos>0)
    {
        while(i<validos && repetido==0)
        {
            if(a[i]==elemento)
            {
                repetido=1;
            }
            i++;
        }
    }

    if(repetido==0)
    {
        validos++;
        a[validos-1]=elemento;
        contaranimado[objeto-3]=0;
    }


    return validos;
}




int AnimarRebotador(mapaFlipper *actual, int contarAnimado[], int indice[], int validos)
{

    int termino=0;
    for(int i=0; i<validos; i++)
    {
        if(contarAnimado[0]<=(9*(validos))  )
        {
            if(actual->rebotador[indice[i]].region!=0)
            {
                actual->rebotador[indice[i]].region-=ANCHOREBOTADOR;
            }
            else
            {
                actual->rebotador[indice[i]].region=ANCHOREBOTADOR*2;
            }
            contarAnimado[0]+=1;
        }
        else
        {
            contarAnimado[0]=0;
            termino=1;
            actual->rebotador[indice[i]].region=ANCHOREBOTADOR*2;
        }
    }
    return termino;
}

int AnimarReactor(mapaFlipper *actual, int contarAnimado[], int indice[], int validos)
{

    int termino=0;
    for(int i=0; i<validos; i++)
    {
        if(contarAnimado[1]<=(113*(validos))  )
        {
            if(actual->reaccionario[indice[i]].region!=0)
            {
                actual->reaccionario[indice[i]].region-=ANCHOREBOTADOR;
            }
            else
            {
                actual->reaccionario[indice[i]].region=ANCHOREBOTADOR*2;
            }
            contarAnimado[1]+=1;
        }
        else
        {
            contarAnimado[1]=0;
            termino=1;
            actual->reaccionario[indice[i]].region=ANCHOREBOTADOR*2;
        }
    }
    return termino;
}

void scratch(ALLEGRO_BITMAP*img, int i,ALLEGRO_MONITOR_INFO info)
{
    srand(clock());
    switch(i)
    {
    case 0:
        al_draw_tinted_bitmap(img,al_map_rgba_f(1,0.6,0.6,0.5),(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0);
        al_flip_display();
        al_draw_tinted_bitmap(img,al_map_rgba_f(1,0.6,0.6,0.5),(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0);
        al_flip_display();
        break;
    case 1:
        al_draw_tinted_bitmap(img,al_map_rgba_f(0,1,0.6,0.6),(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0);
        al_flip_display();
        al_draw_tinted_bitmap(img,al_map_rgba_f(0,1,0.6,0.6),(info.x2-ANCHO)/2,(info.y2-ALTO)/2,0);
        al_flip_display();
        break;
    default:
        break;
    }
}

void Tilt(mapaFlipper * actual)
{
    srand(clock());
    actual->bola.dx=(rand()%3+1)*pow(-1,rand()%2);
    actual->bola.dy=(rand()%3+1)*-1;   ///PARA ARRIBA
    actual->bola.velocidad=(rand()%3)+1;
}


void MostrarTilt(ALLEGRO_FONT* fuente,ALLEGRO_BITMAP* tilt,ALLEGRO_MONITOR_INFO info)
{
    srand(clock());

    al_draw_text(fuente,al_map_rgb(rand()%255,233,rand()%255),(info.x2-ANCHO)/2+(rand()%10)+313,(info.y2-ALTO)/2+(rand()%10)+300,0,"TILT ACTIVE");
    al_draw_tinted_bitmap(tilt,al_map_rgba_f(0.7,0.6,0.6,0.2),(info.x2-ANCHO)/2+rand()%5,(info.y2-ALTO)/2+rand()%5,0);
    al_flip_display();

}

///Agregar scores

void AgregarScoresUsuario(char nameUser[30],scoreMapas ADS[],int score, int flagmap)
{


    usuarioLista nuevo;
    time_t t=time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fecha[70];
    // El formato
    char *formato = "%Y-%m-%d";
    // Intentar formatear
    int bytesEscritos = strftime(fecha, sizeof fecha, formato, &tiempoLocal);
    strcpy(nuevo.nombre,nameUser);
    nuevo.Score=score;
    if(bytesEscritos!=0)
    {
        strcpy(nuevo.Fecha,fecha);
    }
    else
    {
        strcpy(nuevo.Fecha,"unknown");
    }

    nodo* nuevoScore=crearnodo(nuevo);

    ADS[flagmap-1].lista=agregarEnOrden(ADS[flagmap-1].lista,nuevoScore);



}

/// Mover barrera
void MoverBarrera(mapaFlipper *actual, int i, int orientacion, int* aux)  // 0 para x, 1 para y movimiento
{


    switch(orientacion)
    {
    case 0:
        if(actual->barreras[i].x==actual->barreras[i].limiteMin)
            *aux=1;

        if(actual->barreras[i].x==actual->barreras[i].limiteMaX)
            *aux=-1;

        actual->barreras[i].x+=*aux;

        break;

    case 1:
        if(actual->barreras[i].y==actual->barreras[i].limiteMin)
            *aux=1;

        if(actual->barreras[i].y==actual->barreras[i].limiteMaX)
            *aux=-1;
        actual->barreras[i].y+=*aux;

        break;

    default:
        break;
    }
}



void cortarSample(ALLEGRO_SAMPLE_INSTANCE* eff[])
{
    for(int v=0; v<CANTSOUNDS-3; v++)///SONIDO
    {
        if(al_get_sample_instance_playing(eff[v]))
            al_set_sample_instance_playing(eff[v],false);
    }
}
