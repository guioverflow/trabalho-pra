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
    struct ContadorRB* contadorRB;
} ArvoreRB;

// Estrutura criada para armazenar as contabilidades
typedef struct ContadorRB {
    unsigned long int operacoes;
} ContadorRB;

ArvoreRB* criarRB();
int vaziaRB(ArvoreRB* ArvoreRB);

NoRB* criarNoRB(ArvoreRB* ArvoreRB, NoRB* pai, int valor);
NoRB* adicionarNoRB(ArvoreRB* ArvoreRB, NoRB* NoRB, int valor);
NoRB* adicionarRB(ArvoreRB* ArvoreRB, int valor);
NoRB* localizarRB(ArvoreRB* ArvoreRB, int valor);

void percorrerProfundidadeInOrderRB(ArvoreRB* ArvoreRB, NoRB* NoRB, void (*callback)(int));
void percorrerProfundidadePreOrderRB(ArvoreRB* ArvoreRB, NoRB* NoRB, void (*callback)(int));
void percorrerProfundidadePosOrderRB(ArvoreRB* ArvoreRB, NoRB* NoRB, void (callback)(int));

void visitarRB(int valor);
void balancearRB(ArvoreRB* ArvoreRB, NoRB* NoRB);
void rotacionarEsquerdaRB(ArvoreRB* ArvoreRB, NoRB* NoRB);
void rotacionarDireitaRB(ArvoreRB* ArvoreRB, NoRB* NoRB);

void removerRB(ArvoreRB* arvore, int valor);
void balancearRemocaoRB(ArvoreRB* arvore, NoRB* no);
void trocarNosRB(ArvoreRB* arvore, NoRB* no1, NoRB* no2);
NoRB* encontrarMinimoRB(ArvoreRB* arvore, NoRB* no);
