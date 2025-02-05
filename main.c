// Projeto e Análise de Algoritmos - CTCO04
// Trabalho 01 - 26/09/2024
// Giovana Silverio Pereira - 2024000681
// Juliana Vieira Azevedo - 2022000771

#include <stdio.h>
#include <stdlib.h>

// Função para alocar a matriz considerando os três valores de cada célula
int **alocarMatriz(int altura)
{
    int **matriz = (int **)malloc(altura * sizeof(int *)); 
    for (int i = 0; i < altura; i++)
    {
        matriz[i] = (int *)malloc(3 * altura * sizeof(int)); 
        for (int j = 0; j < 3 * altura; j++)
        {
            matriz[i][j] = 0; 
        }
    }
    return matriz; 
}

// Função para ler a matriz
void lerMatriz(int largura, int altura, int ***matriz)
{
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura * 3; j++) 
        {
            scanf("%d", &(*matriz)[i][j]); 
        }
    }
}

// Função para multiplicar cada elemento da célula da matriz
void multiplica(int **A, int **B, int altura, int **C, int n)
{
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < altura * 3; j += 3)
        { 
            for (int k = 0; k < altura * 3; k += 3)
            { 
                C[i][j + n] += A[i][k + n] * B[k / 3][j + n];
            }
        }
    }
}

void multiplicarMatrizes(int **A, int **B, int altura, int **C)
{
    // Multiplicar os elementos indivualmente
    multiplica(A, B, altura, C, 0); 
    multiplica(A, B, altura, C, 1); 
    multiplica(A, B, altura, C, 2); 
}

void imprime_matriz(int linha, int coluna, int **matriz, int valores_por_celula)
{
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna * valores_por_celula; j += valores_por_celula)
        {
            for (int k = 0; k < valores_por_celula; k++)
            {
                printf("%d ", matriz[i][j + k]);
            }
        }
        printf("\n");
    }
}

void somarMatrizes(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n * 3; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtrairMatrizes(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n * 3; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Função para dividir a matriz em submatrizes
void dividir(int **matriz, int **A11, int **A12, int **A21, int **A22, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n * 3; j++)
        {
            A11[i][j] = matriz[i][j];

            A12[i][j] = matriz[i][j + n * 3];

            A21[i][j] = matriz[i + n][j];

            A22[i][j] = matriz[i + n][j + n * 3];
        }
    }
}

// Função para combinar submatrizes de C 
void montarMatriz(int **C, int **C11, int **C12, int **C21, int **C22, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n * 3; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + n * 3] = C12[i][j];
            C[i + n][j] = C21[i][j];
            C[i + n][j + n * 3] = C22[i][j];
        }
    }
}

void liberarMatriz(int **matriz, int altura)
{
    for (int i = 0; i < altura; i++)
    {
        free(matriz[i]); 
    }
    free(matriz); 
}

