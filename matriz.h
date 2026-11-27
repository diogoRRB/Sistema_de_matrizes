#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct {
    int linhas;
    int colunas;
    double **dados;
} Matriz;

Matriz *criar_matriz(int linhas, int colunas);
Matriz *ler_matriz(int numero);
void exibir_matriz(Matriz *m);
void liberar_matriz(Matriz *m);

#endif
