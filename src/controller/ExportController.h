//
// Created by User on 09/06/2026.
//

#ifndef FSOFT2026_1DD_1_EXPORTCONTROLLER_H
#define FSOFT2026_1DD_1_EXPORTCONTROLLER_H

#include "../model/HealthcareCenter.h"
#include <string>


class ExportController {
private:
    HealthcareCenter* hc;

public:
    ExportController(HealthcareCenter* hc);

    bool exportEmployees(const std::string& filename);
    bool exportInventory(const std::string& filename);
    bool exportSNSUsers(const std::string& filename);
    bool exportAppointments(const std::string& filename);
};
#endif //FSOFT2026_1DD_1_EXPORTCONTROLLER_H