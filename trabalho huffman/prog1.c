#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TADProg1.h"

int main() {
    lista *l = NULL;
    registro *r = NULL;
    tree *a = NULL, *aux;
    
    char frase[]= "Amar e sonhar sonhar e viver viver e curtir curtir e amar Cada um tera uma escolha cada um fara a escolha cada um escolhe a sua escolha Levaremos um tempo para crescer levaremos um tempo para amadurecer levaremos um tempo para entender levaremos um tempo para envelhecer levaremos um tempo para morrer"; // 
    separarPalavras(&l, frase);
    Frequencias(&l);
    imprimirLista(l);
    
    // r = criarRegistro(l);
    // imprimirRegistro(r);
    
    criaListaArvore(l, &a);
    // imprimirListaArvore(a);

    criarArvore(&a);
    printf("\n Arvore de Huffman\n");
    aux = a;
    imprimirArvore(aux, 0);

    r = criarRegistro(l);
    // imprimirRegistro(r);

    gerarCodigoHuffman(a, &r);
    codificarFrase(r);
    exibeCodigoFrase();
    
    return 0;
}	
