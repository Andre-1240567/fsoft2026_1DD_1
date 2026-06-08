#ifndef FSOFT2026_1DD_1_NURSECONTROLLER_H
#define FSOFT2026_1DD_1_NURSECONTROLLER_H

#include "../model/HealthcareCenter.h"
#include <string>
#include <vector>

class SNSUser;
class Vaccine;

class NurseController {
private:
    HealthcareCenter* hc;

public:
    NurseController(HealthcareCenter* hc);

    std::vector<SNSUser*> getWaitingRoomUsers();
    bool recordAdministration(const std::string& snsNumber, const std::string& lotNumber);
    static std::string currentTimestamp();
};

#endif //FSOFT2026_1DD_1_NURSECONTROLLER_H
