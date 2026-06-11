#include "MainMenu.h"
#include "Utils.h"
#include "../model/HealthcareCenter.h"
#include "../model/VaccineType.h"
#include "../model/Vaccine.h"
#include "../controller/VaccineController.h"
#include "../controller/EmployeeController.h"
#include "../controller/SNSUserController.h"
#include "../controller/AppointmentController.h"
#include "../controller/NurseController.h"
#include "../model/Employee.h"
#include "../model/SNSUser.h"
#include "../model/FileManager.h"
#include <iostream>
#include <string>
#include <vector>
#include "../controller/ExportController.h"

// Instâncias globais estáticas para a UI conseguir comunicar com a lógica do sistema
static HealthcareCenter globalHC("MedManager Center", "Main Street", "912345678", "general@med.pt");
static VaccineController vaccineController(&globalHC);
static EmployeeController employeeController(&globalHC);
static SNSUserController snsUserController(&globalHC);
static AppointmentController appointmentController(&globalHC);
static NurseController nurseController(&globalHC);
static ExportController exportController(&globalHC);
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

// ---- UC6 ----
void uc6_registerSNSUser() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC6 - Register an SNS User\n";
    std::cout << "========================================\n\n";

    std::string snsNumber, name, address, birthdate, phone, cc, sex;

    std::cout << "Name            : "; std::getline(std::cin, name);
    std::cout << "Address         : "; std::getline(std::cin, address);
    phone = readPhone("Phone           : ");
    std::cout << "SNS User Number : "; std::getline(std::cin, snsNumber);
    cc = readCC("Citizen Card    : ");
    birthdate = readDate("Birth Date (YYYY-MM-DD): ");

    std::cout << "\nSex (optional):\n";
    std::cout << "  1. Male\n"
              << "  2. Female\n"
              << "  3. Other\n"
              << "  4. Not specified\n";
    int sexChoice = readInt("Select sex: ", 1, 4);
    switch (sexChoice) {
        case 1: sex = "Male"; break;
        case 2: sex = "Female"; break;
        case 3: sex = "Other"; break;
        case 4: sex = "N/A"; break;
    }

    std::cout << "\n--- Confirm data ---\n";
    std::cout << "Name            : " << name << "\n";
    std::cout << "Address         : " << address << "\n";
    std::cout << "Phone           : " << phone << "\n";
    std::cout << "SNS User Number : " << snsNumber << "\n";
    std::cout << "Citizen Card    : " << cc << "\n";
    std::cout << "Birth Date      : " << birthdate << "\n";
    std::cout << "Sex             : " << sex << "\n";

    int confirm = readInt("\nConfirm? (1-Yes / 2-No): ", 1, 2);
    if (confirm == 1) {
        bool success = snsUserController.registerSNSUser(
            snsNumber, name, address, birthdate, phone, cc, sex
        );
        if (success) {
            std::cout << "\n[OK] SNS user registered successfully!\n";
        } else {
            std::cout << "\n[ERROR] Failed to register the SNS user. Check mandatory fields, formats, or duplicate Phone/SNS Number.\n";
        }
    } else {
        std::cout << "\n[INFO] Operation canceled.\n";
    }
    pauseConsole();
}

// ---- UC7 ----
void uc7_scheduleVaccineAdministration() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC7 - Schedule Vaccine Administration\n";
    std::cout << "========================================\n\n";

    std::string snsNumber;
    std::cout << "SNS User Number : "; std::getline(std::cin, snsNumber);

    SNSUser* user = globalHC.findSNSUserByNumber(snsNumber);
    if (user == nullptr) {
        std::cout << "\n[ERROR] SNS user not found.\n";
        pauseConsole();
        return;
    }

    std::vector<VaccineType*> catalog = vaccineController.getVaccineCatalog();
    if (catalog.empty()) {
        std::cout << "\n[WARNING] There are no Vaccine Types registered in the system.\n";
        pauseConsole();
        return;
    }

    std::cout << "\nSNS User: " << user->getName() << "\n\n";
    std::cout << "Vaccine types available:\n";
    for (size_t i = 0; i < catalog.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << catalog[i]->getCode()
                  << " - " << catalog[i]->getDisease() << "\n";
    }
    std::cout << "  0. Cancel\n";

    int typeChoice = readInt("Select vaccine type: ", 0, catalog.size());
    if (typeChoice == 0) {
        std::cout << "\n[INFO] Operation canceled.\n";
        pauseConsole();
        return;
    }

    VaccineType* selectedType = catalog[typeChoice - 1];
    std::string date = readDate("Appointment Date (YYYY-MM-DD): ");
    std::string time = readTime("Appointment Time (HH:MM): ");

    std::cout << "\n--- Confirm schedule ---\n";
    std::cout << "SNS User Number : " << snsNumber << "\n";
    std::cout << "Name            : " << user->getName() << "\n";
    std::cout << "Vaccine Type    : " << selectedType->getCode() << "\n";
    std::cout << "Date            : " << date << "\n";
    std::cout << "Time            : " << time << "\n";

    int confirm = readInt("\nConfirm? (1-Yes / 2-No): ", 1, 2);
    if (confirm == 1) {
        bool success = appointmentController.createAppointment(snsNumber, selectedType->getCode(), date, time);
        if (success) {
            std::cout << "\n[OK] Appointment scheduled successfully!\n";
        } else {
            std::cout << "\n[ERROR] Failed to schedule. Check duplicates for this SNS user and vaccine type.\n";
        }
    } else {
        std::cout << "\n[INFO] Operation canceled.\n";
    }
    pauseConsole();
}

