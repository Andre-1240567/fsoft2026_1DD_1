//
// Created by pc-andre on 5/5/26.
//

#include "SNSUser.h"

SNSUser::SNSUser(std::string snsNumber, std::string name, std::string address,
                 std::string birthdate, std::string phone, std::string citizenCardNumber,
                 std::string sex)
    : snsNumber(snsNumber),
      name(name),
      address(address),
      birthdate(birthdate),
      phone(phone),
      sex(sex.empty() ? "N/A" : sex),
      citizenCardNumber(citizenCardNumber) {}

std::string SNSUser::getSnsNumber() const {
    return snsNumber;
}

std::string SNSUser::getName() const {
    return name;
}

std::string SNSUser::getAddress() const {
    return address;
}

std::string SNSUser::getBirthdate() const {
    return birthdate;
}

std::string SNSUser::getPhone() const {
    return phone;
}

std::string SNSUser::getSex() const {
    return sex;
}

std::string SNSUser::getCitizenCardNumber() const {
    return citizenCardNumber;
}
