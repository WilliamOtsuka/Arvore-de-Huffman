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

// struct Tree {
//     char simbolo;
//     int freq;
//     struct tree *esq, *dir;
// }; typedef struct Tree tree;

// //Criar um no da arvore
// tree *criaNo(char simbolo, int freq) {
//     tree *no = (tree*) malloc(sizeof(tree));
//     no->simbolo = simbolo;
//     no->freq = freq;
//     no->esq = NULL;
//     no->dir = NULL;

//     return no;
// }

// Lista encadeada ordenada
struct Lista {
    char palavra[20];
    struct Lista *prox;
}; typedef struct Lista *lista;

// Registros para armazenar o símbolo, a palavra, a frequência e os códigos de Huffman
struct Registro {
    int simbolo;
    char palavra[20];
    float freq;
    char codigo[50];
    struct Registro *prox;
}; typedef struct Registro *reg;  

// Nova Palavra
lista novaPalavra(char palavra[20])
{
    lista novo = (lista)malloc(sizeof(Lista));
    strcpy(novo->palavra, palavra); 
    novo->prox = NULL;

    return novo;
}

// Função para criar um registro
reg criarRegistro(int simbolo, char palavra[20], float freq, char codigo[50]) {
    reg registro = (reg) malloc(sizeof(Registro));
    registro->simbolo = simbolo;
    strcpy(registro->palavra, palavra);
    registro->freq = freq;
    strcpy(registro->codigo, codigo);
    registro->prox = NULL;

    return registro;
}


//Ordenar Lista de Registros por menor frequencia a maior
void ordenarRegistro(Registro **reg) {
    Registro *aux, *aux2;
    char palavra[20];
    float freq;
    int simbolo;

    aux = *reg;

    while((*reg) != NULL) {
        aux2 = (*reg)->prox; 

        while(aux2 != NULL) {
            if((*reg)->freq > aux2->freq) {
                simbolo = (*reg)->simbolo;
                strcpy(palavra, (*reg)->palavra);
                freq = (*reg)->freq;

                (*reg)->simbolo = aux2->simbolo;
                strcpy((*reg)->palavra, aux2->palavra);
                (*reg)->freq = aux2->freq;

                aux2->simbolo = simbolo;
                strcpy(aux2->palavra, palavra);
                aux2->freq = freq;
            }
            aux2 = aux2->prox;
        }
        (*reg) = (*reg)->prox;
    }

    // Imprimir a lista de registros
    *reg = aux;
    aux = *reg;
    while (aux != NULL) {
        printf("%d %s %.2f %s\n", aux->simbolo, aux->palavra, aux->freq, aux->codigo);
        aux = aux->prox;
    }
}


// frequencia de cada palavra na Lista
void frequencia(Lista *lista, Registro **reg) {
    int palavras = 0, flag = 0, i = 1, j = 0, k = 0;
    float freq;

    Lista *p = lista, *verif = lista, *aux = lista;
    Registro *auxReg;

    while(aux != NULL) { // Contar o número de palavras
        palavras++;
        aux = aux->prox;
    }

    aux = p;
    freq = 0;

    while(aux != NULL) { // Enquanto aux nao for nulo
        if(strcmp(aux->palavra, p->palavra) == 0)  // Se a palavra for igual a palavra de p
            freq++;

        aux = aux->prox;
    }

    freq = freq / palavras; // Frequencia da palavra
    *reg = criarRegistro(i, p->palavra, freq, ""); 
    i++;
    j++;

    auxReg = *reg;
    p = p->prox;

    while (p != NULL) {
        freq = 0;
        verif = lista;
        flag = 0;
        k = 0;

        while (k < j && flag == 0){
            if (strcmp(verif->palavra, p->palavra) == 0) 
                flag++;

            verif = verif->prox;
            k++;
        }

        if (flag == 0) {
            aux = p;

            while(aux != NULL) {
                if(strcmp(aux->palavra, p->palavra) == 0) 
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
    // auxReg = *reg;

    // while (auxReg != NULL) {
    //     printf("%d %s %.2f %s\n", auxReg->simbolo, auxReg->palavra, auxReg->freq, auxReg->codigo);
    //     auxReg = auxReg->prox;
    // }

    ordenarRegistro(&(*reg));
}

// Separar as palavras da frase em uma lista encadeada
void separarPalavras(char frase[], Lista **lista) 
{
    int i = 0, j = 0, len = strlen(frase);
    char palavra[20];

    Lista *aux;

    while(i <= len) {
        if(frase[i] != ' ') { // Se não for um espaço
            palavra[j] = frase[i]; // Adiciona a letra na palavra
            j++;
        } 
        else // Se for um espaço
            palavra[j] = '\0'; // Adiciona o caractere de fim de string

        if(frase[i] == '\0' || frase[i] == ' ') {
            if(*lista == NULL)  // Se a lista estiver vazia    
                *lista = novaPalavra(palavra); // Cria uma nova palavra
            
            else { // Se não
                aux = *lista; // Cria um auxiliar para percorrer a lista
                
                while(aux->prox != NULL)  // Enquanto não chegar no final da lista
                    aux = aux->prox; // Vai para o próximo nó
                
                aux->prox = novaPalavra(palavra); // Adiciona a nova palavra no final da lista  
            }
            j = 0;
        }
        i++;
    }
    // Imprimir a lista de palavras
    aux = *lista;

    while (aux != NULL) {
        printf("%s\n", aux->palavra);
        aux = aux->prox;
    }
}

// b) Uma lista (de registos) para armazenar: o símbolo, a palavra, a frequência e os códigos
// de Huffman. Essa lista deverá ser gravada em arquivo em disco (arquivo binário).
// Exemplo de frase para usar na construção da árvore de huffman (ignore a pontuação e
// tamanho da caixa dos caracteres!). Utilize frases com palavras repetidas!!!
