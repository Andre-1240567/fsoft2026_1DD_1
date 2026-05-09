//
// Created by pc-andre on 4/26/26.
//

#include "MainMenu.h"
#include "Utils.h"
#include <iostream>
#include <string>


// ---- UC1 ----
void uc1_createVaccineType() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC1 - Criar Tipo de Vacina\n";
    std::cout << "========================================\n\n";

    std::string code, disease, description;
    std::cout << "Codigo      : "; std::getline(std::cin, code);
    std::cout << "Doenca      : "; std::getline(std::cin, disease);
    std::cout << "Descricao   : "; std::getline(std::cin, description);

    std::cout << "\n--- Confirmar dados ---\n";
    std::cout << "Codigo    : " << code        << "\n";
    std::cout << "Doenca    : " << disease     << "\n";
    std::cout << "Descricao : " << description << "\n";

    int confirm = readInt("\nConfirma? (1-Sim / 2-Nao): ", 1, 2);
    if (confirm == 1) {
        // TODO: VaccineTypeController::create(code, disease, description)
        std::cout << "\n[OK] Tipo de vacina registado!\n";
    } else {
        std::cout << "\n[INFO] Operacao cancelada.\n";
    }
    pause();
    }

// ---- UC2 ----
void uc2_registerPhysicalVaccine() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC2 - Registar Vacina Fisica\n";
    std::cout << "========================================\n\n";

    // TODO: mostrar tipos reais do repositorio
    std::cout << "Tipos disponiveis:\n";
    std::cout << "  1. COVID-19\n  2. Gripe\n  0. Cancelar\n";
    int typeChoice = readInt("Selecione o tipo: ", 0, 2);
    if (typeChoice == 0) return;

    std::cout << "\nTecnologias:\n";
    std::cout << "  1. mRNA\n  2. Viral Vector\n  3. Proteina Subunitaria\n";
    int techChoice = readInt("Selecione a tecnologia: ", 1, 3);

    std::string brand, lotNumber, expirationDate;
    std::cout << "\nMarca           : "; std::getline(std::cin, brand);
    std::cout << "Numero de Lote  : "; std::getline(std::cin, lotNumber);
    std::cout << "Data Validade   : "; std::getline(std::cin, expirationDate);

    std::cout << "\n--- Confirmar dados ---\n";
    std::cout << "Marca         : " << brand          << "\n";
    std::cout << "Lote          : " << lotNumber      << "\n";
    std::cout << "Data Validade : " << expirationDate << "\n";

    int confirm = readInt("\nConfirma? (1-Sim / 2-Nao): ", 1, 2);
    if (confirm == 1) {
        // TODO: VaccineController::register(...)
        std::cout << "\n[OK] Vacina registada!\n";
    } else {
        std::cout << "\n[INFO] Operacao cancelada.\n";
    }
    pause();
}

// ---- UC3 ----
void uc3_listVaccineStock() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC3 - Stock de Vacinas\n";
    std::cout << "========================================\n\n";

    // TODO: obter lista real do repositorio
    std::cout << "Tipo: COVID-19\n";
    std::cout << "  Pfizer | Lote: PF-001 | Validade: 01/12/2026\n\n";
    std::cout << "Tipo: Gripe\n";
    std::cout << "  Sanofi | Lote: SN-007 | Validade: 30/04/2026\n";

    pause();
}

// ---- UC4 ----
void uc4_registerEmployee() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC4 - Registar Funcionario\n";
    std::cout << "========================================\n\n";

    std::cout << "Funcoes:\n  1. Enfermeiro\n  2. Rececionista\n";
    int roleChoice = readInt("Selecione a funcao: ", 1, 2);

    std::string id, name, address, phone, email, cc;
    std::cout << "\nID               : "; std::getline(std::cin, id);
    std::cout << "Nome             : "; std::getline(std::cin, name);
    std::cout << "Morada           : "; std::getline(std::cin, address);
    std::cout << "Telefone         : "; std::getline(std::cin, phone);
    std::cout << "Email            : "; std::getline(std::cin, email);
    std::cout << "Cartao Cidadao   : "; std::getline(std::cin, cc);

    std::cout << "\n--- Confirmar dados ---\n";
    std::cout << "Funcao   : " << (roleChoice == 1 ? "Enfermeiro" : "Rececionista") << "\n";
    std::cout << "ID       : " << id      << "\n";
    std::cout << "Nome     : " << name    << "\n";
    std::cout << "Morada   : " << address << "\n";
    std::cout << "Telefone : " << phone   << "\n";
    std::cout << "Email    : " << email   << "\n";
    std::cout << "CC       : " << cc      << "\n";

    int confirm = readInt("\nConfirma? (1-Sim / 2-Nao): ", 1, 2);
    if (confirm == 1) {
        // TODO: EmployeeController::register(...)
        std::cout << "\n[OK] Funcionario registado!\n";
    } else {
        std::cout << "\n[INFO] Operacao cancelada.\n";
    }
    pause();
}

// ---- UC5 ----
void uc5_listEmployeesByRole() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC5 - Listar Funcionarios por Funcao\n";
    std::cout << "========================================\n\n";

    std::cout << "Funcoes:\n  1. Enfermeiro\n  2. Rececionista\n";
    int roleChoice = readInt("Selecione a funcao: ", 1, 2);

    std::cout << "\n--- " << (roleChoice == 1 ? "Enfermeiros" : "Rececionistas") << " ---\n";
    // TODO: obter lista real do repositorio
    std::cout << "  ID: E001 | Nome: Maria Silva\n";
    std::cout << "  ID: E002 | Nome: Joao Santos\n";

    pause();
}

// ---- Menu Administrador ----
void menuCenterAdministrator() {
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "    ADMINISTRADOR DO CENTRO\n";
        std::cout << "========================================\n";
        std::cout << "  1. Criar Tipo de Vacina\n";
        std::cout << "  2. Registar Vacina Fisica\n";
        std::cout << "  3. Listar Stock de Vacinas\n";
        std::cout << "  4. Registar Funcionario\n";
        std::cout << "  5. Listar Funcionarios por Funcao\n";
        std::cout << "  0. Voltar\n";
        std::cout << "========================================\n";

        option = readInt("Opcao: ", 0, 5);
        switch (option) {
            case 1: uc1_createVaccineType();        break;
            case 2: uc2_registerPhysicalVaccine();  break;
            case 3: uc3_listVaccineStock();          break;
            case 4: uc4_registerEmployee();          break;
            case 5: uc5_listEmployeesByRole();       break;
        }
    } while (option != 0);
}

// ---- Menu Principal ----
void mainMenu() {
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "        MedManager v1.0\n";
        std::cout << "  Gestao do Centro de Vacinacao\n";
        std::cout << "========================================\n";
        std::cout << "  1. Administrador do Centro\n";
        std::cout << "  2. Rececionista       [em breve]\n";
        std::cout << "  3. Enfermeiro         [em breve]\n";
        std::cout << "  0. Sair\n";
        std::cout << "========================================\n";

        option = readInt("Opcao: ", 0, 4);
        switch (option) {
            case 1: menuCenterAdministrator(); break;
            case 2: case 3:
                std::cout << "\n[INFO] Ainda nao implementado.\n";
                std::cout << "Pressione ENTER...";
                std::cin.get();
                break;
            case 0:
                std::cout << "\nAte logo!\n";
                break;
        }
    } while (option != 0);
}