// ---- UC8 ----
void uc8_registerSNSUserArrival() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC8 - Register SNS User Arrival\n";
    std::cout << "========================================\n\n";

    std::string snsNumber;
    std::cout << "SNS User Number : "; std::getline(std::cin, snsNumber);

    bool success = appointmentController.registerArrival(snsNumber);
    if (success) {
        std::cout << "\n[OK] Arrival registered. SNS user moved to the waiting room.\n";
    } else {
        std::cout << "\n[ERROR] Could not register arrival. Check if the user exists, has a scheduled appointment today, or is already waiting.\n";
    }
    pauseConsole();
}

// ---- UC9 ----
void uc9_consultWaitingRoom() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC9 - Waiting Room\n";
    std::cout << "========================================\n\n";

    std::vector<SNSUser*> waitingUsers = nurseController.getWaitingRoomUsers();
    if (waitingUsers.empty()) {
        std::cout << "[INFO] The waiting room is empty.\n";
    } else {
        for (size_t i = 0; i < waitingUsers.size(); ++i) {
            std::cout << "  " << (i + 1) << ". SNS: " << waitingUsers[i]->getSnsNumber()
                      << " | Name: " << waitingUsers[i]->getName() << "\n";
        }
        std::cout << "\nTotal: " << waitingUsers.size() << " user(s) waiting.\n";
    }
    pauseConsole();
}

// ---- UC10 ----
void uc10_recordVaccineAdministration() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC10 - Record Vaccine Administration\n";
    std::cout << "========================================\n\n";

    std::vector<SNSUser*> waitingUsers = nurseController.getWaitingRoomUsers();
    if (waitingUsers.empty()) {
        std::cout << "[INFO] The waiting room is empty.\n";
        pauseConsole();
        return;
    }

    std::cout << "Waiting room users:\n";
    for (size_t i = 0; i < waitingUsers.size(); ++i) {
        std::cout << "  " << (i + 1) << ". SNS: " << waitingUsers[i]->getSnsNumber()
                  << " | Name: " << waitingUsers[i]->getName() << "\n";
    }
    int userChoice = readInt("Select SNS user: ", 1, waitingUsers.size());
    SNSUser* selectedUser = waitingUsers[userChoice - 1];

    std::vector<Vaccine*> inventory = vaccineController.getInventory();
    std::vector<Vaccine*> availableVaccines;
    for (Vaccine* vaccine : inventory) {
        if (vaccine->getQuantity() > 0) {
            availableVaccines.push_back(vaccine);
        }
    }

    if (availableVaccines.empty()) {
        std::cout << "\n[WARNING] There are no vaccine lots with available quantity.\n";
        pauseConsole();
        return;
    }

    std::cout << "\nAvailable vaccine lots:\n";
    for (size_t i = 0; i < availableVaccines.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << availableVaccines[i]->getCommercialName()
                  << " | Brand: " << availableVaccines[i]->getBrand()
                  << " | Lot: " << availableVaccines[i]->getLotNumber()
                  << " | Type: " << availableVaccines[i]->getType()->getCode()
                  << " | Qty: " << availableVaccines[i]->getQuantity() << "\n";
    }
    int vaccineChoice = readInt("Select vaccine lot: ", 1, availableVaccines.size());
    Vaccine* selectedVaccine = availableVaccines[vaccineChoice - 1];

    std::cout << "\n--- Confirm administration ---\n";
    std::cout << "SNS User Number : " << selectedUser->getSnsNumber() << "\n";
    std::cout << "Name            : " << selectedUser->getName() << "\n";
    std::cout << "Vaccine         : " << selectedVaccine->getCommercialName() << "\n";
    std::cout << "Lot Number      : " << selectedVaccine->getLotNumber() << "\n";

    int confirm = readInt("\nConfirm? (1-Yes / 2-No): ", 1, 2);
    if (confirm == 1) {
        bool success = nurseController.recordAdministration(
            selectedUser->getSnsNumber(), selectedVaccine->getLotNumber()
        );
        if (success) {
            std::cout << "\n[OK] Administration recorded. SNS user moved to the recovery room.\n";
        } else {
            std::cout << "\n[ERROR] Failed to record administration. Check appointment type, waiting room status, or stock.\n";
        }
    } else {
        std::cout << "\n[INFO] Operation canceled.\n";
    }
    pauseConsole();
}

