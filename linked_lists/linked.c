#include <stdlib.h>
#include "linked.h"
#include "../data/state.h"

List* create_list() {

   return malloc(sizeof(List));

}

List* head_insert(List* const L, void* value) {
    List* new = malloc(sizeof(List));

    new->pos = value;
    new->next = L;

    return new;

}

void* give_back_head(List* const L) {

    return (L->pos);

}

List* remove_head(List* const L) {

    List* pointer = L;

    if (L) {
        pointer = L->next;
        free(L);
    }

    return pointer;

}

int empty_list (const List* const L){

    return L ? 1 : 0;

}


List* create_pos_list (const State* const state){

    const int sum_pos[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    const Position last_play=get_last_play(state);
    List* position_list = NULL;

    position_list = create_list();

    for (int i=0; i < 8; ++i) {
        Position *pos;
        pos->row = last_play.row + sum_pos[i][0];//(Position) {.row = last_play.row + sum_pos[i][0], .column = last_play.column + sum_pos[i][1]};
        pos->column = last_play.column + sum_pos[i][1];

        if (pos->row >= 0 && pos->row < 8 && pos->column >= 0 && pos->column < 8 &&
            get_position_space(state, *pos) == Blank) {

            position_list = head_insert(position_list, pos);
        }

    }
    return position_list;
}

