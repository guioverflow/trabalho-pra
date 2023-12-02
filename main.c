
#include <stdio.h>
#include <stdlib.h>

#include "trees/avl/avl.h"
#include "trees/b/b.h"
#include "trees/redblack/redblack.h"

/*
Trabalho final de PRA
Professor: Allan dos Santos

Alunos:
Guilherme Matheus Alves
Josué Hass Pereira
Lucas Augusto de Oliveira
Mateus Alayo Hidalgo Schulz

O objetivo deste trabalho consiste em analisar a complexidade algorítmica
das operações de adição e remoção de nós (considerando o balanceamento) em árvores AVL, rubro-negra e B.

Requisitos:

1 - No caso da árvore B, devem ser consideradas o parâmetro de ordem da árvore igual a 1, 5 e 10.
2 - A análise deve ser realizada considerando a geração de um conjunto de dados (chaves) com tamanho variando entre 1 e 10000.
3 - As chaves devem ser geradas reproduzindo um caso médio, isto é, utilizando chaves aleatórias (sugere-se o uso da função rand em C).
4 - Utilizar uma amostra de pelo menos 10 conjuntos para validade estatística, calculando a média dos resultados obtidos.

O resultado final do experimento deve ser apresentado em um relatório contendo dois gráficos
de linha (um para a operação de adição e outro para a operação de remoção),
onde o eixo X representa o tamanho dos conjuntos de dados (1 a 10000) e o eixo Y representa o esforço computacional
das operações considerando eventuais balanceamentos.

Cada gráfico deve apresentar 5 linhas, as quais representam as respectivas operações
para cada estrutura de dados avaliada (árvore AVL, rubro-negra e as três variações da árvore B).
*/


// Requisito 2 - Conjunto de dados entre 1 e 10000
#define TAM_CONJUNTO 100


// Requisito 4 - Amostra de 10 conjuntos
#define NUM_CONJUNTOS 10


int analiseArvoreAVL() {
    ArvoreAVL* arvoreAVL[NUM_CONJUNTOS];

    for (int i = 0; i < NUM_CONJUNTOS; i++)
        arvoreAVL[i] = criarAVL();

    

    
}

int analiseArvoreRB() {

}

int analiseArvoreB(int ordem) {

}


int main() {

}
