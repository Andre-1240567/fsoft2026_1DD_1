//
// Created by pc-andre on 4/26/26.
//

#ifndef FSOFT2026_1DD_1_EMPLOYEECONTROLLER_H
#define FSOFT2026_1DD_1_EMPLOYEECONTROLLER_H

#include "../model/HealthcareCenter.h"
#include <string>

class EmployeeController{
private:
    // Ponteiro para o centro de saúde onde os funcionários vão ser registados
    HealthcareCenter* hc;

public:
    EmployeeController(HealthcareCenter* hc);

    //VC4
    bool registerEmployee(
        std::string name,
        std::string phone,
        std::string email,
        std::string cc,
        std::string role
    );
};



#endif //FSOFT2026_1DD_1_EMPLOYEECONTROLLER_H