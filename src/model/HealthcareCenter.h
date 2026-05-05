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

    void addEmployee(Employee* emp);
    void registerSNSUser(SNSUser* user);
    void addVaccineToInventory(Vaccine* vaccine);

    std::vector<Employee*> getEmployees() const;
    std::vector<SNSUser*> getWaitingRoom() const;
};

#endif //FSOFT2026_1DD_1_HEALTHCARECENTER_H