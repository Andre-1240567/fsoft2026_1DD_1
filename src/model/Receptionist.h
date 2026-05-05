#ifndef FSOFT2026_1DD_1_RECEPTIONIST_H
#define FSOFT2026_1DD_1_RECEPTIONIST_H

#include "Employee.h"

class Receptionist : public Employee {
public:
    Receptionist(std::string n, std::string p, std::string e, std::string cc);
};

#endif //FSOFT2026_1DD_1_RECEPTIONIST_H