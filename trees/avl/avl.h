<<<<<<< HEAD

typedef struct NoAVL {
    struct NoAVL* pai;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int valor;
} NoAVL;

typedef struct arvore {
    struct NoAVL* raiz;
    struct ContadorAVL* contadorAVL;
} ArvoreAVL;

// Estrutura criada para armazenar as contabilidades
typedef struct ContadorAVL {
    int operacoes;
} ContadorAVL;

ArvoreAVL* criarAVL();
int vazia(ArvoreAVL* arvore);
NoAVL* criarNoAVL(int valor);
NoAVL* adicionarNoAVL(NoAVL* NoAVL, int valor);
NoAVL* adicionarNoAVLWithCount(NoAVL* no, int valor, ContadorAVL* contadorAVL);
NoAVL* adicionar(ArvoreAVL* arvore, int valor);
int adicionarWithCount(ArvoreAVL* arvore, int valor, ContadorAVL* contadorAVL);
// void balanceamento(ArvoreAVL* a, NoAVL* NoAVL);
void balanceamentoWithCount(ArvoreAVL* a, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* localizar(NoAVL* NoAVL, int valor);
void percorrer(NoAVL* NoAVL, void (*callback)(int));
void visitar(int valor);
int altura(NoAVL* no, ContadorAVL* contadorAVL);
int fb(NoAVL* no, ContadorAVL* contadorAVL);

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* rde(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
=======
#include <stdlib.h>
#include <stdio.h>

typedef struct NoAVL {
    struct NoAVL* pai;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int valor;
} NoAVL;

typedef struct arvore {
    struct NoAVL* raiz;
} ArvoreAVL;

ArvoreAVL* criarAVL();
int vazia(ArvoreAVL* arvore);
NoAVL* criarNoAVL(int valor);
NoAVL* adicionarNoAVL(NoAVL* NoAVL, int valor);
NoAVL* adicionar(ArvoreAVL* arvore, int valor);
void balanceamento(ArvoreAVL* a, NoAVL* NoAVL);
NoAVL* localizar(NoAVL* NoAVL, int valor);
void percorrer(NoAVL* NoAVL, void (*callback)(int));
void visitar(int valor);
int altura(NoAVL* NoAVL);
int fb(NoAVL* NoAVL);

NoAVL* rse(ArvoreAVL* arvore, NoAVL* NoAVL);
NoAVL* rsd(ArvoreAVL* arvore, NoAVL* NoAVL);
NoAVL* rde(ArvoreAVL* arvore, NoAVL* NoAVL);
NoAVL* rdd(ArvoreAVL* arvore, NoAVL* NoAVL);
>>>>>>> e6a5317d1fd026924e6d3c70542553efe7572334
