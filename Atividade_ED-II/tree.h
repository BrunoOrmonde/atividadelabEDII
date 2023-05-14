#ifndef TREE_H
#define TREE_H

/*
Estrutura Arvore AVL:
-Comtem um bit a mais
para fator de balanceamento,
se o valor for -1, 0 ou 1 a
arvore esta balancedada,
caso contrario serao
necessaios alguns
procedimentos de "rotação"
para que a arvore fique balanceada.
*/

struct arvore
{
  int info;           // Valor do no
  int alt;            // Valor de balanceamento
  struct arvore *esq; // Aponta para o nó da esquerda
  struct arvore *dir; // Aponta para o nó da direita
};

// Cria a assinatura da estrutura
typedef struct arvore Arvore;

// Cria Arvore vazia
Arvore *cria_arv_vazia();

// verifica se o valor existe dentro da arvore,
// retorna 1 encontra e 0 caso contrario
int buscar(Arvore *a, int v);

// Destroi arvore
void destroi_arv(Arvore *arv);

// Inseri novo nó na arvore
Arvore *inserir(Arvore *a, int v);

// Imprime nós a partir da raiz
void pre_ordem(Arvore *arv);

// Imprime nós de forma ordenada(crescente)
void in_ordem(Arvore *arv);

// Imprime nós da esquerda para a direita
void pos_ordem(Arvore *arv);

// Remove nó
Arvore *Remover(Arvore *a, int v);

// Verifica se a arvore esta vazia (return 0 ou 1)
int arvore_vazia(Arvore *arv);

// Retorna a altura da arvore
int altura_arvore(Arvore *arv);

// Retorna a quantidade de nós
int quant_no(Arvore *arv);

// Retorna a quantidade de nós folhas
int contar_folhas(Arvore *arv);

// Retorna a quantidade de nós não folha
int nao_folhas(Arvore *arv);

// Retorna a soma dos nós
int soma_arvore(Arvore *arv);

// Retorna a media da soma dos nós
float media_arvore(Arvore *arv);

// Retorna o valor de arv->alt utilizado no fator de balanceamento
int altura_no(Arvore *arv);

// Rotação simples para a direita
Arvore *rotacao_LL(Arvore *arv);

// Rotação simples para a esquerda
Arvore *rotacao_RR(Arvore *arv);

// Rotação dupla para a direita
Arvore *rotacao_LR(Arvore *arv);

// Rotação dupla para a esquerda
Arvore *rotacao_RL(Arvore *arv);

/* Retorna o valor de balancemanto,
se este valor for maior ou igual a -2 e 2,
a arvore esta desbalanceada
*/
int fator_balanceamento(Arvore *arv);

// Imprime o estado de balancemaneto da arvore
void verifica_balanceamento(Arvore *arv);

// Imprime o menu de opções e recebe um imput do usuario
int menu();

// Retorna valor inteiro com a quantidade de nós contendo apenas um filho
int quant_no_um_filho(Arvore *arv);

/*Conta a quantidade de nós dentro da arvore,
 menor que o valor indicado, função para criar
  um vetor dinamico com a quantidade exata de valores validos
*/
int cont_valor_menor_arvore(Arvore *arv, int v);

// Retorna vetor com valores menores que N
int vetor_valores(Arvore *arv, int *vetor, int v, int *i);

// Retorna maior valor comparando 2 valores inteiros
int maior(int x, int y);

// Aplica balanceamento a partir do nó de entrada
Arvore *aplica_balanceamento(Arvore *arv);

#endif