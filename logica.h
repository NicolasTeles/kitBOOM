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
    Cor matrizPosicoes[6][6];
    Bomba* vetorBombas;
}Kit;

Bomba* criabomba();

void destroirBomba(Bomba* bomba);

