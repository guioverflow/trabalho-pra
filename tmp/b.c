#include <stdio.h>
#include <stdlib.h>


typedef struct noB {
    int total; // o que seria o total?
    int* chaves;
    struct noB** filhos;
    struct noB* pai; 
} NoB;

typedef struct arvoreB {
  NoB* raiz;
  int ordem;
} ArvoreB;

ArvoreB* criaArvoreB(int);
NoB* criaNoB(ArvoreB*);
void percorreArvoreB(NoB*);
int pesquisaBinariaB(NoB*, int);
int localizaChaveB(ArvoreB*, int);
NoB* localizaNoB(ArvoreB*, int);
void adicionaChaveNoB(NoB*, NoB*, int);
int transbordoB(ArvoreB*,NoB*);
NoB* divideNoB(ArvoreB*, NoB*);
void adicionaChaveRecursivoB(ArvoreB*, NoB*, NoB*, int);
void adicionaChaveB(ArvoreB*, int);

void delete_internal_node(ArvoreB* arvore, NoB* x, int k, int i);
void delete_sibling(ArvoreB* arvore, NoB* x, int i, int j);
void delete_merge(ArvoreB* arvore, NoB* x, int i, int j);
int delete_predecessor(ArvoreB* arvore, NoB* x);
int delete_successor(ArvoreB* arvore, NoB* x);

ArvoreB* criaArvoreB(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNoB(a);

    return a;
}

int contador = 0;

NoB* criaNoB(ArvoreB* arvoreB) {

    // ordem = min; max = ordem * 2
    int max = arvoreB->ordem * 2;
    NoB* noB = malloc(sizeof(NoB));

    contador += 1;
    if (noB == NULL) {
        // Tratar falha na alocação de memória, se necessário
        return NULL;
    }

    // o nó ainda não foi inserido na árvore
    // quando é inserido, assume o valor de pai
    noB->pai = NULL;
    
    // +1 por conta da possibilidade de transbordo
    noB->chaves = malloc(sizeof(int) * (max + 1));

    contador += 1;
    if (noB->chaves == NULL) {
        // Tratar falha na alocação de memória, se necessário
        free(noB);
        return NULL;
    }

    // +2 considerando a chave de transbordo e +1 por conta das laterais
    noB->filhos = malloc(sizeof(NoB) * (max + 2));

    contador += 1;
    if (noB->filhos == NULL) {
        // Tratar falha na alocação de memória, se necessário
        free(noB->chaves);
        free(noB);
        return NULL;
    }
    
    // quantidade de filhos, capacidade utilizada do nó
    noB->total = 0;

    for (int i = 0; i < max + 2; i++) {
        contador += 1;
        noB->filhos[i] = NULL;
    }
        

    return noB;
}

// Printa todos os valores que tem na árvore B
// TODO: Verificar a ordem que esses valores são imprimidos e registrar aqui
void percorreArvoreB(NoB* noB) {
    if (noB != NULL) {
        for (int i = 0; i < noB->total; i++){
            percorreArvoreB(noB->filhos[i]); //visita o filho a esquerda
            
            printf("%d ",noB->chaves[i]);
        }

        percorreArvoreB(noB->filhos[noB->total]); //visita ultimo filho (direita)
    }
}

// Algoritmo de pesquisa na página (nó)
// Se a chave não é encontrada, retorna 0?
// Se é encontrada, retorna a posição da chave?
int pesquisaBinariaB(NoB* noB, int chave) {
    printf("Sera NULL");
    contador += 1;
    if (noB == NULL) {
        printf("ENTROU");
        // Tratar falha na alocação de memória, se necessário
        free(noB->chaves);

        printf("ENTROU 2");
        free(noB);

        printf("ENTROU 3");
        return -1;
    }
    printf("Sera nao e");

    printf("Pesquisa Binaria 1\n");

    printf("1\n");
    int inicio = 0;

    printf("2\n");
    printf("noB->total: %i", noB->total);
    int fim = noB->total - 1;

    printf("3\n");
    int meio;		
    
    printf("Pesquisa Binaria 2\n");
    contador += 1;
    while (inicio <= fim) {	
        contador++;
        
        meio = (inicio + fim) / 2;
        
        printf("Pesquisa Binaria 3\n");
        contador += 2;
        if (noB->chaves[meio] == chave) {
            contador -= 1;
		    return meio; //encontrou	
        } else if (noB->chaves[meio] > chave) {
            fim	= meio - 1;	
        } else {
            inicio = meio + 1;
        }

        contador += 1;
        
    }

    printf("Pesquisa Binaria 4\n");

    return inicio; //não encontrou	
}

