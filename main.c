#include <stdlib.h>
#include "data/state.h"
#include "interface/interface.h"



void game_info() {
    puts("Objective :\n\n"
         "This game's objective is to take the white piece to your \"home\" named in the board with the numbers 1 or 2 (whether you are Player 1 or Player 2)."
         "\n\nRules and Victory:\n\n"
         "This game's rules are very simple."
         "You can only move the white piece (symbol is '*') to a place where there are no black pieces (which are represented by '#') and at a distance of 1 piece in all directions."
         "\nThe game ends if you are trapped, in other words, if every piece at a distance at 1 is a black piece, and your opponent wins because you run out of moves."
         "\nThe game also ends if one of the players reaches their \"home\"."
         "\n\nFunctionalities:\n\n"
         "It also has some functionalities like commands that you can access and learn by typing \"Help\" in game.");
}


int main() {
    int cmd, cmd_error=0;
    unsigned int winner;
    State* state = initialize_state();

    if (!state)
        return 1;

    do {
        clear_terminal();

        puts("\t\t\tRastros Game\n\n"
        "\t0 - Exit"
        "\t1 - Play"
        "\t2 - Info");

        if (cmd_error--) // sets back to 0
            puts("\nError: Command not Found\n");

        printf("\n> ");
        cmd = getchar();
        clear_stdin_buffer();

        clear_terminal();

        if (cmd == '1') {
            set_default_state(state);
            winner = interpreter(state);
        }

        else if (cmd == '2') {
            game_info();
            printf("\n\nPress enter to go back to menu...");
            clear_stdin_buffer();
        }

        else if (cmd != '0')
            cmd_error = 1;

        else
            break;

    } while (1);

    free(state);
    return 0;
}
