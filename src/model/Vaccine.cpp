#include "Vaccine.h"

Vaccine::Vaccine(std::string brand, std::string lotNumber, std::string expirationDate, int quantity, VaccineType* type)
    : brand(brand), lotNumber(lotNumber), expirationDate(expirationDate), quantity(quantity), type(type) {}

std::string Vaccine::getBrand() const { return brand; }

std::string Vaccine::getLotNumber() const { return lotNumber; }

std::string Vaccine::getExpirationDate() const { return expirationDate; }

int Vaccine::getQuantity() const { return quantity; }

VaccineType* Vaccine::getType() const { return type; }
