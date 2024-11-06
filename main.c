#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "prototipos.h"

Kit* casoTesteComposicao(char* compArq){
    Kit* kitboom = lerArquivoComposicao(compArq);
    return kitboom;
}

void casoTesteConfiguracao(Kit* kitboom, char* configArq){
    lerArquivoConfiguracao(configArq, kitboom);
}

void casoTeste1(){
    char composicao[] = "composicao.txt";
    char config[] = "configuracao.txt";
    Kit* k = casoTesteComposicao(composicao);
    casoTesteConfiguracao(k, config);
}

void casoTeste2(){
    char composicao[] = "composicao2.txt";
    char config[] = "configuracao2.txt";
    Kit* k = casoTesteComposicao(composicao);
    casoTesteConfiguracao(k, config);
}

void calculaTempoProcessador(struct rusage usage){
    getrusage(RUSAGE_SELF, &usage);
    
    printf("\nTempo no modo de usuário rodando o processo: %ld.%06ld segundos\n", 
        usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("Tempo no modo de sistema rodando o processo: %ld.%06ld segundos\n",
        usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    
    long total_sec = usage.ru_utime.tv_sec + usage.ru_stime.tv_sec, 
        total_usec = usage.ru_utime.tv_usec + usage.ru_stime.tv_usec;
    
    if(total_usec > 1000000){
        total_usec -= 1000000;
        total_sec++;
    }
    printf("Tempo total do processo no processador: %ld.%06ld segundos\n",
        total_sec, total_usec);
    printf("Memória máxima usada ao mesmo tempo: %ld KB\n", usage.ru_maxrss);
}

void calculaTempoReal(struct timeval start, struct timeval end){
    long tempoRealMicro = abs(start.tv_usec - end.tv_usec);
    int diminuirSegundo = 0;
    if(start.tv_usec > end.tv_usec){
        tempoRealMicro = 1000000 - tempoRealMicro;
        diminuirSegundo = 1;
    }
    long tempoRealSegundo = abs(start.tv_sec - end.tv_sec);
    if(diminuirSegundo)
        tempoRealSegundo--;
    printf("Tempo passado na vida real: %ld.%06ld segundos\n",
        tempoRealSegundo, tempoRealMicro);
}

int main(int argc, char* argv[]){
    struct timeval start, end;
    struct rusage usage;

    gettimeofday(&start, NULL);

    char* arquivoComposicao = NULL;
    char* arquivoConfig = NULL;
    obterNomeArquivos(argc, argv, &arquivoComposicao, &arquivoConfig);
    Kit* kitboom = lerArquivoComposicao(arquivoComposicao);
    lerArquivoConfiguracao(arquivoConfig, kitboom);

    gettimeofday(&end, NULL);

    printf("====================================================================================\n");

    calculaTempoProcessador(usage);
    calculaTempoReal(start, end);

    printf("====================================================================================\n");
    return 0;
}