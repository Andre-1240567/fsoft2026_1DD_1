//
// Created by pc-andre on 4/26/26.
//

#ifndef FSOFT2026_1DD_1_VACCINECONTROLLER_H
#define FSOFT2026_1DD_1_VACCINECONTROLLER_H

#include "../model/HealthcareCenter.h"

class VaccineController {
private:
    HealthcareCenter* hc;

public:
    VaccineController(HealthcareCenter* hc);

    bool createVaccineType(
            std::string code,
            std::string disease,
            std::string technology,
            int recoveryPeriod);
};

#endif