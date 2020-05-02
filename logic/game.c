#include <stdlib.h>
#include "../data/state.h"
#include "../linked_lists/linked.h"

/*
 * Checks if play is valid
 */

int check_move(const State* const state, const Position pos){
    const Position last_play = get_last_play(state);

    return pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
        abs(last_play.row - pos.row) <= 1 && abs(last_play.column - pos.column) <= 1 &&
        get_position_space(state, pos) == Blank;

}


/*
 * Changes spaces from each move's position and appends move to moves' array
 */
void make_move(State* const state, const Position pos){
    unsigned int current_player = get_current_player(state);
    Position last_play = get_last_play(state);

    // Changes last move's position in the boarder to Black
    edit_position_space(state, last_play, Black);

    // Changes new move's position in the boarder to White
    edit_position_space(state, pos, White);

    if (current_player == 2) {
        Move move = {.player1 = last_play, .player2 = pos};
        append_move(state, move);
    }

    edit_last_play(state, pos);
}


/*
 * Changes state if played in a valid position
 */

int play(State* const state, const Position pos) {

    if (!check_move(state, pos))
        return 0;

    make_move(state, pos);

    return 1;
}

/*
 * Checks if game finished and returns the winner
 * Returns 0 in case game not finished yet
 */

unsigned int game_finished(const State* const state) {

    const int sum_pos[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    const Position last_play=get_last_play(state);
    Position pos;

    if (last_play.row - last_play.column == 7)
        return 1;
    else if (last_play.column - last_play.row == 7)
        return 2;

    for (int i=0; i < 8; ++i) {
        pos = (Position) {.row = last_play.row + sum_pos[i][0], .column = last_play.column + sum_pos[i][1]};

        if (pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
            get_position_space(state, pos) == Blank)
            return 0; // Game not finished yet
    }

    return get_current_player(state);
}


/*
 * Gives a random position
 */

Position RandomJog (State* state){
    const int sum_pos[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    const Position last_play=get_last_play(state);
    Position positions[8],pos;
    int length = 0;

    List* position_list = NULL;


    position_list = create_list();

    for (int i=0; i < 8; ++i) {
        pos = (Position) {.row = last_play.row + sum_pos[i][0], .column = last_play.column + sum_pos[i][1]};


        if (pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
            get_position_space(state, pos) == Blank) {

            positions[length] = pos;
            position_list = head_insert(position_list, positions + length);
            length++;
        }

    }
    int random = rand() % length;
    Position* jogpos = get_head(position_list);

    for (int j = 0 ; j< random ; j++)
        *jogpos = positions[j];


    return *jogpos;

}


/*
 * Does a random computer move
 */

void computer_move2 (State* const state){
    Position pos = RandomJog(state);
    make_move(state,pos);
}


/*
 * Reads the flood fill matrix, giving a position where to play in order to reach the objetive faster.
 */

Position reads_flood_fill_matrix(int flood_fill_matrix[][8], Position pos, int count) {
    const int sum_pos[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

    while(count != 1) {
        for(int i = 0; i < 8; i++) {
            if (pos.row + sum_pos[i][0] >= 0 && pos.row + sum_pos[i][0] < 8 && pos.column + sum_pos[i][1] >= 0 &&
                pos.column + sum_pos[i][1] < 8 &&
                flood_fill_matrix[pos.row + sum_pos[i][0]][pos.column + sum_pos[i][1]] == count - 1) {

                    pos.row = pos.row + sum_pos[i][0];
                    pos.column = pos.column + sum_pos[i][1];
                    break;
            }
        }
        count--;
    }
    return pos;
}


/*
 * Creates the flood fill matrix on a given state of the game, returning to best position to reach the objetive,.
 */

Position flood_fill(State* state, int flood_fill_matrix[][8] ,unsigned int player) {
    int count = 1;
    const int sum_pos[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    Position last_play[1];
    last_play[0] = get_last_play(state);
    Position positions[64], pos;
    Position* play;
    int length = 0;
    List* position_list1 = NULL;
    List* position_list2 = NULL;

    position_list1 = create_list();
    position_list2 = create_list();

    position_list1 = head_insert (position_list1, last_play);

    while (position_list1->next != NULL) {
        while (position_list1->next != NULL) {
            play = get_head(position_list1);

            for (int i = 0; i < 8; ++i) {
                pos = (Position) {.row = play->row + sum_pos[i][0], .column = play->column + sum_pos[i][1]};

                if ((unsigned) pos.column == (7 * (player - 1)) && (unsigned) pos.row == 7 - (7 * (player - 1))) {
                    flood_fill_matrix[pos.row][pos.column] = count;
                    return reads_flood_fill_matrix(flood_fill_matrix, pos, count);
                }

                if (pos.row >= 0 && pos.row < 8 && pos.column >= 0 && pos.column < 8 &&
                    flood_fill_matrix[pos.row][pos.column] == 0) {

                    positions[length] = pos;
                    position_list2 = head_insert(position_list2, positions + length);
                    flood_fill_matrix[pos.row][pos.column] = count;
                    length++;
                }
            }

            position_list1 = remove_head(position_list1);
        }

        position_list1 = position_list2;
        position_list2 = clear_list();
        count++;
    }
    return RandomJog(state); //in case of being impossible to reach the objetive, does a random play
}


/*
 * Does a computer move using the flood fill method
 */

void computer_move(State* const state){
    int flood_fill_matrix[8][8];

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            if (state->board[i][j] == Blank)
                flood_fill_matrix[i][j] = 0;
            else flood_fill_matrix[i][j] = -1;
        }
    }
    Position pos = flood_fill(state, flood_fill_matrix, get_current_player(state));
    make_move(state,pos);
}


