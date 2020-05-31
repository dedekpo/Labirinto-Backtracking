#include "funcoes.h"


bool movimentaEstudante(int tamLinhas, int tamColunas, int **labirinto,
                        int **visitado, int **caminho, int linhaAtual,
                        int colunaAtual, int *movimentos, int qtdChaves, int *pontColuna) {

  // Se está fora dos limites do mapa, essa coordenada é inválida.
    if (linhaAtual < 0 || colunaAtual < 0 || linhaAtual >= tamLinhas || colunaAtual >= tamColunas) return false;

    if (labirinto[linhaAtual][colunaAtual] == 4 && visitado[linhaAtual][colunaAtual] == 1){
        qtdChaves--;
    }
    if(labirinto[linhaAtual][colunaAtual] == 2) return false;
  // Se tem alguma barreira ou já se foi visitado essa posição, também é inválido.
    if (visitado[linhaAtual][colunaAtual] == 1) return false;

    if (labirinto[linhaAtual][colunaAtual] == 4){
        qtdChaves++;
    }

    if (labirinto[linhaAtual][colunaAtual] == 3){
        if (qtdChaves <= 0){
            return false;
        } else {
            qtdChaves--;
        }
    }
    visitado[linhaAtual][colunaAtual] = 1;
    printf("Linha: %d Coluna: %d\n", linhaAtual, colunaAtual);
    (*movimentos)++;
  // Se já estamos na coordenada final, finaliza a execução!
    if (linhaAtual == 0) {
        caminho[linhaAtual][colunaAtual] = 1;
        (*pontColuna) = colunaAtual;
        return true;
    }

  // Movimenta pra cima.
    if (movimentaEstudante(tamLinhas, tamColunas, labirinto, visitado, caminho, linhaAtual-1, colunaAtual, movimentos, qtdChaves, pontColuna)) {
        caminho[linhaAtual][colunaAtual] = 4;
        return true;
    }
  // Movimenta pra esquerda.
    if (movimentaEstudante(tamLinhas, tamColunas, labirinto, visitado,caminho, linhaAtual, colunaAtual-1, movimentos, qtdChaves, pontColuna)) {
        caminho[linhaAtual][colunaAtual] = 5;
        return true;
    }
    // Movimento pra direita.
    if (movimentaEstudante(tamLinhas, tamColunas, labirinto, visitado,caminho, linhaAtual , colunaAtual+1, movimentos, qtdChaves, pontColuna)) {
        caminho[linhaAtual][colunaAtual] = 6;
        return true;
    }
  // Movimenta pra baixo.
    if (movimentaEstudante(tamLinhas, tamColunas, labirinto, visitado,caminho, linhaAtual+1, colunaAtual, movimentos, qtdChaves, pontColuna)) {
        caminho[linhaAtual][colunaAtual] = 7;
        return true;
    }
  // Retorna falso se deu certo para todas as direções, mas não era a coordenada final.
    return false;
}

void imprimeMatriz(int tamLinhas, int tamColunas, int **matriz){
    for (int i =0; i<tamLinhas ; i++){
        for (int j = 0; j<tamColunas ; j++){
            printf("|");
            if(matriz[i][j] == 4){
                printf("^");
            } else if (matriz[i][j] == 3){
                printf("X");
            } else if (matriz[i][j] == 5){
                printf("<");
            } else if (matriz[i][j] == 6){
                printf(">");
            }else if(matriz[i][j] == 7){
                printf("\/");
            } else if(matriz[i][j] == 1){
                printf("o");
            } else if (matriz[i][j] == 10){
                printf("?");
            } else if(matriz[i][j] == 11){
                printf("!");
            } else {
                printf(" ");
            }
            printf("|");
        }
        printf("\n");
    }
}

void gerarMatriz (int linhas, int colunas, int portas, int chaves, int dificuldade, char nomeArquivo[20]){
    FILE *pont;
    srand(time(0));
    int setEstudante =1, setParedes = (linhas*colunas)*(dificuldade*0.1), matrizTeste[linhas][colunas], testeX, testeY, aleatorio;
    pont = fopen(nomeArquivo, "w");

    if (pont == NULL){
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    fprintf(pont, "%d %d %d\n", linhas, colunas, chaves);
    for (int i = 0; i< linhas; i++){
        for (int j=0; j< colunas; j++){
            aleatorio = rand()%30;
            if (aleatorio == 1){
                matrizTeste[i][j] = 4;
            } else {
                matrizTeste[i][j] = 1;
            }
        }
    }
    while (setParedes > 0){
        testeX = rand()%linhas; testeY = rand()%colunas;
        if (matrizTeste[testeX][testeY] != 2){
            matrizTeste[testeX][testeY] = 2;
            setParedes--;
        }
    }
    while(setEstudante > 0){
        testeX = rand()%linhas; testeY = rand()%colunas;
        if(matrizTeste[testeX][testeY] == 1){
            matrizTeste[testeX][testeY] = 0;
            setEstudante--;
        }
    }
    while (portas > 0){
        testeX = rand()%linhas; testeY = rand()%colunas;
        if (matrizTeste[testeX][testeY] == 1){
            matrizTeste[testeX][testeY] = 3;
            portas--;
        }
    }
    for (int i = 0; i< linhas; i++){
        for (int j=0; j< colunas; j++){
            fprintf(pont, "%d", matrizTeste[i][j]);
        }
        fprintf(pont, "\n");
    }
}
