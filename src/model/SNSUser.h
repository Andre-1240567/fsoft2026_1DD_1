#ifndef FSOFT2026_1DD_1_SNSUSER_H
#define FSOFT2026_1DD_1_SNSUSER_H

#include <string>

class SNSUser {
private:
    std::string snsNumber;
    std::string name;
    std::string address;
    std::string birthdate;
    std::string phone;
    std::string sex; // Opcional
    std::string citizenCardNumber;

public:
    SNSUser(std::string snsNumber, std::string name, std::string address,
            std::string birthdate, std::string phone, std::string citizenCardNumber,
            std::string sex = "N/A");

    std::string getSnsNumber() const;

  std::string getName() const;
    std::string getAddress() const;
    std::string getBirthdate() const;
    std::string getPhone() const;
    std::string getSex() const;
    std::string getCitizenCardNumber() const;

    void setAddress(const std::string& newAddress);
    void setPhone(const std::string& newPhone);
};

#endif //FSOFT2026_1DD_1_SNSUSER_H
