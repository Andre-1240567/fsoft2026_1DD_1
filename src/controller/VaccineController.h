#ifndef FSOFT2026_1DD_1_VACCINECONTROLLER_H
#define FSOFT2026_1DD_1_VACCINECONTROLLER_H

#include "../model/HealthcareCenter.h"
#include <string>
#include <vector>

class VaccineType;

class VaccineController {
private:
    HealthcareCenter* hc;

public:
    VaccineController(HealthcareCenter* hc);

    // UC1
    bool createVaccineType(
            std::string code,
            std::string disease,
            std::string technology,
            int recoveryPeriod);

    // UC2
    std::vector<VaccineType*> getVaccineCatalog();

    bool registerVaccine(
            int typeIndex,
            std::string brand,
            std::string lot,
            std::string expiry,
            int qty);
};

#endif //FSOFT2026_1DD_1_VACCINECONTROLLER_H