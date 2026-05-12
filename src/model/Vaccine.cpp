//
// Created by pc-andre on 4/26/26.
//

#include "Vaccine.h"

Vaccine::Vaccine()
{
    code = "";
    disease = "";
    technology = "";
    recoveryPeriod = 0;
}

Vaccine::Vaccine(string code,
                 string disease,
                 string technology,
                 int recoveryPeriod)
{
    this->code = code;
    this->disease = disease;
    this->technology = technology;
    this->recoveryPeriod = recoveryPeriod;
}

string Vaccine::getCode() const
{
    return code;
}

string Vaccine::getDisease() const
{
    return disease;
}

string Vaccine::getTechnology() const
{
    return technology;
}

int Vaccine::getRecoveryPeriod() const
{
    return recoveryPeriod;
}