#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "prototipos.h"

void substituiQuebraDeLinha(char* string){
    int n = strlen(string);

    for(int j = 0; j < n; j++){
        if(string[j] == '\n')
            string[j] = '\0';
        }
}

void obterNomeArquivos(int argc, char* argv[], char** arquivoKit, char** arquivoConfiguracao){
    int opt;
    while((opt = getopt(argc, argv, "k:c:")) != -1){
        switch (opt){
            case 'c':
                *arquivoConfiguracao = optarg;
                break;
            case 'k':
                *arquivoKit = optarg;
                break;
            default:
                printf("Uso correto: %s -k <arquivo de composição> -c <arquivo de configuração>\n", argv[0]);
                exit(1);
        }
    }
    return;
}

Kit* lerArquivoComposicao(char* nomeArquivo){
    FILE* fp = fopen(nomeArquivo, "r");
    if(fp == NULL){
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    Kit* kitBoom = NULL;
    int qtdeTotalBombas = 0;
    char string[10];
    int* areaTotalBombas = (int*)malloc(sizeof(int));
    *areaTotalBombas = 0;
    int retornoComposicao;
    int qtdeBombas;
    int areaBomba;
    while(!feof(fp)){
        fgets(string, 10, fp);
        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");
        qtdeBombas = atoi(token);
        token = strtok(NULL, " ");
        areaBomba = atoi(token);
        qtdeTotalBombas += qtdeBombas;
        retornoComposicao = testaArquivoComposicao(qtdeBombas, areaBomba, areaTotalBombas);
        if(retornoComposicao == 1)
            break;
    }
    free(areaTotalBombas);
    fclose(fp);
    
    if(retornoComposicao == -1){
        printf("Composição incorreta, está sobrando espaço no kitBOOM\n");
        exit(0);
    }
    if(retornoComposicao == 1){
        printf("Composição incorreta, não cabem todas as bombas no kitBOOM\n");
        exit(0);
    }
    if(retornoComposicao == 0){
        printf("Composição correta, agora testaremos a configuração\n");
        kitBoom = criaKit(qtdeTotalBombas);
    }
    return kitBoom;
}

void lerArquivoConfiguracao(char* nomeArquivo, Kit* kitBOOM){
    FILE* fp = fopen(nomeArquivo, "r");
    if(fp == NULL){
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }
    char string[15];
    int inicioLinha;
    int inicioColuna;
    int fimLinha;
    int fimColuna;
    int tamanho;
    Cor cor;
    int numBombas = 0;
    int contador = 1;
    while(!feof(fp)){
        fgets(string, sizeof(string), fp);
        if(strcmp(string, "\n") == 0){
            printf("A configuração número %d é ", contador);
            if(testaArquivoConfiguracao(kitBOOM)){
                printf("válida!\n");
            }else{
                printf("inválida!\n");
            }
            contador++;
            destroiVetorBombas(kitBOOM->vetorBombas, numBombas);
            kitBOOM->vetorBombas = criaVetorBomba(kitBOOM->numBombas);
            numBombas = 0;
            continue;
        }
        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");
        inicioLinha = atoi(token);
        token = strtok(NULL, " ");
        inicioColuna = atoi(token);
        token = strtok(NULL, " ");
        fimLinha = atoi(token);
        token = strtok(NULL, " ");
        fimColuna = atoi(token);
        token = strtok(NULL, " ");
        tamanho = atoi(token);
        token++;
        strcpy(cor.cor, token);
        cor.cor[2] = '\0';
        kitBOOM->vetorBombas[numBombas] = criabomba(inicioLinha, inicioColuna, fimLinha, fimColuna, tamanho, cor);
        posicionaBombas(kitBOOM, numBombas);
        numBombas++;
    }
    printf("A configuração número %d é ", contador);
        if(testaArquivoConfiguracao(kitBOOM)){
            printf("válida!\n");
        }else{
            printf("inválida!\n");
        }
    // imprimir_matriz(kitBOOM->matrizPosicoes);
    fclose(fp);
    
    destroiKit(kitBOOM);
}