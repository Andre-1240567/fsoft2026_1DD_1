#include "VaccineController.h"
#include "../model/VaccineType.h"
#include "../model/HealthcareCenter.h"
#include "../model/Vaccine.h"
#include "../model/FileManager.h"
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

    bool success = hc->addVaccineType(vt);
    if (!success) {
        delete vt;
    } else {
        FileManager::saveVaccineTypes(hc, "vaccine_types.txt");
    }
    return success;
}


// UC2

std::vector<VaccineType*> VaccineController::getVaccineCatalog() {
    return hc->getVaccineCatalog();
}

std::vector<Vaccine*> VaccineController::getInventory() {
    return hc->getInventory();
}

bool VaccineController::registerVaccine(int typeIndex, std::string commercialName, std::string brand, std::string lot, std::string expiry, int qty) {
    std::vector<VaccineType*> catalog = hc->getVaccineCatalog();

    if (typeIndex < 0 || typeIndex >= catalog.size()) {
        return false;
    }

    VaccineType* selectedType = catalog[typeIndex];
    Vaccine* v = new Vaccine(commercialName, brand, lot, expiry, qty, selectedType);
    bool success = hc->addVaccineToInventory(v);
    
    if (!success) {
        delete v;
        return false;
    }

    FileManager::saveVaccines(hc, "vaccines.txt");
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
