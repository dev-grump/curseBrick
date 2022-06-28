#include <stdlib.h>
#include <curses.h>
#include "colaCrd.h"

int initColaCrd(colaCrd *c, size_t t)
{
    c->T = c-> H = 0;
    if(t > 1)
    {
        c->cola = (crd *)calloc(t, sizeof(crd));
        if(c->cola == NULL)
        {
            c->N = 0;
            return -1;
        }
        c->N = t;
        return 0;
    }
    else
    {
        c->cola = NULL;
        c->N = 0;
        return -2;
    }
}

int meteColaCrd(colaCrd *c, crd valor)
{
    if( ((c->T)+1) % c->N == c->H)
        return -1;
    c->cola[c->T] = valor;
    c->T = (c->T+1)%c->N;
    return 0;
}

int sacaColaCrd(colaCrd *c, crd *valor)
{
    if(c->T == c->H)
        return -1;
    *valor = c->cola[c->H];
    c->H = (c->H+1)%c->N;
    return 0;
}

void liberaColaCrd(colaCrd *c)
{
    if(c->cola != NULL)
    {
        free(c->cola);
        c->N = 0;
        c->H = c->T = 0;
    }
}
