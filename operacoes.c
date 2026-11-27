#include <stdlib.h>
#include <math.h>
#include "operacoes.h"

#define EPSILON 1e-10


/* ADICAO */

Matriz *somar(Matriz *a, Matriz *b) {

    if (a->linhas != b->linhas ||
        a->colunas != b->colunas)
        return NULL;

    Matriz *r = criar_matriz(a->linhas, a->colunas);

    if (!r)
        return NULL;

    for (int i = 0; i < a->linhas; i++)
        for (int j = 0; j < a->colunas; j++)
            r->dados[i][j] =
                a->dados[i][j] + b->dados[i][j];

    return r;
}


/* SUBTRACAO */

Matriz *subtrair(Matriz *a, Matriz *b) {

    if (a->linhas != b->linhas ||
        a->colunas != b->colunas)
        return NULL;

    Matriz *r = criar_matriz(a->linhas, a->colunas);

    if (!r)
        return NULL;

    for (int i = 0; i < a->linhas; i++)
        for (int j = 0; j < a->colunas; j++)
            r->dados[i][j] =
                a->dados[i][j] - b->dados[i][j];

    return r;
}


/* MULTIPLICACAO */

Matriz *multiplicar(Matriz *a, Matriz *b) {

    if (a->colunas != b->linhas)
        return NULL;

    Matriz *r = criar_matriz(a->linhas, b->colunas);

    if (!r)
        return NULL;

    for (int i = 0; i < a->linhas; i++)
        for (int j = 0; j < b->colunas; j++)
            for (int k = 0; k < a->colunas; k++)
                r->dados[i][j] +=
                    a->dados[i][k] * b->dados[k][j];

    return r;
}


/* INVERSA - FUNCAO INTERNA */

static Matriz *inversa(Matriz *m) {

    if (m->linhas != m->colunas)
        return NULL;

    int n = m->linhas;

    Matriz *r = criar_matriz(n, n);

    if (!r)
        return NULL;

    double **a = malloc(n * sizeof(double *));

    if (!a) {
        liberar_matriz(r);
        return NULL;
    }

    /* Cria a matriz aumentada [M | I] */

    for (int i = 0; i < n; i++) {

        a[i] = malloc(2 * n * sizeof(double));

        if (!a[i]) {

            for (int j = 0; j < i; j++)
                free(a[j]);

            free(a);
            liberar_matriz(r);

            return NULL;
        }

        for (int j = 0; j < n; j++)
            a[i][j] = m->dados[i][j];

        for (int j = 0; j < n; j++)
            a[i][n + j] = (i == j) ? 1.0 : 0.0;
    }


    /* Gauss-Jordan */

    for (int col = 0; col < n; col++) {

        int p = col;

        for (int i = col + 1; i < n; i++)
            if (fabs(a[i][col]) > fabs(a[p][col]))
                p = i;


        /* Matriz singular */

        if (fabs(a[p][col]) < EPSILON) {

            for (int i = 0; i < n; i++)
                free(a[i]);

            free(a);
            liberar_matriz(r);

            return NULL;
        }


        /* Troca linhas */

        if (p != col) {

            double *temp = a[col];

            a[col] = a[p];
            a[p] = temp;
        }


        /* Normaliza o pivô */

        double divisor = a[col][col];

        for (int j = 0; j < 2 * n; j++)
            a[col][j] /= divisor;


        /* Elimina os demais elementos da coluna */

        for (int i = 0; i < n; i++) {

            if (i == col)
                continue;

            double fator = a[i][col];

            for (int j = 0; j < 2 * n; j++)
                a[i][j] -= fator * a[col][j];
        }
    }


    /* Copia o lado direito para a inversa */

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            r->dados[i][j] = a[i][n + j];


    for (int i = 0; i < n; i++)
        free(a[i]);

    free(a);

    return r;
}


/* DIVISAO MATRICIAL */

Matriz *dividir(Matriz *a, Matriz *b) {

    if (b->linhas != b->colunas)
        return NULL;

    if (a->colunas != b->linhas)
        return NULL;

    Matriz *inv = inversa(b);

    if (!inv)
        return NULL;

    Matriz *r = multiplicar(a, inv);

    liberar_matriz(inv);

    return r;
}
