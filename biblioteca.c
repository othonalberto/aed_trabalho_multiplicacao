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
	TNo *aux = c1->prim;
	TNo *aux2 = c2->prim;

	while(aux != NULL){
    	aux = aux->prox;
    	aux2 = aux2->prox;
    	if(aux2 == NULL) // se o aux2 já acabou, o c1 é a maior lista
        	return c1;
	}

	return c2; // se o aux já acabou, o c2 é a maior lista
}

void leArquivo(){
    /*
    * A ideia é ler os números (dígitos) e ir salvando-os até encontrar o espaço. Ao encontrá-lo, passamos a salvar os outros números na
    * segunda lista.
    * Quando o segundo conjuntos de dígitos tiver acabado (ou seja, encontrado o '\n') passamos as duas listas para outras
    * funções que farão o trabalho de multiplacar e gravar em outro arquivo a resposta.
    * Após isso, começa tudo novamente até acabar o arquivo 'parametros'
    */

    FILE *arquivo;
    TCabeca *lista1 = criaCabeca();
    TCabeca *lista2 = criaCabeca();
    char aux = '1';

    arquivo = fopen("parametros", "r+");
    if(arquivo == NULL){
        printf("Arquivo 'parametros' não encontrado.\n");
        fclose(arquivo);
        return;
    }
   
    //as próximas três linhas são para garantir um '\n' no final do arquivo
    fseek(arquivo, 0, SEEK_END); //vai até o final do arquivo
    fprintf(arquivo, "\n"); //escreve um '\n'
    fseek(arquivo, 0, SEEK_SET); //volta ao início do arquivo
    
    do{
        char digito = fgetc(arquivo);
        
        if(aux == '1'){ //lista 1    
            if(digito == ' ') //ao encontrar o caracter espaço, passa para a outra lista
                aux = '2';
            else
               insereInicio(lista1, digito);
        }else{ //aux = 2, ou seja, lista2
            if(digito == '\n'){
                //Acabou a linha. Tem que passar as listas para as outras funções
            }else{
                insereInicio(lista2, digito);
            }
       }
    }while(!feof(arquivo));

    fclose(arquivo);
}
