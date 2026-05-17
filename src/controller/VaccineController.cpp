#include "VaccineController.h"
#include "../model/VaccineType.h"
#include "../model/HealthcareCenter.h"
#include "../model/Vaccine.h"
#include <string>
#include <vector>
#include <algorithm>

VaccineController::VaccineController(HealthcareCenter* hc)
{
    this->hc = hc;
}

bool VaccineController::createVaccineType(
        std::string code,
        std::string disease,
        std::string technology,
        int recoveryPeriod)
{
    VaccineType* vt = new VaccineType(
            code,
            disease,
            technology,
            recoveryPeriod);

    return hc->addVaccineType(vt);
}


// UC2

std::vector<VaccineType*> VaccineController::getVaccineCatalog() {
    return hc->getVaccineCatalog();
}

bool VaccineController::registerVaccine(int typeIndex, std::string brand, std::string lot, std::string expiry, int qty) {
    std::vector<VaccineType*> catalog = hc->getVaccineCatalog();

    if (typeIndex < 0 || typeIndex >= catalog.size()) {
        return false;
    }

    VaccineType* selectedType = catalog[typeIndex];
    Vaccine* v = new Vaccine(brand, lot, expiry, qty, selectedType);
    hc->addVaccineToInventory(v);

    return true;
}

// UC3

bool compareVaccinesByBrand(Vaccine* a, Vaccine* b) {
    return a->getBrand() < b->getBrand();
}

std::map<VaccineType*, std::vector<Vaccine*>> VaccineController::getVaccineStockGroupedAndSorted() {
    std::map<VaccineType*, std::vector<Vaccine*>> groupedStock;
    std::vector<Vaccine*> inventory = hc->getInventory();

    for (Vaccine* v : inventory) {
        groupedStock[v->getType()].push_back(v);
    }

    for (auto& pair : groupedStock) {
        std::sort(pair.second.begin(), pair.second.end(), compareVaccinesByBrand);
    }

    return groupedStock;
}