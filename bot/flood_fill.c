#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


/*
 * Choses the adjacent position that is near from the objetive
 */
int arithmeticJog (int flat_board[64], unsigned int player, int last_play){
    const int sum_pos[8] = {9, 8, 7, 1, -1, -7, -8, -9};
    int pos;
    int dist;
    int min_dist = INT_MAX;
    int best_pos;
    int space_base = player - 1 ? 7 : 58;
    flat_board[player - 1 ? 58 : 7] = -1; // We changed to -2 inside flood fill but we must change it back in case there are no more spaces available

    for (int i=0; i < 8; ++i) {
        pos = last_play + sum_pos[i];


        if (pos >= 0 && pos < 64 && (abs((pos & 7) - (last_play & 7)) <= 1 && abs((pos >> 3) - (last_play >> 3)) <= 1) &&
        flat_board[pos] != -2) {

            dist = pow((space_base >> 3) - (pos >> 3), 2) + pow((space_base & 7) - (pos & 7), 2);
            if (dist < min_dist) {
                min_dist = dist;
                best_pos = pos;
            }

        }

    }

    return best_pos;

}


/*
 * Reads the flood fill matrix, giving a position where to play in order to reach the objective faster.
 */

int reads_flood_fill_matrix(int flat_board[64], int play, int count) {
    const int sum_pos[8] = {9, 8, 7, 1, -1, -7, -8, -9};
    int pos;
    --count;
    for ( ; count; --count) {
        for(int i = 0; i < 8; i++) {
            pos = play + sum_pos[i];
            if (pos >= 0 && pos < 64 && (abs((pos & 7) - (play & 7)) <= 1 && abs((pos >> 3) - (play >> 3)) <= 1)
            && flat_board[pos] == count) {
                play = pos;
                break;
            }
        }
    }
    return pos;
}


/*
 * Creates the flood fill matrix on a given state of the game, returning to best position to reach the objective.
 */

int flood_fill(int _flat_board[64], unsigned int player, int last_play) {
    int layer = 1;
    const int sum_pos[8] = {9, 8, 7, 1, -1, -7, -8, -9};
    int _base[64]; // Don't need so much but let's be careful
    int _top[64]; // Don't need so much but let's be careful
    int base_count = 0;
    int top_count = 0;
    int play;
    int pos;
    int* base = _base;
    int* top = _top;
    int* temp;
    int flat_board[64];

    memcpy(flat_board, _flat_board, sizeof(int) * 64); // This copy so if returns early it won't cause problems

    base[base_count++] = last_play;

    flat_board[player - 1 ? 56 : 7] = -2;
    flat_board[last_play] = 0;

    while (base_count) {
        for (int count = 0; count < base_count; ++count) {
            play = base[count];

            for (int pos_iter = 0; pos_iter < 8; ++pos_iter) {
                pos = play + sum_pos[pos_iter];
                if (pos >= 0 && pos < 64 && (abs((pos & 7) - (play & 7)) <= 1 && abs((pos >> 3) - (play >> 3)) <= 1)) {

                    if ((pos == 7 && player == 2) || (pos == 56 && player == 1)) {

                        if (layer == 1)
                            return pos;

                        flat_board[pos] = layer;
                        return reads_flood_fill_matrix(flat_board, pos, layer);
                    } else if (flat_board[pos] == -1) {

                        top[top_count++] = pos;
                        flat_board[pos] = layer;
                    }
                }
            }
        }

        temp = base;
        base = top;
        top = temp;
        base_count = top_count;
        top_count = 0;
        ++layer;
    }

    return arithmeticJog(flat_board, player, last_play); //in case of being impossible to reach the objetive, does an arithmetic calculation
}