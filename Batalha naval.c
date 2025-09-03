#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FACIL 5
#define MEDIO 10
#define DIFICIL 10

void limpar_tela() {
    system("clear || cls");
}

void mostrar_menu() {
    printf("================================\n");
    printf("        BATALHA NAVAL ADS       \n");
    printf("================================\n");
    printf("1. Nivel Facil (%dx%d)\n", FACIL, FACIL);
    printf("2. Nivel Medio (%dx%d)\n", MEDIO, MEDIO);
    printf("3. Nivel Dificil\n");
    printf("4. Sair\n");
    printf("Escolha: ");
}

void jogar_nivel(int tamanho) {
    printf("\n=== INICIANDO NIVEL %dx%d ===\n", tamanho, tamanho);
    printf("Navios posicionados! Tente acertar!\n");
    printf("Digite coordenadas como: 2,3\n\n");
    
    int acertos = 0, tentativas = 0;
    
    while (acertos < 3) {
        printf("Tentativa %d: ", tentativas + 1);
        
        int x, y;
        if (scanf("%d,%d", &x, &y) == 2) {
            if (x >= 0 && x < tamanho && y >= 0 && y < tamanho) {
                printf("Acertou em (%d,%d)!\n", x, y);
                acertos++;
            } else {
                printf("Coordenadas invalidas!\n");
            }
        } else {
            printf("Formato errado! Use: x,y\n");
            while (getchar() != '\n');
        }
        tentativas++;
    }
    
    printf("\nPARABENS! Voce venceu em %d tentativas!\n", tentativas);
}

int main() {
    int opcao;
    
    do {
        limpar_tela();
        mostrar_menu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                jogar_nivel(FACIL);
                break;
            case 2:
                jogar_nivel(MEDIO);
                break;
            case 3:
                jogar_nivel(DIFICIL);
                break;
            case 4:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        if (opcao != 4) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while (opcao != 4);
    
    return 0;
}
