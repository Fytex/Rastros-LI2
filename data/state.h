/**
@file state.h
Definição do estado e das funções que o manipulam.
*/

#ifndef RASTROS_LI2_STATE_H
#define RASTROS_LI2_STATE_H

/**
\brief Tipo de espaço no tabuleiro.
*/
typedef enum {Blank, Black, White} Space;

/**
\brief Tipo de dados das coordenadas no tabuleiro.
*/
typedef struct {
    int column;
    int row;
} Position;

/**
\brief Tipo de dados da jogada.
*/
typedef struct {
    Position player1;
    Position player2;
} Move;

/**
\brief Tipo de dados para as jogadas.
*/
typedef Move Moves[32];

/**
\brief Tipo de dados do estado do jogo.
*/
typedef struct {
    Space board[8][8];
    Position last_play;
    Moves moves;
    int move_count;
    unsigned int current_player;
} State;

/**
\brief Inicializa o valor do estado
Esta função inicializa o valor do estado. Isso implica o tabuleiro ser colocado na posição inicial e todos os campos do estado estarem com o valor por omissão.
@returns O novo estado
*/
State *initialize_state();

/**
\brief Esta função faz a jogada.
@param state Apontador para o estado
@param pos Posição da última jogada
*/
void make_move(State *state, Position pos);

/**
\brief Esta função troca o jogador a jogar.
@param state Apontador para o estado
@returns O próximo jogador a jogar
*/
unsigned int swap_players(State *state);

/**
\brief Esta função obtém o jogador atual
@param state Apontador para o estado 
@returns O jogador atual
*/
unsigned int get_current_player(State *state);

/**
\brief Esta função obtém o número de jogadas
@param state Apontador para o estado 
@returns O número de jogadas
*/
int get_move_count(State *state);

/**
\brief Esta função obtém a última jogada realizada
@param state Apontador para o estado 
@returns A última jogada
*/
Position get_last_play(State *state);

/**
\brief Esta função obtém uma certa jogada
@param state Apontador para o estado 
@param idx Número da jogada
@returns A jogada para esse dado valor
*/
Move get_move(State *state, int idx);

/**
\brief Esta função obtém o tipo de espaço do tabuleiro para uma dada coordenada
@param state Apontador para o estado 
@param pos Coordenada
@returns O tipo de espaço da coordenada
*/
Space get_position_space(State *state, Position pos);

#endif //RASTROS_LI2_STATE_H
