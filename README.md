# Sistema_de_matrizes
Sistema em C interativo que permite o usuário cadastrar matrizes e realizar operações matemáticas entre elas.

## Como testar o programa

O programa pode ser executado utilizando um compilador C, como o GCC.

### 1. Compilação

No terminal, dentro da pasta do projeto, execute:

```bash
gcc -Wall -Wextra -std=c11 main.c matriz.c operacoes.c -o matrizes -lm
```

### 2. Execução

Após a compilação, execute o programa:

**Windows:**
```bash
.\matrizes.exe
```

**Linux:**
```bash
./matrizes
```

### 3. Utilização

Ao executar o programa, o usuário deverá informar a quantidade de matrizes que deseja cadastrar, suas dimensões e os elementos de cada matriz.

Após o cadastro, será apresentado um menu com as seguintes operações:

- Adição;
- Subtração;
- Multiplicação;
- Divisão matricial.

O usuário poderá escolher a operação desejada, visualizar o resultado e repetir o processo até encerrar o programa.
