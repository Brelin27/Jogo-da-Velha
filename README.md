[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Q4JKIyo6)

# Jogo da Velha em C

Este guia apresenta o código em C que implementa o jogo da velha. Ele utiliza diversas estruturas de dados para gerenciar os jogadores, o tabuleiro, as ações e o histórico do jogo.

## Estruturas de Dados Utilizadas

### 1. Struct `Jogador`

Representa um jogador no jogo da velha, com os campos `nome` e `simbolo`.

### 2. Struct `Tabuleiro`

Representa o tabuleiro 3x3 do jogo.

### 3. Lista Circular (`NodoCircular`)

Armazena os jogadores em uma ordem circular.

### 4. Lista Duplamente Encadeada (`NodoDuplo`)

Registra as ações realizadas durante o jogo.

### 5. Lista Simplesmente Encadeada (`NodoSimples`)

Armazena as ações do jogo de forma simplificada.

### 6. Pilha (`NodoPilha`)

Mantém o histórico dos estados do tabuleiro durante o jogo.

### 7. Fila (`NodoFila`)

Gerencia a ordem dos jogadores.

### 8. Tabela Hash (`TabelaHash`)

Armazena os jogadores de forma eficiente.

## Como Jogar

1. **Compilação e Execução**: Compile o código com um compilador C e execute o programa gerado.

2. **Instruções no Terminal**: Siga as instruções no terminal para fazer suas jogadas.

3. **Vitória ou Empate**: O jogo continua até que haja um vencedor ou empate.

