# Desafio Batalha Naval — ADS

**Aluno**: Bruno Jorge Serra das Neves  
**Curso**: Análise e Desenvolvimento de Sistemas (EAD)  
**Disciplina**: Programação / Desafios de Desenvolvimento

## Objetivo

Este projeto implementa o jogo **Batalha Naval** em C, com três níveis de dificuldade:

- **Novato**: Coordenadas dos navios
- **Aventureiro**: Tabuleiro 10x10
- **Mestre**: Habilidades especiais (CONE, CRUZ, OCTAEDRO)

## Descrição dos Níveis

1. **Novato**: Neste nível, o jogador simplesmente insere as coordenadas dos navios em um tabuleiro básico. Ideal para iniciantes no jogo.
2. **Aventureiro**: O tabuleiro passa a ser de 10x10, oferecendo mais complexidade. O jogador deve ser mais estratégico nas jogadas.
3. **Mestre**: O nível mais difícil, com navios de formas especiais (CONE, CRUZ, OCTAEDRO) que aumentam a complexidade e exigem maior habilidade e estratégia.

## Arquivos

O repositório contém os seguintes arquivos:

- **batalha_naval.c**: Código fonte em C
- **Desafio_Batalha_Naval_Bruno_Final.pdf**: PDF com exemplos das saídas do programa

## Como Executar

### Passo 1: Preparar o ambiente
Abra o arquivo **batalha_naval.c** em um compilador C de sua escolha, como:
- [Cxxdroid](https://play.google.com/store/apps/details?id=com.n0n3m4.bloc&hl=pt_BR&pli=1) (para Android)
- [OnlineGDB](https://www.onlinegdb.com/online_c_compiler) (para execução online)
- GCC ou outro compilador C no seu computador

### Passo 2: Compilar o Código
No compilador escolhido, compile o código. Se estiver usando um compilador local, basta executar:




### Passo 3: Executar o Programa
Execute o programa compilado. O jogo exibirá um menu para escolher o nível de dificuldade:


Escolha o nível de dificuldade:
1. Novato
2. Aventureiro
3. Mestre

Digite sua escolha: 2



## Instruções por Plataforma

- **Windows**: Use o [MinGW](https://sourceforge.net/projects/mingw/) ou o [TDM-GCC](https://jmeubank.github.io/tdm-gcc/). Após instalar, abra o terminal (Prompt de Comando) e siga as instruções de compilação e execução.
- **Linux/Mac**: O GCC geralmente já vem instalado. Caso contrário, pode ser instalado via gerenciador de pacotes (`sudo apt install gcc` no Linux ou `brew install gcc` no Mac).
- **Android**: Utilize o [Cxxdroid](https://play.google.com/store/apps/details?id=com.n0n3m4.bloc&hl=pt_BR&pli=1) para compilar e rodar o código.
