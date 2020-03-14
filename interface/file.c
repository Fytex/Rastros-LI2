//
// Created by fytex on 3/13/20.
//

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../data/state.h"
#include "board.h"

#define DIR_MAX 261 // 255 (File name) + 6 (saves/)

/*
 * Escreve para o ficheiro indicado
 */

void write_to_file(State *state, char *filename){

    char directory[DIR_MAX] = "saves/";
    FILE *file;

    mkdir("saves/", 0777); // Creates directory if not exists giving permission to every user

    strncat(directory, filename, DIR_MAX);

    file = fopen(directory, "w");

    print_board(state, file);
    puts("File created\n");

    fclose(file);

}