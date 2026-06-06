#include "CenterAdministrator.h"

CenterAdministrator::CenterAdministrator(std::string n, std::string p, std::string e, std::string cc)
    : Employee(n, p, e, cc) {
}

std::string CenterAdministrator::getRole() const {
    return "Center Administrator";
}