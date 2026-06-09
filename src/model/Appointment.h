#ifndef FSOFT2026_1DD_1_APPOINTMENT_H
#define FSOFT2026_1DD_1_APPOINTMENT_H

#include <string>

class SNSUser;
class VaccineType;
class Vaccine;

class Appointment {
private:
    SNSUser* user;
    VaccineType* vaccineType;
    std::string date;
    std::string time;
    std::string status;
    std::string administeredAt;
    std::string administeredLotNumber;

public:
    Appointment(SNSUser* user, VaccineType* vaccineType, std::string date,
                std::string time, std::string status = "SCHEDULED");

    SNSUser* getUser() const;
    VaccineType* getVaccineType() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getStatus() const;
    std::string getAdministeredAt() const;
    std::string getAdministeredLotNumber() const;

    bool isPending() const;
    void markWaiting();
    void markAdministered(Vaccine* vaccine, const std::string& timestamp);
    void setAdministeredData(const std::string& timestamp, const std::string& lotNumber);
};

#endif //FSOFT2026_1DD_1_APPOINTMENT_H
