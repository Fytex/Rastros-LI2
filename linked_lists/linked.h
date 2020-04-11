#ifndef RASTROS_LI2_LINKED_H
#define RASTROS_LI2_LINKED_H

#include "../data/state.h"

typedef struct List{

    void* pos;
    struct List* next;

} List;

List* create_list();

void* get_head(List* L);

List* head_insert(List* L, void* value);

List* remove_head(List* L);

#endif //RASTROS_LI2_LINKED_H
