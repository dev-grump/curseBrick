#ifndef __COLA__
#define __COLA__

#include <stdlib.h>

typedef struct
{
    int x, y;
}crd;


typedef struct
{
    crd *cola;
    size_t N;
    int H;
    int T;
} colaCrd;

int initColaCrd(colaCrd *c, size_t t);

int meteColaCrd(colaCrd *c, crd valor);

int sacaColaCrd(colaCrd *c, crd *valor);

void liberaColaCrd(colaCrd *c);



#endif
