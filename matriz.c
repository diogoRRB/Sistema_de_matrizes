#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

Matriz *criar_matriz(int linhas, int colunas) {

    Matriz *m = malloc(sizeof(Matriz));

    if (!m)
        return NULL;

    m->linhas = linhas;
    m->colunas = colunas;

    m->dados = malloc(linhas * sizeof(double *));

    if (!m->dados) {
        free(m);
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {

        m->dados[i] = calloc(colunas, sizeof(double));

        if (!m->dados[i]) {

            for (int j = 0; j < i; j++)
                free(m->dados[j]);

            free(m->dados);
            free(m);

            return NULL;
        }
    }

    return m;
}


Matriz *ler_matriz(int numero) {

    int linhas, colunas;

    printf("\nMatriz %d\n", numero);

    printf("Linhas: ");
    if (scanf("%d", &linhas) != 1 || linhas <= 0)
        return NULL;

    printf("Colunas: ");
    if (scanf("%d", &colunas) != 1 || colunas <= 0)
        return NULL;

    Matriz *m = criar_matriz(linhas, colunas);

    if (!m)
        return NULL;

    for (int i = 0; i < linhas; i++) {

        for (int j = 0; j < colunas; j++) {

            printf("Elemento [%d][%d]: ", i + 1, j + 1);

            if (scanf("%lf", &m->dados[i][j]) != 1) {
                liberar_matriz(m);
                return NULL;
            }
        }
    }

    return m;
}


void exibir_matriz(Matriz *m) {

    if (!m)
        return;

    for (int i = 0; i < m->linhas; i++) {

        printf("[ ");

        for (int j = 0; j < m->colunas; j++) {

            printf("%8.2f ", m->dados[i][j]);
        }

        printf("]\n");
    }
}


void liberar_matriz(Matriz *m) {

    if (!m)
        return;

    for (int i = 0; i < m->linhas; i++)
        free(m->dados[i]);

    free(m->dados);
    free(m);
}
