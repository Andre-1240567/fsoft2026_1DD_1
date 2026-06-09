//
// Created by pc-andre on 4/26/26.
//

#ifndef FSOFT2026_1DD_1_HEALTHCARECENTER_H
#define FSOFT2026_1DD_1_HEALTHCARECENTER_H

#include <string>
#include <vector>

class Employee;
class Vaccine;
class VaccineType;
class SNSUser;
class Appointment;

class HealthcareCenter {
private:
    std::string name;
    std::string address;
    std::string phone;
    std::string email;

    std::vector<Employee*> employees;
    std::vector<VaccineType*> vaccineCatalog;
    std::vector<Vaccine*> inventory;
    std::vector<SNSUser*> snsUsersRegistry;
    std::vector<Appointment*> masterSchedule;

    std::vector<SNSUser*> waitingRoom;
    std::vector<SNSUser*> recoveryRoom;

public:
    HealthcareCenter(std::string name, std::string address, std::string phone, std::string email);

    ~HealthcareCenter();

    bool addVaccineType(VaccineType* vt);
    bool addEmployee(Employee* emp);
    bool registerSNSUser(SNSUser* user);
    bool addVaccineToInventory(Vaccine* vaccine);
    bool addAppointment(Appointment* appointment);
    bool registerArrival(const std::string& snsNumber, const std::string& currentDate);
    bool recordAdministration(const std::string& snsNumber, Vaccine* vaccine, const std::string& timestamp);

    SNSUser* findSNSUserByNumber(const std::string& snsNumber) const;
    VaccineType* findVaccineTypeByCode(const std::string& code) const;
    Vaccine* findVaccineByLotNumber(const std::string& lotNumber) const;
    Appointment* findScheduledAppointment(const std::string& snsNumber, const std::string& vaccineTypeCode) const;
    Appointment* findAppointmentForToday(const std::string& snsNumber, const std::string& currentDate) const;
    Appointment* findWaitingAppointment(const std::string& snsNumber) const;

    std::vector<Employee*> getEmployees() const;
    std::vector<SNSUser*> getSnsUsersRegistry() const;
    std::vector<Appointment*> getAppointments() const;
    std::vector<SNSUser*> getWaitingRoom() const;
    std::vector<SNSUser*> getRecoveryRoom() const;
    std::vector<VaccineType*> getVaccineCatalog() const;
    std::vector<Vaccine*> getInventory() const;
};

#endif //FSOFT2026_1DD_1_HEALTHCARECENTER_H
