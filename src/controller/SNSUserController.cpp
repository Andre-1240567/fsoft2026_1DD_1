#include "SNSUserController.h"
#include "../model/SNSUser.h"
#include "../model/FileManager.h"
#include "../view/Utils.h"

SNSUserController::SNSUserController(HealthcareCenter* hc) {
    this->hc = hc;
}

bool SNSUserController::registerSNSUser(
    std::string snsNumber,
    std::string name,
    std::string address,
    std::string birthdate,
    std::string phone,
    std::string citizenCardNumber,
    std::string sex) {

    if (snsNumber.empty() || name.empty() || address.empty() || birthdate.empty() ||
        phone.empty() || citizenCardNumber.empty()) {
        return false;
    }

    if (!isValidPhone(phone) || !isValidCC(citizenCardNumber) || !isValidDate(birthdate)) {
        return false;
    }

    SNSUser* user = new SNSUser(snsNumber, name, address, birthdate, phone, citizenCardNumber, sex);
    bool success = hc->registerSNSUser(user);
    if (!success) {
        delete user;
    } else {
        FileManager::saveSNSUserRegistry(hc, "sns_users.txt");
    }

    return success;
}

bool SNSUserController::updateSNSUser(const std::string& snsNumber, const std::string& newAddress, const std::string& newPhone) {
    SNSUser* user = hc->findSNSUserByNumber(snsNumber);
    if (user != nullptr) {
        user->setAddress(newAddress);
        user->setPhone(newPhone);
        FileManager::saveSNSUserRegistry(hc, "sns_users.txt");
        return true;
    }
    return false;
}