// Algoritmo de pesquisa na árvore, utiliza a pesquisa binária na página
int localizaChaveB(ArvoreB* arvoreB, int chave) {	
    NoB *noB = arvoreB->raiz;
    
    contador += 1;
    while (noB != NULL) {
        

        int i = pesquisaBinariaB(noB, chave);


        // i < noB->total verifica se a posição da chave condiz com a quantidade de filhos
        contador += 1;
        if (i < noB->total && noB->chaves[i] == chave) {
            return 1; //encontrou
        } else {
            // verificar essa parte
            noB = noB->filhos[i];
        }

        contador += 1;
    }

    return 0; //não encontrou	
}

NoB* localizaNoB(ArvoreB* arvoreB, int chave) {	
    NoB *noB = arvoreB->raiz;
    
    contador += 1;
    while (noB != NULL) {

        int i = pesquisaBinariaB(noB, chave);

        contador += 1;
        if (noB->filhos[i] == NULL)
            return noB; //encontrou nó
        else
            noB = noB->filhos[i];

        contador += 1;
    }

    return NULL; //não encontrou nenhum nó
}

void adicionaChaveNoB(NoB* noB, NoB* novo, int chave) {
    printf("1\n");
    int i = pesquisaBinariaB(noB, chave);
    

    printf("2\n");
    contador += 1;
    for (int j = noB->total - 1; j >= i; j--) {
        noB->chaves[j + 1] = noB->chaves[j];
        noB->filhos[j + 2] = noB->filhos[j + 1];

        contador += 1;
    }
    
    printf("3\n");
    noB->chaves[i] = chave;
    noB->filhos[i + 1] = novo;

    printf("4\n");
    noB->total++;
}

int transbordoB(ArvoreB* arvoreB, NoB* noB) {
    contador += 1;
    return noB->total > arvoreB->ordem * 2;
}

NoB* divideNoB(ArvoreB* arvoreB, NoB* noB) {
    int meio = noB->total / 2;
    NoB* novo = criaNoB(arvoreB);
    novo->pai = noB->pai;

    contador += 1;
    for (int i = meio + 1; i < noB->total; i++) {
        novo->filhos[novo->total] = noB->filhos[i];
        novo->chaves[novo->total] = noB->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        
        novo->total++;

        contador += 1;
    }

    novo->filhos[novo->total] = noB->filhos[noB->total];

    contador += 1;
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
    noB->total = meio;
    return novo;
}

void adicionaChaveRecursivoB(ArvoreB* arvoreB, NoB* noB, NoB* novo, int chave) {
    contador += 1;
    
    adicionaChaveNoB(noB, novo, chave);
    
    contador += 1;
    if (transbordoB(arvoreB, noB)) {
        int promovido = noB->chaves[arvoreB->ordem]; 
        NoB* novo = divideNoB(arvoreB, noB);

        contador += 1;
        if (noB->pai == NULL) {
            
            NoB* pai = criaNoB(arvoreB);            
            pai->filhos[0] = noB;
            adicionaChaveNoB(pai, novo, promovido);
            
            noB->pai = pai;
            novo->pai = pai;
            arvoreB->raiz = pai;
        } else
            adicionaChaveRecursivoB(arvoreB, noB->pai, novo, promovido);
    }
}

void adicionaChaveB(ArvoreB* arvoreB, int chave) {
    contador += 1;

    NoB* noB = localizaNoB(arvoreB, chave);

    adicionaChaveRecursivoB(arvoreB, noB, NULL, chave);
}

// https://github.com/msambol/dsa/blob/master/trees/b_tree.py

