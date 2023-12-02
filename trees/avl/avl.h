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