#ifndef LOGICA_H
#define LOGICA_H

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

int testaArquivoComposicao(int numBombas, int areaBomba, int* areaTotalBombas);

void posicionaBombas(Kit* kitBooom, int bombaAdicionada);

#endif