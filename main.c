#include <stdio.h>
#include "logica.h"
#include "entradaSaida.h"

Kit* casoTesteComposicao(){
    Kit* kitboom = lerArquivoComposicao("composicao2.txt");
    return kitboom;
}

void casoTesteConfiguracao(Kit* kitboom){
    lerArquivoConfiguracao("configuracao2.txt", kitboom);
}

int main(int argc, char* argv[]){
    Kit* kitBOOM = casoTesteComposicao();
    casoTesteConfiguracao(kitBOOM);
}