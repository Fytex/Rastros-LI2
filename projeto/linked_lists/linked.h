/**
@file linked.h
        Definição das funções que criam e alteram listas ligadas
*/

#ifndef RASTROS_LI2_LINKED_H
#define RASTROS_LI2_LINKED_H

#include "../data/state.h"

/**
\brief Tipo de dados de uma lista ligada
*/
typedef struct List{

    void* pos;
    struct List* next;

} List;

/**
\brief Cria uma lista ligada
*/
List* create_list();

/**
\brief Obtém a cabeça de uma lista ligada
 @param L Apontador para uma lista ligada
*/
void* get_head(List* L);

/**
\brief Insere um elemento à cabeça de uma lista ligada
 @param L Apontador para uma lista ligada
 @param value Apontador para o elemento a adicionar
 @returns A lista ligada depois de adicionar o elemento à cabeça
*/
List* head_insert(List* L, void* value);

/**
\brief Remove o elemento na cabeça de uma lista ligada
 @param L Apontador para uma lista ligada
 @returns A lista ligada depois de remover a cabeça
*/
List* remove_head(List* L);

/**
\brief Remove o elemento na cabeça de uma lista ligada
 @param L Apontador para uma lista ligada
 @returns A lista ligada depois de limpar a informação
*/
List* clear_list (List* L);

/**
\brief Confirma se a lista é vazia ou não
 @param L Apontador para uma lista ligada
*/
int empty_list(const List* L);

#endif //RASTROS_LI2_LINKED_H
