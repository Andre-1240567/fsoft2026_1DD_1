#ifndef FSOFT2026_1DD_1_EMPLOYEE_H
#define FSOFT2026_1DD_1_EMPLOYEE_H

#include <string>

class Employee {
private:
    std::string name;
    std::string phone;
    std::string email;
    std::string citizenCard;

public:
    Employee(std::string n, std::string p, std::string e, std::string cc);

    // Getters
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getCitizenCard() const;
    virtual std::string getRole() const = 0;

    void setPhone(const std::string& newPhone);
    void setEmail(const std::string& newEmail);

    virtual ~Employee() = default;
};

#endif