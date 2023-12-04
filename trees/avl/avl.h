
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
// NoAVL* adicionar(ArvoreAVL* arvore, int valor);
int adicionarWithCount(ArvoreAVL* arvore, int valor, ContadorAVL* contadorAVL);
// void balanceamento(ArvoreAVL* a, NoAVL* NoAVL);
void balanceamentoAVLWithCount(ArvoreAVL* a, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* encontrarMinimo(NoAVL* no);
NoAVL *removeNoAVL(NoAVL *no, int valor);
NoAVL* remover(ArvoreAVL* arvore, int valor);
NoAVL* localizarAVL(NoAVL* NoAVL, int valor);
void percorrerAVL(NoAVL* NoAVL, void (*callback)(int));
void visitar(int valor);
int alturaAVL(NoAVL* no, ContadorAVL* contadorAVL);
int fbAVL(NoAVL* no, ContadorAVL* contadorAVL);

NoAVL* rseAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* rsdAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* rdeAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
NoAVL* rddAVL(ArvoreAVL* arvore, NoAVL* no, ContadorAVL* contadorAVL);
