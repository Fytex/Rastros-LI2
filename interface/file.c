//
// Created by fytex on 3/13/20.
//

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../data/state.h"
#include "board.h"

#define DIR_MAX 261 // 255 (File name) + 6 (saves/)

/*
 * Escreve para o ficheiro indicado
 */

void write_to_file(State *state, char *filename){

    char directory[DIR_MAX] = "saves/";
    FILE *file;

    mkdir("saves/", 0777); // Creates directory if not exists giving permission to every user

    strncat(directory, filename, DIR_MAX);

    file = fopen(directory, "w");

    print_board(state, file);
    puts("File created\n");

        fclose(file);

    }


void charToSpace(State *state, int nrow,const char *charRow){

    for(int i = 0; i < 16; i += 2){
        if(charRow[i] == '.') state->board[nrow][i/2] = Blank;
        else if (charRow[i] == '#') state->board[nrow][i/2] = Black;
        else state->board[nrow][i/2] = White;
    }
}


void read_from_file(State *state, char *filename){

    char charRow[1024];
    char directory[DIR_MAX] = "saves/";
    FILE *file;

    strncat(directory, filename, DIR_MAX);

    file = fopen(directory, "r");

    for(int i = 0; i < 8; i ++) {
        fgets(charRow, 99, file);
        charToSpace(state, i, charRow);
    }

    fgets(charRow, 99, file);
    fgets(charRow, 99, file);

    if (charRow[1] == '\0'){
        state->current_player = 1;
        state->move_count = 0;
        state->last_play.row = 3;
        state->last_play.column = 4;
        print_board(state, stdout);
    }

    else {
        state->move_count = 0;

        for(int i = 0; charRow[1] != '\0'; i++){
            state->moves[i].player1.row = charRow[7] - '1';
            state->moves[i].player1.column = charRow[6] - 'a';

            if (charRow[8] == '\0') {
                state->current_player = 2;
                state->last_play.row = charRow[7] - '1';
                state->last_play.column = charRow[6] - 'a';
            }

            else {
                state->moves[i].player2.row = charRow[10] - '1';
                state->moves[i].player2.column = charRow[9] - 'a';
                state->last_play.row = charRow[10] - '1';
                state->last_play.column = charRow[9] - 'a';
            }

            state->move_count += 1;
            fgets(charRow, 99, file);
        }

        print_board(state, stdout);
    }
}
