#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "logica.h"

void substituiQuebraDeLinha(char* string, int n){
    if(string[n-1] == '\n')
        string[n-1] = '\0';
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
                fprintf(stderr, "Uso correto: %s -k <arquivo de composição> -c <arquivo de configuração>\n", argv[0]);
                exit(1);
        }
    }
    return 0;
}

void lerArquivoComposicao(char* nomeArquivo){
    FILE* fp = fopen(nomeArquivo, "r");
    if(fp == NULL){
        fprintf(stderr, "Erro na abertura do arquivo\n");
        exit(1);
    }
    char string[6];
    int* areaTotalBombas = (int*)malloc(sizeof(int));
    int retornoComposicao;
    fgets(string, 6, fp);
    while(!feof(fp)){
        substituiQuebraDeLinha(string, 6);
        int qtdeBombas = string[0] - '0';
        int areaBomba = string[2] - '0';
        retornoComposicao = testaArquivoComposicao(qtdeBombas, areaBomba, areaTotalBombas);
        if(retornoComposicao == 1)
            break;
        fgets(string, 6, fp);
    }
    free(areaTotalBombas);
    fclose(fp);
    
    if(retornoComposicao == -1){
        fprintf(stderr, "Composição incorreta, está sobrando espaço no kitBOOM\n");
        exit(0);
    }
    if(retornoComposicao == 1){
        fprintf(stderr, "Composição incorreta, não cabem todas as bombas no kitBOOM\n");
        exit(0);
    }
    if(retornoComposicao == 0){
        printf("Composição correta, agora testaremos a configuração\n");
    }
}