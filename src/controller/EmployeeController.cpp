//
// Created by pc-andre on 4/26/26.
//

#include "EmployeeController.h"
#include "../model/Employee.h"
#include "../model/Nurse.h"
#include "../model/HealthcareCenter.h"
#include "../model/Receptionist.h"
#include <iostream>

// Construtor: guarda a referência do centro de saúde
EmployeeController::EmployeeController(HealthcareCenter* hc) {
    this->hc = hc;
}
//UC4
bool EmployeeController::registerEmployee(
    std::string name, std::string phone, std::string email, std::string cc, std::string role) {

    // ponteiro geral da classe mãe (Employee) inicializado a null
    Employee* newEmp = nullptr;
    if (role == "Enfermeiro") {
        newEmp = new Nurse(name, phone, email, cc);
    }else if (role == "Rececionista") {
        newEmp = new Receptionist(name, phone, email, cc);
    }

    if (newEmp == nullptr) {
        return false;
    }

    // O método 'addEmployee' deve validar se o CC/Email/Telefone já existem.
    bool success = hc->addEmployee(newEmp);
    if (!success) {
        delete newEmp;
        return false;
    }
    return true;
}

//UC5
std::vector<Employee*> EmployeeController::getEmployeesByRole(std::string role) {
    std::vector<Employee*> filteredList;

    // Obter todos os funcionários guardados no centro de saúde
    std::vector<Employee*> allEmployees = hc->getEmployees();

    for (Employee* emp : allEmployees) {
        if (role == "Enfermeiro") {
            // Se conseguir (não for nullptr), significa que ele é mesmo um Enfermeiro
            if (dynamic_cast<Nurse*>(emp) != nullptr) {
                filteredList.push_back(emp);
            }
        }
        else if (role == "Rececionista") {
            // Tenta converter o Employee* genérico para Receptionist*
            if (dynamic_cast<Receptionist*>(emp) != nullptr) {
                filteredList.push_back(emp);
            }
        }
    }

    return filteredList;
}
