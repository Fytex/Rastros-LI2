/**
@file state.h
Definição do estado e das funções que o manipulam
*/

#ifndef RASTROS_LI2_STATE_H
#define RASTROS_LI2_STATE_H

/*!É uma enumeração das possiveis casas do tabuleiro*/
typedef enum {
    Blank = '.', /*!< Reprensenta uma casa vazia*/
    Black = '#', /*!< Reprensenta uma casa ocupada*/
    White = '*'  /*!< Reprensenta a casa atual*/
} Space;

/**
 * @struct Position
 * @brief Tipo de dados das coordenadas no tabuleiro
 * @var Position::column
 * Membro 'column' contém a coordenada y
 * @var Position::row
 * Membro 'row' contém a coordenada x
*/
typedef struct {
    int column;
    int row;
} Position;

/**
\brief Posição inicial no tabuleiro
 */
extern const Position BEGIN_POS;

/**
 * @struct Move
 * @brief Tipo de dados da jogada
 * @var Move::player1
 * Membro 'player1' contém a jogada do jogador 1
 * @var Move::player2
 * Membro 'player2' contém a jogada do jogador 2
*/
typedef struct {
    Position player1;
    Position player2;
} Move;

/**
\brief Tipo de dados para as jogadas
*/
typedef Move Moves[32];

/**
 * @struct State
 * @brief Tipo de dados do estado do jogo
 * @var State::board
 * Membro 'board' contém o tabuleiro do jogo
 * @var State::last_play
 * Membro 'last_play' contém a última jogada feita
 * @var State:moves
 * Membro 'moves' contém todas as jogadas realizadas
 * @var State::move_count
 * Membro 'count' contém o número de jogadas realizadas
 * @var State::current_player
 * Membro 'current_player' contém o jogador que irá jogar a próxima jogada
*/
/**
\brief Tipo de dados do estado do jogo
*/
typedef struct {
    Space board[8][8];
    Position last_play;
    Moves moves;
    int move_count;
    unsigned int current_player;
} State;

/**
\brief Troca o jogador a jogar
@param state Apontador para o estado
@returns O próximo jogador a jogar
*/
unsigned int swap_players(State* state);

/**
\brief Obtém o jogador atual
@param state Apontador para o estado 
@returns O jogador atual
*/
unsigned int get_current_player(const State* state);

/**
\brief Obtém o número de jogadas
@param state Apontador para o estado 
@returns O número de jogadas
*/
int get_move_count(const State* state);

/**
\brief Obtém a última jogada realizada
@param state Apontador para o estado 
@returns A última jogada
*/
Position get_last_play(const State* state);

/**
\brief Obtém uma certa jogada
@param state Apontador para o estado 
@param idx Número da jogada
@returns A jogada para esse dado valor
*/
Move get_move(const State* state, int idx);

/**
\brief Obtém o tipo de espaço do tabuleiro para uma dada coordenada
@param state Apontador para o estado 
@param pos Coordenada
@returns O tipo de espaço da coordenada
*/
Space get_position_space(const State* state, Position pos);

/**
\brief Altera o tipo de espaço numa dada coordenada do tabuleiro
@param state Apontador para o estado
@param pos Coordenada
@param space Tipo de espaço
*/
void edit_position_space(State* state, Position pos, Space space);

/**
\brief Altera o jogador a jogar
@param state Apontador para o estado
@param player Jogador para o qual altera
*/
void edit_current_player(State* state, unsigned int player);

/**
\brief Adiciona uma jogada no array do estado com a lista de jogadas realizadas
@param state Apontador para o estado
@param move Jogada a adicionar
*/
void append_move(State* state, Move move);

/**
\brief Altera a coordenada da última jogada realizada
@param state Apontador para o estado
@param pos Coordenadas da última jogada
*/
void edit_last_play(State* state, Position pos);

/**
\brief Altera o contador do número de jogadas realizadas
@param state Apontador para o estado
@param count Número de jogadas realizadas
*/
void edit_move_count(State* state, int count);

/**
\brief Altera a jogada na posição indicada do array de jogadas do estado
@param state Apontador para o estado
@param idx Posição a alterar no array de jogadas
@param move Jogada
*/
void edit_move(State* state, int idx, Move move);

/**
\brief Altera o estado do jogo para o estado inicial
@param state Apontador para o estado
*/
void set_default_state(State* state);

#endif //RASTROS_LI2_STATE_H
