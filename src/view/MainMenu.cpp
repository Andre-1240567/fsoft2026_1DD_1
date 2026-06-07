#include "MainMenu.h"
#include "Utils.h"
#include "../model/HealthcareCenter.h"
#include "../model/VaccineType.h"
#include "../model/Vaccine.h"
#include "../controller/VaccineController.h"
#include "../controller/EmployeeController.h"
#include "../model/Employee.h"
#include "../model/FileManager.h"
#include <iostream>
#include <string>
#include <vector>

// Instâncias globais estáticas para a UI conseguir comunicar com a lógica do sistema
static HealthcareCenter globalHC("MedManager Center", "Main Street", "912345678", "general@med.pt");
static VaccineController vaccineController(&globalHC);
static EmployeeController employeeController(&globalHC);
// base de dados // .txt // .txt


// ---- UC1 ----
void uc1_createVaccineType() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC1 - Specify Vaccine Type\n";
    std::cout << "========================================\n\n";

    std::string code, disease, technology;
    int recoveryPeriod;

    std::cout << "Code            : "; std::getline(std::cin, code);
    std::cout << "Disease         : "; std::getline(std::cin, disease);

    // Menu para a Tecnologia
    std::cout << "\nAvailable Technologies:\n";
    std::cout << "  1. mRNA\n"
              << "  2. Viral Vector\n"
              << "  3. Subunit Protein\n"
              << "  4. Toxoid\n"
              << "  5. Inactivated Virus\n"
              << "  6. Live-attenuated Virus\n";
    int techChoice = readInt("Select technology: ", 1, 6);

    switch (techChoice) {
        case 1: technology = "mRNA"; break;
        case 2: technology = "Viral Vector"; break;
        case 3: technology = "Subunit Protein"; break;
        case 4: technology = "Toxoid"; break;
        case 5: technology = "Inactivated Virus"; break;
        case 6: technology = "Live-attenuated Virus"; break;
    }

    recoveryPeriod = readInt("\nRecovery Period (minutes): ", 0, 120);

    std::cout << "\n--- Confirm data ---\n";
    std::cout << "Code       : " << code         << "\n";
    std::cout << "Disease    : " << disease      << "\n";
    std::cout << "Technology : " << technology   << "\n";
    std::cout << "Recovery   : " << recoveryPeriod << " mins\n";

    int confirm = readInt("\nConfirm? (1-Yes / 2-No): ", 1, 2);
    if (confirm == 1) {
        bool success = vaccineController.createVaccineType(code, disease, technology, recoveryPeriod);
        if (success) {
            std::cout << "\n[OK] Vaccine type registered successfully!\n";
        } else {
            std::cout << "\n[ERROR] A vaccine type with the code '" << code << "' already exists.\n";
        }
    } else {
        std::cout << "\n[INFO] Operation canceled.\n";
    }
    pauseConsole();
}

// ---- UC2 ----
void uc2_registerPhysicalVaccine() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC2 - Register a Vaccine\n";
    std::cout << "========================================\n\n";

    std::vector<VaccineType*> catalog = vaccineController.getVaccineCatalog();

    if (catalog.empty()) {
        std::cout << "[WARNING] There are no Vaccine Types registered in the system.\n";
        std::cout << "Please execute UC1 first to populate the catalog.\n";
        pauseConsole();
        return;
    }

    std::cout << "Vaccine types available in the catalog:\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << catalog[i]->getCode() << "\n";
    }
    std::cout << "  0. Cancel\n";

    int typeChoice = readInt("Select the type: ", 0, catalog.size());
    if (typeChoice == 0) return;

    int realIndex = typeChoice - 1;

    std::string commercialName, brand, lotNumber, expirationDate;
    int quantity;

    std::cout << "\nCommercial Name : "; std::getline(std::cin, commercialName);
    std::cout << "Brand           : "; std::getline(std::cin, brand);
    std::cout << "Lot Number      : "; std::getline(std::cin, lotNumber);
    expirationDate = readDate("Expiration Date (YYYY-MM-DD): ");
    quantity = readInt("Quantity        : ", 1, 10000);

    std::cout << "\n--- Confirm data ---\n";
    std::cout << "Associated Type : " << catalog[realIndex]->getCode() << "\n";
    std::cout << "Commercial Name : " << commercialName << "\n";
    std::cout << "Brand           : " << brand          << "\n";
    std::cout << "Lot             : " << lotNumber      << "\n";
    std::cout << "Expiration Date : " << expirationDate << "\n";
    std::cout << "Quantity        : " << quantity       << "\n";

    int confirm = readInt("\nConfirm? (1-Yes / 2-No): ", 1, 2);
    if (confirm == 1) {
        bool success = vaccineController.registerVaccine(realIndex, commercialName, brand, lotNumber, expirationDate, quantity);
        if (success) {
            std::cout << "\n[OK] Vaccine lot registered successfully in the inventory!\n";
        } else {
            std::cout << "\n[ERROR] Failed to register the vaccine.\n";
        }
    } else {
        std::cout << "\n[INFO] Operation canceled.\n";
    }
    pauseConsole();
}

