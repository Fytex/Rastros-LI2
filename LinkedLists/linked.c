#include <stdlib.h>
#include "linked.h"
#include "../data/state.h"

typedef struct list *LIST;

struct list {

    Position pos;
    LIST prox;

};

LIST create_list() {

   LIST list = malloc(sizeof (struct list));

   return list;
}

LIST head_insert (LIST L , Position *value) {

   LIST new = malloc (sizeof(struct list));

    new->pos.column = value->column;
    new->pos.row = value->row;
    new->prox = L;

    return new;

}

Position* give_back_head (LIST L) {

    return (&(L->pos));

}

LIST remove_head (LIST L) {

    LIST res = NULL;

    if (L != NULL) {
        res = L->prox;
    }

    return res;

}

int empty_list (LIST L){

    int res = 0;

    if ( L != NULL)
        res = 1;
    return res;

}