void delete(ArvoreB* arvore, NoB* x, int k) {
    // t is the minimum number of filhos that a non-root node can have is
    // ordem
    int t = arvore->ordem;
    int i = 0;

    while (i < x->total && k > x->chaves[i]) {
        i++;
    }
    printf("%i ", i);
    if (x->filhos[0] == NULL) {
        printf("Entrou\n");
        if (i < x->total && x->chaves[i] == k) {
            for (int j = i; j < x->total - 1; j++) {
                x->chaves[j] = x->chaves[j + 1];
            }
            x->total--;
        }
        return;
    }
    printf("Passou\n");
    if (i < x->total && x->chaves[i] == k) {
        delete_internal_node(arvore, x, k, i);
    } else if (x->filhos[i]->total >= t) {
        delete(arvore, x->filhos[i], k);
    } else {
        if (i != 0 && i + 2 < x->total) {
            if (x->filhos[i - 1]->total >= t) {
                delete_sibling(arvore, x, i, i - 1);
            } else if (x->filhos[i + 1]->total >= t) {
                delete_sibling(arvore, x, i, i + 1);
            } else {
                delete_merge(arvore, x, i, i + 1);
            }
        } else if (i == 0) {
            if (x->filhos[i + 1]->total >= t) {
                delete_sibling(arvore, x, i, i + 1);
            } else {
                delete_merge(arvore, x, i, i + 1);
            }
        } else if (i + 1 == x->total) {
            if (x->filhos[i - 1]->total >= t) {
                delete_sibling(arvore, x, i, i - 1);
            } else {
                delete_merge(arvore, x, i, i - 1);
            }
        }
        delete(arvore, x->filhos[i], k);
    }
}

void delete_internal_node(ArvoreB* arvore, NoB* x, int k, int i) {
    int t = arvore->ordem;
    if (x->filhos[0] == NULL) {
        if (x->chaves[i] == k) {
            for (int j = i; j < x->total - 1; j++) {
                x->chaves[j] = x->chaves[j + 1];
            }
            x->total--;
        }
        return;
    }

    if (x->filhos[i]->total >= t) {
        x->chaves[i] = delete_predecessor(arvore, x->filhos[i]);
    } else if (x->filhos[i + 1]->total >= t) {
        x->chaves[i] = delete_successor(arvore, x->filhos[i + 1]);
    } else {
        delete_merge(arvore, x, i, i + 1);
        delete_internal_node(arvore, x->filhos[i], k, t - 1);
    }
}

int delete_predecessor(ArvoreB* arvore, NoB* x) {
    if (x->filhos[0] == NULL) {
        return x->chaves[--x->total];
    }

    int n = x->total - 1;
    if (x->filhos[n]->total >= arvore->ordem) {
        delete_sibling(arvore, x, n + 1, n);
    } else {
        delete_merge(arvore, x, n, n + 1);
    }
    return delete_predecessor(arvore, x->filhos[n]);
}

int delete_successor(ArvoreB* arvore, NoB* x) {
    if (x->filhos[0] == NULL) {
        return x->chaves[0];
    }

    if (x->filhos[1]->total >= arvore->ordem) {
        delete_sibling(arvore, x, 0, 1);
    } else {
        delete_merge(arvore, x, 0, 1);
    }
    return delete_successor(arvore, x->filhos[0]);
}

void delete_merge(ArvoreB* arvore, NoB* x, int i, int j) {
    NoB* cnode = x->filhos[i];
    NoB* new_node = NULL;

    if (j > i) {
        NoB* rsnode = x->filhos[j];
        cnode->chaves[cnode->total++] = x->chaves[i];
        for (int k = 0; k < rsnode->total; k++) {
            cnode->chaves[cnode->total++] = rsnode->chaves[k];
            if (rsnode->filhos[k] != NULL) {
                cnode->filhos[cnode->total - 1] = rsnode->filhos[k];
            }
        }
        if (rsnode->filhos[rsnode->total] != NULL) {
            cnode->filhos[cnode->total] = rsnode->filhos[rsnode->total];
        }
        NoB* new_node = cnode;
        for (int k = i; k < x->total - 1; k++) {
            x->chaves[k] = x->chaves[k + 1];
            x->filhos[k + 1] = x->filhos[k + 2];
        }
        free(rsnode);
        x->total--;
    } else {
        NoB* lsnode = x->filhos[j];
        lsnode->chaves[lsnode->total++] = x->chaves[j];
        for (int k = 0; k < cnode->total; k++) {
            lsnode->chaves[lsnode->total++] = cnode->chaves[k];
            if (cnode->filhos[k] != NULL) {
                lsnode->filhos[lsnode->total - 1] = cnode->filhos[k];
            }
        }
        if (cnode->filhos[cnode->total] != NULL) {
            lsnode->filhos[lsnode->total] = cnode->filhos[cnode->total];
        }
        NoB* new_node = lsnode;
        for (int k = j; k < x->total - 1; k++) {
            x->chaves[k] = x->chaves[k + 1];
            x->filhos[k + 1] = x->filhos[k + 2];
        }
        free(cnode);
        x->total--;
    }

    if (x == arvore->raiz && x->total == 0) {
        arvore->raiz = new_node;
    }
}

