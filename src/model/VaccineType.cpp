//
// Created by pedroguilherme on 07/05/26.
//
#include "VaccineType.h"

VaccineType::VaccineType(std::string code, std::string disease, std::string technology, int recoveryPeriod)
    : code(code), disease(disease), technology(technology), recoveryPeriod(recoveryPeriod) {
}

std::string VaccineType::getCode() const {
    return code;
}

std::string VaccineType::getDisease() const {
    return disease;
}

std::string VaccineType::getTechnology() const {
    return technology;
}

int VaccineType::getRecoveryPeriod() const {
    return recoveryPeriod;
}
