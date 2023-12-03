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

NoAVL* adicionarNoAVL(NoAVL* no, int valor, ContadorAVL* contadorAVL) {
    contadorAVL->operacoes += 1;
    if (valor > no->valor) {
        contadorAVL->operacoes += 1;
        if (no->direita == NULL) {
            NoAVL* novo = criarNoAVL(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNoAVL(no->direita, valor, contadorAVL);
        }
    } else {
        contadorAVL->operacoes += 1;
        if (no->esquerda == NULL) {
            NoAVL* novo = criarNoAVL(valor);
			novo->pai = no;
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNoAVL(no->esquerda, valor, contadorAVL);
        }
    }
}

int inserirNoAVL(ArvoreAVL* arvore, int valor, ContadorAVL* contadorAVL) {
    contadorAVL->operacoes += 1;

    if (arvore->raiz == NULL) {
        NoAVL* novo = criarNoAVL(valor);

        arvore->raiz = novo;
        return contadorAVL->operacoes;
    }
    
    NoAVL* no = adicionarNoAVL(arvore->raiz, valor, contadorAVL);
    balanceamentoAVL(arvore, no, contadorAVL);
    return contadorAVL->operacoes;
}

void balanceamentoAVL(ArvoreAVL* a, NoAVL* no, ContadorAVL* contadorAVL) {
    contadorAVL->operacoes += 1;
    while (no != NULL) {
        contadorAVL->operacoes += 1;

        int fator = fbAVL(no, contadorAVL);

        contadorAVL->operacoes += 2;
        if (fator > 1) { //arvore mais profunda a esquerda
            contadorAVL->operacoes -= 1;
            
            //rotacao a direita
            contadorAVL->operacoes += 1;
            if (fbAVL(no->esquerda, contadorAVL) > 0) {
                rsdAVL(a, no, contadorAVL);
            } else {
                rddAVL(a, no, contadorAVL);
            }
        } else if (fator < -1) {
            contadorAVL->operacoes -= 1;
            //rotacao a esquerda
            contadorAVL->operacoes += 1;
            if (fbAVL(no->direita, contadorAVL) < 0) {
                rseAVL(a, no, contadorAVL);
            } else {
                rdeAVL(a, no, contadorAVL);
            }
        }
        contadorAVL->operacoes -= 2;

        no = no->pai;
    }
}


// Não é utilizado nas adições, portanto não precisa de contabilidade
NoAVL* localizarAVL(NoAVL* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizarAVL(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizarAVL(no->direita, valor);
            }
        }
    }

    return NULL;
}

// Não é utilizado nas adições, portanto não precisa de contabilidade
void percorrerAVL(NoAVL* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrerAVL(no->esquerda,callback);
        callback(no->valor);
        percorrerAVL(no->direita,callback);
    }
}

// Não é utilizado nas adições, portanto não precisa de contabilidade
void visitarAVL(int valor){
    printf("%d ", valor);
}

// É utilizado
int alturaAVL(NoAVL* no, ContadorAVL* contadorAVL){
    int esquerda = 0,direita = 0;

    contadorAVL->operacoes += 1;
    if (no->esquerda != NULL) {
        esquerda = alturaAVL(no->esquerda, contadorAVL) + 1;
    }

    contadorAVL->operacoes += 1;
    if (no->direita != NULL) {
        direita = alturaAVL(no->direita, contadorAVL) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

// É utilizado
int fbAVL(NoAVL* no, ContadorAVL* contadorAVL) {
    int esquerda = 0,direita = 0;
  
    contadorAVL->operacoes += 1;
    if (no->esquerda != NULL) {
        esquerda = alturaAVL(no->esquerda, contadorAVL) + 1;
    }

    contadorAVL->operacoes += 1;
    if (no->direita != NULL) {
        direita = alturaAVL(no->direita, contadorAVL) + 1;
    }
  
    return esquerda - direita;
}

NoAVL* rseAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
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

NoAVL* rsdAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
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

NoAVL* rdeAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
    no->direita = rsdAVL(arvore, no->direita, contadorAVL);
    return rseAVL(arvore, no, contadorAVL);
}

NoAVL* rddAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL) {
    no->esquerda = rseAVL(arvore, no->esquerda, contadorAVL);
    return rsdAVL(arvore, no, contadorAVL);
}
