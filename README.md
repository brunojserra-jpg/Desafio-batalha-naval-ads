# Desafio Batalha Naval – ADS

**Aluno**: Bruno Jorge Serra das Neves  
**Curso**: Análise e Desenvolvimento de Sistemas (EAD)  
**Disciplina**: Programação / Desafios de Desenvolvimento  

---

## Objetivo

Este projeto implementa o jogo **Batalha Naval** em C, com três níveis de dificuldade:

- **Novato**: Tabuleiro 5x5 com navios simples
- **Aventureiro**: Tabuleiro 10x10 com navios aleatórios  
- **Mestre**: Tabuleiro 10x10 com formas especiais (CONE, CRUZ, OCTAEDRO)

---

## Descrição dos Níveis

1. **Novato**: Tabuleiro 5x5 com navios pré-definidos. Ideal para iniciantes.
2. **Aventureiro**: Tabuleiro 10x10 com navios aleatórios de diferentes tamanhos.
3. **Mestre**: O nível mais difícil, com navios em formas especiais que exigem mais estratégia.

---

## Arquivos

- **batalha_naval.c**: Código fonte completo em C
- **Desafio_Batalha_Naval_Bruno_Final.pdf**: PDF com exemplos de saída

---

## Código Fonte

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* --------------------------
   Constantes e Utilidades
---------------------------*/
#define TAM_NOVATO 5
#define TAM_AVENTUREIRO 10
#define TAM_MESTRE 10
#define MAX_NAVIOS 5
#define AGUA 0
#define NAVIO 1
#define ACERTOU 2
#define ERROU 3

void print_div(const char *title) {
    printf("\n==========================================\n");
    printf("          %s", title);
    printf("\n==========================================\n");
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* --------------------------
   Estruturas de Dados
---------------------------*/
typedef struct {
    int x;
    int y;
} Coordenada;

typedef struct {
    Coordenada posicao;
    int tamanho;
    int direcao; // 0: horizontal, 1: vertical, 2: diagonal
    int afundado;
} Navio;

/* --------------------------
   NÍVEL NOVATO
---------------------------*/
void inicializar_tabuleiro(int tam, int tabuleiro[][tam]) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void exibir_tabuleiro_novato(int tam, int tabuleiro[][tam]) {
    printf("\n   ");
    for (int j = 0; j < tam; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < tam; i++) {
        printf("%d |", i);
        for (int j = 0; j < tam; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf("~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("N ");
            } else if (tabuleiro[i][j] == ACERTOU) {
                printf("X ");
            } else if (tabuleiro[i][j] == ERROU) {
                printf("O ");
            }
        }
        printf("\n");
    }
}

void posicionar_navio_novato(int tam, int tabuleiro[][tam], int x, int y, int tamanho, int direcao) {
    if (direcao == 0) { // Horizontal
        for (int i = 0; i < tamanho; i++) {
            if (y + i < tam) {
                tabuleiro[x][y + i] = NAVIO;
            }
        }
    } else { // Vertical
        for (int i = 0; i < tamanho; i++) {
            if (x + i < tam) {
                tabuleiro[x + i][y] = NAVIO;
            }
        }
    }
}

void nivel_novato() {
    print_div("NÍVEL NOVATO");
    printf("Tabuleiro %dx%d\n", TAM_NOVATO, TAM_NOVATO);
    
    int tabuleiro[TAM_NOVATO][TAM_NOVATO];
    inicializar_tabuleiro(TAM_NOVATO, tabuleiro);
    
    // Posicionar navios manualmente (apenas para demonstração)
    posicionar_navio_novato(TAM_NOVATO, tabuleiro, 1, 1, 2, 0); // Navio horizontal
    posicionar_navio_novato(TAM_NOVATO, tabuleiro, 3, 2, 3, 1); // Navio vertical
    
    int tentativas = 0, acertos = 0, total_navios = 5;
    char entrada[10];
    
    printf("Navios posicionados! Tente acertar as coordenadas.\n");
    
    while (acertos < total_navios) {
        exibir_tabuleiro_novato(TAM_NOVATO, tabuleiro);
        
        printf("\nTentativa %d - Digite coordenadas (x,y): ", tentativas + 1);
        scanf("%s", entrada);
        
        int x, y;
        if (sscanf(entrada, "%d,%d", &x, &y) == 2 && x >= 0 && x < TAM_NOVATO && y >= 0 && y < TAM_NOVATO) {
            if (tabuleiro[x][y] == NAVIO) {
                printf("ACERTOU!\n");
                tabuleiro[x][y] = ACERTOU;
                acertos++;
            } else if (tabuleiro[x][y] == AGUA) {
                printf("ÁGUA!\n");
                tabuleiro[x][y] = ERROU;
            } else {
                printf("Você já tentou esta posição!\n");
            }
            tentativas++;
        } else {
            printf("Coordenadas inválidas! Use o formato x,y (ex: 1,2)\n");
        }
    }
    
    printf("\nPARABÉNS! Você afundou todos os navios em %d tentativas!\n", tentativas);
    exibir_tabuleiro_novato(TAM_NOVATO, tabuleiro);
}

/* --------------------------
   NÍVEL AVENTUREIRO
---------------------------*/
int posicionar_navio_aventureiro(int tam, int tabuleiro[][tam], int tamanho) {
    int direcao = rand() % 2; // 0: horizontal, 1: vertical
    int x, y;
    
    if (direcao == 0) { // Horizontal
        x = rand() % tam;
        y = rand() % (tam - tamanho + 1);
        
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[x][y + i] != AGUA) {
                return 0; // Posição ocupada
            }
        }
        
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[x][y + i] = NAVIO;
        }
    } else { // Vertical
        x = rand() % (tam - tamanho + 1);
        y = rand() % tam;
        
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[x + i][y] != AGUA) {
                return 0; // Posição ocupada
            }
        }
        
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[x + i][y] = NAVIO;
        }
    }
    
    return 1; // Navio posicionado com sucesso
}

