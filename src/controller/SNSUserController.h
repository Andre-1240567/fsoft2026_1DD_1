#ifndef FSOFT2026_1DD_1_SNSUSERCONTROLLER_H
#define FSOFT2026_1DD_1_SNSUSERCONTROLLER_H

#include "../model/HealthcareCenter.h"
#include <string>

class SNSUserController {
private:
    HealthcareCenter* hc;

public:
    SNSUserController(HealthcareCenter* hc);

    bool registerSNSUser(
        std::string snsNumber,
        std::string name,
        std::string address,
        std::string birthdate,
        std::string phone,
        std::string citizenCardNumber,
        std::string sex = "N/A"
    );

    bool updateSNSUser(const std::string& snsNumber, const std::string& newAddress, const std::string& newPhone);
};

#endif //FSOFT2026_1DD_1_SNSUSERCONTROLLER_H
