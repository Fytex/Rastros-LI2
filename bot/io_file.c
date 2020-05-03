#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LINE 11 // Each line from file contains a max of 10 chars + 1 (End of string)

// returns moves_count
int bot_read(int flat_board[64], char moves[64][3], const char* const filename){
    char file_line[BUFFER_LINE];
    char* line;
    int count=0;
    int moves_count = 0;
    char space;
    //char last_play[3] = "";
    FILE * file;

    file = fopen(filename, "r");

    for(int *pos = flat_board, row = 0; row < 8; ++row) {

        fgets(file_line, BUFFER_LINE, file);
        line = file_line;

        for(int col = 0; col < 8; ++col, ++pos, ++line){
            space = *line;
            if (space == '.' || space == '1' || space == '2')
                *pos = -1;
            else{
                ++moves_count;
                *pos = -2;
            }

        }
    }

    --moves_count;

    if (fgets(file_line, BUFFER_LINE, file)) { // if the file doesn't end (and skips one line)

        for ( ; fgets(file_line, BUFFER_LINE, file); ++count) {

            if (file_line[6]) { // file_line[6] is '\0' if no second Position in Move

                strncpy(*moves++, file_line + 4, 2);
                strncpy(*moves++, file_line + 7, 2);

            }
            else {
                strncpy(*moves, file_line + 4, 2);
            }
        }
    }

    fclose(file);
    return moves_count;
}




void bot_write(int flat_board[64], const char moves[64][3], const int moves_count , const int last_play, const char* const filename){

    FILE *file;
    int* last_play_p = flat_board + last_play;

    file = fopen(filename, "w");

    for (int row = 0; row < 8; ++row) {

        if (row == 7) {
            if (last_play == 56)
                putc('*', file);
            else
                fprintf(file, "1");
        }

        for (int col = 0; col < 8; ++col, ++flat_board)
            if (abs(row - col) != 7)
                putc((flat_board == last_play_p) ? '*' : ((*flat_board == -1) ? '.' : '#'), file);

        if (row == 0) {
            if (last_play == 7)
                putc('*', file);
            else
                putc('2', file);
        }

        fprintf(file, "\n");
    }

    int count = 0;

    fprintf(file ,"\n");


    for (int count_moves = moves_count >> 1 ; count < count_moves; ++count) {

        fprintf(file, "%02d: %.2s %.2s\n", count + 1,
                *moves, *(moves + 1));

        moves = moves + 2;
    }

    if (moves_count & 1)
        fprintf(file, "%02d: %.2s %c%d\n", count + 1, *moves, 'a' + (last_play & 7), 8 - (last_play >> 3));
    else
        fprintf(file, "%02d: %c%d\n", count + 1, 'a' + (last_play & 7), 8 - (last_play >> 3));
    fclose(file);

}
