#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"

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

void posicionaBomba(Kit* kitBooom, int bombaAdicionada){
    Bomba* bomba = kitBooom->vetorBombas[bombaAdicionada];
    int inicioLinha = bomba->inicioLinha;
    int inicioColuna = bomba->inicioColuna;
    int fimLinha = bomba->fimLinha;
    int fimColuna = bomba->fimColuna;
    for(int i = inicioLinha-1; i < fimLinha; i++){
        for(int j = inicioColuna-1; j < fimColuna; j++){
            //printf("%d %d\n", i, j);
            strcpy(kitBooom->matrizPosicoes[i][j].cor,bomba->cor.cor); //copiando a string da bomba na matriz do kit
            //printf("Chegou\n");
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

int testaArquivoConfiguracao(Kit* kitBoom){
    Bomba *bomba;
    for(int i = 0; i < kitBoom->numBombas; i++){
        bomba = kitBoom->vetorBombas[i];
        for(int j = bomba->inicioLinha-1; j < bomba->fimLinha; j++){
            int indexColunaAntes = bomba->inicioColuna-2;
            int indexColunaDepois = bomba->fimColuna;
            
            Cor corConferida = kitBoom->matrizPosicoes[j][bomba->inicioColuna-1];
            if(indexColunaDepois <=5){ //verifica se a coluna posterior não ultrapassa os limites da matriz
                Cor corAdjacenteDepois = kitBoom->matrizPosicoes[j][indexColunaDepois];
                if(strcmp(corConferida.cor, corAdjacenteDepois.cor) == 0){ //verifica se possuem a mesma cor, se sim retorna 0 de erro
                    return 0;
                }
            }
            if(indexColunaAntes >= 0){//verifica se a coluna anterior busca indice fora da matriz
                Cor corAdjacenteAntes = kitBoom->matrizPosicoes[j][indexColunaAntes];
                if(strcmp(corConferida.cor, corAdjacenteAntes.cor) == 0){//verifica se possuem a mesma cor, se sim retorna 0 de erro
                    return 0;
                }
            }
        }
        for(int j = bomba->inicioColuna-1; j < bomba->fimColuna; j++){
            int indexLinhaAntes = bomba->inicioLinha-2;
            int indexLinhaDepois = bomba->fimLinha;
            
            Cor corConferida = kitBoom->matrizPosicoes[bomba->inicioLinha-1][j];
            if(indexLinhaDepois <=5){ //verifica se a linha busca indice de fora da matriz 
                Cor corAdjacenteDepois = kitBoom->matrizPosicoes[indexLinhaDepois][j];
                if(strcmp(corConferida.cor, corAdjacenteDepois.cor) == 0){ //verifica se possuem a mesma cor, se sim retorna 0 de erro
                    return 0;
                }
            }
            if(indexLinhaAntes >= 0){ //verifica se a linha busca indice de fora da matriz 
                Cor corAdjacenteAntes = kitBoom->matrizPosicoes[indexLinhaAntes][j];
                if(strcmp(corConferida.cor, corAdjacenteAntes.cor) == 0){//verifica se possuem a mesma cor, se sim retorna 0 de erro
                    return 0;
                }
            }
        }
    }
    return 1;
}

void imprimir_matriz(Cor **matriz) {
    int i, j;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            printf("%s\t", matriz[i][j].cor);
        }
        printf("\n");
    }
}

void destroirBomba(Bomba* bomba){
    if(bomba == NULL)
        return;
    free(bomba);
}

Bomba** criaVetorBomba(int numeroBombas){
    return (Bomba**)malloc(numeroBombas * sizeof(Bomba*));
}

Kit* criaKit(int numBombas){
    Kit* kitBOOM = (Kit*)malloc(sizeof(Kit));

    kitBOOM->numBombas = numBombas;

    kitBOOM->matrizPosicoes = (Cor**)malloc(6 * sizeof(Cor*));
    for(int i = 0; i < 6; i++){
        kitBOOM->matrizPosicoes[i] = (Cor*)malloc(6 * sizeof(Cor));
    }
    
    kitBOOM->vetorBombas = criaVetorBomba(numBombas);

    return kitBOOM;
}

void destroiMatriz(Cor** matriz){
    if(matriz == NULL)
        return;
    for(int i = 0; i < 6; i++)
        free(matriz[i]);
    free(matriz);
}

void destroiVetorBombas(Bomba** vetor, int n){
    if(vetor == NULL || *vetor ==  NULL)
        return;
    for(int i = 0; i < n; i++){
        destroirBomba(vetor[i]);
    }
    free(vetor);
}

void destroiKit(Kit* kitBoom){
    if(kitBoom == NULL)
        return;
    destroiMatriz(kitBoom->matrizPosicoes);
    destroiVetorBombas(kitBoom->vetorBombas, kitBoom->numBombas);
    free(kitBoom);
}