// ---- UC11 ----
void uc11_exportReports() {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "   UC11 - Export Reports\n";
    std::cout << "========================================\n\n";

    std::cout << "Select data to export:\n";
    std::cout << "  1. Employees List\n";
    std::cout << "  2. Vaccine Inventory\n";
    std::cout << "  3. SNS Users\n";
    std::cout << "  4. Appointments (Master Schedule)\n";
    std::cout << "  0. Cancel\n";

    int choice = readInt("Option: ", 0, 4);
    if (choice == 0) return;

    bool success = false;
    std::string filename;

    switch (choice) {
        case 1:
            filename = "report_employees.csv";
            success  = exportController.exportEmployees(filename);
            break;
        case 2:
            filename = "report_inventory.csv";
            success  = exportController.exportInventory(filename);
            break;
        case 3:
            filename = "report_sns_users.csv";
            success  = exportController.exportSNSUsers(filename);
            break;
        case 4:
            filename = "report_appointments.csv";
            success  = exportController.exportAppointments(filename);
            break;
    }

    if (success) {
        std::cout << "\n[OK] Report saved to: " << filename << "\n";
    } else {
        std::cout << "\n[WARNING] No data available to export. File not created.\n";
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
        std::cout << "  6. [UC11] Export Reports\n";
        std::cout << "  0. Back\n";
        std::cout << "========================================\n";

        option = readInt("Option: ", 0, 6);
        switch (option) {
            case 1: uc1_createVaccineType();       break;
            case 2: uc2_registerPhysicalVaccine(); break;
            case 3: uc3_registerEmployee();        break;
            case 4: uc4_listEmployeesByRole();     break;
            case 5: uc5_listVaccineStock();        break;
            case 6: uc11_exportReports();          break;
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
            uc6_registerSNSUser();
            break;
        case 2:
            uc7_scheduleVaccineAdministration();
            break;
        case 3:
            uc8_registerSNSUserArrival();
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

        option = readInt("Option: ", 0, 2);
        switch (option) {
        case 1:
            uc9_consultWaitingRoom();
            break;
        case 2:
            uc10_recordVaccineAdministration();
            break;
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
    FileManager::loadSNSUserRegistry(&globalHC, "sns_users.txt");
    FileManager::loadAppointments(&globalHC, "appointments.txt");
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
        
        bool authenticated = false;
        if (option == 1) {
            std::string cc;
            std::cout << "Login (Citizen Card / 'admin' / '0' to cancel): ";
            std::getline(std::cin, cc);
            if (cc == "0") continue;
            if (cc == "admin") authenticated = true;
            else {
                for (Employee* emp : globalHC.getEmployees()) {
                    if (emp->getCitizenCard() == cc && emp->getRole() == "Center Administrator") {
                        authenticated = true; break;
                    }
                }
                if (!authenticated) {
                    std::cout << "\n[ERROR] Authentication failed for Administrator.\n";
                    pauseConsole();
                    continue;
                }
            }
        } else if (option == 2) {
            std::string cc;
            std::cout << "Login (Citizen Card / '0' to cancel): ";
            std::getline(std::cin, cc);
            if (cc == "0") continue;
            for (Employee* emp : globalHC.getEmployees()) {
                if (emp->getCitizenCard() == cc && emp->getRole() == "Receptionist") {
                    authenticated = true; break;
                }
            }
            if (!authenticated) {
                std::cout << "\n[ERROR] Authentication failed for Receptionist.\n";
                pauseConsole();
                continue;
            }
        } else if (option == 3) {
            std::string cc;
            std::cout << "Login (Citizen Card / '0' to cancel): ";
            std::getline(std::cin, cc);
            if (cc == "0") continue;
            for (Employee* emp : globalHC.getEmployees()) {
                if (emp->getCitizenCard() == cc && emp->getRole() == "Nurse") {
                    authenticated = true; break;
                }
            }
            if (!authenticated) {
                std::cout << "\n[ERROR] Authentication failed for Nurse.\n";
                pauseConsole();
                continue;
            }
        }

        switch (option) {
            case 1: menuCenterAdministrator(); break;
            case 2: menuReceptionist(); break;
            case 3: menuNurse(); break;
            case 0:
                std::cout << "\nGoodbye!\n";
                break;
        }
    } while (option != 0);
}
