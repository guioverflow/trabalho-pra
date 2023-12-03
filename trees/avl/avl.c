<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"


ArvoreAVL* criarAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;

    // inicializa variavel
    arvore->contadorAVL = malloc(sizeof(ContadorAVL));
    if (arvore->contadorAVL == NULL) {
        free(arvore); // Avoid memory leak
        return NULL;
    }
    arvore->contadorAVL->operacoes = 0;
  
    return arvore;
}

int vazia(ArvoreAVL* arvore) {
    return arvore->raiz == NULL;
}

// Sem alterações necessárias
// Nenhuma condicional
NoAVL* criarNoAVL(int valor) {
    NoAVL* no = malloc(sizeof(NoAVL));
    if (no == NULL) {
        printf("Falha na alocação de memória.\n");
        return NULL; // Return early if memory allocation fails
    }
    no->valor = valor;
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAVL* adicionarNoAVL(NoAVL* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            NoAVL* novo = criarNoAVL(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNoAVL(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            NoAVL* novo = criarNoAVL(valor);
			novo->pai = no;
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNoAVL(no->esquerda, valor);
        }
    }
}

NoAVL* adicionarNoAVLWithCount(NoAVL* no, int valor, ContadorAVL* contadorAVL) {
    contadorAVL->operacoes += 1;
    if (valor > no->valor) {
        contadorAVL->operacoes += 1;
        if (no->direita == NULL) {
            NoAVL* novo = criarNoAVL(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNoAVLWithCount(no->direita, valor, contadorAVL);
        }
    } else {
        contadorAVL->operacoes += 1;
        if (no->esquerda == NULL) {
            NoAVL* novo = criarNoAVL(valor);
			novo->pai = no;
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNoAVLWithCount(no->esquerda, valor, contadorAVL);
        }
    }
}

/*
NoAVL* adicionar(ArvoreAVL* arvore, int valor) {
    if (arvore->raiz == NULL) {
        NoAVL* novo = criarNoAVL(valor);
        arvore->raiz = novo;
			
        return novo;
    } else {
        NoAVL* no = adicionarNoAVL(arvore->raiz, valor);
        balanceamento(arvore, no);
        return no;
    }
}
*/


int adicionarWithCount(ArvoreAVL* arvore, int valor, ContadorAVL* contadorAVL) {
    contadorAVL->operacoes += 1;

    if (arvore->raiz == NULL) {
        NoAVL* novo = criarNoAVL(valor);

        arvore->raiz = novo;
        return contadorAVL->operacoes;
    }
    
    NoAVL* no = adicionarNoAVLWithCount(arvore->raiz, valor, contadorAVL);
    balanceamentoWithCount(arvore, no, contadorAVL);
    return contadorAVL->operacoes;
}


/*
void balanceamentoWithCount(ArvoreAVL* a, NoAVL* no) {
    while (no != NULL) {
        int fator = fb(no);

        if (fator > 1) { //arvore mais profunda a esquerda
            //rotacao a direita
            if (fb(no->esquerda) > 0) {
                rsd(a, no);
            } else {
                rdd(a, no);
            }
        } else if (fator < -1) {
            //rotacao a esquerda
            if (fb(no->direita) < 0) {
                rse(a, no);
            } else {
                rde(a, no);
            }
        }

        no = no->pai;
    }
}
*/

void balanceamentoWithCount(ArvoreAVL* a, NoAVL* no, ContadorAVL* contadorAVL) {
    contadorAVL->operacoes += 1;
    while (no != NULL) {
        contadorAVL->operacoes += 1;

        int fator = fb(no, contadorAVL);

        contadorAVL->operacoes += 2;
        if (fator > 1) { //arvore mais profunda a esquerda
            contadorAVL->operacoes -= 1;
            
            //rotacao a direita
            contadorAVL->operacoes += 1;
            if (fb(no->esquerda, contadorAVL) > 0) {
                rsd(a, no, contadorAVL);
            } else {
                rdd(a, no, contadorAVL);
            }
        } else if (fator < -1) {
            contadorAVL->operacoes -= 1;
            //rotacao a esquerda
            contadorAVL->operacoes += 1;
            if (fb(no->direita, contadorAVL) < 0) {
                rse(a, no, contadorAVL);
            } else {
                rde(a, no, contadorAVL);
            }
        }
        contadorAVL->operacoes -= 2;

        no = no->pai;
    }
}


// Não é utilizado nas adições, portanto não precisa de contabilidade
NoAVL* localizar(NoAVL* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

// Não é utilizado nas adições, portanto não precisa de contabilidade
void percorrer(NoAVL* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

// Não é utilizado nas adições, portanto não precisa de contabilidade
void visitar(int valor){
    printf("%d ", valor);
}

// É utilizado
int altura(NoAVL* no, ContadorAVL* contadorAVL){
    int esquerda = 0,direita = 0;

    contadorAVL->operacoes += 1;
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda, contadorAVL) + 1;
    }

    contadorAVL->operacoes += 1;
    if (no->direita != NULL) {
        direita = altura(no->direita, contadorAVL) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

// É utilizado
int fb(NoAVL* no, ContadorAVL* contadorAVL) {
    int esquerda = 0,direita = 0;
  
    contadorAVL->operacoes += 1;
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda, contadorAVL) + 1;
    }

    contadorAVL->operacoes += 1;
    if (no->direita != NULL) {
        direita = altura(no->direita, contadorAVL) + 1;
    }
  
    return esquerda - direita;
}

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    contadorAVL->operacoes += 1;
    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    contadorAVL->operacoes += 1;
    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        contadorAVL->operacoes += 1;
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    contadorAVL->operacoes += 1;
    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    contadorAVL->operacoes += 1;
    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        contadorAVL->operacoes += 1;
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

NoAVL* rde(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
    no->direita = rsd(arvore, no->direita, contadorAVL);
    return rse(arvore, no, contadorAVL);
}

NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
    no->esquerda = rse(arvore, no->esquerda, contadorAVL);
    return rsd(arvore, no, contadorAVL);
}
=======
#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
} Arvore;

