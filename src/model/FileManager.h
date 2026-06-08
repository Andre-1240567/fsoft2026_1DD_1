#ifndef FSOFT2026_1DD_1_FILEMANAGER_H
#define FSOFT2026_1DD_1_FILEMANAGER_H

#include <string>
#include <vector>

class HealthcareCenter;

class FileManager {
public:
    static bool saveVaccineTypes(HealthcareCenter* hc, const std::string& filename);
    static bool loadVaccineTypes(HealthcareCenter* hc, const std::string& filename);
    static bool saveVaccines(HealthcareCenter* hc, const std::string& filename);
    static bool loadVaccines(HealthcareCenter* hc, const std::string& filename);
    static bool saveEmployees(HealthcareCenter* hc, const std::string& filename);
    static bool loadEmployees(HealthcareCenter* hc, const std::string& filename);
    static bool saveSNSUserRegistry(HealthcareCenter* hc, const std::string& filename);
    static bool loadSNSUserRegistry(HealthcareCenter* hc, const std::string& filename);
    static bool saveAppointments(HealthcareCenter* hc, const std::string& filename);
    static bool loadAppointments(HealthcareCenter* hc, const std::string& filename);
};

#endif //FSOFT2026_1DD_1_FILEMANAGER_H
