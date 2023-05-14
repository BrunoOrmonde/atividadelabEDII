#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int cont = 0;
Arvore *cria_arv_vazia()
{
    return NULL;
}

// Retorna 1 se arvore esta vazia e 0 caso contrario
int arvore_vazia(Arvore *arv)
{
    if (arv == NULL)
        return 1;
    return 0;
}

// Função recursiva que destroi arvore
void destroi_arv(Arvore *arv)
{
    // Verifica arvore vazia
    if (arvore_vazia(arv) != 1)
    {
        // Chamada recursiva move para nó esquerda
        destroi_arv(arv->esq);
        // Chamada recursiva move para nó direita
        destroi_arv(arv->dir);
        // Destroi nó atual
        free(arv);
    }
}

Arvore *inserir(Arvore *a, int v)
{
    /* Variavel extra para efetuar balanceamento,
       funciona como uma forma de backup
       recebendo o valor do nó inicial
    */
    if (buscar(a, v))
    {
        printf("\n**Valor ja cadastrado!!**\n");
    }

    if (arvore_vazia(a))
    {
        Arvore *novo;
        novo = (Arvore *)malloc(sizeof(Arvore));
        novo->info = v;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        a = novo;
    }
    // Caso o valor inserido seja menor que a raiz
    if (v < a->info)
    {
        // chama a função inserir de forma recursiva
        a->esq = inserir(a->esq, v);
    }
    // Caso o valor inserido seja maior que a raiz
    else if (v > a->info)
    {
        a->dir = inserir(a->dir, v);
    }
    a->alt = maior(altura_no(a->esq), altura_no(a->dir)) + 1;
    a = aplica_balanceamento(a);
    return a;
}

// função recursiva imprime nós a partir da raiz
void pre_ordem(Arvore *arv)
{
    if (arv != NULL)
    {
        printf("%d, ", arv->info);
        pre_ordem(arv->esq);
        pre_ordem(arv->dir);
    }
}

// função recursiva imprime nós de forma ordenada
void in_ordem(Arvore *arv)
{
    if (arv != NULL)
    {
        in_ordem(arv->esq);
        printf("%d, ", arv->info);

        in_ordem(arv->dir);
    }
}

// função recursiva imprime nós da esquerda para a direita
void pos_ordem(Arvore *arv)
{
    if (arv != NULL)
    {
        pos_ordem(arv->esq);
        pos_ordem(arv->dir);
        printf("%d, ", arv->info);
    }
}

// verifica se o valor existe dentro da arvore,
// retorna 1 encontra e 0 caso contrario
int buscar(Arvore *a, int v)
{
    if (a == NULL)
    {
        return 0;
    }
    else if (v < a->info)
    {
        return buscar(a->esq, v);
    }
    else if (v > a->info)
    {
        return buscar(a->dir, v);
    }
    else
    {
        return 1;
    }
}

// Remove nó da arvore
Arvore *Remover(Arvore *a, int v)
{
    // verifica se a arvore esta vazia
    if (arvore_vazia(a))
    {
        return NULL;
    }
    // verifica se o valor existe na arvore
    if (buscar(a, v) != 1)
    {
        printf("\n**Valor nao encontrado!!**\n");
    }
    else
    {
        // se valor nó maior valor, move para nó esquerda
        if (a->info > v)
        {
            a->esq = Remover(a->esq, v);
        }
        // se valor nó menor valor, move para nó direita
        else if (a->info < v)
        {
            a->dir = Remover(a->dir, v);
        }
        // encontrando o valor a ser removido
        else
        {
            // nó nao possui filhos, pode ser removido diretamente
            if ((a->esq == NULL) && (a->dir == NULL))
            {
                free(a);
                a = NULL;
            }
            // nó nao possui filho na direita, rotina para manter estrutura
            else if (a->dir == NULL)
            {
                // variavel temporaria para armazenar valores do nó
                Arvore *tmp = a;
                a = a->esq;
                free(tmp);
            }
            // nó nao possui filho na esquerda, rotina para manter estrutura
            else if (a->esq == NULL)
            {
                Arvore *tmp = a;
                a = a->dir;
                free(tmp);
            }
            // nó possui ambos os filhos
            else
            {
                Arvore *tmp = a->esq;
                while (tmp->dir != NULL)
                {
                    tmp = tmp->dir;
                }
                a->info = tmp->info;
                tmp->info = v;
                a->esq = Remover(a->esq, v);
            }
        }
    }
    return a;
}

