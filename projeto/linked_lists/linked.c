#include <stdlib.h>
#include "linked.h"

/*
 * Creates a list
 */
List* create_list() {

    List* l = NULL;

    return l;

}

/*
 * Inserts in the head of the list
 */
List* head_insert(List* const L, void* value) {
    List* new = malloc(sizeof(List));

    new->pos = value;
    new->next = L;

    return new;

}

/*
 * Gets the head of the list
 */
void* get_head(List* const L) {

    return L->pos;

}

/*
 * Removes the head of the list
 */
List* remove_head(List* const L) {

    List* pointer = L;

    if (L) {
        pointer = L->next;
        free(L);
    }

    return pointer;

}

/*
 * Clears the information in the list
 */
List*  clear_list (List* L) {

    while (L != NULL)
        L = remove_head(L);

    return L;
}

/*
 * Confirms if it is an empty list or not
 */
int empty_list (const List* const L){

    return L ? 1 : 0;

}
