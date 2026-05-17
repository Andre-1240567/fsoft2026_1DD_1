#include "MainMenu.h"
#include "Utils.h"
#include "../model/HealthcareCenter.h"
#include "../model/VaccineType.h"
#include "../model/Vaccine.h"
#include "../controller/VaccineController.h"
#include "../controller/EmployeeController.h"
#include "../model/Employee.h"
#include <iostream>
#include <string>
#include <vector>

// Instâncias globais estáticas para a UI conseguir comunicar com a lógica do sistema
static HealthcareCenter globalHC("MedManager Center", "Rua Principal", "912345678", "geral@med.pt");
static VaccineController vaccineController(&globalHC);
static EmployeeController employeeController(&globalHC);

// ---- UC1 ----
void uc1_createVaccineType() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC1 - Criar Tipo de Vacina\n";
    std::cout << "========================================\n\n";

    std::string code, disease, technology;
    int recoveryPeriod;

    std::cout << "Codigo      : "; std::getline(std::cin, code);
    std::cout << "Doenca      : "; std::getline(std::cin, disease);

    // Menu para a Tecnologia
    std::cout << "\nTecnologias disponiveis:\n";
    std::cout << "  1. mRNA\n  2. Viral Vector\n  3. Proteina Subunitaria\n";
    int techChoice = readInt("Selecione a tecnologia: ", 1, 3);

    if (techChoice == 1) technology = "mRNA";
    else if (techChoice == 2) technology = "Viral Vector";
    else technology = "Proteina Subunitaria";

    recoveryPeriod = readInt("\nPeriodo de Recobro (minutos): ", 0, 120);

    std::cout << "\n--- Confirmar dados ---\n";
    std::cout << "Codigo     : " << code         << "\n";
    std::cout << "Doenca     : " << disease      << "\n";
    std::cout << "Tecnologia : " << technology   << "\n";
    std::cout << "Recobro    : " << recoveryPeriod << " mins\n";

    int confirm = readInt("\nConfirma? (1-Sim / 2-Nao): ", 1, 2);
    if (confirm == 1) {
        bool success = vaccineController.createVaccineType(code, disease, technology, recoveryPeriod);
        if (success) {
            std::cout << "\n[OK] Tipo de vacina registado com sucesso!\n";
        } else {
            std::cout << "\n[ERRO] Ja existe um tipo de vacina com o codigo '" << code << "'.\n";
        }
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

    std::vector<VaccineType*> catalog = vaccineController.getVaccineCatalog();

    if (catalog.empty()) {
        std::cout << "[AVISO] Nao existem Tipos de Vacina registados no sistema.\n";
        std::cout << "Por favor, execute a UC1 primeiro para popular o catalogo.\n";
        pause();
        return;
    }

    std::cout << "Tipos de vacina disponiveis no catalogo:\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << catalog[i]->getCode() << "\n";
    }
    std::cout << "  0. Cancelar\n";

    int typeChoice = readInt("Selecione o tipo: ", 0, catalog.size());
    if (typeChoice == 0) return;

    int realIndex = typeChoice - 1;

    std::string brand, lotNumber, expirationDate;
    int quantity;

    std::cout << "\nMarca           : "; std::getline(std::cin, brand);
    std::cout << "Numero de Lote  : "; std::getline(std::cin, lotNumber);
    std::cout << "Data Validade   : "; std::getline(std::cin, expirationDate);
    quantity = readInt("Quantidade      : ", 1, 10000);

    std::cout << "\n--- Confirmar dados ---\n";
    std::cout << "Tipo Associado: " << catalog[realIndex]->getCode() << "\n";
    std::cout << "Marca         : " << brand          << "\n";
    std::cout << "Lote          : " << lotNumber      << "\n";
    std::cout << "Data Validade : " << expirationDate << "\n";
    std::cout << "Quantidade    : " << quantity       << "\n";

    int confirm = readInt("\nConfirma? (1-Sim / 2-Nao): ", 1, 2);
    if (confirm == 1) {
        bool success = vaccineController.registerVaccine(realIndex, brand, lotNumber, expirationDate, quantity);
        if (success) {
            std::cout << "\n[OK] Lote de vacinas registado com sucesso no inventario!\n";
        } else {
            std::cout << "\n[ERRO] Falha ao registar a vacina.\n";
        }
    } else {
        std::cout << "\n[INFO] Operacao cancelada.\n";
    }
    pause();
}

