#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cor{
    char cor[3];
}Cor;

typedef struct bomba{
    int inicioLinha;
    int inicioColuna;
    int fimLinha;
    int fimColuna;
    int tamanho;
    Cor cor;
} Bomba;

typedef struct kit{
    int numBombas;
    Cor** matrizPosicoes;
    Bomba** vetorBombas;
}Kit;

Bomba* criabomba(int inicioLinha, int inicioColuna, int fimLinha, int fimColuna, int tamanho, Cor cor);

Kit* criaKit(int numBombas);

void destroirBomba(Bomba* bomba);

void imprimir_matriz(Cor **matriz);

int testaArquivoComposicao(int numBombas, int areaBomba, int* areaTotalBombas);

void posicionaBomba(Kit* kitBooom, int bombaAdicionada);

void destroiVetorBombas(Bomba** vetor, int n);

void destroiMatriz(Cor** matriz);

void destroiKit(Kit* kitBoom);

int testaArquivoConfiguracao(Kit* kitBoom);

void substituiQuebraDeLinha(char* string);

void obterNomeArquivos(int argc, char* argv[], char** arquivoKit, char** arquivoConfiguracao);

Kit* lerArquivoComposicao(char* nomeArquivo);

void lerArquivoConfiguracao(char* nomeArquivo, Kit* kitBOOM);

void destroirBomba(Bomba* bomba);

Bomba** criaVetorBomba(int numeroBombas);

#endif