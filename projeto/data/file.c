#ifdef WIN32
    // Windows OS
    int mkdir(const char *pathname, mode_t mode); // It avoids displaying warning compiling on mingw (Windows)
#endif

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "state.h"
#include "../interface/board.h"
#include "list_contents/OS_list.h"

#define DIR_MAX 261 // 255 (File name) + 6 (saves/)
#define BUFFER_LINE 11 // Each line from file contains a max of 10 chars + 1 (End of string)
#define DIR "saves/"


/*
 * Write to the indicated file
 */

void write_to_file(const State* const state, const char* const filename){

    char directory[DIR_MAX] = DIR;
    FILE *file;

    mkdir(DIR, 0777); // Creates directory if not exists giving permission to every user

    strncat(directory, filename, DIR_MAX - 1);

    file = fopen(directory, "w");

    print_board(state, file);

    fclose(file);

}


/*
 * Convertes caracters in the typer of space in the board
 */

void line_to_board(State* state, const int row, const char* const line){
    Position pos;

    for(int col = 0; col < 8; ++col){

        pos = (Position) {.row = row, .column = col};

        if (line[col] == '1' || line[col] == '2')
            edit_position_space(state, pos, Blank);
        else
            edit_position_space(state, pos, line[col]);

    }
}


/*
 * Reads information from a file
 */

int read_from_file(State* const state, const char* const filename){
    char file_line[BUFFER_LINE];
    char directory[DIR_MAX] = DIR;
    int count=0;
    FILE * file;
    Position pos1, pos2;
    Move move;

    strncat(directory, filename, DIR_MAX - 1);

    file = fopen(directory, "r");

    if (!file)
        return 0;

    for(int row = 0; row < 8; ++row) {
        if (fgets(file_line, BUFFER_LINE, file)!= NULL)
        line_to_board(state, row, file_line);
    }

    edit_current_player(state, 2);

    if (fgets(file_line, BUFFER_LINE, file)) { // if the file doesn't end (and skips one line)

        for ( ; fgets(file_line, BUFFER_LINE, file); ++count) {

            if (file_line[6] && file_line[7]) { // file_line[6] is '\0' if no second Position in Move
                pos1 = (Position) {.row = '8' - file_line[5], .column = file_line[4] - 'a'};
                pos2 = (Position) {.row = '8' - file_line[8], .column = file_line[7] - 'a'};
                move = (Move) {.player1 = pos1, .player2 = pos2};

                edit_move(state, count, move);
                edit_last_play(state, pos2);
            }
            else {
                pos1 = (Position) {.row = '8' - file_line[5], .column = file_line[4] - 'a'};
                edit_last_play(state, pos1);

                edit_current_player(state, 1);
                --count;
            }
        }
    }
    else {
        pos2 = (Position) {.row = 3, .column = 4}; // pos2 is in reality the first position of the game
        edit_last_play(state, pos2);
    }

    fclose(file);
    edit_move_count(state, count);
    return 1;
}


/*
 * Prints every file in /saves (ls command)
 */

void print_dir_contents() {
    print_OS_dir_contents(DIR);
}