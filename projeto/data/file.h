/**
@file file.h
Funções que manipulam ficheiros de texto
*/

#ifndef RASTROS_LI2_FILE_H
#define RASTROS_LI2_FILE_H

#include "state.h"

/** Maior comprimento possivel do nome do ficheiro de destino */
#define DIR_MAX 261 // 255 (File name) + 6 (saves/)

/** Buffer de uma linha */
#define BUFFER_LINE 11 // Each line from file contains a max of 10 chars + 1 (End of string)

/** Directoria onde irá gravar os ficheiros */
#define DIR "saves/"

/**
\brief Escreve num ficheiro indicado a informacção do estado
@param state Apontador para o estado
@param filename Apontador para o nome do ficheiro
*/
void write_to_file(const State* state, const char* filename);

/**
\brief Lê um ficheiro indicado e altera a informação do estado pela do ficheiro
@param state Apontador para o estado
@param filename Apontador para o nome do ficheiro
@returns Sucesso da função
*/
int read_from_file(State* state, const char* filename);

/**
\brief Mostra todos o ficheiros na pasta saves/ (comando ls no terminal)
*/
void print_dir_contents();

/**
\brief Converte uma linha de caracteres no tipo de casa do tabuleiro nessa linha
@param state Apontador para o estado
@param row Linha do tabuleiro
@param line Linha de caracteres
*/
void line_to_board(State* state, const int row, const char* const line);

#endif //RASTROS_LI2_FILE_H