void delete_sibling(ArvoreB* arvore, NoB* x, int i, int j) {
    NoB* cnode = x->filhos[i];
    if (i < j) {
        NoB* rsnode = x->filhos[j];
        cnode->chaves[cnode->total++] = x->chaves[i];
        x->chaves[i] = rsnode->chaves[0];
        if (rsnode->filhos[0] != NULL) {
            cnode->filhos[cnode->total] = rsnode->filhos[0];
            rsnode->filhos[0] = NULL;
        }
        for (int k = 0; k < rsnode->total - 1; k++) {
            rsnode->chaves[k] = rsnode->chaves[k + 1];
            rsnode->filhos[k] = rsnode->filhos[k + 1];
        }
        rsnode->filhos[rsnode->total - 1] = rsnode->filhos[rsnode->total];
        rsnode->filhos[rsnode->total] = NULL;
        rsnode->total--;
    } else {
        NoB* lsnode = x->filhos[j];
        for (int k = cnode->total; k > 0; k--) {
            cnode->chaves[k] = cnode->chaves[k - 1];
            cnode->filhos[k + 1] = cnode->filhos[k];
        }
        cnode->filhos[1] = cnode->filhos[0];
        cnode->chaves[0] = x->chaves[j - 1];
        x->chaves[j - 1] = lsnode->chaves[lsnode->total - 1];
        if (lsnode->filhos[lsnode->total] != NULL) {
            cnode->filhos[0] = lsnode->filhos[lsnode->total];
            lsnode->filhos[lsnode->total] = NULL;
        } else {
            cnode->filhos[0] = NULL;
        }
        lsnode->total--;
    }
}

#define QTD_ARVORES 10

int main() {
    ArvoreB* B[QTD_ARVORES];

    for (int i = 0; i < QTD_ARVORES; i++) {

        contador = 0;
        B[i] = criaArvoreB(2);

        for (int j = 0; j < 100; j++) {
            printf("%i;", contador);
            adicionaChaveB(B[i], 12);
        }

        printf("\n\n\n\n\n");
    }
        
    
    contador = 0;

    adicionaChaveB(B, 12);
    adicionaChaveB(B, 3);
    adicionaChaveB(B, 5);
    adicionaChaveB(B, 7);
    adicionaChaveB(B, 15);
    adicionaChaveB(B, 99);
    adicionaChaveB(B, 1);

    percorreArvoreB(B->raiz);

    printf("\nNumero de operacoes: %d\n", contador);
    printf("\n--- Case 1: DELETED 3 ---\n");
    delete(B, B->raiz, 3);

    percorreArvoreB(B->raiz);

    printf("\n--- Case 2a: DELETED 7 ---\n");
    delete(B, B->raiz, 7);
    percorreArvoreB(B->raiz);

    printf("\n--- Case 2b: DELETED 1 ---\n");
    delete(B, B->raiz, 1);
    percorreArvoreB(B->raiz);

    printf("\n--- Case 2c: DELETED 5 ---\n");
    delete(B, B->raiz, 5);
    percorreArvoreB(B->raiz);

    printf("\n--- Case 3b: DELETED 17 ---\n");
    delete(B, B->raiz, 17);
    percorreArvoreB(B->raiz);

    printf("\n--- Case 3a: DELETED 12 ---\n");
    delete(B, B->raiz, 12);
    percorreArvoreB(B->raiz);

    printf("Antes");
    adicionaChaveB(B, 7);
    printf("Meio");
    percorreArvoreB(B->raiz);
    printf("Depois");

    return 0;
}