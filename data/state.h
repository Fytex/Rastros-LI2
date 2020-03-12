

#ifndef RASTROS_LI2_STATE_H
#define RASTROS_LI2_STATE_H

typedef enum {Blank, Black, White} Space;

typedef struct {
    int column;
    int row;
} Position;

typedef struct {
    Position player1;
    Position player2;
} Move;

typedef Move Moves[32];

typedef struct {
    Space board[8][8];
    Position last_play;
    Moves moves;
    int move_count;
    unsigned int current_player;
} State;

State *initialize_state();
void make_move(State* state, Position pos);
void swap_players(State* state);
//int get_current_player(State *state);
//int get_move_count(State *state);
//int get_state_space(State *e, Position c);

#endif //RASTROS_LI2_STATE_H
