#include <allegro.h>
#include "inicia.h"
#include <iostream>
#define MAXFILAS 21
#define MAXCOLUMNAS 82

using namespace std;
//usaremos las variables MAX para hacer una matriz
//que contendran los bloques en x 30 en y 19 y 100pre se deja 1 mas
//de espacios en el vector
BITMAP *buffer;
BITMAP *fondo;
BITMAP *muro;
BITMAP *personaje;
BITMAP *monigote;
BITMAP *comida;
//Declaramos 3 variables int para controlar la pos del muñquito y la bala
static int score;
static int variable=0;
int direccion=0;
int px=30*10;//no se por q
int py=30*10;
//def la matriz

char mapa[MAXFILAS][MAXCOLUMNAS]={
    "                                                                                ",
    "                                                                                ",
    "                   o         o                                                  ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "   xxo         xxxxx          xxx            o         xxxxx          xxx       ",
    "   xx          xxxxx          xxx                      xxxxx          xxx       ",
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "                                                                                ",
    "                                                                                ",
    " o                    o                                                   o     ",
    "                                                        o                       ",
    "                               o                                                ",
    "                                                            o                   ",
    "        xx          xxx               xxxx          xx           xxx           o",
    "        xx          xxx               xxxx          xx           xxx            ",
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",


};//se pone NO OLVIDAR

void dibujar_mapa(){

    int row,col;
    //buscara en todas las filas donde halla x y q si hay q cargue los muros
    for(row=0;row<MAXFILAS;row++)
    {

        for(col=0;col<MAXCOLUMNAS;col++)
        {
            if(mapa[row][col]=='x')
            {

                draw_sprite(buffer,muro,(col+variable)*30,row*30);

            }
            else if(mapa[row][col]=='o')
            {
                draw_sprite(buffer,comida,(col+variable)*30,row*30);//siempre por el tamaño de IMG
                if(px/30==col &&py/30==row)//si pacman esta en esa posicion DEBEMOS DIVIDR /30
                {
                    mapa[row][col]=' ';
                    score++;
                }
            }

        }
    }
}


void pantalla()
{

    blit(buffer,screen,0,0,0,0,900,570) ;
    //blit(fondo,buffer,0,0,0,0,900,570);


}
//funcion que dibuja al pacman
void dibujar_monigote()
{   //desde donde cogemos el pacman en x y y la sotras 3 las medidas del pacman
    blit(monigote,personaje,direccion*33,0,0,0,33,33);//imprimimos la img del monigote sobre el peqñobuffer "personaje"    cewamos
    //el resto de coordenadas es desde donde vamos a agarrar una parte de la tira y la dejamos caer
   draw_sprite(buffer,personaje,px,py);//para q se respete la trasnparencia del pacman dibujo y el buffer

}
int main()
{
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    //iniciamis pantalla de Allegro
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,900,570,0,0);
    //el tamaño de pantalla multiplicado por "30" X los MAX
    buffer = create_bitmap(900,570);//crea la ventana
    fondo = load_bitmap("escenario_2.bmp",NULL);
    muro=load_bitmap("murito_2.bmp",NULL);
    //cargamos las IMG del personage y monigote
    monigote=load_bitmap("pacman.bmp",NULL);
    personaje=create_bitmap(33,33);//fuffer
    comida=load_bitmap("Comida.bmp",NULL);


    while(!key[KEY_ESC])
    {

            blit(fondo,buffer,0,0,0,0,900,570);
            variable-=1;
                //CUIDADO
if(key[KEY_LEFT])
{
direccion=0;
}
else if(key[KEY_RIGHT])
{
direccion=1;
}
else if(key[KEY_UP])
{
direccion=2;
}
else if(key[KEY_DOWN])
{
direccion=3;
}
if(direccion==0)
  if(mapa[py/30][(px-30)/30]!='x')
    px-=30;
    else direccion=4; //no hara mov aluno ya q no existe direccion=4
if(direccion==1)
    if(mapa[py/30][(px+30)/30]!='x')
    px+=30;
    else direccion=4;

if(direccion==2)
if(mapa[(py-30)/30][(px)/30]!='x')
 py-=30;
 else direccion=4;

if(direccion==3)
if(mapa[(py+30)/30][(px)/30]!='x')
    py+=30;
else direccion=4;
//clear(buffer);//limpiara pantalla
if(variable==(MAXCOLUMNAS)*(-1))
{
    variable=30;
    cout<<"HOL";
}

                dibujar_mapa();
                dibujar_monigote();
                pantalla();//imprimimos todo en pantalla
                rest(70);
                clear(personaje);//aqui hacemos clear sobre el boffer del personaje asi q no afecta en si a la pantalla
                blit(monigote,personaje,4*33,0,0,0,33,33);//imprimira bolita cerrada
                draw_sprite(buffer,personaje,px,py);
                pantalla();
                rest(90);

    }

    readkey();

    destroy_bitmap(buffer);
    cout<<"your score"<<score<<endl;
    return 0;
}
END_OF_MAIN();
