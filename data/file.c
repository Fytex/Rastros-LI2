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
    Position pos;

    for(int col = 0; col < 8; col++){

        pos = (Position) {.row = row, .column = col};

        if (line[col] == '1' || line[col] == '2')
            edit_position_space(state, pos, Blank);
        else
            edit_position_space(state, pos, line[col]);

    }
}


void read_from_file(State *state, char *filename){
    char file_line[BUFFER_LINE];
    char directory[DIR_MAX] = "saves/";
    int count=0;
    FILE *file;
    Position pos1, pos2;
    Move move;

    strncat(directory, filename, DIR_MAX);

    file = fopen(directory, "r");

    for(int row = 0; row < 8; row ++) {
        fgets(file_line, BUFFER_LINE, file);
        line_to_board(state, row, file_line);
    }

    edit_current_player(state, 2); // Represents last player to make a move. Changed later if was the first one

    if (fgets(file_line, BUFFER_LINE, file)) { // if the file doesn't end (and skips one line)

        for ( ; fgets(file_line, BUFFER_LINE, file); count++) {

            if (file_line[7]) { // file_line[7] is '\0' if no second Position in Move
                pos1 = (Position) {.row = file_line[6] - '1', .column = file_line[5] - 'a'};
                pos2 = (Position) {.row = file_line[9] - '1', .column = file_line[8] - 'a'};
                move = (Move) {.player1 = pos1, .player2 = pos2};

                edit_move(state, count, move);
                edit_last_play(state, pos2);
            }
            else {
                pos1 = (Position) {.row = file_line[6] - '1', .column = file_line[5] - 'a'};
                edit_last_play(state, pos1);

                edit_current_player(state, 1); // Represents last player to make a move.
            }
        }
    }
    else {
        pos2 = (Position) {.row = 3, .column = 4}; // pos2 is in reality the first position of the game
        edit_last_play(state, pos2);
    }

    fclose(file);
    edit_move_count(state, count);
}
