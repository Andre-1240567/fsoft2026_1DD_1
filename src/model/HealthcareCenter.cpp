#include "HealthcareCenter.h"
#include "VaccineType.h"

HealthcareCenter::HealthcareCenter(std::string name, std::string address, std::string phone, std::string email)
    : name(name), address(address), phone(phone), email(email) {}

HealthcareCenter::~HealthcareCenter() {
}

bool HealthcareCenter::addVaccineType(VaccineType* vt) {
    for (VaccineType* existingVt : vaccineCatalog) {
        if (existingVt->getCode() == vt->getCode()) {
            return false;
        }
    }

    vaccineCatalog.push_back(vt);
    return true;
}

// UC2

std::vector<VaccineType*> HealthcareCenter::getVaccineCatalog() const {
    return vaccineCatalog;
}

void HealthcareCenter::addVaccineToInventory(Vaccine* vaccine) {
    inventory.push_back(vaccine);
}