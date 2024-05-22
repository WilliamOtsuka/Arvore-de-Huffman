#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TAD.h"

int main() {
    lista *l = NULL;
    registro *r = NULL;
    listaFolha *lf = NULL;
    tree *arvore = NULL;
    
    char palavra[]= "Amar e sonhar sonhar e viver viver e curtir curtir e amar Cada um tera uma escolha cada um fara a escolha cada um escolhe a sua escolha Levaremos um tempo para crescer levaremos um tempo para amadurecer levaremos um tempo para entender levaremos um tempo para envelhecer levaremos um tempo para morrer"; //
    l = separarPalavras(palavra , l);
    r = criarRegistro(l, r);
    criarFolhas(&lf, r);
    constroiArvore(&arvore, lf);
    imprimeArvore(arvore);
    return 0;
}
