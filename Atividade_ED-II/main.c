/*

Para execurar o programa utilize o comando:

    $~ gcc tree.c main.c

Apos gerar o executável o programa pode ser
iniciado com o comando:

    $~ ./a.out


*/

#include <stdio.h>
#include "tree.h"

int main()
{
    int *j; // variavel do tipo ponteiro, utilizada no indice do vetor

    int i = 0, opcao, valor;
    Arvore *a = cria_arv_vazia();

    // valores de teste
    a = inserir(a, 5);
    a = inserir(a, 7);
    a = inserir(a, 3);
    a = inserir(a, 4);
    a = inserir(a, 2);

    // chama a funçao menu()
    opcao = menu();
    // Enquanto opcao diferente de 0
    while (opcao != 0)
    {
        // Inserir novo nó na árvore
        if (opcao == 1)
        {
            printf("\nDigite o valor para o nó: ");
            scanf("%d", &valor);
            a = inserir(a, valor);
        }
        // Remover nó da árvore
        else if (opcao == 2)
        {
            printf("Digite o valor que deseja remover: ");
            scanf("%d", &valor);
            a = Remover(a, valor);
            a = aplica_balanceamento(a);
        }
        // Imprime valores dos nós da árvore
        else if (opcao == 3)
        {
            printf("\nEm ordem\n");
            in_ordem(a);

            printf("\nPre ordem\n");
            pre_ordem(a);

            printf("\nPos ordem\n");
            pos_ordem(a);
        }
        // Imprime imformação sobre nós
        else if (opcao == 4)
        {
            int quant = quant_no(a);
            printf("\n\nQuantidade de nós: %d\n", quant);

            int um_filho = quant_no_um_filho(a);
            printf("\nQuantidade de nós com 1 filho: %d\n", um_filho);

            int folhas = contar_folhas(a);
            printf("\nQuantidade de nós FOLHA: %d\n", folhas);

            int nao_folha = nao_folhas(a);
            printf("\nNao Folhas: %d\n\n", nao_folha);
        }
        // Imprime a altura da árvore
        else if (opcao == 5)
        {
            int altura = altura_arvore(a);
            printf("\n\nAltura: %d\n\n", altura);
        }
        // Imprime a soma dos nós da arvore
        else if (opcao == 6)
        {
            int soma = soma_arvore(a);
            printf("\n\nSoma: %d\n\n", soma);
        }
        // Imprime a media dos nós da arvore
        else if (opcao == 7)
        {
            float media = media_arvore(a);
            printf("\n\nMedia dos valores: %.1f\n\n", media);
        }
        // Imprime se a arvore esta balanceada ou não
        else if (opcao == 8)
        {
            verifica_balanceamento(a);
        }
        // Imprime um vetor de tamanho N contendo N elementos menores que o valor informado
        else if (opcao == 9)
        {
            int k = 0; // variavel utilizada como indice do vetor
            j = &k;    // ponteiro recebe valor de k,
            printf("Digite o valor: ");
            scanf("%d", &valor);
            int tam_vetor = cont_valor_menor_arvore(a, valor);
            // cria tamanho do vetor de forma dinamica
            int vetor[tam_vetor];
            if (tam_vetor==0){
                printf("\nArvore nãopossui nenhum valor menor que * %d *!\n", valor);
            }
            if (vetor_valores(a, vetor, valor, j))
                for (int i = 0; i < tam_vetor; i++)
                {
                    printf(" * %d * ", vetor[i]);
                }
            else
                printf("\nArvore vazia!\n");
        }
        else if (opcao < 0 || opcao > 9)
        {

            printf("\n**Opção invalida!!\n");
        }
        // Chama a função menu para manter o fluxo de repetição
        opcao = menu();
    }
    destroi_arv(a);
    printf("\n**PROGRAMA FINALIZADO**\n");
    return 0;
}