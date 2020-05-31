#include "Menu.h"

void menuPrincipal(){
    char nomeArq[20], textoString[30], *split;
    int altura, largura, qtdPortas, qtdChaves, dificuldade, mostrar, **caminho, contMovimentos = 0, colunaFinal= -1, *pontColuna;
    int cont=0, valoresMatriz[3], aux=0, j =0, opcao, flag =0, **matrizCaminhos, **visitado, *linhaInicial, *colunaInicial, *movimentos;
    long int tamanhoString;
    FILE *pontArq;
    movimentos = &contMovimentos;
    pontColuna = & colunaFinal;
    do{
        printf("PROGRAMA LABIRINTO: Opcoes do programa:\n1) Carregar novo arquivo de dados.\n2) Processar e exibir resposta.\n3) Criar um labirinto aleatorio \n4) Sair\n");
        scanf("%d", &opcao);
        fflush(stdin);
        system("cls");
        switch(opcao){
            case 1:
                pontArq = lerArquivo();
                while(fgets(textoString, 30, pontArq) != NULL){
                    if (cont == 0){
                        tamanhoString = strlen(textoString) + 1;
                        split = strtok(textoString, " ");
                        while (split != NULL){
                            valoresMatriz[aux] = atoi(split);
                            split = strtok (NULL, " ");
                            aux++;
                        }
                    }
                    cont++;
                }
                matrizCaminhos = alocarMatriz(valoresMatriz[0], valoresMatriz[1]);
                visitado = alocarMatriz(valoresMatriz[0], valoresMatriz[1]);
                caminho = alocarMatriz(valoresMatriz[0], valoresMatriz[1]);
                fseek(pontArq, tamanhoString, SEEK_SET );
                j = 0;
                while(fgets(textoString, 30, pontArq) != NULL){
                    for (int i = 0; i < valoresMatriz[0]; i++){
                        matrizCaminhos[j][i] = textoString[i] - '0';
                        if (matrizCaminhos[j][i] == 1 || matrizCaminhos[j][i] == 0){
                            visitado[j][i] = 0;
                            caminho[j][i] = 0;
                        } else if(matrizCaminhos[j][i] == 3){
                            visitado[j][i] = 10;
                            caminho[j][i] = 10;
                        } else if (matrizCaminhos[j][i] == 4){
                            visitado[j][i] = 11;
                            caminho[j][i] = 11;
                        } else {
                            visitado[j][i] = 3;
                            caminho[j][i] = 3;
                        }
                        if(matrizCaminhos[j][i] == 0){
                            linhaInicial = j;
                            colunaInicial = i;
                        }
                    }
                    j++;
                }
                flag = 1;
                break;
            case 2:
                if(flag!=1){
                    printf("Entre com um arquivo primeiro\n\n");
                    break;
                }
                if(movimentaEstudante(valoresMatriz[0], valoresMatriz[1], matrizCaminhos,
                                       visitado, caminho, linhaInicial, colunaInicial, movimentos, valoresMatriz[2], pontColuna)){
                    printf("O estudante se movimentou %d vezes e chegou na %d coluna\n", contMovimentos-1, colunaFinal+1);

                } else {
                    printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida\n", contMovimentos);
                }
                printf("\nEscolha o tipo de caminho a ser mostrado:\n1)Mostrar todo o caminho do estudante\n2)Mostrar caminho resumido\n");
                scanf("%d", &mostrar);
                switch(mostrar){
                    case 1:
                        imprimeMatriz(valoresMatriz[0], valoresMatriz[1], visitado);
                        break;
                    case 2:
                        imprimeMatriz(valoresMatriz[0], valoresMatriz[1], caminho);
                        break;
                    default:
                        printf("Opcao invalida\n");
                        return;
                        break;
                }
                break;
            case 3:
                printf("Entre com a altura e largura da matriz: (Entre espaço)\n");
                scanf("%d %d", &altura, &largura);
                printf("Entre com a quantidade de portas: \n");
                scanf("%d", &qtdPortas);
                printf("Entre com a quantidade de chaves: \n");
                scanf("%d", &qtdChaves);
                printf("Entre com a dificuldade do labirinto:   (1 até 5)\n");
                scanf("%d", &dificuldade);
                printf("Entre com o nome do arquivo: (Com .txt)\n");
                fflush(stdin);
                scanf("%s", &nomeArq);
                gerarMatriz (altura, largura, qtdPortas, qtdChaves, dificuldade, nomeArq);
                printf("Arquivo gerado com sucesso na pasta do programa (Reinicie a aplicação)\n");
                break;
            default:
                system("cls");
                return;
                break;
        }
    }while (opcao == 1 || opcao == 2 || opcao == 3);
    fclose(pontArq);
    liberarMatriz(valoresMatriz[0], valoresMatriz[1], matrizCaminhos);
    liberarMatriz(valoresMatriz[0], valoresMatriz[1], visitado);
}

int **alocarMatriz (int m, int n){
    int **v;  /* ponteiro para a matriz */
    int   i;    /* variavel auxiliar      */
    if (m < 1 || n < 1) { /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        return (NULL);
    }
  /* aloca as linhas da matriz */
    v = (int **) calloc (m, sizeof(int *));
    if (v == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
  /* aloca as colunas da matriz */
    for ( i = 0; i < m; i++ ) {
        v[i] = (int*) calloc (n, sizeof(int));
        if (v[i] == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
        }
    }
    return (v); /* retorna o ponteiro para a matriz */
}

int **liberarMatriz (int m, int n, int **v){
    int  i;  /* variavel auxiliar */
    if (v == NULL) return (NULL);
    if (m < 1 || n < 1) {  /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        return (v);
    }
    for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
    free (v);      /* libera a matriz */
    return (NULL); /* retorna um ponteiro nulo */
}

FILE *lerArquivo(){
    FILE *pontArq;
    char nomeArq[30];
    printf("Entre com o caminho do arquivo: \n");
    scanf("%s", &nomeArq);
    fflush(stdin);
    system("cls");
    pontArq = fopen(nomeArq, "r");

    if (pontArq == NULL){
        printf("FALHA AO ABRIR O ARQUIVO!\n");
        menuPrincipal();
    }
    return pontArq;
}
