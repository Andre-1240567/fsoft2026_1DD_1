#include "NurseController.h"
#include "../model/Vaccine.h"
#include "../model/FileManager.h"
#include <ctime>

NurseController::NurseController(HealthcareCenter* hc) {
    this->hc = hc;
}

std::vector<SNSUser*> NurseController::getWaitingRoomUsers() {
    return hc->getWaitingRoom();
}

std::vector<SNSUser*> NurseController::getRecoveryRoomUsers() {
    return hc->getRecoveryRoom();
}

bool NurseController::recordAdministration(const std::string& snsNumber, const std::string& lotNumber) {
    Vaccine* vaccine = hc->findVaccineByLotNumber(lotNumber);
    bool success = hc->recordAdministration(snsNumber, vaccine, currentTimestamp());
    if (success) {
        FileManager::saveAppointments(hc, "appointments.txt");
        FileManager::saveVaccines(hc, "vaccines.txt");
    }
    return success;
}

std::string NurseController::currentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
    return buffer;
}
