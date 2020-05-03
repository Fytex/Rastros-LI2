//
// Created by fytex on 5/3/20.
//

#ifndef RASTROS_LI2_IO_FILE_H
#define RASTROS_LI2_IO_FILE_H

/**
\brief Ler o ficheiro do jogo e fazer tradução
@param flat_board Apontador para o vetor numérico
@param filename Apontador para o nome do ficheiro
*/
int bot_read(int flat_board[64], char moves[64][3], const char* filename);

/**
\brief Escrever no ficheiro
@param flat_board Apontador para o vetor numérico
@param moves_count Número de jogadas
@param last_play Última jogada
@param filename Apontador para o nome do ficheiro
*/
void bot_write(int flat_board[64], char moves[64][3], int moves_count , int last_play, char* filename);


#endif //RASTROS_LI2_IO_FILE_H
