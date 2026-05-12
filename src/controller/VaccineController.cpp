//
// Created by pc-andre on 4/26/26.
//

#include "VaccineController.h"
#include "../model/VaccineType.h"
#include "../model/HealthcareCenter.h"

VaccineController::VaccineController(HealthcareCenter* hc)
{
    this->hc = hc;
}

bool VaccineController::createVaccineType(
        std::string code,
        std::string disease,
        std::string technology,
        int recoveryPeriod)
{
    VaccineType* vt = new VaccineType(
            code,
            disease,
            technology,
            recoveryPeriod);

    return hc->addVaccineType(vt);
}