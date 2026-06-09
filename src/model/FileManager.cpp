#include "FileManager.h"
#include "HealthcareCenter.h"
#include "VaccineType.h"
#include "Vaccine.h"
#include "Employee.h"
#include "Nurse.h"
#include "Receptionist.h"
#include "CenterAdministrator.h"
#include "SNSUser.h"
#include "Appointment.h"
#include <fstream>
#include <iostream>
#include <iostream>

bool FileManager::saveVaccineTypes(HealthcareCenter* hc, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    for (VaccineType* vt : hc->getVaccineCatalog()) {
        file << vt->getCode() << ";" 
             << vt->getDisease() << ";" 
             << vt->getTechnology() << ";" 
             << vt->getRecoveryPeriod() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadVaccineTypes(HealthcareCenter* hc, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) {
            std::string code = line.substr(0, pos1);
            std::string disease = line.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string tech = line.substr(pos2 + 1, pos3 - pos2 - 1);
            int recovery = std::stoi(line.substr(pos3 + 1));
            
            VaccineType* vt = new VaccineType(code, disease, tech, recovery);
            hc->addVaccineType(vt);
        }
    }
    file.close();
    return true;
}

bool FileManager::saveVaccines(HealthcareCenter* hc, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    for (Vaccine* v : hc->getInventory()) {
        file << v->getCommercialName() << ";"
             << v->getBrand() << ";"
             << v->getLotNumber() << ";"
             << v->getExpirationDate() << ";"
             << v->getQuantity() << ";"
             << v->getType()->getCode() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadVaccines(HealthcareCenter* hc, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        size_t p3 = line.find(';', p2 + 1);
        size_t p4 = line.find(';', p3 + 1);
        size_t p5 = line.find(';', p4 + 1);
        
        if (p1 != std::string::npos && p5 != std::string::npos) {
            std::string cName = line.substr(0, p1);
            std::string brand = line.substr(p1 + 1, p2 - p1 - 1);
            std::string lot = line.substr(p2 + 1, p3 - p2 - 1);
            std::string expiry = line.substr(p3 + 1, p4 - p3 - 1);
            int qty = std::stoi(line.substr(p4 + 1, p5 - p4 - 1));
            std::string tCode = line.substr(p5 + 1);
            
            VaccineType* vt = nullptr;
            for (VaccineType* catVt : hc->getVaccineCatalog()) {
                if (catVt->getCode() == tCode) {
                    vt = catVt;
                    break;
                }
            }
            if (vt != nullptr) {
                Vaccine* v = new Vaccine(cName, brand, lot, expiry, qty, vt);
                hc->addVaccineToInventory(v);
            }
        }
    }
    file.close();
    return true;
}

bool FileManager::saveEmployees(HealthcareCenter* hc, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    for (Employee* e : hc->getEmployees()) {
        file << e->getName() << ";"
             << e->getPhone() << ";"
             << e->getEmail() << ";"
             << e->getCitizenCard() << ";"
             << e->getRole() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadEmployees(HealthcareCenter* hc, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        size_t p3 = line.find(';', p2 + 1);
        size_t p4 = line.find(';', p3 + 1);
        
        if (p1 != std::string::npos && p4 != std::string::npos) {
            std::string name = line.substr(0, p1);
            std::string phone = line.substr(p1 + 1, p2 - p1 - 1);
            std::string email = line.substr(p2 + 1, p3 - p2 - 1);
            std::string cc = line.substr(p3 + 1, p4 - p3 - 1);
            std::string role = line.substr(p4 + 1);
            
            Employee* emp = nullptr;
            if (role == "Nurse") emp = new Nurse(name, phone, email, cc);
            else if (role == "Receptionist") emp = new Receptionist(name, phone, email, cc);
            else if (role == "Center Administrator") emp = new CenterAdministrator(name, phone, email, cc);
            
            if (emp != nullptr) {
                hc->addEmployee(emp);
            }
        }
    }
    file.close();
    return true;
}

bool FileManager::saveSNSUserRegistry(HealthcareCenter* hc, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (SNSUser* user : hc->getSnsUsersRegistry()) {
        file << user->getSnsNumber() << ";"
             << user->getName() << ";"
             << user->getAddress() << ";"
             << user->getBirthdate() << ";"
             << user->getPhone() << ";"
             << user->getCitizenCardNumber() << ";"
             << user->getSex() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadSNSUserRegistry(HealthcareCenter* hc, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        size_t p3 = line.find(';', p2 + 1);
        size_t p4 = line.find(';', p3 + 1);
        size_t p5 = line.find(';', p4 + 1);
        size_t p6 = line.find(';', p5 + 1);

        if (p1 != std::string::npos && p6 != std::string::npos) {
            std::string snsNumber = line.substr(0, p1);
            std::string name = line.substr(p1 + 1, p2 - p1 - 1);
            std::string address = line.substr(p2 + 1, p3 - p2 - 1);
            std::string birthdate = line.substr(p3 + 1, p4 - p3 - 1);
            std::string phone = line.substr(p4 + 1, p5 - p4 - 1);
            std::string cc = line.substr(p5 + 1, p6 - p5 - 1);
            std::string sex = line.substr(p6 + 1);

            SNSUser* user = new SNSUser(snsNumber, name, address, birthdate, phone, cc, sex);
            if (!hc->registerSNSUser(user)) {
                delete user;
            }
        }
    }
    file.close();
    return true;
}

bool FileManager::saveAppointments(HealthcareCenter* hc, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (Appointment* appointment : hc->getAppointments()) {
        file << appointment->getUser()->getSnsNumber() << ";"
             << appointment->getVaccineType()->getCode() << ";"
             << appointment->getDate() << ";"
             << appointment->getTime() << ";"
             << appointment->getStatus() << ";"
             << appointment->getAdministeredAt() << ";"
             << appointment->getAdministeredLotNumber() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::loadAppointments(HealthcareCenter* hc, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t p1 = line.find(';');
        size_t p2 = line.find(';', p1 + 1);
        size_t p3 = line.find(';', p2 + 1);
        size_t p4 = line.find(';', p3 + 1);
        size_t p5 = line.find(';', p4 + 1);
        size_t p6 = line.find(';', p5 + 1);

        if (p1 != std::string::npos && p6 != std::string::npos) {
            std::string snsNumber = line.substr(0, p1);
            std::string vaccineTypeCode = line.substr(p1 + 1, p2 - p1 - 1);
            std::string date = line.substr(p2 + 1, p3 - p2 - 1);
            std::string time = line.substr(p3 + 1, p4 - p3 - 1);
            std::string status = line.substr(p4 + 1, p5 - p4 - 1);
            std::string administeredAt = line.substr(p5 + 1, p6 - p5 - 1);
            std::string administeredLot = line.substr(p6 + 1);

            SNSUser* user = hc->findSNSUserByNumber(snsNumber);
            VaccineType* vaccineType = hc->findVaccineTypeByCode(vaccineTypeCode);
            if (user != nullptr && vaccineType != nullptr) {
                Appointment* appointment = new Appointment(user, vaccineType, date, time, status);
                appointment->setAdministeredData(administeredAt, administeredLot);
                if (!hc->addAppointment(appointment)) {
                    delete appointment;
                }
            }
        }
    }
    file.close();
    return true;
}
