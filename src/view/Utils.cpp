//
// Created by pc-andre on 4/26/26.
//

#include "Utils.h"
#include <iostream>
#include <limits>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int readInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [ERRO] Opcao invalida. Introduza um numero entre "
                  << min << " e " << max << ".\n";
    }
}

void pause() {
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.get();
}