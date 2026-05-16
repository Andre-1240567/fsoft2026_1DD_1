#ifndef FSOFT2026_1DD_1_VACCINE_H
#define FSOFT2026_1DD_1_VACCINE_H

#include <string>
#include "VaccineType.h"

class Vaccine {
private:
    std::string brand;
    std::string lotNumber;
    std::string expirationDate;
    int quantity;
    VaccineType* type;

public:
    Vaccine(std::string brand, std::string lotNumber, std::string expirationDate, int quantity, VaccineType* type);
    
    // Getters
    std::string getBrand() const;
    std::string getLotNumber() const;
    std::string getExpirationDate() const;
    int getQuantity() const;
    VaccineType* getType() const;
};

#endif