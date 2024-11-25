//O primeiro program devera ter:
// a) Um algoritmo para construcao da arvore de Huffman (utilize uma lista encadeada
// ordenada no processo de construcao da arvore). A arvore nao devera ter a palavra e sim
// um simbolo (numerico, um codigo!). Os espacos em branco da frase tambem devem ser
// considerados e tera um simbolo na arvore. A frequencia das palavras e dos espacos
// devera ser contada e armazenada na lista do item b) antes de montar a arvore.

// Estrutura da arvore de Huffman
struct tree {
    int simbolo;
    int frequencia;
    struct tree *esq, *dir, *prox;
}; typedef struct tree tree;

// Estrutura da lista encadeada
struct lista {
    char palavra[50];
    int frequencia, simbolo;
    struct lista *prox;
}; typedef struct lista lista;

// Estrutura do registro
struct registro {
    int simbolo;
    char palavra[50];
    int frequencia;
    char codigo[50];
    struct registro *prox;
}; typedef struct registro registro;

struct bits {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
}; typedef struct bits bits;

union byte {
    unsigned char byte;
    struct bits bits;
}; typedef union byte byte;

// Funcao para criar uma nova palavra na lista
lista* novaPalavra(char *palavra, int simbolo) {
    lista *novo = (lista*)malloc(sizeof(lista));

    strcpy(novo->palavra, palavra);
    novo->frequencia = 1;

    if(strcmp(palavra, " ") == 0) {
        simbolo = 0;
    } 
    novo->simbolo = simbolo;
    novo->prox = NULL;

    return novo;
}

// Aiciona uma palavra a lista
void adicionarPalavra(lista **l, char *palavra, int *simbolo) {
    lista *atual = *l, *anterior = NULL, *novo;
    int encontrada = 0;

    while(atual != NULL && !encontrada) {  // Verifica se a palavra ja esta na lista
        if(strcmp(atual->palavra, palavra) == 0) {
            atual->frequencia++;
            encontrada = 1;
        } 
        else {
            anterior = atual;
            atual = atual->prox;
        }
    }
    if(!encontrada) {  // Se a palavra nao estiver na lista, adiciona um novo no
        novo = novaPalavra(palavra, (*simbolo)++);

        if(anterior == NULL) {
            *l = novo;
        }
        else {
            anterior->prox = novo;
        }
    }
}

// Separa as palavras da frase e adicionar a lista
void separarPalavras(lista **l, char *frase) {
    char palavra[50];
    int i = 0, j = 0, k, simbolo = 1;

    while(frase[i] != '\0') {
        if(frase[i] == ' ') {
            if(j > 0) {
                palavra[j] = '\0';
                
                for (k = 0; k < j; k++) {  
                    palavra[k] = tolower(palavra[k]);
                }
                adicionarPalavra(l, palavra, &simbolo);
                j = 0;
            }
            palavra[0] = ' ';
            palavra[1] = '\0';
            adicionarPalavra(l, palavra, &simbolo);
        } 
        else {
            palavra[j++] = tolower(frase[i]);
        }
        i++;
    }
    if(j > 0) {
        palavra[j] = '\0';

        for (k = 0; k < j; k++) { 
            palavra[k] = tolower(palavra[k]);
        }
        adicionarPalavra(l, palavra, &simbolo);
    }
}

// Frequencias das palavras
// int Frequencias(lista **l) {
//     lista *atual = *l;
//     int soma = 0;

//     while(atual != NULL) {
//         soma += atual->frequencia;
//         atual = atual->prox;
//     }

//     printf("Soma: %d\n", soma);

//     return soma;
//     // Calcula a frequencia de cada palavra
//     // atual = *l;
//     // while(atual != NULL) {
//         // atual->frequencia = (atual->frequencia / soma) * 100;
//     //     atual = atual->prox;
//     // }
// }

// Funcao para imprimir a lista
void imprimirLista(lista *l) {
    lista *atual = l;

    printf("\nLista:\n");
    while(atual != NULL) {
        printf("Simbolo: %d, Palavra: %s, Frequencia: %d\n", atual->simbolo, atual->palavra, atual->frequencia);
        atual = atual->prox;
    }
}

