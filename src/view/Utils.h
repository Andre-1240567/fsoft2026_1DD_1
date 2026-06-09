//
// Created by pc-andre on 4/26/26.
//

#ifndef FSOFT2026_1DD_1_UTILS_H
#define FSOFT2026_1DD_1_UTILS_H


#include <string>

void clearScreen(); //Uma função simples que limpa o ecrã para os menus não ficarem acumulados.
int readInt(const std::string& prompt, int min, int max); //Garante que o programa só avança quando o utilizador digita um número válido

bool isValidPhone(const std::string& phone);
bool isValidCC(const std::string& cc);
bool isValidDate(const std::string& date);
bool isValidTime(const std::string& time);
bool isValidEmail(const std::string& email);

std::string readPhone(const std::string& prompt);
std::string readCC(const std::string& prompt);
std::string readDate(const std::string& prompt);
std::string readTime(const std::string& prompt);
std::string readEmail(const std::string& prompt);
void pauseConsole();
#endif //FSOFT2026_1DD_1_UTILS_H
