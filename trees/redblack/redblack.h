#include <stdlib.h>
#include <stdio.h>

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct NoRB {
    struct NoRB* pai;
    struct NoRB* esquerda;
    struct NoRB* direita;
    Cor cor;
    int valor;
} NoRB;

typedef struct ArvoreRB {
    struct NoRB* raiz;
    struct NoRB* nulo; 
} ArvoreRB;

ArvoreRB* criar();
int vazia(ArvoreRB* ArvoreRB);

NoRB* criarNoRB(ArvoreRB* ArvoreRB, NoRB* pai, int valor);
NoRB* adicionarNoRB(ArvoreRB* ArvoreRB, NoRB* NoRB, int valor);
NoRB* adicionar(ArvoreRB* ArvoreRB, int valor);
NoRB* localizar(ArvoreRB* ArvoreRB, int valor);

void percorrerProfundidadeINoRBrder(ArvoreRB* ArvoreRB, NoRB* NoRB, void (*callback)(int));
void percorrerProfundidadePreOrder(ArvoreRB* ArvoreRB, NoRB* NoRB, void (*callback)(int));
void percorrerProfundidadePosOrder(ArvoreRB* ArvoreRB, NoRB* NoRB, void (callback)(int));

void visitar(int valor);
void balancear(ArvoreRB* ArvoreRB, NoRB* NoRB);
void rotacionarEsquerda(ArvoreRB* ArvoreRB, NoRB* NoRB);
void rotacionarDireita(ArvoreRB* ArvoreRB, NoRB* NoRB);