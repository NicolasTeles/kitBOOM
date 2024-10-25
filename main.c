#include <stdio.h>
#include "logica.h"
#include "entradaSaida.h"

void casoTesteComposicao(){
    Kit* kitboom = lerArquivoComposicao("composicao.txt");
    free(kitboom);
}

int main(int argc, char* argv[]){
    casoTesteComposicao();
}