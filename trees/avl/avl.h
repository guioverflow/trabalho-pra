
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
int vaziaAVL(ArvoreAVL* arvore);
NoAVL* criarNoAVL(int valor);
NoAVL* adicionarNoAVL(NoAVL* no, int valor);
int adicionarAVL(ArvoreAVL* arvore, int valor);
void balanceamentoAVLWithCount(ArvoreAVL* a, NoAVL* no);
NoAVL* encontrarMinimoAVL(NoAVL* no);
NoAVL* removeNoAVL(NoAVL *no, int valor);
NoAVL* removerAVL(ArvoreAVL* arvore, int valor);
NoAVL* localizarAVL(NoAVL* NoAVL, int valor);
void percorrerAVL(NoAVL* NoAVL, void (*callback)(int));
void visitarAVL(int valor);
int alturaAVL(NoAVL* no);
int fbAVL(NoAVL* no);

NoAVL* rseAVL(ArvoreAVL* arvore, NoAVL* no);
NoAVL* rsdAVL(ArvoreAVL* arvore, NoAVL* no);
NoAVL* rdeAVL(ArvoreAVL* arvore, NoAVL* no);
NoAVL* rddAVL(ArvoreAVL* arvore, NoAVL* no);
