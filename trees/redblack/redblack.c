#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "redblack.h"

unsigned long int contadorRB = 0;
unsigned long int contadorRBTeste = 0;
unsigned long int contadorRBSearch = 0;

ArvoreRB* criarRB() {
    ArvoreRB *arvore = malloc(sizeof(ArvoreRB));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNoRB(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    // arvore->contadorRB->operacoes = 0;

    return arvore;
}

int vaziaRB(ArvoreRB* arvore) {
    return arvore->raiz == NULL;
}

NoRB* criarNoRB(ArvoreRB* arvore, NoRB* pai, int valor) {
    NoRB* no = malloc(sizeof(NoRB));

    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

NoRB* adicionarNoRB(ArvoreRB* arvore, NoRB* no, int valor) {
    contadorRB++;   // CONTAGEM
    contadorRBTeste++;

    if (valor > no->valor) {
        contadorRB++;   // CONTAGEM
        
        if (no->direita == arvore->nulo) {
            no->direita = criarNoRB(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNoRB(arvore, no->direita, valor);
        }
    } else {
        contadorRB++;   // CONTAGEM
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNoRB(arvore, no, valor);
            no->esquerda->cor = Vermelho;
            
            return no->esquerda;
        } else {
            return adicionarNoRB(arvore, no->esquerda, valor);
        }
    }
}

NoRB* adicionarRB(ArvoreRB* arvore, int valor) {
    // contadorRB->operacoes += 1;
    contadorRB += 1;    // CONTAGEM
    contadorRBTeste++;
    if (vaziaRB(arvore)) {
        arvore->raiz = criarNoRB(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        	
        return arvore->raiz;
    } else {
        NoRB* no = adicionarNoRB(arvore, arvore->raiz, valor);
        balancearRB(arvore, no);
        
        return no;
    }
}

NoRB* localizarRB(ArvoreRB* arvore, int valor) {
    contadorRB++;   // CONTAGEM
    if (!vaziaRB(arvore)) {
        NoRB* no = arvore->raiz;

        contadorRB++;   // CONTAGEM
        while (no != arvore->nulo) {
            contadorRBSearch++;
            contadorRB++;   // CONTAGEM
            
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
            contadorRB++;   // CONTAGEM
            // contadorRBTeste++;
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrderRB(ArvoreRB* arvore, NoRB* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        
        
        percorrerProfundidadeInOrderRB(arvore, no->esquerda,callback);
        callback(no->valor);
        percorrerProfundidadeInOrderRB(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePreOrderRB(ArvoreRB* arvore, NoRB* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        callback(no->valor);
        percorrerProfundidadePreOrderRB(arvore, no->esquerda,callback);
        percorrerProfundidadePreOrderRB(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePosOrderRB(ArvoreRB* arvore, NoRB* no, void (callback)(int)) {
    if (no != arvore->nulo) {
        percorrerProfundidadePosOrderRB(arvore, no->esquerda,callback);
        percorrerProfundidadePosOrderRB(arvore, no->direita,callback);
        callback(no->valor);
    }
}

void visitarRB(int valor){
    printf("%d ", valor);
}

void balancearRB(ArvoreRB* arvore, NoRB* no) {
    contadorRB++;   // CONTAGEM
    while (no->pai->cor == Vermelho) {
        // contadorRBTeste++;
        contadorRB++;   // CONTAGEM
        if (no->pai == no->pai->pai->esquerda) {
            NoRB *tio = no->pai->pai->direita;
            
            contadorRB++;   // CONTAGEM
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                contadorRB++;   // CONTAGEM
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerdaRB(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarDireitaRB(arvore, no->pai->pai); //Caso 3
                }
            }
        } else {
            NoRB *tio = no->pai->pai->esquerda;
            
            contadorRB++;   // CONTAGEM
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                contadorRB++;   // CONTAGEM
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireitaRB(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarEsquerdaRB(arvore, no->pai->pai); //Caso 3
                }
            }
        }
        contadorRB++;   // CONTAGEM
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerdaRB(ArvoreRB* arvore, NoRB* no) {
    NoRB* direita = no->direita;
    no->direita = direita->esquerda; 

    contadorRB++;   // CONTAGEM
    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        contadorRB++;   // CONTAGEM
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        contadorRB += 2;   // CONTAGEM
        no->pai->esquerda = direita;
    } else {
        contadorRB += 2;   // CONTAGEM
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireitaRB(ArvoreRB* arvore, NoRB* no) {
    NoRB* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    
    contadorRB++;   // CONTAGEM
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        contadorRB++;   // CONTAGEM
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        contadorRB += 2;   // CONTAGEM
        no->pai->esquerda = esquerda;
    } else {
        contadorRB += 2;   // CONTAGEM
        no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}

void exibirArvore(NoRB* no, int nivel) {
    if (no != NULL) {
        exibirArvore(no->direita, nivel + 1);

        for (int i = 0; i < nivel; i++) {
            printf("   ");
        }

        if (no->cor == Vermelho) {
            printf("|--[%d] (Vermelho)\n", no->valor);
        } else {
            printf("|--[%d] (Preto)\n", no->valor);
        }

        exibirArvore(no->esquerda, nivel + 1);
    }
}

void exibirArvoreRubroNegra(ArvoreRB* arvore) {
    printf("Árvore Rubro-Negra:\n");
    exibirArvore(arvore->raiz, 0);
}


NoRB* encontrarMinimoRB(ArvoreRB* arvore, NoRB* no) {
    contadorRB++;   // CONTAGEM
    while (no->esquerda != arvore->nulo) {
        no = no->esquerda;
        contadorRB++;   // CONTAGEM
    }
    return no;
}

void trocarNosRB(ArvoreRB* arvore, NoRB* no1, NoRB* no2) {
    contadorRB++;   // CONTAGEM
    if (no1->pai == arvore->nulo) {
        arvore->raiz = no2;
    } else if (no1 == no1->pai->esquerda) {
        contadorRB += 2;   // CONTAGEM
        no1->pai->esquerda = no2;
    } else {
        no1->pai->direita = no2;
    }
    no2->pai = no1->pai;
}

void removerRB(ArvoreRB* arvore, int valor) {
    NoRB* no = localizarRB(arvore, valor);

    contadorRB++;   // CONTAGEM
    if (no == NULL) {
        printf("Valor não encontrado na árvore.\n");
        return;
    }


    NoRB* noRemover = no;
    Cor corOriginal = noRemover->cor;
    NoRB* noSubstituto;
    
    if (no->esquerda == arvore->nulo) {
        contadorRB++;   // CONTAGEM
        noSubstituto = no->direita;
        trocarNosRB(arvore, no, no->direita);
    } else if (no->direita == arvore->nulo) {
        contadorRB += 2;   // CONTAGEM
        noSubstituto = no->esquerda;
        trocarNosRB(arvore, no, no->esquerda);
    } else {
        contadorRB += 2;   // CONTAGEM
        noRemover = encontrarMinimoRB(arvore, no->direita);
        corOriginal = noRemover->cor;
        noSubstituto = noRemover->direita;

        contadorRB++;   // CONTAGEM
        if (noRemover->pai == no) {
            noSubstituto->pai = noRemover;
        } else {
            trocarNosRB(arvore, noRemover, noRemover->direita);
            noRemover->direita = no->direita;
            noRemover->direita->pai = noRemover;
        }

        trocarNosRB(arvore, no, noRemover);
        noRemover->esquerda = no->esquerda;
        noRemover->esquerda->pai = noRemover;
        noRemover->cor = no->cor;
    }

    free(no);

    contadorRB++;   // CONTAGEM
    if (corOriginal == Preto) {
        // Rebalancear a árvore após a remoção
        contadorRB++;   // CONTAGEM
        if (noSubstituto != arvore->nulo)
            balancearRB(arvore, noSubstituto);
    }
}

#define QTD_ARVORES 10
#define QTD_ITERACOES 100

int main() {

    // Seed random de acordo com o tempo
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);

    ArvoreRB* RB[QTD_ARVORES];


    unsigned long int resultados[QTD_ARVORES][QTD_ITERACOES];
    unsigned long int valores[QTD_ARVORES][QTD_ITERACOES];

    int tmp;
    unsigned long int anteriorRB;

    // ARVORE RB - INSERÇÃO
    for (int i = 0; i < QTD_ARVORES; i++) {

        contadorRB = 0;
        contadorRBTeste = 0;
        contadorRBSearch = 0;
        RB[i] = criarRB();

        for (int j = 0; j < QTD_ITERACOES; j++) {
            tmp = rand() % 1000 + 1;
            valores[i][j] = tmp;
            anteriorRB = contadorRB;
            adicionarRB(RB[i], tmp);
            //localizarRB(RB[i], tmp);
            //printf("%i;", contadorRB - anteriorRB);
            resultados[i][j] = contadorRB - anteriorRB; // CONTADOR
        }
    }

    unsigned long int media[QTD_ITERACOES];
    unsigned long int aux;

    // cuidar com a troca de i e j
    for (int i = 0; i < QTD_ITERACOES; i++) {
        aux = 0;
        for (int j = 0; j < QTD_ARVORES; j++) {
            aux += resultados[j][i];
        }

        media[i] = (aux / QTD_ARVORES);
    }

    printf("\n\n\n\nPASSOU\n\n\n\n\n");

    for (int i = 0; i < QTD_ITERACOES; i++) {
        printf("%i;", media[i]);
    }

    printf("\n\n\n\nREMOVER\n\n\n\n\n");

    //REMOVER
    int temp;
    int randomIndex;

    for (int j = 0; j < QTD_ARVORES; j++) {     // fill array
       
        for (int i = 0; i < QTD_ITERACOES; i++) {    // shuffle array
            temp = valores[j][i];
            randomIndex = rand() % QTD_ITERACOES;
            valores[j][i] = valores[j][randomIndex];
            valores[j][randomIndex] = temp;
        }
    }
    anteriorRB = 0;

    printf("opa");
    for (int i = 0; i < QTD_ARVORES; i++) {

        contadorRB = 0;

        for (int j = 0; j < QTD_ITERACOES; j++) {
            anteriorRB = contadorRB;

            //printf("%i %i %i\n", i, j, valores[i][j]);
            removerRB(RB[i], valores[i][j]);
            printf("%i %i %i %i %i\n", i, j, valores[i][j], contadorRB, contadorRB - anteriorRB);
            resultados[i][j] = contadorRB - anteriorRB;
        }
    }

    // cuidar com a troca de i e j
    for (int i = 0; i < QTD_ITERACOES; i++) {
        aux = 0;
        for (int j = 0; j < QTD_ARVORES; j++) {
            aux += resultados[j][i];
        }

        media[i] = aux / QTD_ARVORES;
    }

    for (int i = 0; i < QTD_ITERACOES; i++) {
        printf("%i;", media[i]);
    }

    // ARVORE RB - REMOÇÃO
    
}
