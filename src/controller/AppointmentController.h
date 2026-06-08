#ifndef FSOFT2026_1DD_1_APPOINTMENTCONTROLLER_H
#define FSOFT2026_1DD_1_APPOINTMENTCONTROLLER_H

#include "../model/HealthcareCenter.h"
#include <string>

class AppointmentController {
private:
    HealthcareCenter* hc;

public:
    AppointmentController(HealthcareCenter* hc);

    bool createAppointment(const std::string& snsNumber, const std::string& vaccineTypeCode,
                           const std::string& date, const std::string& time);
    bool registerArrival(const std::string& snsNumber);
    static std::string currentDate();
};

#endif //FSOFT2026_1DD_1_APPOINTMENTCONTROLLER_H
