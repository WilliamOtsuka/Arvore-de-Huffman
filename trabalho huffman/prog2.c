#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TADProg2.h"

int main() {
    tree *a = NULL;
    registro *r = NULL;

    ArvoreBinaria(&a);
    imprimirArvore(a, 0);
    decodificarFrase(a);

    return 0;
}