// Criar No
tree* criarNoArvore(int simbolo, int frequencia, tree *esq, tree *dir) {
    tree *novo = (tree*)malloc(sizeof(tree));

    novo->simbolo = simbolo;
    novo->frequencia = frequencia;
    novo->esq = esq;
    novo->dir = dir;
    novo->prox = NULL;

    return novo;
}

// fazer uma lista de nos ordenada
void criaListaArvore(lista *l, tree **a) {
    lista *atual = l;
    tree *novo = NULL, *aux = NULL, *ant = NULL;

    while(atual != NULL) {
        novo = criarNoArvore(atual->simbolo, atual->frequencia, NULL, NULL);

        if(*a == NULL) {
            *a = novo;
        } 
        else {
            aux = *a;
            ant = NULL;

            while(aux != NULL && novo->frequencia > aux->frequencia) {
                ant = aux;
                aux = aux->prox;
            }

            if(ant == NULL) {
                novo->prox = *a;
                *a = novo;
            } 
            else {
                ant->prox = novo;
                novo->prox = aux;
            }
        }
        atual = atual->prox;
    }
}

// Imprime a lista de nos
void imprimiristaArvore(tree *a) {
    tree *atual = a;

    printf("\ntree:\n");
    while(atual != NULL) {
        printf("Simbolo: %d, Frequencia: %d\n", atual->simbolo, atual->frequencia);
        atual = atual->prox;
    }
}

// Cria a arvore de Huffman
void criarArvore(tree **a) {
    tree *no1, *no2, *pai, *aux, *ant;

    while(*a != NULL && (*a)->prox != NULL) {
        no1 = *a;
        no2 = no1->prox;
        *a = no2->prox;

        pai = criarNoArvore(0, no1->frequencia + no2->frequencia, no1, no2);

        aux = *a;
        ant = NULL;

        while(aux != NULL && pai->frequencia > aux->frequencia) {
            ant = aux;
            aux = aux->prox;
        }
        if(ant == NULL) {
            pai->prox = *a;
            *a = pai;
        } 
        else {
            ant->prox = pai;
            pai->prox = aux;
        }
    }
}

// c) Imprime a arvore
void imprimirArvore(tree *a, int nivel) {
    int i;

    if(a != NULL) {
        imprimirArvore(a->dir, nivel + 1);

        for (i = 0; i < nivel; i++) {
            printf("     "); 
        }

        if(a->simbolo == 0) {
            printf("0 %d\n", a->frequencia);
        } 
        else {
            printf("%d %d\n", a->simbolo, a->frequencia); 
        }
        imprimirArvore(a->esq, nivel + 1);
    }
}

// b) Uma lista (de registos) para armazenar: o simbolo, a palavra, a frequencia e os codigos
// de Huffman. Essa lista devera ser gravada em arquivo em disco (arquivo binario).
// Exemplo de frase para usar na construcao da arvore de huffman (ignore a pontuacao e
// tamanho da caixa dos caracteres!). Utilize frases com palavras repetidas!!!

// Cria novo Registro
registro* novoRegistro(int simbolo, char *palavra, int frequencia, char *codigo) {
    registro *novo = (registro*)malloc(sizeof(registro));

    novo->simbolo = simbolo;
    strcpy(novo->palavra, palavra);
    novo->frequencia = frequencia;
    strcpy(novo->codigo, codigo);
    novo->prox = NULL;

    return novo;
}

