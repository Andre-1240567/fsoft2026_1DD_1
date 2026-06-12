#include "Vaccine.h"

Vaccine::Vaccine(std::string commercialName, std::string brand, std::string lotNumber, std::string expirationDate, int quantity, VaccineType* type)
    : commercialName(commercialName), brand(brand), lotNumber(lotNumber), expirationDate(expirationDate), quantity(quantity), type(type) {}

std::string Vaccine::getCommercialName() const { return commercialName; }

std::string Vaccine::getBrand() const { return brand; }

std::string Vaccine::getLotNumber() const { return lotNumber; }

std::string Vaccine::getExpirationDate() const { return expirationDate; }

int Vaccine::getQuantity() const { return quantity; }

VaccineType* Vaccine::getType() const { return type; }

bool Vaccine::decreaseQuantity(int amount) {
    if (amount <= 0 || quantity < amount) {
        return false;
    }

    quantity -= amount;
    return true;
}

void Vaccine::setQuantity(int newQuantity) {
    quantity = newQuantity;
}
