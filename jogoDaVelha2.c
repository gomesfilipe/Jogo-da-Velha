#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CONTINUA 0 
#define VITORIA 1
#define VELHA 2
#define TEMPO 1.5

int impar(int n){
    return n % 2;
}

void printaTabuleiro(char tab[3][3]){
    printf("JOGO DA VELHA [PVP]\n");
    printf("Para fazer uma jogada digite, respectivamente, linha e coluna correspondentes.\n");
    printf("    1   2   3\n");
    printf(" 1 %2c |%2c |%2c\n", tab[0][0], tab[0][1], tab[0][2]);
    printf("   ---+---+---\n");
    printf(" 2 %2c |%2c |%2c\n", tab[1][0], tab[1][1], tab[1][2]);
    printf("   ---+---+---\n");
    printf(" 3 %2c |%2c |%2c\n\n", tab[2][0], tab[2][1], tab[2][2]);
}

int iguais(int a, int b, int c){
    return a == b && b == c && a != ' ';
}

int fimDeJogo(char tab[3][3]){
    // Vitoria por vertical
    if(iguais(tab[0][0], tab[1][0], tab[2][0]) || 
       iguais(tab[0][1], tab[1][1], tab[2][1]) || 
       iguais(tab[0][2], tab[1][2], tab[2][2])){
        return VITORIA;
    }

    // Vitoria por horizontal
    if(iguais(tab[0][0], tab[0][1], tab[0][2]) || 
       iguais(tab[1][0], tab[1][1], tab[1][2]) ||
       iguais(tab[2][0], tab[2][1], tab[2][2])){
           return VITORIA;
    }

    // Vitoria por diagonal
    if(iguais(tab[0][0], tab[1][1], tab[2][2]) ||
       iguais(tab[2][0], tab[1][1], tab[0][2])){
           return VITORIA;
    }

    // Velha
    if(tab[0][0] != ' ' && tab[0][1] != ' ' && tab[0][2] != ' ' && 
       tab[1][0] != ' ' && tab[1][1] != ' ' && tab[1][2] != ' ' && 
       tab[2][0] != ' ' && tab[2][1] != ' ' && tab[2][2] != ' '){
        return VELHA;
    }

    return CONTINUA;
}

void inicTabuleiro(char tab[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tab[i][j] = ' ';
        }
    }
}

int main(){
    int x, y;
    char jogada, game = 's', tabuleiro[3][3];

    while(game == 's'){
        inicTabuleiro(tabuleiro);

        for(int rdd = 1; !fimDeJogo(tabuleiro); rdd++){
            system("cls");
            printaTabuleiro(tabuleiro);
            
            jogada = impar(rdd) ? 'X' : 'O'; 
            printf("Jogador [%c]: ", jogada);
            
            scanf("%d %d", &x, &y);
            getchar();
            
            if(x < 1 || x > 3 || y < 1 || y > 3 || tabuleiro[x - 1][y - 1] != ' '){
                printf("\nJogada invalida. Jogue novamente.");
                rdd--;
                sleep(TEMPO);
                continue;
            }

            tabuleiro[x - 1][y - 1] = jogada;
            system("cls");     
        }

        printaTabuleiro(tabuleiro);
        
        if(fimDeJogo(tabuleiro) == VITORIA){
            printf("Vencedor: Jogador %c!\n\n", jogada);
        
        } else{
            printf("Velha! Nao houve vencedor!\n\n");
        }

        printf("Tecle 's' para jogar novamente.\n");
        scanf("%c", &game);
        getchar();
    }

    return 0;
}
// Entre loops, está limpando a tela duas vezes. Encontrar uma forma de
// não repetir o comando