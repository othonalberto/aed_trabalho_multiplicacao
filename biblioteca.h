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


/*  Função para criar a cabeça da lista.
    Implementada por Pedro Warmling Botelho */
TCabeca *criaCabeca();

/*  Função para inserer no inicio da lista.
    Implementada por Pedro Warmling Botelho */
TNo *insereInicio(TCabeca *cabeca, char k);

/*  Função para inserir no fim da lista.
    Implementada por Othon Alberto */
TNo *insereFim(TCabeca *cabeca, char k);

/*  Procedimento para deletar toda a lista (liberar todos os nós)
    Implementado por Othon Alberto */
void deletaLista(TCabeca *cabeca);

/*  Função que retorna a cabeca para a maior lista entre as duas comparadas
    Implementada por Othon Alberto e Pedro Warmling Botelho */
TCabeca *retornaMaiorLista(TCabeca *c1, TCabeca *c2);

/*  Procedimento que abre o arquivo, lê os números e salva-os em listas
    Implementado por Othon Alberto */   
void leArquivo();

/*  Função que soma duas listas e retorna a cabeca para o resultado da soma
    Implementada por Othon Alberto */
TCabeca *somaListas(TCabeca *lista1, TCabeca *lista2);

/*  Procedimento que abre o arquivo 'resultados', chama a função que printa a lista, printa um "\n" e fecha o arquivo.
    Implementado por Othon Alberto */
void escreveArquivo(TNo *lista);

/*  Procedimento que printa a lista do último elemento ao primeiro, usando recursividade
    Implementado por Othon Alberto */
void printaListaRecursivo(TNo *lista, FILE **arquivo);

/*  Procedimento que remove os zeros à esquerda do número gerado na multiplicação
    Implementado por Othon Alberto e Pedro Botelho */
void removeZeroEsquerda(TCabeca *lista);

#endif
