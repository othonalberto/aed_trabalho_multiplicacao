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
                //Acabou a linha no arquivo. Agora, tem que passar essas listas para outras funções para multiplicar e
                //salvar no arquivo
                aux = '1';
                /* Na verdade, essas duas linhas estarão na função multiplicaListas
                 * deletaLista(lista1)
                 * deletaLista(lista2);
                */
                TCabeca *resultado = somaListas(lista1, lista2);
                escreveArquivo(resultado->prim);
                deletaLista(lista1);
                deletaLista(lista2);
            }else{
                insereInicio(lista2, digito);
            }
       }
    }while(!feof(arquivo));

    fclose(arquivo);
}

TCabeca *somaListas(TCabeca *lista1, TCabeca *lista2){
    TCabeca *aux1 = lista1;
    TCabeca *aux2 = lista2;

    TCabeca *resultado = criaCabeca();
    unsigned short int vai = 0;
    unsigned short int n = 0;

    while(aux1->prim != NULL || aux2->prim != NULL){
        if(aux1->prim == NULL)
            insereInicio(aux1, '0');

        if(aux2->prim  == NULL)
            insereInicio(aux2, '0');

        n = (((aux1->prim->digito)-48) + ((aux2->prim->digito)-48) + vai) % 10;
        vai = (((aux1->prim->digito)-48) + ((aux2->prim->digito)-48) + vai) / 10;
        insereFim(resultado, n+48);

        aux1->prim = (aux1->prim)->prox;
        aux2->prim = (aux2->prim)->prox;
    }

    if(vai > 0)
        insereFim(resultado, vai+48);

    return resultado;
}

void escreveArquivo(TNo *lista){
    if(lista == NULL)
        return;

    FILE *arquivo = fopen("resultados", "a+");
    if(arquivo == NULL){
        printf("Não foi possível acessar o arquivo 'resultados'\n");
        return;
    }

    printaListaRecursivo(lista, &arquivo);
    fprintf(arquivo, "\n");
    fclose(arquivo);
}

void printaListaRecursivo(TNo *lista, FILE **arquivo){
    if(lista == NULL)
        return;

    printaListaRecursivo(lista->prox, arquivo);
    fprintf(*arquivo, "%c", lista->digito);
}

void removeZeroEsquerda(TCabeca *lista){
    if(lista->prim == NULL)
        return;

    TNo *aux = NULL;

    while(lista->prim->digito == '0'){
        aux = lista->prim;
        lista->prim = (lista->prim)->prox;
        free(aux);
    }
}

TCabeca *multiplicaListas(TCabeca *lista1, TCabeca *lista2){
    if(lista1->prim == NULL || lista2->prim == NULL)
        return;
    
    /* 
     * A ideia é "travar" no primeiro digito da lista menor e multiplica-lo por todos os digitos da lista maior
     * Assim, se tem uma nova lista representando o numero calculado.
     * Depois, passa-se para o próximo elemento e repete tudo. Faz isso sucessivas vezes até o fim da lista menor
     * De duas em duas "passagens" soma-se as listas.
     */
}