void strassen(int **A, int **B, int **C, int n)
{
    if (n <= 64)
    {
        multiplicarMatrizes(A, B, n, C);
        return;
    }

    // Divide o tamanho da matriz por 2 para obter o tamanho das submatrizes
    int divideTamanho = n / 2;

    int **A11 = alocarMatriz(divideTamanho);
    int **A12 = alocarMatriz(divideTamanho);
    int **A21 = alocarMatriz(divideTamanho);
    int **A22 = alocarMatriz(divideTamanho);

    int **B11 = alocarMatriz(divideTamanho);
    int **B12 = alocarMatriz(divideTamanho);
    int **B21 = alocarMatriz(divideTamanho);
    int **B22 = alocarMatriz(divideTamanho);

    int **C11 = alocarMatriz(divideTamanho);
    int **C12 = alocarMatriz(divideTamanho);
    int **C21 = alocarMatriz(divideTamanho);
    int **C22 = alocarMatriz(divideTamanho);

    int **P1 = alocarMatriz(divideTamanho);
    int **P2 = alocarMatriz(divideTamanho);
    int **P3 = alocarMatriz(divideTamanho);
    int **P4 = alocarMatriz(divideTamanho);
    int **P5 = alocarMatriz(divideTamanho);
    int **P6 = alocarMatriz(divideTamanho);
    int **P7 = alocarMatriz(divideTamanho);

    int **temp1 = alocarMatriz(divideTamanho);
    int **temp2 = alocarMatriz(divideTamanho);

    // Divide as matrizes A e B em 4 submatrizes cada
    dividir(A, A11, A12, A21, A22, divideTamanho);
    dividir(B, B11, B12, B21, B22, divideTamanho);

    // Calcula os 7 produtos (algoritmo de Strassen)

    // P1 = A11 * (B12 - B22)
    subtrairMatrizes(B12, B22, temp2, divideTamanho); // temp2 = B12 - B22
    strassen(A11, temp2, P1, divideTamanho); // P1 = A11 * temp2

    // P2 = (A11 + A12) * B22
    somarMatrizes(A11, A12, temp1, divideTamanho); // temp1 = A11 + A12
    strassen(temp1, B22, P2, divideTamanho); // P2 = temp1 * B22


    // P3 = (A21 + A22) * B11
    somarMatrizes(A21, A22, temp1, divideTamanho); // temp1 = A21 + A22
    strassen(temp1, B11, P3, divideTamanho); // P3 = temp1 * B11


    // P4 = A22 * (B21 - B11)
    subtrairMatrizes(B21, B11, temp2, divideTamanho); // temp2 = B21 - B11
    strassen(A22, temp2, P4, divideTamanho); // P4 = A22 * temp2

    // P5 = (A11 + A22) * (B11 + B22)
    somarMatrizes(A11, A22, temp1, divideTamanho); // temp1 = A11 + A22 
    somarMatrizes(B11, B22, temp2, divideTamanho); // temp2 = B11 + B22
    strassen(temp1, temp2, P5, divideTamanho); // P5 = temp1 * temp2

    // P6 = (A12 - A22) * (B21 + B22)
    subtrairMatrizes(A12, A22, temp1, divideTamanho); // temp1 = A12 - A22
    somarMatrizes(B21, B22, temp2, divideTamanho); // temp2 = B21 + B22
    strassen(temp1, temp2, P6, divideTamanho); // P6 = temp1 * temp2

    // P7 = (A11 - A21) * (B11 + B12)
    subtrairMatrizes(A11, A21, temp1, divideTamanho); // temp1 = A11 - A21
    somarMatrizes(B11, B12, temp2, divideTamanho); // temp2 = B11 + B12
    strassen(temp1, temp2, P7, divideTamanho); // P7 = temp1 * temp2

    // Calcula as submatrizes de C

    // C11 = P5 + P4 - P2 + P6
    somarMatrizes(P5, P4, temp1, divideTamanho); // temp1 = P5 + P4
    subtrairMatrizes(temp1, P2, temp2, divideTamanho); // temp2 = temp1 - P2
    somarMatrizes(temp2, P6, C11, divideTamanho); // C11 = temp2 + P6

    // C12 = P1 + P2
    somarMatrizes(P1, P2, C12, divideTamanho);

    // C21 = P3 + P4
    somarMatrizes(P3, P4, C21, divideTamanho);

    // C22 = P1 + P5 - P3 - P7
    somarMatrizes(P1, P5, temp1, divideTamanho); // temp1 = P1 + P5
    subtrairMatrizes(temp1, P3, temp2, divideTamanho); // temp2 = temp1 - P3
    subtrairMatrizes(temp2, P7, C22, divideTamanho); // C22 = temp2 - P7


    // Combina as submatrizes na matriz final C
    montarMatriz(C, C11, C12, C21, C22, divideTamanho);

    liberarMatriz(A11, divideTamanho);
    liberarMatriz(A12, divideTamanho);
    liberarMatriz(A21, divideTamanho);
    liberarMatriz(A22, divideTamanho);
    liberarMatriz(B11, divideTamanho);
    liberarMatriz(B12, divideTamanho);
    liberarMatriz(B21, divideTamanho);
    liberarMatriz(B22, divideTamanho);
    liberarMatriz(C11, divideTamanho);
    liberarMatriz(C12, divideTamanho);
    liberarMatriz(C21, divideTamanho);
    liberarMatriz(C22, divideTamanho);
    liberarMatriz(P1, divideTamanho);
    liberarMatriz(P2, divideTamanho);
    liberarMatriz(P3, divideTamanho);
    liberarMatriz(P4, divideTamanho);
    liberarMatriz(P5, divideTamanho);
    liberarMatriz(P6, divideTamanho);
    liberarMatriz(P7, divideTamanho);
    liberarMatriz(temp1, divideTamanho);
    liberarMatriz(temp2, divideTamanho);
}


int main()
{
    char tipo[3];
    int altura, largura, max_val;

    // le as infos do cabeçalho
    scanf("%s", tipo); 
    scanf("%d %d", &altura, &largura);
    scanf("%d", &max_val);

    int **A = alocarMatriz(altura);
    int **B = alocarMatriz(altura);
    int **C = alocarMatriz(altura);

    lerMatriz(largura, altura, &A);
    lerMatriz(largura, altura, &B);

    strassen(A, B, C, altura);

    printf("P3\n%d %d\n%d\n", altura, largura, max_val);
    imprime_matriz(altura, largura, C, 3);

    liberarMatriz(A, altura);
    liberarMatriz(B, altura);
    liberarMatriz(C, altura);

    return 0;
}