#include "HealthcareCenter.h"
#include "VaccineType.h"
#include "Employee.h"

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

std::vector<Vaccine*> HealthcareCenter::getInventory() const {
    return inventory;
}

//UC4

bool HealthcareCenter::addEmployee(Employee* emp) {
    // Percorre a lista de funcionários já existentes no centro de saúde
    for (Employee* existing : employees) {
        // Se encontrar alguém com o mesmo CC, Email ou Telefone, aborta o registo
        if (existing->getCitizenCard() == emp->getCitizenCard() ||
            existing->getEmail() == emp->getEmail() ||
            existing->getPhone() == emp->getPhone()) {
            return false;
            }
    }

    // Se os dados forem únicos, adiciona o funcionário ao vetor usando o push_back do C++
    employees.push_back(emp);
    return true;
}
//UC5
std::vector<Employee*> HealthcareCenter::getEmployees() const {
    return employees; // Garante que o nome deste vetor condiz com o definido no teu HealthcareCenter.h
}