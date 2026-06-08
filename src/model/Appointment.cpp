#include "Appointment.h"
#include "Vaccine.h"

Appointment::Appointment(SNSUser* user, VaccineType* vaccineType, std::string date,
                         std::string time, std::string status)
    : user(user),
      vaccineType(vaccineType),
      date(date),
      time(time),
      status(status) {}

SNSUser* Appointment::getUser() const { return user; }

VaccineType* Appointment::getVaccineType() const { return vaccineType; }

std::string Appointment::getDate() const { return date; }

std::string Appointment::getTime() const { return time; }

std::string Appointment::getStatus() const { return status; }

std::string Appointment::getAdministeredAt() const { return administeredAt; }

std::string Appointment::getAdministeredLotNumber() const { return administeredLotNumber; }

bool Appointment::isPending() const {
    return status == "SCHEDULED" || status == "WAITING";
}

void Appointment::markWaiting() {
    status = "WAITING";
}

void Appointment::markAdministered(Vaccine* vaccine, const std::string& timestamp) {
    status = "ADMINISTERED";
    administeredAt = timestamp;
    administeredLotNumber = vaccine->getLotNumber();
}

void Appointment::setAdministeredData(const std::string& timestamp, const std::string& lotNumber) {
    administeredAt = timestamp;
    administeredLotNumber = lotNumber;
}