void exibir_tabuleiro_aventureiro(int tam, int tabuleiro[][tam], int mostrar_navios) {
    printf("\n   ");
    for (int j = 0; j < tam; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < tam; i++) {
        printf("%2d|", i);
        for (int j = 0; j < tam; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" ~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                if (mostrar_navios) {
                    printf(" N ");
                } else {
                    printf(" ~ ");
                }
            } else if (tabuleiro[i][j] == ACERTOU) {
                printf(" X ");
            } else if (tabuleiro[i][j] == ERROU) {
                printf(" O ");
            }
        }
        printf("\n");
    }
}

void nivel_aventureiro() {
    print_div("NÍVEL AVENTUREIRO");
    printf("Tabuleiro %dx%d\n", TAM_AVENTUREIRO, TAM_AVENTUREIRO);
    
    srand(time(NULL));
    int tabuleiro[TAM_AVENTUREIRO][TAM_AVENTUREIRO];
    inicializar_tabuleiro(TAM_AVENTUREIRO, tabuleiro);
    
    // Posicionar navios aleatoriamente
    int navios[] = {5, 4, 3, 3, 2}; // Tamanhos dos navios
    int total_navios = 5;
    int celulas_navios = 0;
    
    for (int i = 0; i < total_navios; i++) {
        int posicionado = 0;
        while (!posicionado) {
            posicionado = posicionar_navio_aventureiro(TAM_AVENTUREIRO, tabuleiro, navios[i]);
        }
        celulas_navios += navios[i];
    }
    
    int tentativas = 0, acertos = 0;
    char entrada[10];
    
    printf("Navios posicionados aleatoriamente! Tente acertar!\n");
    
    while (acertos < celulas_navios) {
        exibir_tabuleiro_aventureiro(TAM_AVENTUREIRO, tabuleiro, 0);
        
        printf("\nTentativa %d - Acertos: %d/%d\n", tentativas + 1, acertos, celulas_navios);
        printf("Digite coordenadas (x,y): ");
        scanf("%s", entrada);
        
        int x, y;
        if (sscanf(entrada, "%d,%d", &x, &y) == 2 && x >= 0 && x < TAM_AVENTUREIRO && y >= 0 && y < TAM_AVENTUREIRO) {
            if (tabuleiro[x][y] == NAVIO) {
                printf("ACERTOU!\n");
                tabuleiro[x][y] = ACERTOU;
                acertos++;
            } else if (tabuleiro[x][y] == AGUA) {
                printf("ÁGUA!\n");
                tabuleiro[x][y] = ERROU;
            } else {
                printf("Você já tentou esta posição!\n");
            }
            tentativas++;
        } else {
            printf("Coordenadas inválidas! Use o formato x,y (ex: 5,7)\n");
        }
    }
    
    printf("\nPARABÉNS! Você afundou todos os navios em %d tentativas!\n", tentativas);
    exibir_tabuleiro_aventureiro(TAM_AVENTUREIRO, tabuleiro, 1);
}

