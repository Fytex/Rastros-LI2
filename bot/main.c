#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "io_file.h"
#include "flood_fill.h"

typedef struct {
    int wins;
    int loses;
    int status;
} TreeInfo;


int generate_possible_positions(int* const possible_positions, int flat_board[64], int last_play) {
    const int sum_pos[8] = {9, 8, 7, 1, -1, -7, -8, -9};
    int length = 0, pos;

    for (int i=0; i < 8; ++i) {
        pos = last_play + sum_pos[i];
        // ((abs(pos % 8 - last_play % 8) <= 1 && abs(pos / 8 - last_play / 8) <= 1)
        if (pos >= 0 && pos < 64 &&
        (abs((pos & 7) - (last_play & 7)) <= 1 && abs((pos >> 3) - (last_play >> 3)) <= 1) &&
            flat_board[pos] == -1)
            possible_positions[length++] = pos;
    }

    return length;
}

int can_brute_force(int* _flat_board, int last_play) {
    const int sum_pos[8] = {9, 8, 7, 1, -1, -7, -8, -9};
    int layer_pos_idx[64];
    int layer = 0;
    int *space, pos, pos_iter = 0;
    int total = 0;
    int flat_board[64];


    int bytes = sizeof(int) * 64;
    memset(layer_pos_idx, -1, bytes);
    memcpy(flat_board, _flat_board, bytes); // This copy so if returns early it won't cause problems


    while (layer >= 0) {

        for ( ; pos_iter < 8; ++pos_iter) {
            pos = last_play + sum_pos[pos_iter];
            space = flat_board + pos;
            if (pos < 64 && pos >= 0 &&
                // (abs(pos % 8 - last_play % 8) <= 1 && abs(pos / 8 - last_play / 8) <= 1)
                (abs((pos & 7) - (last_play & 7)) <= 1 && abs((pos >> 3) - (last_play >> 3)) <= 1) && *space != -2) {

                ++total;

                if (*space == -1) {
                    *space = last_play;
                    layer_pos_idx[layer++] = pos_iter;
                    break;
                }
            }

        }
        if (pos_iter == 8 && --layer >= 0) {
            last_play = flat_board[last_play];
            pos_iter = ++layer_pos_idx[layer];
        } else {
            pos_iter = 0;
            last_play = pos;
        }
    }
    return total <= 115;
}



int get_space_winner(int pos, int player) {
    if (pos == 7)
        return -((~player + 2) | 1);
    else if (pos == 58)
        return (~player + 2) | 1;
    else
        return 0;
}



TreeInfo brute_force(int _flat_board[64], const int player, int last_play, int best_status) {

    int space_winner;
    int pos_iter = 0, pos;
    int layer = 0; // Layer 0 represents the play that jog will make
    int* space = NULL;
    int* pos_last_play;
    int flat_board[64];
    const int sum_pos[8] = {9, 8, 7, 1, -1, -7, -8, -9};
    int layer_pos_idx[64];
    TreeInfo tree_info = {.wins = 0, .loses = 0, .status = 0};

    int bytes = sizeof(int) * 64;
    memset(layer_pos_idx, -1, bytes);
    memcpy(flat_board, _flat_board, bytes); // This copy so if returns early it won't cause problems


    while (layer >= 0) {

        for ( ; pos_iter < 8; ++pos_iter) {
            pos = last_play + sum_pos[pos_iter];
            space = flat_board + pos;
            if (pos < 64 && pos >= 0 &&
            // (abs(pos % 8 - last_play % 8) <= 1 && abs(pos / 8 - last_play / 8) <= 1)
            (abs((pos & 7) - (last_play & 7)) <= 1 && abs((pos >> 3) - (last_play >> 3)) <= 1) && *space == -1) {
                *space = last_play;
                layer_pos_idx[layer] = pos_iter;
                break;
            }
        }


        if (pos_iter == 8 ) { // we increment pos_iter before we break
            if (layer_pos_idx[layer] == -1) {

                if (layer & 1)
                    ++tree_info.loses;
                else
                    ++tree_info.wins;

            }

            if (layer >= 0){ // avoid causing SegFault at layer 0
                pos_last_play = flat_board + last_play;

                layer_pos_idx[layer--] = -1;
                last_play = *pos_last_play;
                *pos_last_play = -1;
                pos_iter = ++layer_pos_idx[layer];

            }
        }

        else {

            space_winner = get_space_winner(pos, player);

            if (space_winner == 1)
                ++tree_info.wins;

            else if (space_winner == -1) {

                if (layer == 0) { // Really bad
                    tree_info.status = -2;
                    return tree_info;
                    }

                else if (layer == 2) { // Really bad

                    tree_info.status = -1;

                    // If the status before is above -1 there is no need to continue searching because this move will never b chosen
                    if (best_status > -1)
                        return tree_info;
                }

                ++tree_info.loses;
            }

            else {
                ++layer;
                pos_iter = 0;
                last_play = pos;
                continue;
            }

            *space = -1;
            ++pos_iter;
        }
    }

    return tree_info;
}


int main(int argc, char** argv) {

    int possible_positions[8];
    //Position last_play = state->last_play;
    char* last_play;
    int flat_board[64];
    char moves[64][3];
    int moves_count;
    int *space;
    //int last_position = last_play.row * 8 + last_play.column;
    int last_position;
    int pos;
    int best_position;
    int total;
    int space_winner;
    int player;
    
    TreeInfo tree, best_tree = {.wins = 0, .loses = INT_MAX, .status = -2};

    moves_count = bot_read(flat_board, moves, argv[1]);

    if (moves_count) {
        last_play = moves[moves_count - 1];
        last_position = ('8' - last_play[1]) * 8 + (last_play[0] - 'a');
    } else
        last_position = 28;

    player = (moves_count & 1) + 1;


    if (can_brute_force(flat_board, last_position)) {

    /*
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col) {
            flat_board[row * 8 + col] = state->board[row][col] == Blank ? -1 : -2;
        }
    */


        total = generate_possible_positions(possible_positions, flat_board, last_position);

        for (int i = 0; i < total; ++i) { // test 1 cases wins
            pos = *(possible_positions + i);
            space_winner = get_space_winner(pos, player);

            if (space_winner == 1) {
                bot_write(flat_board, moves, moves_count, pos, argv[2]);
                return 1;
            }
            else if (space_winner == -1)
                *(possible_positions + i) = -1;
        }

        best_position = *possible_positions; // first move (to prevent not playing if next player's move is a loss)

        for (int i = 0; i < total; ++i) {
            pos = *(possible_positions + i);

            if (pos != -1) {

                space = flat_board + pos;
                *space = -2;
                tree = brute_force(flat_board, player, pos, best_tree.status);

                if (!best_tree.wins || tree.status > best_tree.status || (tree.wins && tree.status == best_tree.status &&
                                                                        ((!tree.loses && best_tree.loses) ||
                                                                        tree.wins - tree.loses >= best_tree.wins -
                                                                                                 best_tree.loses))) { // Division or Subtraction?
                    best_tree = tree;
                    best_position = pos;
                }

                *space = -1;
            }
        }
    }

    else {
        best_position = flood_fill(flat_board, player, last_position);
        flat_board[best_position] = -2;
    }



    bot_write(flat_board, moves, moves_count, best_position, argv[2]);

    return 1;

}