// ---- UC3 ----
void uc3_registerEmployee() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC3 - Register an Employee\n";
    std::cout << "========================================\n\n";

    std::cout << "Roles:\n  1. Nurse\n  2. Receptionist\n";
    int roleChoice = readInt("Select the role: ", 1, 2);

    std::string name, phone, email, cc;
    std::cout << "Name            : "; std::getline(std::cin, name);
    phone = readPhone("Phone           : ");
    email = readEmail("Email           : ");
    cc = readCC("Citizen Card    : ");

    std::cout << "\n--- Confirm data ---\n";
    std::cout << "Role     : " << (roleChoice == 1 ? "Nurse" : "Receptionist") << "\n";
    std::cout << "Name     : " << name  << "\n";
    std::cout << "Phone    : " << phone << "\n";
    std::cout << "Email    : " << email << "\n";
    std::cout << "CC       : " << cc    << "\n";

    int confirm = readInt("\nConfirm? (1-Yes / 2-No): ", 1, 2);
    if (confirm == 1) {
        std::string role = (roleChoice == 1 ? "Nurse" : "Receptionist");
        bool success = employeeController.registerEmployee(name, phone, email, cc, role);
        if (success) {
            std::cout << "\n[OK] Employee registered successfully!\n";
        } else {
            std::cout << "\n[ERROR] Failed to register the employee!\n";
        }
    } else {
        std::cout << "\n[INFO] Operation canceled.\n";
    }
    pauseConsole();
}

// ---- UC4 ----
void uc4_listEmployeesByRole() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC4 - List Employees by Role\n";
    std::cout << "========================================\n\n";

    std::cout << "Roles:\n  1. Nurse\n  2. Receptionist\n";
    int choice = readInt("Select the role: ", 1, 2);

    std::string roleChoice = (choice == 1 ? "Nurse" : "Receptionist");

    std::cout << "\n--- " << (choice == 1 ? "Nurses" : "Receptionists") << " ---\n";
    std::vector<Employee*> list = employeeController.getEmployeesByRole(roleChoice);
    if (list.empty()) {
        std::cout << " [INFO] No employees registered in this role.\n";
    } else {
        for (Employee* emp : list) {
            std::cout << "  -> Name : " << emp->getName()        << "\n"
                      << "     Phone: " << emp->getPhone()       << "\n"
                      << "     Email: " << emp->getEmail()       << "\n"
                      << "     CC   : " << emp->getCitizenCard() << "\n";
            std::cout << "  --------------------------------------\n";
        }
        std::cout << " Total: " << list.size() << " employee(s) listed.\n";
    }
    pauseConsole();
}

// ---- UC5 ----
void uc5_listVaccineStock() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC5 - List All Vaccines\n";
    std::cout << "========================================\n\n";

    std::map<VaccineType*, std::vector<Vaccine*>> stock = vaccineController.getVaccineStockGroupedAndSorted();

    if (stock.empty()) {
        std::cout << "[INFO] There is no vaccine stock in the Center's inventory.\n";
    } else {
        for (const auto& pair : stock) {
            VaccineType* vt = pair.first;
            const std::vector<Vaccine*>& vaccines = pair.second;

            std::cout << "Type: " << vt->getCode() << " (" << vaccines.size() << " lots)\n";

            for (Vaccine* v : vaccines) {
                std::cout << "  -> Comm. Name: " << v->getCommercialName()
                          << " | Brand: " << v->getBrand()
                          << " | Lot: "       << v->getLotNumber()
                          << " | Expiry: "    << v->getExpirationDate()
                          << " | Qty: "       << v->getQuantity() << "\n";
            }
            std::cout << "\n";
        }
    }
    pauseConsole();
}

