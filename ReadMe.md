Este algoritmo é um trabalho da disciplina: Projeto e Análise de Algoritmos - CTCO04  
Realizado por: Giovana Silverio Pereira e Juliana Vieira Azevedo

Este programa processa 10 imagens no formato PPM, lendo-as a partir da entrada padrão. Para cada imagem, uma matriz de filtro é fornecida, com as mesmas dimensões da matriz RGB da imagem.

* O objetivo do programa é multiplicar a matriz de filtro pela matriz RGB de cada imagem utilizando o método de Strassen. A multiplicação será feita da seguinte maneira:

* Para matrizes com dimensões menores do que 64x64, será utilizada a multiplicação comum de matrizes.
Para matrizes com dimensões maiores ou iguais a 64x64, será aplicado o algoritmo de Strassen.

A motivação por trás do uso do algoritmo de Strassen é observar que, para matrizes de maiores dimensões, a diferença de tempo de execução entre a multiplicação comum e a multiplicação por Strassen é considerável, mostrando os benefícios de otimização com algoritmos mais avançados.



