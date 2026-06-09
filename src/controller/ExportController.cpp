//
// Created by User on 09/06/2026.
//
#include "ExportController.h"
#include "../model/Employee.h"
#include "../model/Vaccine.h"
#include "../model/SNSUser.h"
#include "../model/Appointment.h"
#include <fstream>
#include <iostream>

ExportController::ExportController(HealthcareCenter* hc) {
    this->hc = hc;
}

bool ExportController::exportEmployees(const std::string& filename) {
    std::vector<Employee*> list = hc->getEmployees();
    if (list.empty()) return false;

    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // Cabeçalho CSV
    file << "Name;Phone;Email;CitizenCard;Role\n";
    for (Employee* e : list) {
        file << e->getName()        << ";"
             << e->getPhone()       << ";"
             << e->getEmail()       << ";"
             << e->getCitizenCard() << ";"
             << e->getRole()        << "\n";
    }
    file.close();
    return true;
}

bool ExportController::exportInventory(const std::string& filename) {
    std::vector<Vaccine*> list = hc->getInventory();
    if (list.empty()) return false;

    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "CommercialName;Brand;LotNumber;ExpirationDate;Quantity;VaccineType\n";
    for (Vaccine* v : list) {
        file << v->getCommercialName()  << ";"
             << v->getBrand()           << ";"
             << v->getLotNumber()       << ";"
             << v->getExpirationDate()  << ";"
             << v->getQuantity()        << ";"
             << v->getType()->getCode() << "\n";
    }
    file.close();
    return true;
}

bool ExportController::exportSNSUsers(const std::string& filename) {
    std::vector<SNSUser*> list = hc->getSnsUsersRegistry();
    if (list.empty()) return false;

    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "SNSNumber;Name;Address;Birthdate;Phone;CitizenCard;Sex\n";
    for (SNSUser* u : list) {
        file << u->getSnsNumber()          << ";"
             << u->getName()               << ";"
             << u->getAddress()            << ";"
             << u->getBirthdate()          << ";"
             << u->getPhone()              << ";"
             << u->getCitizenCardNumber()  << ";"
             << u->getSex()               << "\n";
    }
    file.close();
    return true;
}

bool ExportController::exportAppointments(const std::string& filename) {
    std::vector<Appointment*> list = hc->getMasterSchedule();
    if (list.empty()) return false;

    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "DateTime;SNSNumber;UserName;VaccineType;Status\n";
    for (Appointment* a : list) {
        file << a->getDate()                  << ";"
             << a->getUser()->getSnsNumber()       << ";"
             << a->getUser()->getName()            << ";"
             << a->getVaccineType()->getCode()     << ";"
             << a->getStatus()                     << "\n";
    }
    file.close();
    return true;
}