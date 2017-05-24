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
	Implementada por Pedro Warmling Botelho	*/
TCabeca *criaCabeca();

/*	Função para inserer no inicio da lista.
	Implementada por Pedro Warmling Botelho	*/
TNo *insereInicio(TCabeca *cabeca, char k);

/* Função para inserir no fim da lista.
   Implementada por Othon Alberto */
TNo *insereFim(TCabeca *cabeca, char k);

/* Função para deletar toda a lista (liberar todos os nós)
   Implementada por Othon Alberto */
void deletaLista(TCabeca *cabeca);

/* Função que retorna a cabeca para a maior lista entre as duas comparadas
   Implementada por Othon Alberto e Pedro Warmling Botelho */
TCabeca *retornaMaiorLista(TCabeca *c1, TCabeca *c2);

#endif
