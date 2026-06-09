#include "AppointmentController.h"
#include "../model/Appointment.h"
#include "../model/SNSUser.h"
#include "../model/VaccineType.h"
#include "../model/FileManager.h"
#include "../view/Utils.h"
#include <ctime>

AppointmentController::AppointmentController(HealthcareCenter* hc) {
    this->hc = hc;
}

bool AppointmentController::createAppointment(const std::string& snsNumber, const std::string& vaccineTypeCode,
                                              const std::string& date, const std::string& time) {
    if (!isValidDate(date) || !isValidTime(time)) {
        return false;
    }

    SNSUser* user = hc->findSNSUserByNumber(snsNumber);
    VaccineType* vaccineType = hc->findVaccineTypeByCode(vaccineTypeCode);
    if (user == nullptr || vaccineType == nullptr) {
        return false;
    }

    Appointment* appointment = new Appointment(user, vaccineType, date, time);
    bool success = hc->addAppointment(appointment);
    if (!success) {
        delete appointment;
    } else {
        FileManager::saveAppointments(hc, "appointments.txt");
    }

    return success;
}

bool AppointmentController::registerArrival(const std::string& snsNumber) {
    bool success = hc->registerArrival(snsNumber, currentDate());
    if (success) {
        FileManager::saveAppointments(hc, "appointments.txt");
    }
    return success;
}

std::string AppointmentController::currentDate() {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
    return buffer;
}
