#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED
#include "Menu.h"



#endif // FUNCOES_H_INCLUDED

void imprimeMatriz(int tamLinhas, int tamColunas, int **matriz);

bool movimentaEstudante(int tamLinhas, int tamColunas, int **labirinto, int **visitado,
                         int **caminho, int linhaAtual, int colunaAtual, int *movimentos,
                          int qtdChaves, int *pontColuna);

void gerarMatriz (int linhas, int colunas, int portas, int chaves, int dificuldade, char nomeArquivo[20]);
//int labirinto(int l, int c, int mat[l][c], int deltaL[], int deltaC[], int Li, int Ci, int Lf, int Cf);
