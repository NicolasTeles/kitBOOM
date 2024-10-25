#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "logica.h"
#include "entradaSaida.h"

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

Kit* lerArquivoComposicao(char* nomeArquivo){
    FILE* fp = fopen(nomeArquivo, "r");
    if(fp == NULL){
        fprintf(stderr, "Erro na abertura do arquivo\n");
        exit(1);
    }

    Kit* kitBoom = NULL;
    int qtdeTotalBombas = 0;
    char string[6];
    int* areaTotalBombas = (int*)malloc(sizeof(int));
    int retornoComposicao;
    int qtdeBombas;
    int areaBomba;
    fgets(string, 6, fp);
    while(!feof(fp)){
        substituiQuebraDeLinha(string, 6);
        qtdeBombas = string[0] - '0';
        areaBomba = string[2] - '0';
        qtdeTotalBombas += qtdeBombas;
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
        kitBoom = criaKit(qtdeTotalBombas);
    }
    return kitBoom;
}

void lerArquivoConfiguracao(char* nomeArquivo, Kit* kitBOOM){
    FILE* fp = fopen(nomeArquivo, "r");
    if(fp == NULL){
        fprintf(stderr, "Erro na abertura do arquivo\n");
        exit(1);
    }
    char string[12];
    int inicioLinha;
    int inicioColuna;
    int fimLinha;
    int fimColuna;
    int tamanho;
    Cor cor;
    fgets(string, 12, fp);
    int i = 0;
    while(!feof){
        substituiQuebraDeLinha(string, 12);
        inicioLinha = string[0];
        inicioColuna = string[2];
        fimLinha = string[4];
        fimColuna = string[6];
        tamanho = string[8];
        for(int j = 0; j < 12; j++)
            cor.cor[j] = string[j+9];
        kitBOOM->vetorBombas[i] = criabomba(inicioLinha, inicioColuna, fimLinha, fimColuna, tamanho, cor);
        i++;
        posicionaBombas(kitBOOM, i);
    }
    fclose(fp);
    if(testaArquivoConfiguracao(kitBOOM)){
        printf("A configuração é válida!\n");
    }else{
        printf("A configuração é inválida!\n");
    }
    destroiKit(kitBOOM);
}