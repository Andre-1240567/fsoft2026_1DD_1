//
// Created by pc-andre on 5/5/26.
//

#include "SNSUser.h"

SNSUser::SNSUser(std::string snsNumber, std::string name, std::string address,
                 std::string birthdate, std::string phone,
                 std::string citizenCardNumber, std::string sex)
{
    this->snsNumber         = snsNumber;
    this->name              = name;
    this->address           = address;
    this->birthdate         = birthdate;
    this->phone             = phone;
    this->citizenCardNumber = citizenCardNumber;
    this->sex               = sex;
}
std::string SNSUser::getSnsNumber()         const { return snsNumber; }
std::string SNSUser::getName()              const { return name; }
std::string SNSUser::getAddress()           const { return address; }
std::string SNSUser::getBirthdate()         const { return birthdate; }
std::string SNSUser::getPhone()             const { return phone; }
std::string SNSUser::getCitizenCardNumber() const { return citizenCardNumber; }
std::string SNSUser::getSex()               const { return sex; }
