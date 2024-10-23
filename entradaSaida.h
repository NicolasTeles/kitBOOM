#ifndef ENTRADA_SAIDA_H
#define ENTRADA_SAIDA_H

#include "logica.h"

void substituiQuebraDeLinha(char* string, int n);

void obterNomeArquivos(int argc, char* argv[], char** arquivoKit, char** arquivoConfiguracao);

void lerArquivoComposicao(char* nomeArquivo);

void lerArquivoConfiguracao(char* nomeArquivo, Kit* kitBOOM);

#endif