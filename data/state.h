

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
void make_move(State *state, Position pos);

unsigned int swap_players(State *state);
unsigned int get_current_player(State *state);
int get_move_count(State *state);

Position get_last_play(State *state);
Move get_move(State *state, int idx);
Space get_position_space(State *state, Position pos);

#endif //RASTROS_LI2_STATE_H
