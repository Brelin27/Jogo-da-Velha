#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições das Structs
typedef struct {
    char nome[50];
    char simbolo; // 'X' ou 'O'
} Jogador;

typedef struct {
    char tabuleiro[3][3];
} Tabuleiro;

typedef struct Acao {
    int linha;
    int coluna;
    char simbolo;
    struct Acao* prox;
} Acao;
// Lista Circular
typedef struct NodoCircular {
    Jogador jogador;
    struct NodoCircular* prox;
} NodoCircular;

// Lista Duplamente Encadeada
typedef struct NodoDuplo {
    Acao acao;
    struct NodoDuplo* prox;
    struct NodoDuplo* ant;
} NodoDuplo;

// Lista Simplesmente Encadeada
typedef struct NodoSimples {
    Acao acao;
    struct NodoSimples* prox;
} NodoSimples;

// Pilha
typedef struct NodoPilha {
    Tabuleiro estado;
    struct NodoPilha* prox;
} NodoPilha;

// Fila
typedef struct NodoFila {
    Jogador jogador;
    struct NodoFila* prox;
} NodoFila;

typedef struct {
    NodoFila* frente;
    NodoFila* traseira;
} Fila;

// Tabela Hash
#define TAMANHO_TABELA 10
typedef struct {
    Jogador* jogadores[TAMANHO_TABELA];
} TabelaHash;

// Funções de Hashing
unsigned int hash(char* nome) {
    unsigned int hash = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        hash = hash * 31 + nome[i];
    }
    return hash % TAMANHO_TABELA;
}

void inicializarTabelaHash(TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->jogadores[i] = NULL;
    }
}

void inserirJogadorHash(TabelaHash* tabela, Jogador jogador) {
    unsigned int indice = hash(jogador.nome);
    tabela->jogadores[indice] = (Jogador*)malloc(sizeof(Jogador));
    *(tabela->jogadores[indice]) = jogador;
}

Jogador* buscarJogador(TabelaHash* tabela, char* nome) {
    unsigned int indice = hash(nome);
    return tabela->jogadores[indice];
}
// Funções da Lista Circular
NodoCircular* inicializarListaCircular(Jogador jogador) {
    NodoCircular* novo = (NodoCircular*)malloc(sizeof(NodoCircular));
    novo->jogador = jogador;
    novo->prox = novo;
    return novo;
}

void inserirJogador(NodoCircular** lista, Jogador jogador) {
    NodoCircular* novo = (NodoCircular*)malloc(sizeof(NodoCircular));
    novo->jogador = jogador;
    if (*lista == NULL) {
        novo->prox = novo;
        *lista = novo;
    } else {
        NodoCircular* temp = *lista;
        while (temp->prox != *lista) {
            temp = temp->prox;
        }
        temp->prox = novo;
        novo->prox = *lista;
    }
}

void imprimirListaCircular(NodoCircular* lista) {
    NodoCircular* temp = lista;
    if (lista != NULL) {
        do {
            printf("Jogador: %s, Simbolo: %c\n", temp->jogador.nome, temp->jogador.simbolo);
            temp = temp->prox;
        } while (temp != lista);
    }
}

// Funções da Lista Duplamente Encadeada
NodoDuplo* inicializarListaDupla() {
    return NULL;
}

void inserirAcao(NodoDuplo** lista, Acao acao) {
    NodoDuplo* novo = (NodoDuplo*)malloc(sizeof(NodoDuplo));
    novo->acao = acao;
    novo->prox = *lista;
    novo->ant = NULL;
    if (*lista != NULL) {
        (*lista)->ant = novo;
    }
    *lista = novo;
}

void imprimirListaDupla(NodoDuplo* lista) {
    NodoDuplo* temp = lista;
    while (temp != NULL) {
        printf("Acao: linha=%d, coluna=%d, simbolo=%c\n", temp->acao.linha, temp->acao.coluna, temp->acao.simbolo);
        temp = temp->prox;
    }
}

// Funções da Lista Simplesmente Encadeada
NodoSimples* inicializarListaSimples() {
    return NULL;
}

void inserirAcaoSimples(NodoSimples** lista, Acao acao) {
    NodoSimples* novo = (NodoSimples*)malloc(sizeof(NodoSimples));
    novo->acao = acao;
    novo->prox = *lista;
    *lista = novo;
}

void imprimirListaSimples(NodoSimples* lista) {
    NodoSimples* temp = lista;
    while (temp != NULL) {
        printf("Acao: linha=%d, coluna=%d, simbolo=%c\n", temp->acao.linha, temp->acao.coluna, temp->acao.simbolo);
        temp = temp->prox;
    }
}

// Funções para a Pilha
NodoPilha* inicializarPilha() {
    return NULL;
}

void push(NodoPilha** pilha, Tabuleiro estado) {
    NodoPilha* novo = (NodoPilha*)malloc(sizeof(NodoPilha));
    novo->estado = estado;
    novo->prox = *pilha;
    *pilha = novo;
}

Tabuleiro pop(NodoPilha** pilha) {
    if (*pilha == NULL) {
        Tabuleiro vazio;
        memset(&vazio, 0, sizeof(Tabuleiro));
        return vazio;
    }
    NodoPilha* temp = *pilha;
    Tabuleiro estado = temp->estado;
    *pilha = temp->prox;
    free(temp);
    return estado;
}