// ---- Menu Administrator ----
void menuCenterAdministrator() {
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "        CENTER ADMINISTRATOR\n";
        std::cout << "========================================\n";
        std::cout << "  1. [UC1] Specify Vaccine Type\n";
        std::cout << "  2. [UC2] Register a Vaccine\n";
        std::cout << "  3. [UC3] Register an Employee\n";
        std::cout << "  4. [UC4] List Employees by Role\n";
        std::cout << "  5. [UC5] List All Vaccines\n";
        std::cout << "  0. Back\n";
        std::cout << "========================================\n";

        option = readInt("Option: ", 0, 5);
        switch (option) {
            case 1: uc1_createVaccineType();       break;
            case 2: uc2_registerPhysicalVaccine(); break;
            case 3: uc3_registerEmployee();        break;
            case 4: uc4_listEmployeesByRole();     break;
            case 5: uc5_listVaccineStock();        break;
        }
    } while (option != 0);
}

// ---- Menu Receptionist ----
void menuReceptionist()
{
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "            RECEPTIONIST\n";
        std::cout << "========================================\n";
        std::cout << "  1. [UC6] Register an SNS user\n";
        std::cout << "  2. [UC7] Schedule a vaccine administration\n";
        std::cout << "  3. [UC8] Register SNS User Arrival\n";
        std::cout << "  0. Back\n";
        std::cout << "========================================\n";

        option = readInt("Option: ", 0, 3);
        switch (option) {
        case 1:
            std::cout << "\n[INFO] Not implemented yet.\n";
            std::cout << "Press ENTER...";
            std::cin.get(); break;
        case 2:
            std::cout << "\n[INFO] Not implemented yet.\n";
            std::cout << "Press ENTER...";
            std::cin.get(); break;
        case 3:
            std::cout << "\n[INFO] Not implemented yet.\n";
            std::cout << "Press ENTER...";
            std::cin.get();
            break;
        case 0:
            std::cout << "\nGoodbye!\n";
            break;
        }
    }while (option != 0);
}

// ---- Menu Nurse ----
void menuNurse()
{
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "               NURSE\n";
        std::cout << "========================================\n";
        std::cout << "  1. [UC9] Consult SNS Users in the Waiting Room\n";
        std::cout << "  2. [UC10] Record vaccine administration\n";
        std::cout << "  0. Back\n";
        std::cout << "========================================\n";

        option = readInt("Option: ", 0, 3);
        switch (option) {
        case 1:
            std::cout << "\n[INFO] Not implemented yet.\n";
            std::cout << "Press ENTER...";
            std::cin.get(); break;
        case 2:
            std::cout << "\n[INFO] Not implemented yet.\n";
            std::cout << "Press ENTER...";
            std::cin.get(); break;
        case 0:
            std::cout << "\nGoodbye!\n";
            break;
        }
    }while (option != 0);
}

// ---- Main Menu ----
void mainMenu(){
    FileManager::loadVaccineTypes(&globalHC, "vaccine_types.txt");
    FileManager::loadVaccines(&globalHC, "vaccines.txt");
    FileManager::loadEmployees(&globalHC, "employees.txt");
    int option;
    do {
        clearScreen();
        std::cout << "========================================\n";
        std::cout << "          MedManager v1.2\n";
        std::cout << "  Healthcare Center Management\n";
        std::cout << "========================================\n";
        std::cout << "  1. Center Administrator\n";
        std::cout << "  2. Receptionist\n";
        std::cout << "  3. Nurse\n";
        std::cout << "  0. Exit\n";
        std::cout << "========================================\n";

        option = readInt("Option: ", 0, 3);
        switch (option) {
            case 1: menuCenterAdministrator(); break;
            case 2: menuReceptionist(); break;
            case 3: menuNurse(); break;
            case 0:
                pauseConsole();
        }
    } while (option != 0);
}