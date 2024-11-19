//O primeiro program deverá ter:
// a) Um algoritmo para construção da árvore de Huffman (utilize uma lista encadeada
// ordenada no processo de construção da árvore). A árvore não deverá ter a palavra e sim
// um símbolo (numérico, um código!). Os espaços em branco da frase também devem ser
// considerados e terá um símbolo na árvore. A frequência das palavras e dos espaços
// deverá ser contada e armazenada na lista do item b) antes de montar a árvore.

// c) Codificação de uma frase e armazenamento do resultado (uma sequência de bits sem
// espaços, que deverá ser gravada byte a byte! Para montar um byte com 8 bits você pode
// utilizar union).
// Utilize uma frase diferente da que foi usada na construção da árvore!


// Estrutura da árvore de Huffman
struct arvore {
    char simbolo;
    float frequencia;
    struct arvore *esq;
    struct arvore *dir;
}; typedef struct arvore arvore;

// Estrutura da lista encadeada
struct lista {
    char palavra[50];
    float frequencia;
    struct lista *prox;
}; typedef struct lista lista;

// Estrutura do registro
struct registro {
    int simbolo;
    char palavra[50];
    float frequencia;
    char codigo[50];
    struct registro *prox;
}; typedef struct registro registro;

// Função para criar um novo nó
lista* criarNo(char *palavra) {
    lista *novo = (lista*)malloc(sizeof(lista));
    strcpy(novo->palavra, palavra);
    novo->frequencia = 1;
    novo->prox = NULL;

    return novo;
}

// Função para adicionar uma palavra à lista
void adicionarPalavra(lista **l, char *palavra) {
    lista *atual = *l;
    lista *anterior = NULL;
    int encontrada = 0;

    while (atual != NULL && !encontrada) {  // Verifica se a palavra já está na lista
        if (strcmp(atual->palavra, palavra) == 0) {
            atual->frequencia++;
            encontrada = 1;
        } 
        else {
            anterior = atual;
            atual = atual->prox;
        }
    }
    if (!encontrada) {  // Se a palavra não estiver na lista, adiciona um novo nó
        lista *novo = criarNo(palavra);

        if (anterior == NULL) {
            *l = novo;
        }
        else {
            anterior->prox = novo;
        }
    }
}

// Função para separar as palavras da frase e adicionar à lista
void separarPalavras(lista **l, char *frase) {
    char palavra[50];
    int i = 0, j = 0, k;

    while (frase[i] != '\0') {
        if (frase[i] == ' ') {
            if (j > 0) {
                palavra[j] = '\0';
                
                for (k = 0; k < j; k++) {   // Converte a palavra para minúsculas
                    palavra[k] = tolower(palavra[k]);
                }
                adicionarPalavra(l, palavra);
                j = 0;
            }
            palavra[0] = ' ';
            palavra[1] = '\0';
            adicionarPalavra(l, palavra);
        } 
        else {
            palavra[j++] = tolower(frase[i]);
        }
        i++;
    }
    if (j > 0) {
        palavra[j] = '\0';

        for (k = 0; k < j; k++) {   // Converte a palavra para minúsculas
            palavra[k] = tolower(palavra[k]);
        }
        adicionarPalavra(l, palavra);
    }
}

// Frequências das palavras
void Frequencias(lista **l) {
    lista *atual = *l;
    int soma = 0;

    while (atual != NULL) {
        soma += atual->frequencia;
        atual = atual->prox;
    }

    printf("Soma: %d\n", soma);

    // Calcula a frequência de cada palavra
    atual = *l;
    while (atual != NULL) {
        atual->frequencia = (atual->frequencia / soma) * 100;
        atual = atual->prox;
    }
}

// Função para imprimir a lista
void imprimirLista(lista *l) {
    lista *atual = l;

    printf("\nLista:\n");
    while (atual != NULL) {
        printf("Palavra: %s, Frequencia: %.2f\n", atual->palavra, atual->frequencia);
        atual = atual->prox;
    }
}

// Ordena a lista encadeada de registros

    

// Função para criar um registro
registro* criarRegistro(lista *l) {
    int simbolo = 1;
    lista *atual = l;
    registro *r = NULL;
    registro *novo = NULL;

    while (atual != NULL) {
        novo = (registro*)malloc(sizeof(registro));
        
        if (strcmp(atual->palavra, " ") == 0) {
            novo->simbolo = 0; //
        } 
        else {
            novo->simbolo = simbolo++;
        }

        strcpy(novo->palavra, atual->palavra);
        novo->frequencia = atual->frequencia;
        novo->prox = NULL;

        if (r == NULL) {
            r = novo;
        } 
        else {
            novo->prox = r;
            r = novo;
        }
        atual = atual->prox;
    }
    ordenarRegistro(&r);

    return r;
}

// Função para imprimir o registro
void imprimirRegistro(registro *r) {
    registro *atual = r;
    printf("\nRegistro:\n");
    while (atual != NULL) {
        printf("Simbolo: %d, Palavra: %s, Frequencia: %.2f\n", atual->simbolo, atual->palavra, atual->frequencia);
        atual = atual->prox;
    }
}

// Criar No
arvore* criarNoArvore(char simbolo, float frequencia) {
    arvore *novo = (arvore*)malloc(sizeof(arvore));
    novo->simbolo = simbolo;
    novo->frequencia = frequencia;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

// Função para adicionar fazer


// b) Uma lista (de registos) para armazenar: o símbolo, a palavra, a frequência e os códigos
// de Huffman. Essa lista deverá ser gravada em arquivo em disco (arquivo binário).
// Exemplo de frase para usar na construção da árvore de huffman (ignore a pontuação e
// tamanho da caixa dos caracteres!). Utilize frases com palavras repetidas!!!

