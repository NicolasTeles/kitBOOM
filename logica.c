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

