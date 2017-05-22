#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct TNo{
	char digito;
	struct TNo *prox;
} TNo;

typedef struct TCabeca{
	TNo *prim;
	TNo *ult;
} TCabeca;


#endif