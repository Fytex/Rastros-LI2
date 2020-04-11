#ifndef RASTROS_LI2_LINKED_H
#define RASTROS_LI2_LINKED_H

#include "../data/state.h"

typedef struct List{

    void* pos;
    struct List* next;

} List;

List* create_pos_list(const State* state);

void* give_back_head(List* L);

List* remove_head(List* L);

#endif //RASTROS_LI2_LINKED_H
