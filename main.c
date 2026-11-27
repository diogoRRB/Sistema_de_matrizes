#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"
#include "operacoes.h"


int main() {

    int quantidade, opcao;

    /* Cadastro da quantidade de matrizes */

    printf("Quantas matrizes deseja cadastrar? ");

    if (scanf("%d", &quantidade) != 1 || quantidade < 2) {

        printf("Cadastre pelo menos duas matrizes.\n");

        return 1;
    }


    /* Aloca o vetor de matrizes */

    Matriz **matrizes = calloc(
        quantidade,
        sizeof(Matriz *)
    );

    if (!matrizes) {
        printf("Erro de memoria.\n");
        return 1;
    }


    /* Leitura das matrizes */

    for (int i = 0; i < quantidade; i++) {

        matrizes[i] = ler_matriz(i + 1);

        if (!matrizes[i]) {

            printf("Erro ao cadastrar matriz.\n");

            for (int j = 0; j < quantidade; j++)
                liberar_matriz(matrizes[j]);

            free(matrizes);

            return 1;
        }
    }


    /* Menu */

    do {

        printf("\n===== MENU =====\n");
        printf("1 - Adicao\n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao\n");
        printf("4 - Divisao matricial\n");
        printf("0 - Encerrar\n");

        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {

            printf("Entrada invalida.\n");

            break;
        }


        if (opcao >= 1 && opcao <= 4) {

            /* Copia a primeira matriz */

            Matriz *resultado = criar_matriz(
                matrizes[0]->linhas,
                matrizes[0]->colunas
            );

            if (!resultado) {

                printf("Erro de memoria.\n");

                break;
            }

            for (int i = 0; i < resultado->linhas; i++)
                for (int j = 0; j < resultado->colunas; j++)
                    resultado->dados[i][j] =
                        matrizes[0]->dados[i][j];


            /* Operacoes sequenciais */

            int sucesso = 1;

            for (int i = 1; i < quantidade; i++) {

                Matriz *novo = NULL;


                if (opcao == 1)
                    novo = somar(resultado, matrizes[i]);

                else if (opcao == 2)
                    novo = subtrair(resultado, matrizes[i]);

                else if (opcao == 3)
                    novo = multiplicar(resultado, matrizes[i]);

                else if (opcao == 4) {

                    if (matrizes[i]->linhas !=
                        matrizes[i]->colunas) {

                        printf(
                            "Matriz %d nao e quadrada.\n",
                            i + 1
                        );

                    }

                    else if (
                        resultado->colunas !=
                        matrizes[i]->linhas
                    ) {

                        printf(
                            "Dimensoes incompatíveis "
                            "na divisao pela matriz %d.\n",
                            i + 1
                        );

                    }

                    else {

                        novo = dividir(
                            resultado,
                            matrizes[i]
                        );

                        if (!novo)
                            printf(
                                "Matriz %d e singular "
                                "ou houve falha no calculo.\n",
                                i + 1
                            );
                    }
                }


                /* Verifica se a operacao foi realizada */

                if (!novo) {

                    if (opcao == 1)
                        printf(
                            "Adicao impossivel: "
                            "dimensoes diferentes.\n"
                        );

                    else if (opcao == 2)
                        printf(
                            "Subtracao impossivel: "
                            "dimensoes diferentes.\n"
                        );

                    else if (opcao == 3)
                        printf(
                            "Multiplicacao impossivel: "
                            "dimensoes incompatíveis.\n"
                        );

                    sucesso = 0;

                    break;
                }


                /* Atualiza o resultado */

                liberar_matriz(resultado);

                resultado = novo;
            }


            /* Exibe o resultado final */

            if (sucesso) {

                printf("\nResultado:\n");

                exibir_matriz(resultado);
            }

            liberar_matriz(resultado);
        }

        else if (opcao != 0) {

            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);


    /* Libera todas as matrizes */

    for (int i = 0; i < quantidade; i++)
        liberar_matriz(matrizes[i]);

    free(matrizes);

    printf("Programa encerrado.\n");

    return 0;
}
