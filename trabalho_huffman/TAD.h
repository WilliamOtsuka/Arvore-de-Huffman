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


// Lista encadeada ordenada
struct Lista {
    char palavra[20];
    struct Lista *prox;
}; typedef struct Lista lista;

// Registros para armazenar o símbolo, a palavra, a frequência e os códigos de Huffman
struct Registro {
    int simbolo;
    char palavra[20];
    float freq;
    char codigo[50];
    struct Registro *prox;
}; typedef struct Registro registro;  

// Estrutura da árvore de Huffman
struct Tree {
    char simbolo;
    float freq;
    struct Tree *esq, *dir;
}; typedef struct Tree tree;

struct listafolhas {
    tree *no;
    struct listafolhas *prox;
}; typedef struct listafolhas listaFolha;


// Nova Palavra
lista *novaPalavra(char palavra[20])
{
    lista *novo = (lista*)malloc(sizeof(lista));
    strcpy(novo->palavra, palavra); 
    novo->prox = NULL;

    return novo;
}

// Função para criar um registro
registro *criarRegistro(int simbolo, char palavra[20], float freq, char codigo[50]) {
    registro *reg = (registro*) malloc(sizeof(registro));
    reg->simbolo = simbolo;
    strcpy(reg->palavra, palavra);
    reg->freq = freq;
    strcpy(reg->codigo, codigo);
    reg->prox = NULL;

    return reg;
}

