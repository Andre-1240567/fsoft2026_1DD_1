#include "HealthcareCenter.h"
#include "VaccineType.h"
#include "Employee.h"
#include "Vaccine.h"
#include "SNSUser.h"
#include "Appointment.h"

HealthcareCenter::HealthcareCenter(std::string name, std::string address, std::string phone, std::string email)
    : name(name), address(address), phone(phone), email(email) {}

HealthcareCenter::~HealthcareCenter() {
    for (Employee* emp : employees) {
        delete emp;
    }
    for (VaccineType* vt : vaccineCatalog) {
        delete vt;
    }
    for (Vaccine* v : inventory) {
        delete v;
    }
    for (SNSUser* u : snsUsersRegistry) {
        delete u;
    }
    for (Appointment* a : masterSchedule) {
        delete a;
    }
}

bool HealthcareCenter::addVaccineType(VaccineType* vt) {
    for (VaccineType* existingVt : vaccineCatalog) {
        if (existingVt->getCode() == vt->getCode()) {
            return false;
        }
    }

    vaccineCatalog.push_back(vt);
    return true;
}

// UC2

std::vector<VaccineType*> HealthcareCenter::getVaccineCatalog() const {
    return vaccineCatalog;
}

bool HealthcareCenter::addVaccineToInventory(Vaccine* vaccine) {
    for (Vaccine* existing : inventory) {
        if (existing->getBrand() == vaccine->getBrand() && 
            existing->getLotNumber() == vaccine->getLotNumber()) {
            return false;
        }
    }
    inventory.push_back(vaccine);
    return true;
}

std::vector<Vaccine*> HealthcareCenter::getInventory() const {
    return inventory;
}

//UC4

bool HealthcareCenter::addEmployee(Employee* emp) {
    // Percorre a lista de funcionários já existentes no centro de saúde
    for (Employee* existing : employees) {
        // Se encontrar alguém com o mesmo CC, Email ou Telefone, aborta o registo
        if (existing->getCitizenCard() == emp->getCitizenCard() ||
            existing->getEmail() == emp->getEmail() ||
            existing->getPhone() == emp->getPhone()) {
            return false;
            }
    }

    // Se os dados forem únicos, adiciona o funcionário ao vetor usando o push_back do C++
    employees.push_back(emp);
    return true;
}
//UC5
std::vector<Employee*> HealthcareCenter::getEmployees() const {
    return employees; // Garante que o nome deste vetor condiz com o definido no teu HealthcareCenter.h
}

// UC6
bool HealthcareCenter::registerSNSUser(SNSUser* user) {
    for (SNSUser* existing : snsUsersRegistry) {
        if (existing->getPhone() == user->getPhone() ||
            existing->getSnsNumber() == user->getSnsNumber()) {
            return false;
        }
    }

    snsUsersRegistry.push_back(user);
    return true;
}

std::vector<SNSUser*> HealthcareCenter::getSnsUsersRegistry() const {
    return snsUsersRegistry;
}

SNSUser* HealthcareCenter::findSNSUserByNumber(const std::string& snsNumber) const {
    for (SNSUser* user : snsUsersRegistry) {
        if (user->getSnsNumber() == snsNumber) {
            return user;
        }
    }
    return nullptr;
}

VaccineType* HealthcareCenter::findVaccineTypeByCode(const std::string& code) const {
    for (VaccineType* type : vaccineCatalog) {
        if (type->getCode() == code) {
            return type;
        }
    }
    return nullptr;
}

Vaccine* HealthcareCenter::findVaccineByLotNumber(const std::string& lotNumber) const {
    for (Vaccine* vaccine : inventory) {
        if (vaccine->getLotNumber() == lotNumber) {
            return vaccine;
        }
    }
    return nullptr;
}

Appointment* HealthcareCenter::findScheduledAppointment(const std::string& snsNumber, const std::string& vaccineTypeCode) const {
    for (Appointment* appointment : masterSchedule) {
        if (appointment->getUser()->getSnsNumber() == snsNumber &&
            appointment->getVaccineType()->getCode() == vaccineTypeCode &&
            appointment->isPending()) {
            return appointment;
        }
    }
    return nullptr;
}

Appointment* HealthcareCenter::findAppointmentForToday(const std::string& snsNumber, const std::string& currentDate) const {
    for (Appointment* appointment : masterSchedule) {
        if (appointment->getUser()->getSnsNumber() == snsNumber &&
            appointment->getDate() == currentDate &&
            appointment->getStatus() == "SCHEDULED") {
            return appointment;
        }
    }
    return nullptr;
}

Appointment* HealthcareCenter::findWaitingAppointment(const std::string& snsNumber) const {
    for (Appointment* appointment : masterSchedule) {
        if (appointment->getUser()->getSnsNumber() == snsNumber &&
            appointment->getStatus() == "WAITING") {
            return appointment;
        }
    }
    return nullptr;
}

bool HealthcareCenter::addAppointment(Appointment* appointment) {
    if (findScheduledAppointment(appointment->getUser()->getSnsNumber(),
                                 appointment->getVaccineType()->getCode()) != nullptr) {
        return false;
    }

    masterSchedule.push_back(appointment);
    return true;
}

bool HealthcareCenter::registerArrival(const std::string& snsNumber, const std::string& currentDate) {
    SNSUser* user = findSNSUserByNumber(snsNumber);
    if (user == nullptr) {
        return false;
    }

    for (SNSUser* waitingUser : waitingRoom) {
        if (waitingUser->getSnsNumber() == snsNumber) {
            return false;
        }
    }

    Appointment* appointment = findAppointmentForToday(snsNumber, currentDate);
    if (appointment == nullptr) {
        return false;
    }

    appointment->markWaiting();
    waitingRoom.push_back(user);
    return true;
}

bool HealthcareCenter::recordAdministration(const std::string& snsNumber, Vaccine* vaccine, const std::string& timestamp) {
    if (vaccine == nullptr || vaccine->getQuantity() <= 0) {
        return false;
    }

    Appointment* appointment = findWaitingAppointment(snsNumber);
    if (appointment == nullptr ||
        appointment->getVaccineType()->getCode() != vaccine->getType()->getCode()) {
        return false;
    }

    for (auto it = waitingRoom.begin(); it != waitingRoom.end(); ++it) {
        if ((*it)->getSnsNumber() == snsNumber) {
            if (!vaccine->decreaseQuantity()) {
                return false;
            }

            SNSUser* user = *it;
            waitingRoom.erase(it);
            recoveryRoom.push_back(user);
            appointment->markAdministered(vaccine, timestamp);
            return true;
        }
    }

    return false;
}

std::vector<Appointment*> HealthcareCenter::getAppointments() const {
    return masterSchedule;
}

std::vector<SNSUser*> HealthcareCenter::getWaitingRoom() const {
    return waitingRoom;
}

std::vector<SNSUser*> HealthcareCenter::getRecoveryRoom() const {
    return recoveryRoom;
}

std::vector<Appointment*> HealthcareCenter::getMasterSchedule() const {
    return masterSchedule;
}
