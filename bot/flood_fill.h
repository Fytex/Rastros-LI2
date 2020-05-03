//
// Created by fytex on 5/3/20.
//

#ifndef BOT_FLOOD_FILL_H
#define BOT_FLOOD_FILL_H

/**
\brief Executa o algoritmo flood fill caso não tenha ligação à casa destino utiliza a distância euclidiana
@param flat_board Apontador para o vetor numérico
@param player Jogador em questão
@param last_play Última jogada
*/
int flood_fill(int* flat_board, int player, int last_play);

#endif //BOT_FLOOD_FILL_H