// ---- UC3 ----
void uc3_registerEmployee() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC3 - Registar Funcionario\n";
    std::cout << "========================================\n\n";

    std::cout << "Funcoes:\n  1. Enfermeiro\n  2. Rececionista\n";
    int roleChoice = readInt("Selecione a funcao: ", 1, 2);

    std::string name, phone, email, cc;
    std::cout << "Nome             : "; std::getline(std::cin, name);
    std::cout << "Telefone         : "; std::getline(std::cin, phone);
    std::cout << "Email            : "; std::getline(std::cin, email);
    std::cout << "Cartao Cidadao   : "; std::getline(std::cin, cc);

    std::cout << "\n--- Confirmar dados ---\n";
    std::cout << "Funcao   : " << (roleChoice == 1 ? "Enfermeiro" : "Rececionista") << "\n";
    std::cout << "Nome     : " << name  << "\n";
    std::cout << "Telefone : " << phone << "\n";
    std::cout << "Email    : " << email << "\n";
    std::cout << "CC       : " << cc    << "\n";

    int confirm = readInt("\nConfirma? (1-Sim / 2-Nao): ", 1, 2);
    if (confirm == 1) {
        std::string role = (roleChoice == 1 ? "Enfermeiro" : "Rececionista");
        bool success = employeeController.registerEmployee(name, phone, email, cc, role);
        if (success) {
            std::cout << "\n[OK] Funcionario registado com sucesso!\n";
        } else {
            std::cout << "\n[ERRO] Falha ao registar o funcionario!\n";
        }
    } else {
        std::cout << "\n[INFO] Operacao cancelada.\n";
    }
    pause();
}

// ---- UC4 ----
void uc4_listEmployeesByRole() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC4 - Listar Funcionarios por Funcao\n";
    std::cout << "========================================\n\n";

    std::cout << "Funcoes:\n  1. Enfermeiro\n  2. Rececionista\n";
    int choice = readInt("Selecione a funcao: ", 1, 2);

    std::string roleChoice = (choice == 1 ? "Enfermeiro" : "Rececionista");

    std::cout << "\n--- " << (choice == 1 ? "Enfermeiros" : "Rececionistas") << " ---\n";
    std::vector<Employee*> list = employeeController.getEmployeesByRole(roleChoice);
    if (list.empty()) {
        std::cout << " [INFO] Nenhum funcionario registado nesta funcao.\n";
    } else {
        for (Employee* emp : list) {
            std::cout << "  -> Nome : " << emp->getName()        << "\n"
                      << "     Tel  : " << emp->getPhone()       << "\n"
                      << "     Email: " << emp->getEmail()       << "\n"
                      << "     CC   : " << emp->getCitizenCard() << "\n";
            std::cout << "  --------------------------------------\n";
        }
        std::cout << " Total: " << list.size() << " funcionario(s) listado(s).\n";
    }
    pause();
}

// ---- UC5 ----
void uc5_listVaccineStock() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC5 - Listar Stock de Vacinas\n";
    std::cout << "========================================\n\n";

    std::map<VaccineType*, std::vector<Vaccine*>> stock = vaccineController.getVaccineStockGroupedAndSorted();

    if (stock.empty()) {
        std::cout << "[INFO] Nao existe stock de vacinas no inventario do Centro.\n";
    } else {
        for (const auto& pair : stock) {
            VaccineType* vt = pair.first;
            const std::vector<Vaccine*>& vaccines = pair.second;

            std::cout << "Tipo: " << vt->getCode() << " (" << vaccines.size() << " lotes)\n";

            for (Vaccine* v : vaccines) {
                std::cout << "  -> Marca: "    << v->getBrand()
                          << " | Lote: "       << v->getLotNumber()
                          << " | Validade: "   << v->getExpirationDate()
                          << " | Qtd: "        << v->getQuantity() << "\n";
            }
            std::cout << "\n";
        }
    }
    pause();
}

// ---- Menu Administrator ----
void menuCenterAdministrator() {
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "      ADMINISTRADOR DO CENTRO\n";
        std::cout << "========================================\n";
        std::cout << "  1. Criar Tipo de Vacina\n";
        std::cout << "  2. Registar Vacina Fisica\n";
        std::cout << "  3. Registar Funcionario\n";
        std::cout << "  4. Listar Funcionarios por Funcao\n";
        std::cout << "  5. Listar Stock de Vacinas\n";
        std::cout << "  0. Voltar\n";
        std::cout << "========================================\n";

        option = readInt("Opcao: ", 0, 5);
        switch (option) {
            case 1: uc1_createVaccineType();       break;
            case 2: uc2_registerPhysicalVaccine(); break;
            case 3: uc3_registerEmployee();        break;
            case 4: uc4_listEmployeesByRole();     break;
            case 5: uc5_listVaccineStock();        break;
        }
    } while (option != 0);
}

// ---- Menu Principal ----
void mainMenu() {
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "          MedManager v1.0\n";
        std::cout << "  Gestao do Centro de Vacinacao\n";
        std::cout << "========================================\n";
        std::cout << "  1. Administrador do Centro\n";
        std::cout << "  2. Rececionista       [em breve]\n";
        std::cout << "  3. Enfermeiro         [em breve]\n";
        std::cout << "  0. Sair\n";
        std::cout << "========================================\n";

        option = readInt("Opcao: ", 0, 3);
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