//Criar um no da arvore
tree *criaNo(char simbolo, float freq) {
    tree *no = (tree*) malloc(sizeof(tree));
    no->simbolo = simbolo;
    no->freq = freq;
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

// funcao pra criar uma nova folha
listaFolha *novaFolha(tree *no) {
    listaFolha *novo = (listaFolha*)malloc(sizeof(listaFolha));
    novo->no = no;
    novo->prox = NULL;

    return novo;
}


//Ordenar Lista de Registros por menor frequencia a maior
registro *ordenarRegistro(registro *reg) {
    Registro *aux, *aux2;
    char palavra[20];
    float freq;
    int simbolo;

    aux = reg;

    while(reg != NULL) {
        aux2 = reg->prox; 

        while(aux2 != NULL) {
            if(reg->freq > aux2->freq) {
                simbolo = reg->simbolo;
                strcpy(palavra, reg->palavra);
                freq = reg->freq;

                reg->simbolo = aux2->simbolo;
                strcpy(reg->palavra, aux2->palavra);
                reg->freq = aux2->freq;

                aux2->simbolo = simbolo;
                strcpy(aux2->palavra, palavra);
                aux2->freq = freq;
            }
            aux2 = aux2->prox;
        }
        reg = reg->prox;
    }

    // Imprimir a lista de registros
    reg = aux;
    aux = reg;
    // while (aux != NULL) {
    //     printf("Simb: %-4d \t Palavra:'%-4s' \t Freq: %-4.2f \t Cod: %-4s\n", aux->simbolo, aux->palavra, aux->freq, aux->codigo);
    //     aux = aux->prox;
    // }

    return reg;
}


// frequencia de cada palavra na Lista
registro *criarRegistro(lista *l, registro *reg) {
    int palavras = 0, flag = 0, i = 1, j = 0, k = 0;
    float freq;

    lista *p = l, *verif = l, *aux = l;
    registro *auxReg;

    while(aux != NULL) { // Contar o número de palavras
        palavras++;
        aux = aux->prox;
    }

    aux = p;
    freq = 0;

    while(aux != NULL) { // Enquanto aux nao for nulo
        if(stricmp(aux->palavra, p->palavra) == 0)  // Se a palavra for igual a palavra de p
            freq++;

        aux = aux->prox;
    }

    freq = freq / palavras; // Frequencia da palavra
    reg = criarRegistro(i, p->palavra, freq, ""); 
    i++;
    j++;

    auxReg = reg;
    p = p->prox;

    while (p != NULL) {
        freq = 0;
        verif = l;
        flag = 0;
        k = 0;

        while (k < j && flag == 0){
            if (stricmp(verif->palavra, p->palavra) == 0) 
                flag++;

            verif = verif->prox;
            k++;
        }

        if (flag == 0) {
            aux = p;

            while(aux != NULL) {
                if(stricmp(aux->palavra, p->palavra) == 0) 
                    freq++;

                aux = aux->prox;
            }
            freq = freq / palavras; // Frequencia da palavra
            
            auxReg->prox = criarRegistro(i, p->palavra, freq, "");
            auxReg = auxReg->prox;
            i++;
        }
        j++;
        p = p->prox;
    }

    // Imprimir a lista de registros
    // auxReg = reg;

    // while (auxReg != NULL) {
    //     printf("%d %s %.2f %s\n", auxReg->simbolo, auxReg->palavra, auxReg->freq, auxReg->codigo);
    //     auxReg = auxReg->prox;
    // }

    reg = ordenarRegistro(reg);

    return reg;
}

// Separar as palavras da frase em uma lista encadeada
lista *separarPalavras(char frase[], lista *l) 
{
    int i = 0, j = 0, len = strlen(frase);
    char palavra[20];

    lista *aux;

    while(i <= len) {
        if(frase[i] != ' ') { // Se não for um espaço
            palavra[j] = frase[i]; // Adiciona a letra na palavra
            j++;
        } 
        else { // Se for um espaço
            palavra[j] = '\0'; // Adiciona o caractere de fim de string
        }

        if(frase[i] == '\0' || frase[i] == ' ') {
            if(l == NULL)  // Se a lista estiver vazia    
                l = novaPalavra(palavra); // Cria uma nova palavra na lista
            
            else { // Se não
                aux = l; // Cria um auxiliar para percorrer a lista
                
                while(aux->prox != NULL)  // Enquanto não chegar no final da lista
                    aux = aux->prox; // Vai para o próximo nó
                
                aux->prox = novaPalavra(" ");

                aux = aux->prox;
                aux->prox = novaPalavra(palavra); // Adiciona a nova palavra no final da lista  
            }
            j = 0;
        }
        i++;
    }
    // Imprimir a lista de palavras
    // aux = l;

    // while (aux != NULL) {
    //     printf("%s\n", aux->palavra);
    //     aux = aux->prox;
    // }

    return l;
}

void criarFolhas(listaFolha **l, registro *reg) 
{
    listaFolha *aux, *aux2;
    registro *auxReg = reg;
    tree *no, *no2;

    while(auxReg != NULL) {
        no = criaNo(auxReg->simbolo, auxReg->freq);

        if(*l == NULL) {
            *l = novaFolha(no);
        }
        
        else {
            aux = *l;

            while(aux->prox != NULL) 
                aux = aux->prox;
            
            aux->prox = novaFolha(no);
        }
        auxReg = auxReg->prox;
    }
    // while (aux != NULL) {
    //     printf("\n%d %.2f", aux->no->simbolo, aux->no->freq);
    //     aux = aux->prox;    
    // }
}

void constroiArvore(tree **raiz, listaFolha *l)
{
    listaFolha *aux = l, *fno, *aux3;
    tree *no, *no2, *no3;
    float freq;

    while(aux->prox != NULL) {
        no = aux->no;
        no2 = aux->prox->no;

        no3 = criaNo(0, no->freq + no2->freq);
        no3->esq = no;
        no3->dir = no2;

        aux3 = l;
        while(aux3 -> prox != NULL)
            aux3 = aux3->prox;
        
      aux3 = novaFolha(no3);

      aux = aux->prox->prox;
    }

    *raiz = no3;
}

void imprimeArvore(tree *raiz) {
    if (raiz != NULL) {
        if (raiz->simbolo != 0)
            printf("%d %.2f\n", raiz->simbolo, raiz->freq);
        else
            printf("%.2f\n", raiz->freq);
        
        imprimeArvore(raiz->esq);
        imprimeArvore(raiz->dir);
    }
}


// b) Uma lista (de registos) para armazenar: o símbolo, a palavra, a frequência e os códigos
// de Huffman. Essa lista deverá ser gravada em arquivo em disco (arquivo binário).
// Exemplo de frase para usar na construção da árvore de huffman (ignore a pontuação e
// tamanho da caixa dos caracteres!). Utilize frases com palavras repetidas!!!

