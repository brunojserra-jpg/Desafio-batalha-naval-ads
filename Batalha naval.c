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
    printf("
