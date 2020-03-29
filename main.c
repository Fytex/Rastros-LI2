#include <stdlib.h>
#include "data/state.h"
#include "interface/interface.h"



void game_info() {
    puts("Objective :\n\n"
         "This game's objective is to take the white piece to your \"home\" named in the board with the numbers 1 or 2 (whether you are Player 1 or Player 2)."
         "\n\n\nRules and Victory:\n\n"
         "This game's rules are very simple."
         "You can only move the white piece (symbol is '*') to a place where there are no black pieces (which are represented by '#') and at a distance of 1 piece in all directions."
         "\nThe game ends if you are trapped, in other words, if every piece at a distance at 1 is a black piece, and your opponent wins because you run out of moves."
         "\nThe game also ends if one of the players reaches their \"home\"."
         "\n\n\nFunctionalities:\n\n"
         "It also has some functionalities like commands that you can access and learn by typing \"Help\" in game."
         "\n\n\nGame Developed by:\n\n"
         "Fytex  > github.com/fytex\n"
         "Shiiva > github.com/tiago885\n"
         "CJGNP  > github.com/cjgnp");
}


int main() {
    int cmd, cmd_error=0;
    unsigned int winner;
    State* state = initialize_state();

    if (!state)
        return 1;

    do {
        clear_terminal();

        puts("  __________                  __                       \n"
             "  \\______   \\_____    _______/  |________  ____  ______\n"
             "   |       _/\\__  \\  /  ___/\\   __\\_  __ \\/  _ \\/  ___/\n"
             "   |    |   \\ / __ \\_\\___ \\  |  |  |  | \\(  <_> )___ \\ \n"
             "   |____|_  /(____  /____  > |__|  |__|   \\____/____  >\n"
             "          \\/      \\/     \\/                         \\/");

        puts("\n\t0 - Exit"
        "\t1 - Play"
        "\t2 - Info");

        if (cmd_error) {
            puts("\n\nError: Command not Found");
            cmd_error = 0;
        }

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

    free(state); // Almost all OS do this when process finishes but lets take care by our own
    return 0;
}
