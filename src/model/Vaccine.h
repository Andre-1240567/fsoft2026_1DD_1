//
// Created by pc-andre on 4/26/26.
//

#ifndef FSOFT2026_1DD_1_VACCINE_H
#define FSOFT2026_1DD_1_VACCINE_H

#include <string>

using namespace std;

class Vaccine
{
private:
    string code;
    string disease;
    string technology;
    int recoveryPeriod;

public:
    Vaccine();

    Vaccine(string code,
            string disease,
            string technology,
            int recoveryPeriod);
    string getCode() const;
    string getDisease() const;
    string getTechnology() const;
    int getRecoveryPeriod() const;
};

#endif //FSOFT2026_1DD_1_VACCINE_H