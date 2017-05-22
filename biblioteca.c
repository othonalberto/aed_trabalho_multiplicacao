#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

TCabeca *criaCabeca(){
    TCabeca *cabeca = (TCabeca *) malloc(sizeof(TCabeca));
    if (cabeca == NULL)
        return NULL;

    cabeca->prim = NULL;
    cabeca->ult = NULL;

    return cabeca;
}