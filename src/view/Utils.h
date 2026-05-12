//
// Created by pc-andre on 4/26/26.
//

#ifndef FSOFT2026_1DD_1_UTILS_H
#define FSOFT2026_1DD_1_UTILS_H


#include <string>

void clearScreen(); //Uma função simples que limpa o ecrã para os menus não ficarem acumulados.
int readInt(const std::string& prompt, int min, int max); //Garante que o programa só avança quando o utilizador digita um número válido
void pause();
#endif //FSOFT2026_1DD_1_UTILS_H