void balanceamento(Arvore*, No*);
int altura(No*);
int fb(No*);
No* rsd(Arvore*, No*);
No* rse(Arvore*, No*);
No* rdd(Arvore*, No*);
No* rde(Arvore*, No*);

Arvore* criarAVL() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* criarNo(int valor) {
    No* no = malloc(sizeof(No));
    no->valor = valor;
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

No* adicionarNo(No* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            printf("Adicionando %d\n",valor);
            No* novo = criarNo(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNo(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            printf("Adicionando %d\n",valor);
            No* novo = criarNo(valor);
			novo->pai = no;
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNo(no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (arvore->raiz == NULL) {
        printf("Adicionando %d\n",valor);
        No* novo = criarNo(valor);
        arvore->raiz = novo;
			
        return novo;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balanceamento(arvore, no);
        return no;
    }
}


// TODO: Adicionar retorno de contagem da quantidade de operações
// Função adaptada para retornar a quantidade de operações envolvidas em um count
int adicionarWithCount(Arvore* arvore, int valor) {
    if (arvore->raiz == NULL) {
        printf("Adicionando %d\n",valor);
        No* novo = criarNo(valor);
        arvore->raiz = novo;
			
        return novo;
    } else {
        No* no = adicionarNo(arvore->raiz, valor);
        balanceamento(arvore, no);
        return no;
    }
}

void balanceamento(Arvore* a, No* no) {
    while (no != NULL) {
        int fator = fb(no);

        if (fator > 1) { //arvore mais profunda a esquerda
            //rotacao a direita
            if (fb(no->esquerda) > 0) {
                printf("RSD(%d)\n", no->valor);
                rsd(a, no);
            } else {
                printf("RDD(%d)\n", no->valor);
                rdd(a, no);
            }
        } else if (fator < -1) {
            //rotacao a esquerda
            if (fb(no->direita) < 0) {
                printf("RSE(%d)\n", no->valor);
                rse(a, no);
            } else {
                printf("RDE(%d)\n", no->valor);
                rde(a, no);
            }
        }

        no = no->pai;
    }
}

No* localizar(No* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrer(No* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

int altura(No* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(No* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda - direita;
}

No* rse(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

No* rsd(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

/*
int main() {
    Arvore* a = criar();
    
    adicionar(a, 4);
    adicionar(a, 2);
    adicionar(a, 8);
    adicionar(a, 1);
    adicionar(a, 3);
    adicionar(a, 6);
    adicionar(a, 9);
    adicionar(a, 5);
    adicionar(a, 7);
    int i;
    for (i = 1; i <= 9; i++) {
        adicionar(a, i);
    }

    printf("Altura: %d\n", altura(a->raiz) + 1);
    printf("In-order: ");
    percorrer(a->raiz,visitar);
    printf("\n");
}
*/

>>>>>>> e6a5317d1fd026924e6d3c70542553efe7572334
