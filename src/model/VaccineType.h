//
// Created by pedroguilherme on 07/05/26.
//

#ifndef FSOFT2026_1DD_1_VACCINETYPE_H
#define FSOFT2026_1DD_1_VACCINETYPE_H

#include <string>

class VaccineType {
private:
    std::string code;
    std::string disease;
    std::string technology;
    int recoveryPeriod;

public:
    VaccineType(std::string code,
                std::string disease,
                std::string technology,
                int recoveryPeriod);

    std::string getCode() const;
};

#endif // FSOFT2026_1DD_1_VACCINETYPE_H