#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logica.h"
#include "entradaSaida.h"

Bomba* criabomba(int inicioLinha, int inicioColuna, int fimLinha, int fimColuna, int tamanho, Cor cor){
    Bomba *bomba = (Bomba*)malloc(sizeof(Bomba));
    bomba->cor = cor;
    bomba->inicioLinha = inicioLinha;
    bomba->inicioColuna = inicioColuna;
    bomba->fimLinha = fimLinha;
    bomba->fimColuna = fimColuna;
    bomba->tamanho = tamanho;
    return bomba;
}

void posicionaBombas(Kit* kitBooom, int bombaAdicionada){
    Bomba* bomba = kitBooom->vetorBombas[bombaAdicionada];
    int inicioLinha = bomba->inicioLinha;
    int inicioColuna = bomba->inicioColuna;
    int fimLinha = bomba->fimLinha;
    int fimColuna = bomba->fimColuna;
    for(int i = inicioLinha-1; i < fimLinha; i++){
        for(int j = inicioColuna-1; j < fimColuna; j++){
            kitBooom->matrizPosicoes[i][j] = bomba->cor;
        }
    }
}

int testaArquivoComposicao(int numBombas, int areaBomba, int* areaTotalBombas){
    *areaTotalBombas += numBombas*areaBomba;
    if(*areaTotalBombas < 36)
        return -1;
    if(*areaTotalBombas > 36)
        return 1;
    return 0;
}

void destroirBomba(Bomba* bomba){
    free(bomba);
}

Kit* criaKit(int numBombas){
    Kit* kitBOOM = (Kit*)malloc(sizeof(Kit));

    kitBOOM->numBombas = numBombas;

    kitBOOM->matrizPosicoes = (Cor**)malloc(6 * sizeof(Cor*));
    for(int i = 0; i < 6; i++){
        kitBOOM->matrizPosicoes[i] = (Cor*)malloc(6 * sizeof(Cor));
    }
    
    kitBOOM->vetorBombas = (Bomba**)malloc(numBombas * sizeof(Bomba*));

    return kitBOOM;
}
