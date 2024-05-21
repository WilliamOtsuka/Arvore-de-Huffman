#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TAD.h"

int main() {
    lista *lista = NULL;
    registro *registro = NULL;
    char palavra[]= "Amar e sonhar sonhar e viver viver e curtir curtir e amar Cada um tera uma escolha cada um fara a escolha cada um escolhe a sua escolha Levaremos um tempo para crescer levaremos um tempo para amadurecer levaremos um tempo para entender levaremos um tempo para envelhecer levaremos um tempo para morrer"; //
    lista = separarPalavras(palavra , lista);
    registro = criarRegistro(lista, registro);

    return 0;
}
