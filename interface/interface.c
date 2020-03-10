

#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "../data/state.h"
#include "../logic/game.h"

#define BUF_SIZE 1024

void typeSpace(Space p) {
    switch(p) {
        case (Blank):
            printf(". ");
            break;
        case (Black):
            printf("# ");
            break;
        case (White):
            printf("* ");
            break;
    }
}



void print_board(State state) {

    for(int i = 0; i < 8; i++) {
        printf("%d\t", i + 1);

        if (i == 7)
            printf("1 ");

        for(int j = 0; j < 8; j++)
            if ((i != 0 || j != 7) && (i != 7 || j != 0))
                typeSpace(state.board[i][j]);

        if ( i == 0)
            printf("2");

        puts("");
    }

    printf("\n\t");

    for(int i = 0; i < 8; i ++)
        printf("%c ", 'A' + i);
}


int interpreter(State *state) {
    char line[BUF_SIZE];
    char col[2], row[2];

    if (fgets(line, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(line) == 3 && sscanf(line, "%[a-h]%[1-8]", col, row) == 2) {
        Position pos = {*col -'a', *row -'1'};
        play(state, pos);
        print_board(*state);
    }

    return 1;
}