void imprimirPilha(NodoPilha* pilha) {
    NodoPilha* temp = pilha;
    while (temp != NULL) {
        // Implementar a função para imprimir o tabuleiro
        temp = temp->prox;
    }
}

// Funções para a Fila
Fila* inicializarFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->frente = NULL;
    f->traseira = NULL;
    return f;
}

void enfileirar(Fila* fila, Jogador jogador) {
    NodoFila* novo = (NodoFila*)malloc(sizeof(NodoFila));
    novo->jogador = jogador;
    novo->prox = NULL;
    if (fila->traseira == NULL) {
        fila->frente = novo;
        fila->traseira = novo;
    } else {
        fila->traseira->prox = novo;
        fila->traseira = novo;
    }
}

Jogador desenfileirar(Fila* fila) {
    if (fila->frente == NULL) {
        Jogador vazio;
        memset(&vazio, 0, sizeof(Jogador));
        return vazio;
    }
    NodoFila* temp = fila->frente;
    Jogador jogador = temp->jogador;
    fila->frente = temp->prox;
    if (fila->frente == NULL) {
        fila->traseira = NULL;
    }
    free(temp);
    return jogador;
}

void imprimirFila(Fila* fila) {
    NodoFila* temp = fila->frente;
    while (temp != NULL) {
        printf("Jogador: %s, Simbolo: %c\n", temp->jogador.nome, temp->jogador.simbolo);
        temp = temp->prox;
    }
}
// Funções do Jogo da Velha
void inicializarTabuleiro(Tabuleiro* tabuleiro) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro->tabuleiro[i][j] = ' ';
        }
    }
}

void imprimirTabuleiro(Tabuleiro* tabuleiro) {
    printf("  0 1 2\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i);
        for (int j = 0; j < 3; j++) {
            printf("%c", tabuleiro->tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  -----\n");
    }
}

int verificarVencedor(Tabuleiro* tabuleiro, char simbolo) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro->tabuleiro[i][0] == simbolo && tabuleiro->tabuleiro[i][1] == simbolo && tabuleiro->tabuleiro[i][2] == simbolo) return 1;
        if (tabuleiro->tabuleiro[0][i] == simbolo && tabuleiro->tabuleiro[1][i] == simbolo && tabuleiro->tabuleiro[2][i] == simbolo) return 1;
    }
    if (tabuleiro->tabuleiro[0][0] == simbolo && tabuleiro->tabuleiro[1][1] == simbolo && tabuleiro->tabuleiro[2][2] == simbolo) return 1;
    if (tabuleiro->tabuleiro[0][2] == simbolo && tabuleiro->tabuleiro[1][1] == simbolo && tabuleiro->tabuleiro[2][0] == simbolo) return 1;
    return 0;
}

int main() {
    Jogador jogador1 = {"Jogador 1", 'X'};
    Jogador jogador2 = {"Jogador 2", 'O'};

    TabelaHash tabelaJogadores;
    inicializarTabelaHash(&tabelaJogadores);
    inserirJogadorHash(&tabelaJogadores, jogador1);
    inserirJogadorHash(&tabelaJogadores, jogador2);

    NodoCircular* listaJogadores = inicializarListaCircular(jogador1);
    inserirJogador(&listaJogadores, jogador2);

    NodoDuplo* listaAcoesDupla = inicializarListaDupla();
    NodoSimples* listaAcoesSimples = inicializarListaSimples();
    NodoPilha* pilhaEstados = inicializarPilha();
    Fila* filaJogadores = inicializarFila();
    enfileirar(filaJogadores, jogador1);
    enfileirar(filaJogadores, jogador2);

    Tabuleiro tabuleiro;
    inicializarTabuleiro(&tabuleiro);

    NodoCircular* jogadorAtual = listaJogadores;
    int linha, coluna;
    int jogadas = 0;

    while (1) {
        imprimirTabuleiro(&tabuleiro);
        printf("Jogador %s (%c), digite sua jogada (linha e coluna): ", jogadorAtual->jogador.nome, jogadorAtual->jogador.simbolo);
        scanf("%d %d", &linha, &coluna);

        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || tabuleiro.tabuleiro[linha][coluna] != ' ') {
            printf("Jogada inválida! Tente novamente.\n");
            continue;
        }

        tabuleiro.tabuleiro[linha][coluna] = jogadorAtual->jogador.simbolo;
        Acao novaAcao = {linha, coluna, jogadorAtual->jogador.simbolo, NULL};
        inserirAcao(&listaAcoesDupla, novaAcao);
        inserirAcaoSimples(&listaAcoesSimples, novaAcao);
        push(&pilhaEstados, tabuleiro);

        if (verificarVencedor(&tabuleiro, jogadorAtual->jogador.simbolo)) {
            imprimirTabuleiro(&tabuleiro);
            printf("Jogador %s (%c) venceu!\n", jogadorAtual->jogador.nome, jogadorAtual->jogador.simbolo);
            break;
        }

        jogadas++;
        if (jogadas == 9) {
            imprimirTabuleiro(&tabuleiro);
            printf("Empate!\n");
            break;
        }

        jogadorAtual = jogadorAtual->prox;
    }

    return 0;
}
