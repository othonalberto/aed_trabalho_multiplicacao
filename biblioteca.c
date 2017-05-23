#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

TCabeca *criaCabeca(){
    // Criando um nó cabeça
	TCabeca *cabeca = (TCabeca *) malloc(sizeof(TCabeca));
    if (cabeca == NULL)
        return NULL;

    cabeca->prim = NULL;
    cabeca->ult = NULL;

    return cabeca;
}

TNo *insereInicio(TCabeca *cabeca, char k){
	// caso não houver cabeça criada
	if(cabeca == NULL)
		return NULL;
	
	// novo nó
	TNo *novo = malloc(sizeof(TNo));
    	if(novo == NULL)
		return NULL;

	novo->digito = k;
	novo->prox = cabeca->prim;
	cabeca->prim = novo;	

	// caso a lista seja vazia, o cabeca->prim e cabeca->ult receberão o novo nó.
	if(cabeca->ult == NULL)
		cabeca->ult = novo;
	// caso contrário, o cabeca->ult continua tendo o mesmo nó.

	return novo;
}

TNo *insereFim(TCabeca *cabeca, char digito){
	if(cabeca == NULL) //se não houver cabeça criada
		return NULL;

	if(cabeca->ult == NULL) //se não tiver nenhum elemento, o prim e o ult são iguais: nó recém criado.
		return insereInicio(cabeca, digito);

	TNo *novo = (TNo*)malloc(sizeof(TNo)); //novo nó
	if(novo == NULL)
		return NULL;

	(cabeca->ult)->prox = novo; //o nó que até então é o último, passa a apontar para o novo último
	novo->prox = NULL;
	novo->digito = digito;
	cabeca->ult = novo; //ponteiro para o último é atualizado para o novo último

	return novo;
}

void deletaLista(TCabeca *cabeca){
    if(cabeca == NULL)
        return;
   
    TNo *ant = cabeca->prim;
    TNo *atual = cabeca->prim;

    while(atual != NULL){
        atual = ant->prox;
        free(ant);
        ant = atual;
    }
    
    cabeca->prim = NULL;
    cabeca->ult = NULL;
}

TCabeca *retornaMaiorLista(TCabeca *c1, TCabeca *c2){
    unsigned int n1 = 0, n2 = 0;
    TNo *aux = c1->prim;
    
    if(c1->prim == NULL && c2->prim == NULL)
        return NULL;

    while(aux != NULL){
        n1++;
        aux = aux->prox;
    }

    aux = c2->prim;

    while(aux != NULL){
        n2++;
        if(n2 > n1)
            return c2; //quando já ultrapassou o valor de n1 não tem necessidade de continuar contando
        aux = aux->prox;
    }

    return c1; //se n2 não ultrapassou n1 ou o n1 é maior ou são iguais. Sendo assim, retorna a cabeca da lista 1(c1). 
}
