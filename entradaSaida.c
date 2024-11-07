#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "prototipos.h"

//função para substituir o \n para um \0 nas linhas do arquivo
void substituiQuebraDeLinha(char* string){
    int n = strlen(string);

    for(int j = 0; j < n; j++){
        if(string[j] == '\n')
            string[j] = '\0';
        }
}

void obterNomeArquivos(int argc, char* argv[], char** arquivoKit, char** arquivoConfiguracao, int* n){
    int opt;
    while((opt = getopt(argc, argv, "k:c:n:")) != -1){
        switch (opt){
            case 'c':
                *arquivoConfiguracao = optarg;
                break;
            case 'k':
                *arquivoKit = optarg;
                break;
            case 'n':
                *n = atoi(optarg);
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
        char* token = strtok(string, " "); //separa a linha em strings diferentes ao achar um espaço
        qtdeBombas = atoi(token);
        token = strtok(NULL, " "); //muda para a outra string
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
    int indiceBomba = 0; //qual a bomba que está sendo lida e criada e depois posicionada
    int contador = 1;
    while(!feof(fp)){
        fgets(string, sizeof(string), fp);
        if(strcmp(string, "\r\n") == 0 || strcmp(string, "\n") == 0){
            //printf("A configuração número %d é ", contador);
            if(testaArquivoConfiguracao(kitBOOM)){
                //printf("válida!\n");
            }else{
                //printf("inválida!\n");
            }
            contador++;
            destroiVetorBombas(kitBOOM->vetorBombas, indiceBomba);
            kitBOOM->vetorBombas = criaVetorBomba(kitBOOM->numBombas);
            indiceBomba = 0;
            continue;
        }
        substituiQuebraDeLinha(string);
        char* token = strtok(string, " ");  //separa a linha em strings diferentes ao achar um espaço
        inicioLinha = atoi(token);
        token = strtok(NULL, " "); //muda para a outra string
        inicioColuna = atoi(token);
        token = strtok(NULL, " ");
        fimLinha = atoi(token);
        token = strtok(NULL, " ");
        fimColuna = atoi(token);
        token = strtok(NULL, " ");
        tamanho = atoi(token);
        token++;
        strcpy(cor.cor, token);
        cor.cor[2] = '\0'; //garantir o que na string cor tenha o \0 na última posição
        kitBOOM->vetorBombas[indiceBomba] = criabomba(inicioLinha, inicioColuna, fimLinha, fimColuna, tamanho, cor);
        posicionaBomba(kitBOOM, indiceBomba);
        indiceBomba++;
    }
    //printf("A configuração número %d é ", contador);
    if(testaArquivoConfiguracao(kitBOOM)){
        //printf("válida!\n");
    }else{
        //printf("inválida!\n");
    }
    //destroiVetorBombas(kitBOOM->vetorBombas, indiceBomba);
    //kitBOOM->vetorBombas = criaVetorBomba(kitBOOM->numBombas);
    // imprimir_matriz(kitBOOM->matrizPosicoes);
    fclose(fp);
}