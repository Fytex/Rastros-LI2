//
// Created by fytex on 3/13/20.
//

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "state.h"
#include "../interface/board.h"

#define DIR_MAX 261 // 255 (File name) + 6 (saves/)
#define BUFFER_LINE 12 // Each line from file contains a max of 11 chars + 1 (End of string)

/*
 * Write to the indicated file
 */

void write_to_file(State *state, char *filename){

    char directory[DIR_MAX] = "saves/";
    FILE *file;

    mkdir("saves/", 0777); // Creates directory if not exists giving permission to every user

    strncat(directory, filename, DIR_MAX);

    file = fopen(directory, "w");

    print_board(state, file);

    fclose(file);
    puts("File created\n");
}




void line_to_board(State *state, int row, const char *line){

    for(int col = 0; col < 8; col++){
        switch(line[col]) {

            case ('#'):
                state->board[row][col] = Black;
                break;

            case ('*'):
                state->board[row][col] = White;
                break;

            default: state->board[row][col] = Blank; // 1 and 2 spaces will always be Blank because they can't save a finished game
        }
    }
}


void read_from_file(State *state, char *filename){
    char file_line[BUFFER_LINE];
    char directory[DIR_MAX] = "saves/";
    int count=0;
    FILE *file;

    strncat(directory, filename, DIR_MAX);

    file = fopen(directory, "r");

    for(int row = 0; row < 8; row ++) {
        fgets(file_line, BUFFER_LINE, file);
        line_to_board(state, row, file_line);
    }

    state->current_player = 2; // Represents last player to make a move. Changed later if was the first one

    if (fgets(file_line, BUFFER_LINE, file)) { // if the file doesn't end (and skips one line)

        for ( ; fgets(file_line, BUFFER_LINE, file); count++) {

            if (file_line[7]) { // file_line[7] is '\0' if no second Position in Move
                state->moves[count].player1.column = file_line[5] - 'a';
                state->moves[count].player1.row = file_line[6] - '1';
                state->last_play.column = state->moves[count].player2.column = file_line[8] - 'a';
                state->last_play.row = state->moves[count].player2.row = file_line[9] - '1';
            }
            else {
                state->last_play.column = file_line[5] - 'a';
                state->last_play.row = file_line[6] - '1';
                state->current_player = 1; // Represents last player to make a move.
            }
        }
    }
    else {
        state->last_play.row = 3;
        state->last_play.column = 4;
    }

    fclose(file);
    state->move_count = count;
}
