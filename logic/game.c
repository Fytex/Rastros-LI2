//
// Created by fytex on 3/9/20.
//

#include <stdio.h>
#include "game.h"
#include "../data/state.h"


int play(State *state, Position pos) {
    printf("jogar %d %d\n", pos.column, pos.row);
    return 1;
}