//
// Created by pc-andre on 4/26/26.
//

#include "HealthcareCenter.h"

HealthcareCenter::HealthcareCenter(std::string name, std::string address, std::string phone, std::string email)
    : name(name), address(address), phone(phone), email(email) {}

HealthcareCenter::~HealthcareCenter() {
}

bool HealthcareCenter::addVaccineType(VaccineType* vt) {
    vaccineCatalog.push_back(vt);
    return true;
