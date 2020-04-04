#include <stdlib.h>
#include "../data/state.h"

typedef struct List{

    Position pos;
    struct List* next;

} List;


List* create_list() {

   return malloc(sizeof(List));

}

List* head_insert(List* const L, const Position value) {

    List* new = malloc(sizeof(List));

    new->pos.column = value.column;
    new->pos.row = value.row;
    new->next = L;

    return new;

}

Position* give_back_head(List* const L) {

    return &(L->pos);

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