/* --------------------------
   NÍVEL MESTRE
---------------------------*/
void aplicar_forma_cone(int tam, int tabuleiro[][tam], int x, int y) {
    // Formato de cone
    if (x >= 0 && x < tam && y >= 0 && y < tam) tabuleiro[x][y] = NAVIO;
    if (x+1 >= 0 && x+1 < tam && y-1 >= 0 && y-1 < tam) tabuleiro[x+1][y-1] = NAVIO;
    if (x+1 >= 0 && x+1 < tam && y >= 0 && y < tam) tabuleiro[x+1][y] = NAVIO;
    if (x+1 >= 0 && x+1 < tam && y+1 >= 0 && y+1 < tam) tabuleiro[x+1][y+1] = NAVIO;
    if (x+2 >= 0 && x+2 < tam && y-2 >= 0 && y-2 < tam) tabuleiro[x+2][y-2] = NAVIO;
    if (x+2 >= 0 && x+2 < tam && y-1 >= 0 && y-1 < tam) tabuleiro[x+2][y-1] = NAVIO;
    if (x+2 >= 0 && x+2 < tam && y >= 0 && y < tam) tabuleiro[x+2][y] = NAVIO;
    if (x+2 >= 0 && x+2 < tam && y+1 >= 0 && y+1 < tam) tabuleiro[x+2][y+1] = NAVIO;
    if (x+2 >= 0 && x+2 < tam && y+2 >= 0 && y+2 < tam) tabuleiro[x+2][y+2] = NAVIO;
}

void aplicar_forma_cruz(int tam, int tabuleiro[][tam], int x, int y) {
    // Formato de cruz
    if (x >= 0 && x < tam && y >= 0 && y < tam) tabuleiro[x][y] = NAVIO;
    if (x-1 >= 0 && x-1 < tam && y >= 0 && y < tam) tabuleiro[x-1][y] = NAVIO;
    if (x+1 >= 0 && x+1 < tam && y >= 0 && y < tam) tabuleiro[x+1][y] = NAVIO;
    if (x >= 0 && x < tam && y-1 >= 0 && y-1 < tam) tabuleiro[x][y-1] = NAVIO;
    if (x >= 0 && x < tam && y+1 >= 0 && y+1 < tam) tabuleiro[x][y+1] = NAVIO;
}

void aplicar_forma_octaedro(int tam, int tabuleiro[][tam], int x, int y) {
    // Formato de octaedro (diamante)
    if (x >= 0 && x < tam && y >= 0 && y < tam) tabuleiro[x][y] = NAVIO;
    if (x-1 >= 0 && x-1 < tam && y >= 0 && y < tam) tabuleiro[x-1][y] = NAVIO;
    if (x+1 >= 0 && x+1 < tam && y >= 0 && y < tam) tabuleiro[x+1][y] = NAVIO;
    if (x >= 0 && x < tam && y-1 >= 0 && y-1 < tam) tabuleiro[x][y-1] = NAVIO;
    if (x >= 0 && x < tam && y+1 >= 0 && y+1 < tam) tabuleiro[x][y+1] = NAVIO;
    if (x-1 >= 0 && x-1 < tam && y-1 >= 0 && y-1 < tam) tabuleiro[x-1][y-1] = NAVIO;
    if (x-1 >= 0 && x-1 < tam && y+1 >= 0 && y+1 < tam) tabuleiro[x-1][y+1] = NAVIO;
    if (x+1 >= 0 && x+1 < tam && y-1 >= 0 && y-1 < tam) tabuleiro[x+1][y-1] = NAVIO;
    if (x+1 >= 0 && x+1 < tam && y+1 >= 0 && y+1 < tam) tabuleiro[x+1][y+1] = NAVIO;
}

void exibir_tabuleiro_mestre(int tam, int tabuleiro[][tam], int mostrar_navios) {
    printf("\n   ");
    for (int j = 0; j < tam; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < tam; i++) {
        printf("%2d|", i);
        for (int j = 0; j < tam; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" ~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                if (mostrar_navios) {
                    printf(" N ");
                } else {
                    printf(" ~ ");
                }
            } else if (tabuleiro[i][j] == ACERTOU) {
                printf(" X ");
            } else if (tabuleiro[i][j] == ERROU) {
                printf(" O ");
            }
        }
        printf("\n");
    }
}

