#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Biblioteca do sleep
#define VITORIA 1
#define VELHA 2
#define TEMPO 1.5

int i;

typedef struct tabuleiro{
    char A1, A2, A3, B1, B2, B3, C1, C2, C3; 
    
} tTabuleiro;

char converteMinuscula(char c){
    int constante = 'a' - 'A';

    if(c > 'A' && c < 'Z'){
        c += constante;
    }

    return c;
}

int fimDeJogo(tTabuleiro tab){
    // Vitória por linha
    if((tab.A1 == tab.A2 && tab.A1 == tab.A3 && tab.A1 != ' ') ||
       (tab.B1 == tab.B2 && tab.B1 == tab.B3 && tab.B1 != ' ') ||
       (tab.C1 == tab.C2 && tab.C1 == tab.C3 && tab.C1 != ' ')){
        return VITORIA;
    }

    // Vitória por coluna
    if((tab.A1 == tab.B1 && tab.A1 == tab.C1 && tab.A1 != ' ') ||
       (tab.A2 == tab.B2 && tab.A2 == tab.C2 && tab.A2 != ' ') ||
       (tab.A3 == tab.B3 && tab.A3 == tab.C3 && tab.A3 != ' ')){
        return VITORIA;
    }

    // Vitória por diagonal
    if((tab.A1 == tab.B2 && tab.A1 == tab.C3 && tab.A1 != ' ') ||
       (tab.C1 == tab.B2 && tab.C1 == tab.A3 && tab.C1 != ' ')){
        return VITORIA;
    }

    // Velha
    if(tab.A1 != ' ' && tab.A2 != ' ' && tab.A3 != ' ' && 
       tab.B1 != ' ' && tab.B2 != ' ' && tab.B3 != ' ' && 
       tab.C1 != ' ' && tab.C2 != ' ' && tab.C3 != ' '){
        return VELHA;
    }
    return 0;
}

void printTabuleiro(tTabuleiro tab){
    printf("JOGO DA VELHA [PVP]\nPara fazer uma jogada digite, respectivamente, linha e coluna correspondentes.\n");
    printf("    1   2   3\n A %2c |%2c |%2c \n   ---+---+---\n B %2c |%2c |%2c \n   ---+---+---\n C %2c |%2c |%2c \n\n", tab.A1, tab.A2, tab.A3, tab.B1, tab.B2, tab.B3, tab.C1, tab.C2, tab.C3);
}

tTabuleiro atualizaTabuleiro(tTabuleiro tab, char l, int c){
    char jogada;
    
    if(i % 2 == 1){
        jogada = 'X';
        
    } else{
        jogada = 'O';
    }
    
    if(l == 'a'){
        if(c == 1 && tab.A1 == ' '){
            tab.A1 = jogada;

        } else if(c == 2 && tab.A2 == ' '){
            tab.A2 = jogada;

        } else if(c == 3 && tab.A3 == ' '){
            tab.A3 = jogada;

        } else{
            i--;
            printf("Jogada invalida. Jogue novamente.\n");
            sleep(TEMPO);
            return tab;
        }
    
    } else if(l == 'b'){
        if(c == 1 && tab.B1 == ' '){
            tab.B1 = jogada;

        } else if(c == 2 && tab.B2 == ' '){
            tab.B2 = jogada;

        } else if(c == 3 && tab.B3 == ' '){
            tab.B3 = jogada;

        } else{
            i--;
            printf("Jogada invalida. Jogue novamente.\n");
            sleep(TEMPO);
            return tab;
        }

    } else if(l == 'c'){
        if(c == 1 && tab.C1 == ' '){
            tab.C1 = jogada;

        } else if(c == 2 && tab.C2 == ' '){
            tab.C2 = jogada;

        } else if(c == 3 && tab.C3 == ' '){
            tab.C3 = jogada;
        
        } else{
            i--;
            printf("Jogada invalida. Jogue novamente.\n");
            sleep(TEMPO);
            return tab;
        }

    } else{
        i--;
        printf("Jogada invalida. Jogue novamente.\n");
        sleep(TEMPO);
        return tab;
    }

    return tab;
}

int main(){
    char l, jogada, game = 's';
    int c;
    tTabuleiro tab;
    tab.A1 = ' '; tab.A2 = ' '; tab.A3 = ' '; 
    tab.B1 = ' '; tab.B2 = ' '; tab.B3 = ' '; 
    tab.C1 = ' '; tab.C2 = ' '; tab.C3 = ' ';
    
    system("cls");

    while(game == 's'){
        for(i = 1; !fimDeJogo(tab); i++){
            printTabuleiro(tab);
            
            if(i % 2 == 1){
                printf("Jogada player [X]: ");
            
            } else{
                printf("Jogada player [O]: ");
            }
            
            scanf("%c%d", &l, &c);
            getchar();
            l = converteMinuscula(l);
            tab = atualizaTabuleiro(tab, l, c);

            system("cls");
        }
        
        printTabuleiro(tab);

        if(fimDeJogo(tab) == VITORIA){
            i--;
            if(i % 2 == 1){
                printf("Vitoria do jogador [X]!!!\n\n");

            } else{
                printf("Vitoria do jogador [O]!!!\n\n");
            }
        
        } else{
            printf("Velha! Ninguem venceu!\n\n");
        }

        printf("Se quiser jogar mais, digite 's'. Caso contrario, digite qualquer outra coisa.\n");
        scanf("%c", &game);
        getchar();
        system("cls");

        // Resetando o tabuleiro
        tab.A1 = ' '; tab.A2 = ' '; tab.A3 = ' '; 
        tab.B1 = ' '; tab.B2 = ' '; tab.B3 = ' '; 
        tab.C1 = ' '; tab.C2 = ' '; tab.C3 = ' ';
        i = 1;
    }    
    return 0;
}