// Retorna valor inteiro com a altura da arvore
int altura_arvore(Arvore *arv)
{
    if (arvore_vazia(arv))
        return 0;
    int alt_esq = altura_arvore(arv->esq);
    int alt_dir = altura_arvore(arv->dir);
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

// Retorna valor inteiro com a quantidade de nós
int quant_no(Arvore *arv)
{
    if (arvore_vazia(arv))
        return 0;
    int alt_esq = quant_no(arv->esq);
    int alt_dir = quant_no(arv->dir);
    return (alt_esq + alt_dir + 1);
}

// Retorna valor inteiro com a quantidade de nós contendo apenas um filho
int quant_no_um_filho(Arvore *arv)
{
    if (arvore_vazia(arv))
        return 0;
    if ((arv->esq == NULL && arv->dir != NULL) || (arv->dir == NULL && arv->esq != NULL))
        return 1;
    return quant_no_um_filho(arv->esq) + quant_no_um_filho(arv->dir);
}

// Retorna valor inteiro com a quantidade de nós folha
int contar_folhas(Arvore *arv)
{
    if (arvore_vazia(arv))
        return 0;
    if (arv->esq == NULL && arv->dir == NULL)
        return 1;
    return contar_folhas(arv->esq) + contar_folhas(arv->dir);
}

// Retorna valor inteiro com a quantidade de nós nao folha
int nao_folhas(Arvore *arv)
{
    return quant_no(arv) - contar_folhas(arv);
}

// Retorna a soma de todos os nós
int soma_arvore(Arvore *arv)
{
    if (arvore_vazia(arv))
        return 0;
    return (arv->info + soma_arvore(arv->esq) + soma_arvore(arv->dir));
}

// Retorna a média dos valores dos nós
float media_arvore(Arvore *arv)
{
    int nos = quant_no(arv);
    int soma = soma_arvore(arv);
    float media = (float)soma / (float)nos;
    return media;
}

// Retorna a altura do nó, utilizada no fator de balanceamento
int altura_no(Arvore *arv)
{
    if (arvore_vazia(arv))
        return -1;
    else
        return arv->alt;
}

// Retorna o valor de balanceamento do nó
int fator_balanceamento(Arvore *arv)
{
    return (altura_no(arv->esq) - altura_no(arv->dir));
}

// Compara dois valores inteiros e retorna o maior
int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

// Rotação simples para a direita
Arvore *rotacao_LL(Arvore *arv)
{
    Arvore *no1, *no2;
    no1 = arv->esq;
    no2 = no1->dir;
    no1->dir = arv;
    arv->esq = no2;
    arv->alt = maior(altura_no(arv->esq), altura_no(arv->dir)) + 1;
    no1->alt = maior(altura_no(no1->esq), altura_no(no1->dir)) + 1;
    return no1;
}

// Rotação simples para a esquerda
Arvore *rotacao_RR(Arvore *arv)
{
    Arvore *no1, *no2;
    no1 = arv->dir;
    no2 = no1->esq;
    no1->esq = arv;
    arv->dir = no2;
    arv->alt = maior(altura_no(arv->esq), altura_no(arv->dir)) + 1;
    no1->alt = maior(altura_no(no1->esq), altura_no(no1->dir)) + 1;
    return no1;
}

// Rotação dupla para a direita
Arvore *rotacao_LR(Arvore *arv)
{
    arv->esq = rotacao_RR(arv->esq);
    return rotacao_LL(arv);
}

// Rotação simples para a esquerda
Arvore *rotacao_RL(Arvore *arv)
{
    arv->dir = rotacao_LL(arv->dir);
    return rotacao_RR(arv);
}

// Verifica se a arvore esta balanceada
void verifica_balanceamento(Arvore *arv)
{
    int validador = fator_balanceamento(arv);
    if (validador >= 2 || validador <= -2)
    {
        printf("\nArvore desbalanceada!!\n");
    }
    else
    {
        printf("\nArvore balanceada!!!\n");
    }
}

// Imprime menu e retorna o input do usuario
int menu()
{
    int input;
    printf("\n================================\n");
    printf("Opção 1: Inserir NÓ\n");
    printf("Opção 2: Remover NÓ\n");
    printf("Opção 3: Listar NÓS da Arvore\n");
    printf("Opção 4: Informação dos NÓS\n");
    printf("Opção 5: Altura da arvore\n");
    printf("Opção 6: Soma dos valores dos NÓS\n");
    printf("Opção 7: Media dos valores da Arvore\n");
    printf("Opção 8: Verifique se a Arvore esta balanceada\n");
    printf("Opção 9: Imprime vetor com valores menores que N\n");
    printf("Opção 0: sair\n");
    printf("================================\n");

    printf("Digite uma opção: ");
    // atribue um valor de entrada para input
    scanf("%d", &input);
    return input;
}

// Retorna numero inteiro com quantidade de valores para o vetor
int cont_valor_menor_arvore(Arvore *arv, int v)
{
    if (arvore_vazia(arv))
        return 0;
    int quant_esq = cont_valor_menor_arvore(arv->esq, v);
    int quant_dir = cont_valor_menor_arvore(arv->dir, v);
    if (arv->info <= v)
        return (quant_esq + quant_dir + 1);
    else
    {
        return 0;
    }
}

// Retorna vetor com valores menores que N
int vetor_valores(Arvore *arv, int *vetor, int v, int *i)
{
    if (arvore_vazia(arv))
        return 0;
        
    // Adiciona os valores no vetor em ordem
    vetor_valores(arv->esq, vetor, v, i);
    if (arv->info <= v)
    {
        vetor[*i] = arv->info;
        *i += 1;
    }
    vetor_valores(arv->dir, vetor, v, i);

    return 1;
}

// Aplica balanceamento a partir do nó de entrada
Arvore *aplica_balanceamento(Arvore *arv)
{
    int fator_b = fator_balanceamento(arv);

    // Rotação esquerda
    if (fator_b < -1 && fator_balanceamento(arv->dir) <= 0)
        arv = rotacao_RR(arv);

    // Rotação direita
    else if (fator_b > 1 && fator_balanceamento(arv->esq) >= 0)
        arv = rotacao_LL(arv);

    // Dupla rotação para esquerda
    else if (fator_b > 1 && fator_balanceamento(arv->esq) < 0)
        arv = rotacao_RL(arv);

    // Dupla rotação para direita
    else if (fator_b < -1 && fator_balanceamento(arv->dir) > 0)
        arv = rotacao_LR(arv);
    return arv;
}
