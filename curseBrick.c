#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include "colaCrd.h"
#include "colaCrd.c"

void printCola(colaCrd *c, size_t t)
{
    int i;
    for(i=c->H;(i+1)%c->N!=c->H;i=(i+1)%c->N)
        mvprintw(c->cola[c->H+i].y,c->cola[c->H+i].x,"o");
    
}

int main()
{
    WINDOW *win;
    /*Inicializamos la instancia de ncurses*/
    win = initscr();
    nodelay(stdscr, TRUE);
    cbreak();
    curs_set(FALSE);
    keypad(win, TRUE);

    int hght = 0;
    int wdt = 0;
    int i, c, bx = 1, by = 1; /*bx, by serviran como banderas para el movimiento*/

    //inicializamos una cola de miembros crd para la raqueta y una para la pelota
    colaCrd bola, raqueta;
    initColaCrd(&bola, 5);
    initColaCrd(&raqueta, 5);
    
    /*Inicializamos la pelota en la posicion 1,1*/
    crd b = {1,1};
    for(i=0;i<bola.N-1;i++)
    {
        meteColaCrd(&bola, b);
        b.x++;
        b.y++;
    }

    /*Inicializamos la raqueta al centro de la parte inferior de la pantalla*/
    crd r = {1, 0};
    for(i=0;i<raqueta.N-1;i++)
    {
        meteColaCrd(&raqueta, r);
        r.x++;
        r.y++;
    }

    /*Inicializamos un elemento crd temporal para almacenar las coordenadas*/
    crd tmpBola;
    crd tmpRaqueta;

    /*Llamamos a getmax para crear la pantalla y delimitar las paredes.*/
    getmaxyx(win, hght, wdt);

    while(1)
    {   
        /*reimpresion*/
        printCola(&bola, bola.N);
        printCola(&raqueta, raqueta.N);

        /*Actualiza la posicion de la pelota haciendo que la posicion H de la cola salga
          y se inserte un nuevo miembro con coordenadas (x+bx/y+by)*/
        if(bola.cola[bola.H].x == wdt || bola.cola[bola.H].x == 0){
            bx *= -1;
        }
        if(bola.cola[bola.H].y == hght || bola.cola[bola.H].y == 0){
            by *= -1;
        }

        tmpBola.x = bola.cola[bola.T].x+bx;
        tmpBola.y = bola.cola[bola.T].y+by;

        sacaColaCrd(&bola, &bola.cola[bola.H]);
        meteColaCrd(&bola, tmpBola);

        switch (c = getch())
        {
        case 'd':
        case KEY_RIGHT:
            if(raqueta.cola[raqueta.H].x == wdt);
            else 
            {
                tmpRaqueta.x = raqueta.cola[raqueta.H].x+1;
                sacaColaCrd(&raqueta, &raqueta.cola[raqueta.H]);
                meteColaCrd(&raqueta, tmpRaqueta);
                printCola(&raqueta, raqueta.N);
            }
            break;
        case 'a':
        case KEY_LEFT:
            if(raqueta.cola[raqueta.H].x == 0);
            else 
            {
                tmpRaqueta.x = raqueta.cola[raqueta.H].x-1;
                sacaColaCrd(&raqueta, &raqueta.cola[raqueta.H]);
                meteColaCrd(&raqueta, tmpRaqueta);
                printCola(&raqueta, raqueta.N);
            }
            
            break;
        default:
            break;
        }
        refresh();
        usleep(50000); /*Pausa para poder obserar el movimiento*/
        clear();
    }
}


