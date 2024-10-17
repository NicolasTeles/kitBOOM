#include <stdio.h>
#include <stdlib.h>
#include "logica.h"

Bomba* criabomba(){
    Bomba *bomba = (Bomba*)malloc(sizeof(Bomba));
    return bomba;
}

void destroirBomba(Bomba* bomba){
    free(bomba);
}