// Ordena a lista de registros por Simbolo
void ordernarRegistro(registro **r) {
    registro *atual, *aux;
    int tempSimbolo,  tempFrequencia;
    char tempPalavra[50], tempCodigo[50];

    atual = *r;
    while(atual != NULL) {
        aux = atual->prox;

        while(aux != NULL) {
            if(atual->simbolo > aux->simbolo) {
                // Troca os simbolos
                tempSimbolo = aux->simbolo;
                aux->simbolo = atual->simbolo;
                atual->simbolo = tempSimbolo;

                // Troca as palavras
                strcpy(tempPalavra, aux->palavra);
                strcpy(aux->palavra, atual->palavra);
                strcpy(atual->palavra, tempPalavra);

                // Troca as frequências
                tempFrequencia = aux->frequencia;
                aux->frequencia = atual->frequencia;
                atual->frequencia = tempFrequencia;

                // Troca os codigos
                strcpy(tempCodigo, aux->codigo);
                strcpy(aux->codigo, atual->codigo);
                strcpy(atual->codigo, tempCodigo);
            }
            aux = aux->prox;
        }
        atual = atual->prox;
    }
}

// Cria a lista de registros a partir da lista de palavras
registro* criarRegistro(lista *l) {
    lista *atual = l;
    registro *r = NULL;
    registro *novo = NULL;

    while(atual != NULL) {
        novo = novoRegistro(atual->simbolo, atual->palavra, atual->frequencia, "");
        
        if(r == NULL) {
            r = novo;
        } 
        else {
            novo->prox = r;
            r = novo;
        }
        atual = atual->prox;
    }

    ordernarRegistro(&r);

    return r;
}

// Imprime a lista de registros
void imprimirRegistro(registro *r) {
    registro *atual = r;

    printf("\nRegistro:\n");

    while(atual != NULL) {
        printf("Simbolo: %d, Palavra: %s, Frequencia: %d, Codigo: %s\n", atual->simbolo, atual->palavra, atual->frequencia, atual->codigo);
        atual = atual->prox;
    }
}

// Encontra o registro correspondente ao simbolo
registro* encontrarRegistro(registro *r, int simbolo) {
    while(r != NULL) {
        if(r->simbolo == simbolo) {
            return r;
        }
        r = r->prox;
    }
    return NULL;
}

// Gera o codigo de Huffman
void gerarCodigoHuffmanAux(tree *a, char *codigo, int nivel, registro **r) {
    registro *reg = NULL;

    if(a != NULL) {
        // Se for uma folha, armazena o codigo do simbolo
        if(a->esq == NULL && a->dir == NULL) {
            reg = encontrarRegistro(*r, a->simbolo);

            if(reg != NULL) {
                codigo[nivel] = '\0'; // Termina o codigo
                strcpy(reg->codigo, codigo);
            }
        } 
        else {
            // Recursao para filhos
            if(a->esq != NULL) {
                codigo[nivel] = '0';
                gerarCodigoHuffmanAux(a->esq, codigo, nivel + 1, r);
            }
            if(a->dir != NULL) {
                codigo[nivel] = '1';
                gerarCodigoHuffmanAux(a->dir, codigo, nivel + 1, r);
            }
        }
    }
}

// Armazena em arquivo binario
void armazenarRegistro(registro *r) {
    FILE *arq = fopen("registro.bin", "wb");
    registro *atual = r;

    while(atual != NULL) {
        fwrite(atual, sizeof(registro), 1, arq);
        atual = atual->prox;
    }
    fclose(arq);
}

// Huffman
void gerarCodigoHuffman(tree *a, registro **r) {
    char codigo[50];

    gerarCodigoHuffmanAux(a, codigo, 0, r);
    
    armazenarRegistro(*r);
    exibeArqRegistro();
}

// c) Print Arquivo Binario de registros
void exibeArqRegistro() {
    FILE *arq = fopen("registro.bin", "rb");
    registro reg;

    printf("\nArquivo Binario:\n");

    while(fread(&reg, sizeof(registro), 1, arq)) {
        printf("Simbolo: %d, Palavra: %s, Frequencia: %d, Codigo: %s\n", reg.simbolo, reg.palavra, reg.frequencia, reg.codigo);
    }
    fclose(arq);
}

