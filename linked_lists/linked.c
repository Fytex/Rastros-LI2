#include <stdlib.h>
#include "linked.h"

List* create_list() {

    List* l = malloc(sizeof(List));

    l->pos = NULL;
    l->next = NULL;

   return l;

}

List* head_insert(List* const L, void* value) {
    List* new = malloc(sizeof(List));

    new->pos = value;
    new->next = L;

    return new;

}

void* get_head(List* const L) {

    return L->pos;

}

List* remove_head(List* const L) {

    List* pointer = L;

    if (L) {
        pointer = L->next;
        free(L);
    }

    return pointer;

}


List* clear_list() {
   return create_list();
}


int empty_list (const List* const L){

    return L ? 1 : 0;

}
