//a) Um algoritmo que abra os arquivos binario (registros) e o arquivo da frase codificada,
// faca a decodificacao da frase e mostre na tela. Para fazer a decodificacao monte uma
// arvore binaria a partir dos codigos de huffman armazenados da tabela (arquivo binario),
// e com varreduras na arvore seguindo as sequencias binarias voce chegara nas folhas,
// onde estao os codigos das palavras. Va no arquivo, busque o codigo e pegue a palavra ou
// o espaco em branco, concatene em uma string e no final voce tera a frase decodificada.
// Apos ter a frase decodificada mostre na tela.

// Estrutura de um no da arvore
struct tree {
    int simbolo;         
    struct tree *esq, *dir;
};
typedef struct tree tree;

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
};
typedef struct bits bits;

union byte {
    unsigned char byte;
    struct bits bits;
};
typedef union byte byte;

tree *criarNoArvore(int simbolo, tree *esq, tree *dir) {
    tree *novo = (tree *) malloc(sizeof(tree));
    novo->simbolo = simbolo;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

void ArvoreBinaria(tree **a) {
    FILE *arqReg = fopen("registro.bin", "rb");
    char codigo[50] = "";
    registro reg;
    tree *atual, *novo;
    byte b;
    int i;

    if(arqReg == NULL) {
        printf("Erro ao abrir o arquivo de Registros.\n");
    }
    else {

        // Inicializa a arvore
        *a = criarNoArvore(-1, NULL, NULL);

        // Arvore a partir dos codigos armazenados
        while(fread(&reg, sizeof(registro), 1, arqReg)) { 
            atual = *a;
            printf("Codigo: %s\n", reg.codigo);
            for (i = 0; i < strlen(reg.codigo); i++) {
                if(reg.codigo[i] == '0') {
                    if(atual->esq == NULL) {
                        novo = criarNoArvore(-1, NULL, NULL);
                        atual->esq = novo;
                    }
                    atual = atual->esq;
                } else {
                    if(atual->dir == NULL) {
                        novo = criarNoArvore(-1, NULL, NULL);
                        atual->dir = novo;
                    }
                    atual = atual->dir;
                }
            }
            atual->simbolo = reg.simbolo;
        }
        fclose(arqReg);
    }
}

// Funcao para imprimir a arvore
void imprimirArvore(tree *a, int nivel) {
    int i;

    if(a != NULL) {
        imprimirArvore(a->dir, nivel + 1);

        for (i = 0; i < nivel; i++) {
            printf("     ");
        }

        printf("%d\n", a->simbolo);

        imprimirArvore(a->esq, nivel + 1);
    }
}

registro encontrarSimbolo(int simbolo) {
    FILE *arq = fopen("registro.bin", "rb");
    registro reg;

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de registros\n");
        return reg;
    }

    while(fread(&reg, sizeof(registro), 1, arq)) {
        if(reg.simbolo == simbolo) {
            fclose(arq);
            return reg;
        }
    }

    fclose(arq);
    return reg;
}

// Funcao para decodificar a frase
void decodificarFrase(tree *a) {
    FILE *arq = fopen("frase.bin", "rb");
    byte b;
    tree *atual = a;
    registro reg;
    int i;

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo de frase.\n");
    }
    else {
        // Percorre a arvore 
        while(fread(&b.byte, sizeof(unsigned char), 1, arq)) {
            for (i = 0; i < 8; i++) {
                if(b.bits.b7 == 0) {
                    atual = atual->esq;
                } else {
                    atual = atual->dir;
                }

                if(atual->esq == NULL && atual->dir == NULL) {
                    reg = encontrarSimbolo(atual->simbolo);
                    printf("%s ", reg.palavra);
                    atual = a;
                }

                b.byte <<= 1;
            }
        }
    }

}