// d) Codificacao de uma frase e armazenamento do resultado (uma sequência de bits sem
// espacos, que devera ser gravada byte a byte! Para montar um byte com 8 bits você pode
// utilizar union).
// Utilize uma frase diferente da que foi usada na construcao da arvore!
// Funcao auxiliar para encontrar o registro correspondente a palavra
// Funcao para encontrar o registro correspondente a palavra
registro* encontrarPalavra(char *palavra) {
    registro reg;
    registro *encontrado = NULL;
    FILE *arq = fopen("registro.bin", "rb");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de registros\n");

        return NULL;
    }

    while(fread(&reg, sizeof(registro), 1, arq)) {
        if(strcmp(reg.palavra, palavra) == 0) {
            encontrado = (registro*)malloc(sizeof(registro));
            *encontrado = reg;

            printf("Palavra: %s, Codigo: %s\n", encontrado->palavra, encontrado->codigo);

            fclose(arq);
            return encontrado;
        }
    }

    fclose(arq);
    return NULL;
}

// Codificacao de uma frase
void codificarFrase(registro *r) {
    char frase[100], palavra[50];
    FILE *arq;
    int i = 0, j = 0, k;
    byte b;
    registro *reg;
    int bitCount = 0;
    arq = fopen("frase.bin", "wb+");
 
    printf("Digite uma frase: ");
    gets(frase);

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de saida\n");
    } 
    else {
        b.byte = 0;

        while(frase[i] != '\0') {
            if(frase[i] == ' ') {
                if(j > 0) {
                    palavra[j] = '\0';
                    for (k = 0; k < j; k++) {   // Converte a palavra para minusculas
                        palavra[k] = tolower(palavra[k]);
                    }
                    reg = encontrarPalavra(palavra);
                    if(reg != NULL) {
                        for (k = 0; k < strlen(reg->codigo); k++) {
                            if(reg->codigo[k] == '1') {
                                b.byte |= (1 << (7 - bitCount));
                            }
                            bitCount++;
                            if(bitCount == 8) {
                                fwrite(&b.byte, sizeof(unsigned char), 1, arq);
                                b.byte = 0;
                                bitCount = 0;
                            }
                        }
                        free(reg);
                    }
                    j = 0;
                }
                palavra[0] = ' ';
                palavra[1] = '\0';
                reg = encontrarPalavra(palavra);
                if(reg != NULL) {
                    for (k = 0; k < strlen(reg->codigo); k++) {
                        if(reg->codigo[k] == '1') {
                            b.byte |= (1 << (7 - bitCount));
                        }
                        bitCount++;
                        if(bitCount == 8) {
                            fwrite(&b.byte, sizeof(unsigned char), 1, arq);
                            b.byte = 0;
                            bitCount = 0;
                        }
                    }
                    free(reg);
                }
            } else {
                palavra[j++] = tolower(frase[i]);
            }
            i++;
        }

        if(j > 0) {
            palavra[j] = '\0';
            for (k = 0; k < j; k++) {   // Converte a palavra para minusculas
                palavra[k] = tolower(palavra[k]);
            }
            reg = encontrarPalavra(palavra);
            if(reg != NULL) {
                for (k = 0; k < strlen(reg->codigo); k++) {
                    if(reg->codigo[k] == '1') {
                        b.byte |= (1 << (7 - bitCount));
                    }
                    bitCount++;
                    if(bitCount == 8) {
                        fwrite(&b.byte, sizeof(unsigned char), 1, arq);
                        b.byte = 0;
                        bitCount = 0;
                    }
                }
                free(reg);
            }
        }

        // Grava o ultimo byte com padding, se necessario
        if(bitCount > 0) {
            fwrite(&b.byte, sizeof(unsigned char), 1, arq);
        }

        fclose(arq);
    }
}

// Print Arquivo Binario de Frase
void exibeCodigoFrase() {
    FILE *arq = fopen("frase.bin", "rb");
    byte b;

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de saida\n");
    }
    else {
        printf("\nArquivo Binario da Frase:\n");

        while(fread(&b.byte, sizeof(unsigned char), 1, arq)) {
            printf("%d%d%d%d%d%d%d%d", b.bits.b7, b.bits.b6, b.bits.b5, b.bits.b4, b.bits.b3, b.bits.b2, b.bits.b1, b.bits.b0);
        }
        fclose(arq);
    }
}
