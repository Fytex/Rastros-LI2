//
// Created by fytex on 3/9/20.
//

#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "../data/state.h"
#include "../logic/game.h"

#define BUF_SIZE 1024

void print_board(State state) {

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