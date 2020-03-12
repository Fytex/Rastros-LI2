

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "interface.h"
#include "../data/state.h"
#include "../logic/game.h"

#define BUF_SIZE 1024

/*
 * Recebe uma casa e imprime no ecrã
 */

void type_space(Space p, FILE *file) {

    switch(p) {

        case (Black):
            fprintf(file, "# ");
            break;

        case (White):
            fprintf(file, "* ");
            break;

        default: fprintf(file, ". ");
    }
}

/*
 * Limpa o ecrã e imprime informações sobre a última jogada
 */

void print_last_info(State state) {

    // Executar comando no terminal para o limpar (Compatível com Win e *nix)
    system("cls || clear");

    printf("Last Play:\n\tPlayer: %d\n\tRow: %d\n\tColumn: %c\n\n",
           state.current_player, state.last_play.row + 1, state.last_play.column + 'a');
}

/*
 * Imprime o tabuleiro
 */

void print_board(State state, FILE *file) {

    for (int row = 0; row < 8; row++) {
        if (file == stdout)
            printf("%d     ", row + 1);

        if (row == 7) {
            if (state.last_play.row == 7 && state.last_play.column == 0)
                type_space(White, file);
            else
                fprintf(file, "1 ");
        }

        for (int col = 0; col < 8; col++)
            if (abs(row - col) != 7)
                type_space(state.board[row][col], file);

        if (row == 0) {
            if (state.last_play.row == 0 && state.last_play.column == 7)
                type_space(White, file);
            else
                fprintf(file, "2");
        }

        fprintf(file, "\n"); // New line
    }

    fprintf(file, "\n");

    if (file == stdout) {
        printf("      ");

        for (int i = 0; i < 8; i++)
            printf("%c ", 'a' + i);

        puts("\n"); // New Line
    } else {
        int i = 0;

        for ( ; i < state.move_count; i++)

            fprintf(file, "%02d : %c%d %c%d\n", i, state.moves[i].player1.column + 'a',
                    state.moves[i].player1.row + 1, state.moves[i].player2.column + 'a',
                    state.moves[i].player2.row + 1);

        if (state.current_player == 2)
            fprintf(file, "%02d : %c%d", i, state.last_play.column + 'a',
                    state.last_play.row + 1);

    }
}


/*
 * Escreve para o ficheiro indicado
 */

void write_to_file(State state, char *filename){

    char directory[BUF_SIZE] = "saves/";
    FILE *file;

    strcat(directory, filename);

    file = fopen(directory, "w");

    print_board(state, file);
    puts("File created\n");

    fclose(file);

}

/*
 * Interpretador (Comunicação com o terminal)
 */

int interpreter(State *state) {

    char line[BUF_SIZE];
    char col[2], row[2];
    unsigned int winner;


    print_board(*state, stdout);
    printf("Player %d >> ", state->current_player);

    while (fgets(line, BUF_SIZE, stdin) != NULL) {

        if (strlen(line) == 3 && sscanf(line, "%[a-hA-H]%[1-8]", col, row) == 2) {
            Position pos = {tolower(*col) - 'a', *row - '1'};

            if (play(state, pos)) {
                print_last_info(*state);
                print_board(*state, stdout);

                winner = game_finished(*state);

                if (winner) {
                    printf("Congrats Player %d\n", winner);
                    return 1;
                }

                swap_players(state);
            }
            else
                puts("Introduza Jogada válida");
        }

        else if (strlen(line) == 2 && *line == 'Q')
            exit(0);

        else if (strncmp(line, "gr ", 3)== 0)
             write_to_file(*state, line + 3);

        else
            puts("Introduza Jogada válida");

        printf("Player %d >> ", state->current_player);
    }

    return 0;
}
