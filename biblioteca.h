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


/*	Função para criar a cabeça da lista.
	implementada por Pedro Warmling Botelho	*/
TCabeca *criaCabeca();


/* Função para inserir no fim da lista.
   Implementada por Othon Alberto */
TNo *insereFim(TCabeca *cabeca, char k);

#endif