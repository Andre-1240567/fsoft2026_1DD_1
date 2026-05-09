//
// Created by pc-andre on 4/26/26.
//

#include "Utils.h"
#include <iostream>
#include <limits>
#include <conio.h> // Biblioteca para Windows

void clearScreen() {

    #ifdef _WIN32 //é uma diretiva do compilador. Usa o comando cls (do CMD do Windows). Se estiver em Linux ou Mac, usa o comando clear (do terminal Unix).
        system("cls");
    #else
        system("clear");
    #endif

    //std::cout << std::string(50, '\n');
}
int readInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt; // (ex: "Opcao: ")
        if (std::cin >> value && value >= min && value <= max) {
            //std::cin >> value: Tenta puxar algo para value
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // limpa o Buffer
            //Ignora o número máximo de caracteres possível (numeric_limits::max()) até encontrares o Enter (\n)". Ou seja, limpa o lixo todo.
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [ERRO] Opcao invalida. Introduza um numero entre "
                  << min << " e " << max << ".\n";
    }
}

void pause() {
    std::cout << "\nPressione qualquer tecla para continuar...";
    _getch();
}