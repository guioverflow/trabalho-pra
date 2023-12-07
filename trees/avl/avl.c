#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "avl.h"

unsigned long int contadorAVL = 0;

ArvoreAVL* criarAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;

    // inicializa variavel
    arvore->contadorAVL = malloc(sizeof(ContadorAVL));
    if (arvore->contadorAVL == NULL) {
        free(arvore); // Avoid memory leak
        return NULL;
    }
    // arvore->contadorAVL->operacoes = 0;
  
    return arvore;
}

int vazia(ArvoreAVL* arvore) {
    return arvore->raiz == NULL;
}

// Sem alterações necessárias
// Nenhuma condicional
NoAVL* criarNoAVL(int valor) {
    NoAVL* no = malloc(sizeof(NoAVL));
    contadorAVL++;   // CONTAGEM
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

NoAVL* adicionarNoAVLWithCount(NoAVL* no, int valor) {
    // contadorAVL->operacoes += 1;

    contadorAVL++;   // CONTAGEM
    if (valor > no->valor) {
        // contadorAVL->operacoes += 1;
        contadorAVL++;   // CONTAGEM
        if (no->direita == NULL) {
            NoAVL* novo = criarNoAVL(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNoAVLWithCount(no->direita, valor);
        }
    } else {
        // contadorAVL->operacoes += 1;
        contadorAVL++;   // CONTAGEM
        if (no->esquerda == NULL) {
            NoAVL* novo = criarNoAVL(valor);
			novo->pai = no;
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNoAVLWithCount(no->esquerda, valor);
        }
    }
}

int inserirNoAVL(ArvoreAVL* arvore, int valor/** contadorAVL*/) {
    // contadorAVL->operacoes += 1;

    contadorAVL++;  //CONTAGEM
    if (arvore->raiz == NULL) {
        NoAVL* novo = criarNoAVL(valor);

        arvore->raiz = novo;
        // return contadorAVL->operacoes;
    }
    
    NoAVL* no = adicionarNoAVLWithCount(arvore->raiz, valor);
    balanceamentoAVLWithCount(arvore, no);
    // return contadorAVL->operacoes;
}

void balanceamentoAVLWithCount(ArvoreAVL* a, NoAVL* no) {
    // contadorAVL->operacoes += 1;

    contadorAVL++;   // CONTAGEM
    while (no != NULL) {
        // contadorAVL->operacoes += 1;

        int fator = fbAVL(no);

        // contadorAVL->operacoes += 2;
        if (fator > 1) { //arvore mais profunda a esquerda
            contadorAVL++;   // CONTAGEM
            // contadorAVL->operacoes -= 1;
            
            //rotacao a direita
            // contadorAVL->operacoes += 1;
            contadorAVL++;   // CONTAGEM
            if (fbAVL(no->esquerda) > 0) {
                rsdAVL(a, no);
            } else {
                rddAVL(a, no);
            }
        } else if (fator < -1) {
            contadorAVL += 2;   // CONTAGEM
            // contadorAVL->operacoes -= 1;
            //rotacao a esquerda
            // contadorAVL->operacoes += 1;
            contadorAVL++;   // CONTAGEM
            if (fbAVL(no->direita) < 0) {
                rseAVL(a, no);
            } else {
                rdeAVL(a, no);
            }
        }
        // contadorAVL->operacoes -= 2;

        no = no->pai;
        contadorAVL++;   // CONTAGEM
    }
}

// implementar contador;
NoAVL* encontrarMinimo(NoAVL* no) {
    // contadorAVL++;   // CONTAGEM
    while (no->esquerda != NULL) {
        no = no->esquerda;
        // contadorAVL++;   // CONTAGEM
    }
    return no;
}

// implementar contador
NoAVL *removeNoAVL(NoAVL *no, int valor) {
  // Find the node and delete it
  contadorAVL++;   // CONTAGEM
  if (no == NULL)
    return no;


  if (valor < no->valor){
    contadorAVL++;   // CONTAGEM
    no->esquerda = removeNoAVL(no->esquerda, valor);
  } else if (valor > no->valor){
    contadorAVL += 2;   // CONTAGEM
    no->direita = removeNoAVL(no->direita, valor);
  } else {
    contadorAVL += 3;   // CONTAGEM
    if ((no->esquerda == NULL) || (no->direita == NULL)) {
      NoAVL *temp = no->esquerda ? no->esquerda : no->direita;
      contadorAVL++;   // CONTAGEM
      if (temp == NULL) {
        temp = no;
        no = NULL;
      } else {
        *no = *temp;
      }
      free(temp);
    } else {
      NoAVL *temp = encontrarMinimo(no->direita);

      no->valor = temp->valor;

      no->direita = removeNoAVL(no->direita, temp->valor);
    }
  }

  if (no == NULL)
    return no;

  return no;
}

// implementar contador
NoAVL* remover(ArvoreAVL* arvore, int valor){
    // contadorAVL++;   // CONTAGEM
    if (arvore == NULL || arvore->raiz == NULL) {
        return NULL;
    }
    NoAVL* noParaBalancear = removeNoAVL(arvore->raiz, valor/*  */);

    balanceamentoAVLWithCount(arvore, noParaBalancear);
    return noParaBalancear;
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
int alturaAVL(NoAVL* no){
    int esquerda = 0,direita = 0;

    // contadorAVL->operacoes += 1;
    contadorAVL++;   // CONTAGEM
    if (no->esquerda != NULL) {
        esquerda = alturaAVL(no->esquerda) + 1;
    }
    contadorAVL++;   // CONTAGEM
    // contadorAVL->operacoes += 1;
    if (no->direita != NULL) {
        direita = alturaAVL(no->direita) + 1;
    }
    
    contadorAVL++;   // CONTAGEM
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

// É utilizado
int fbAVL(NoAVL* no) {
    int esquerda = 0,direita = 0;
  
    // contadorAVL->operacoes += 1;
    // contadorAVL++;   // CONTAGEM
    if (no->esquerda != NULL) {
        esquerda = alturaAVL(no->esquerda) + 1;
    }

    // contadorAVL++;   // CONTAGEM
    // contadorAVL->operacoes += 1;
    if (no->direita != NULL) {
        direita = alturaAVL(no->direita) + 1;
    }
  
    return esquerda - direita;
}

NoAVL* rseAVL(ArvoreAVL* arvore, NoAVL* no) {
    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    // contadorAVL->operacoes += 1;
    // contadorAVL++;   // CONTAGEM
    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    // contadorAVL->operacoes += 1;
    // contadorAVL++;   // CONTAGEM
    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        // contadorAVL->operacoes += 1;
        // contadorAVL++;   // CONTAGEM
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

NoAVL* rsdAVL(ArvoreAVL* arvore, NoAVL* no) {
    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    // contadorAVL->operacoes += 1;
    // contadorAVL++;   // CONTAGEM
    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    // contadorAVL++;   // CONTAGEM
    // contadorAVL->operacoes += 1;
    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        // contadorAVL->operacoes += 1;
        // contadorAVL++;   // CONTAGEM
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

NoAVL* rdeAVL(ArvoreAVL* arvore, NoAVL* no) {
    no->direita = rsdAVL(arvore, no->direita);
    return rseAVL(arvore, no);
}

NoAVL* rddAVL(ArvoreAVL* arvore, NoAVL* no) {
    no->esquerda = rseAVL(arvore, no->esquerda);
    return rsdAVL(arvore, no);
}

#define QTD_ARVORES 10
#define QTD_ITERACOES 100

int main() {

    // Seed random de acordo com o tempo
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);

    ArvoreAVL* RB[QTD_ARVORES];


    unsigned long int resultados[QTD_ARVORES][QTD_ITERACOES];
    unsigned long int valores[QTD_ARVORES][QTD_ITERACOES];

    int tmp;
    unsigned long int anteriorAVL;

    // ARVORE RB - INSERÇÃO
    for (int i = 0; i < QTD_ARVORES; i++) {

        contadorAVL = 0;
        RB[i] = criarAVL();

        for (int j = 0; j < QTD_ITERACOES; j++) {
            tmp = rand() % 1000 + 1;
            valores[i][j] = tmp;
            anteriorAVL = contadorAVL;
            inserirNoAVL(RB[i], tmp);
            resultados[i][j] = contadorAVL - anteriorAVL; // CONTADOR
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
    anteriorAVL = 0;

    printf("opa");
    for (int i = 0; i < QTD_ARVORES; i++) {

        contadorAVL = 0;

        for (int j = 0; j < QTD_ITERACOES; j++) {
            anteriorAVL = contadorAVL;

            //printf("%i %i %i\n", i, j, valores[i][j]);
            remover(RB[i], valores[i][j]);
            printf("%i %i %i %i %i\n", i, j, valores[i][j], contadorAVL, contadorAVL - anteriorAVL);
            resultados[i][j] = contadorAVL - anteriorAVL;
        }

        for (int i = 0; i < QTD_ITERACOES; i++) {
            printf("%i;", resultados[0][i]);
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
