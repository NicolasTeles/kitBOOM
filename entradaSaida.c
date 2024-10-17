#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

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
                fprintf(stderr, "Uso correto: %s -k <arquivo de composição> -c <arquivo de configuração>", argv[0]);
                exit(1);
        }
    }
    return 0;
}