void nivel_mestre() {
    print_div("NÍVEL MESTRE");
    printf("Tabuleiro %dx%d com formas especiais\n", TAM_MESTRE, TAM_MESTRE);
    
    srand(time(NULL));
    int tabuleiro[TAM_MESTRE][TAM_MESTRE];
    inicializar_tabuleiro(TAM_MESTRE, tabuleiro);
    
    // Posicionar formas especiais
    aplicar_forma_cone(TAM_MESTRE, tabuleiro, 2, 4);
    aplicar_forma_cruz(TAM_MESTRE, tabuleiro, 5, 2);
    aplicar_forma_octaedro(TAM_MESTRE, tabuleiro, 7, 7);
    
    // Contar células com navios
    int celulas_navios = 0;
    for (int i = 0; i < TAM_MESTRE; i++) {
        for (int j = 0; j < TAM_MESTRE; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                celulas_navios++;
            }
        }
    }
    
    int tentativas = 0, acertos = 0;
    char entrada[10];
    
    printf("Formas especiais posicionadas! Tente acertar!\n");
    printf("Dica: Procure por padrões de CONE, CRUZ e OCTAEDRO!\n");
    
    while (acertos < celulas_navios) {
        exibir_tabuleiro_mestre(TAM_MESTRE, tabuleiro, 0);
        
        printf("\nTentativa %d - Acertos: %d/%d\n", tentativas + 1, acertos, celulas_navios);
        printf("Digite coordenadas (x,y): ");
        scanf("%s", entrada);
        
        int x, y;
        if (sscanf(entrada, "%d,%d", &x, &y) == 2 && x >= 0 && x < TAM_MESTRE && y >= 0 && y < TAM_MESTRE) {
            if (tabuleiro[x][y] == NAVIO) {
                printf("ACERTOU!\n");
                tabuleiro[x][y] = ACERTOU;
                acertos++;
            } else if (tabuleiro[x][y] == AGUA) {
                printf("ÁGUA!\n");
                tabuleiro[x][y] = ERROU;
            } else {
                printf("Você já tentou esta posição!\n");
            }
            tentativas++;
        } else {
            printf("Coordenadas inválidas! Use o formato x,y (ex: 5,7)\n");
        }
    }
    
    printf("\nPARABÉNS! Você dominou o nível Mestre em %d tentativas!\n", tentativas);
    exibir_tabuleiro_mestre(TAM_MESTRE, tabuleiro, 1);
}

/* --------------------------
   MENU PRINCIPAL
---------------------------*/
void mostrar_menu() {
    print_div("BATALHA NAVAL");
    printf("1. Nível Novato (%dx%d)\n", TAM_NOVATO, TAM_NOVATO);
    printf("2. Nível Aventureiro (%dx%d)\n", TAM_AVENTUREIRO, TAM_AVENTUREIRO);
    printf("3. Nível Mestre (formas especiais)\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;
    
    do {
        mostrar_menu();
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case 1:
                nivel_novato();
                break;
            case 2:
                nivel_aventureiro();
                break;
            case 3:
                nivel_mestre();
                break;
            case 4:
                printf("Obrigado por jogar! Até a próxima!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
        if (opcao != 4) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    } while (opcao != 4);
    
    return 0;
}
```

---

## Como Executar

### Passo 1: Preparar o ambiente

Abra o arquivo **batalha_naval.c** em um compilador C:

- **Cxxdroid (para Android)**
- **OnlineGDB (para execução online)**
- **GCC no Linux/Windows/Mac**

### Passo 2: Compilar o Código

```bash
gcc batalha_naval.c -o batalha_naval
```

### Passo 3: Executar o Programa

```bash
./batalha_naval
```

---

## Instruções por Plataforma

- **Windows**: Use MinGW ou TDM-GCC. Compile com `gcc batalha_naval.c -o batalha_naval.exe`
- **Linux/Mac**: Use o GCC instalado. Execute com `./batalha_naval`
- **Android**: Use o Cxxdroid para compilar e executar

---

## Funcionalidades Implementadas

- ✅ Três níveis de dificuldade
- ✅ Tabuleiros de diferentes tamanhos
- ✅ Sistema de acertos e erros
- ✅ Formas especiais no nível Mestre
- ✅ Interface interativa
- ✅ Contagem de tentativas e pontuação
- ✅ Posicionamento aleatório de navios
- ✅ Menu de seleção de níveis
