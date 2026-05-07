#include "Employee.h"

Employee::Employee(std::string n, std::string p, std::string e, std::string cc) 
    : name(n), phone(p), email(e), citizenCard(cc) {}

std::string Employee::getName() const { return name; }
std::string Employee::getPhone() const { return phone; }
std::string Employee::getEmail() const { return email; }