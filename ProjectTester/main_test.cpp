#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <cstdio>

#include "HealthcareCenter.h"
#include "VaccineController.h"
#include "EmployeeController.h"
#include "SNSUserController.h"
#include "AppointmentController.h"
#include "NurseController.h"
#include "VaccineType.h"
#include "Vaccine.h"
#include "Employee.h"
#include "SNSUser.h"
#include "Appointment.h"
#include "FileManager.h"
#include "Utils.h"
#include "ExportController.h"
#include <fstream>

// =========================================================================
// UC1 Tests - Specify Vaccine Type
// =========================================================================

TEST(UC1_Tests, CreateMultipleVaccineTypes) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);

    // Should create successfully
    EXPECT_TRUE(vc.createVaccineType("V-001", "COVID-19", "mRNA", 30));
    EXPECT_TRUE(vc.createVaccineType("V-002", "Flu", "Viral Vector", 15));
    
    // Check if they were added to the catalog
    EXPECT_EQ(hc.getVaccineCatalog().size(), 2);
    EXPECT_EQ(hc.getVaccineCatalog()[0]->getCode(), "V-001");
    EXPECT_EQ(hc.getVaccineCatalog()[1]->getCode(), "V-002");
}

TEST(UC1_Tests, RejectDuplicateVaccineType) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);

    EXPECT_TRUE(vc.createVaccineType("V-001", "COVID-19", "mRNA", 30));
    
    // Duplicate code should fail and NOT be added to the catalog
    EXPECT_FALSE(vc.createVaccineType("V-001", "Different Disease", "Subunit Protein", 45));
    EXPECT_EQ(hc.getVaccineCatalog().size(), 1);
}

// =========================================================================
// UC2 Tests - Register Physical Vaccine
// =========================================================================

TEST(UC2_Tests, RegisterMultipleVaccineLots) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);

    vc.createVaccineType("V-001", "COVID-19", "mRNA", 30);
    
    // Valid registrations on the same type
    EXPECT_TRUE(vc.registerVaccine(0, "Comirnaty", "Pfizer", "LOT123", "2026-12-31", 500));
    EXPECT_TRUE(vc.registerVaccine(0, "Spikevax", "Moderna", "LOT999", "2027-01-01", 1000));
    
    EXPECT_EQ(hc.getInventory().size(), 2);
    EXPECT_EQ(hc.getInventory()[0]->getQuantity(), 500);
    EXPECT_EQ(hc.getInventory()[1]->getQuantity(), 1000);
}

TEST(UC2_Tests, RejectDuplicateVaccineLots) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);

    vc.createVaccineType("V-001", "COVID-19", "mRNA", 30);
    
    // First lot succeeds
    EXPECT_TRUE(vc.registerVaccine(0, "Comirnaty", "Pfizer", "LOT123", "2026-12-31", 500));
    
    // Exact same brand and lot number should fail
    EXPECT_FALSE(vc.registerVaccine(0, "Comirnaty", "Pfizer", "LOT123", "2026-12-31", 1000));
    
    // Same lot number but different brand should succeed
    EXPECT_TRUE(vc.registerVaccine(0, "Spikevax", "Moderna", "LOT123", "2026-12-31", 1000));

    EXPECT_EQ(hc.getInventory().size(), 2);
}

TEST(UC2_Tests, RejectInvalidTypeIndex) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);

    vc.createVaccineType("V-001", "COVID-19", "mRNA", 30);
    
    // Out of bounds index (1) should fail, catalog only has index 0
    EXPECT_FALSE(vc.registerVaccine(1, "Spikevax", "Moderna", "LOT456", "2026-12-31", 300));
    
    // Negative index should fail
    EXPECT_FALSE(vc.registerVaccine(-1, "Spikevax", "Moderna", "LOT456", "2026-12-31", 300));

    EXPECT_EQ(hc.getInventory().size(), 0);
}

// =========================================================================
// UC3 Tests - Register Employee
// =========================================================================

TEST(UC3_Tests, RegisterDifferentRoles) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    EmployeeController ec(&hc);

    EXPECT_TRUE(ec.registerEmployee("John", "910000001", "john@med.pt", "CC001", "Nurse"));
    EXPECT_TRUE(ec.registerEmployee("Jane", "910000002", "jane@med.pt", "CC002", "Receptionist"));
    
    // In our model, we also have Center Administrator
    EXPECT_TRUE(ec.registerEmployee("Admin", "910000003", "admin@med.pt", "CC003", "Center Administrator"));

    EXPECT_EQ(hc.getEmployees().size(), 3);
}

TEST(UC3_Tests, RejectDuplicateEmployeeData) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    EmployeeController ec(&hc);

    EXPECT_TRUE(ec.registerEmployee("Original", "910000001", "orig@med.pt", "CC001", "Nurse"));

    // Duplicate email
    EXPECT_FALSE(ec.registerEmployee("Copy1", "910000002", "orig@med.pt", "CC002", "Nurse"));
    // Duplicate phone
    EXPECT_FALSE(ec.registerEmployee("Copy2", "910000001", "copy2@med.pt", "CC003", "Nurse"));
    // Duplicate CC
    EXPECT_FALSE(ec.registerEmployee("Copy3", "910000004", "copy3@med.pt", "CC001", "Nurse"));

    // Ensure only the original was added
    EXPECT_EQ(hc.getEmployees().size(), 1);
}

TEST(UC3_Tests, RejectInvalidRole) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    EmployeeController ec(&hc);

    EXPECT_FALSE(ec.registerEmployee("Invalid", "910000004", "inv@med.pt", "CC004", "Doctor"));
    EXPECT_EQ(hc.getEmployees().size(), 0);
}

// =========================================================================
// UC4 Tests - List Employees By Role
// =========================================================================

TEST(UC4_Tests, ListEmployeesEmptyAndFilled) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    EmployeeController ec(&hc);

    // Empty center
    EXPECT_EQ(ec.getEmployeesByRole("Nurse").size(), 0);

    // Add some employees
    ec.registerEmployee("N1", "910000001", "n1@med.pt", "CC001", "Nurse");
    ec.registerEmployee("N2", "910000002", "n2@med.pt", "CC002", "Nurse");
    ec.registerEmployee("R1", "910000003", "r1@med.pt", "CC003", "Receptionist");

    std::vector<Employee*> nurses = ec.getEmployeesByRole("Nurse");
    EXPECT_EQ(nurses.size(), 2);
    EXPECT_EQ(nurses[0]->getName(), "N1");
    EXPECT_EQ(nurses[1]->getName(), "N2");
    
    std::vector<Employee*> receps = ec.getEmployeesByRole("Receptionist");
    EXPECT_EQ(receps.size(), 1);
    EXPECT_EQ(receps[0]->getName(), "R1");
}

// =========================================================================
// UC5 Tests - List Vaccine Stock
// =========================================================================

TEST(UC5_Tests, ListVaccineStockAlphabeticalSorting) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);

    vc.createVaccineType("V-001", "COVID", "mRNA", 30);
    vc.createVaccineType("V-002", "Flu", "Viral Vector", 15);

    // Register Vaccines out of alphabetical order
    vc.registerVaccine(0, "Comirnaty", "Pfizer", "L1", "2026-12", 100);
    vc.registerVaccine(0, "Vaxzevria", "AstraZeneca", "L3", "2026-12", 50);
    vc.registerVaccine(0, "Spikevax", "Moderna", "L2", "2026-12", 200);

    vc.registerVaccine(1, "Z-Shot", "Z-Pharma", "L4", "2026-12", 10);
    vc.registerVaccine(1, "AlphaVax", "AlphaMed", "L5", "2026-12", 20);

    auto grouped = vc.getVaccineStockGroupedAndSorted();
    EXPECT_EQ(grouped.size(), 2);

    VaccineType* vtCovid = hc.getVaccineCatalog()[0]; // V-001
    VaccineType* vtFlu   = hc.getVaccineCatalog()[1]; // V-002

    EXPECT_EQ(grouped[vtCovid].size(), 3);
    EXPECT_EQ(grouped[vtFlu].size(), 2);
    
    // Verify strict alphabetical sorting for COVID vaccines
    EXPECT_EQ(grouped[vtCovid][0]->getBrand(), "AstraZeneca");
    EXPECT_EQ(grouped[vtCovid][1]->getBrand(), "Moderna");
    EXPECT_EQ(grouped[vtCovid][2]->getBrand(), "Pfizer");

    // Verify strict alphabetical sorting for Flu vaccines
    EXPECT_EQ(grouped[vtFlu][0]->getBrand(), "AlphaMed");
    EXPECT_EQ(grouped[vtFlu][1]->getBrand(), "Z-Pharma");
}

TEST(UC5_Tests, EmptyVaccineStock) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);

    // Even if types exist, if there's no inventory, the map should be empty
    vc.createVaccineType("V-001", "COVID", "mRNA", 30);

    auto grouped = vc.getVaccineStockGroupedAndSorted();
    EXPECT_TRUE(grouped.empty());
}

// =========================================================================
// UC6 Tests - Register SNS User
// =========================================================================

TEST(UC6_Tests, RegisterSNSUserWithMandatoryAndOptionalFields) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);

    EXPECT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678", "Female"));

    ASSERT_EQ(hc.getSnsUsersRegistry().size(), 1);
    EXPECT_EQ(hc.getSnsUsersRegistry()[0]->getName(), "Maria");
    EXPECT_EQ(hc.getSnsUsersRegistry()[0]->getSex(), "Female");
}

TEST(UC6_Tests, RegisterSNSUserWithoutSex) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);

    EXPECT_TRUE(sc.registerSNSUser("SNS002", "Joao", "Rua B", "1985-05-05", "912345679", "12345679"));

    ASSERT_EQ(hc.getSnsUsersRegistry().size(), 1);
    EXPECT_EQ(hc.getSnsUsersRegistry()[0]->getSex(), "N/A");
}

TEST(UC6_Tests, RejectInvalidOrMissingSNSUserData) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);

    EXPECT_FALSE(sc.registerSNSUser("", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    EXPECT_FALSE(sc.registerSNSUser("SNS001", "", "Rua A", "1990-01-01", "912345678", "12345678"));
    EXPECT_FALSE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "123456789", "12345678"));
    EXPECT_FALSE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "1234567"));
    EXPECT_FALSE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "01-01-1990", "912345678", "12345678"));

    EXPECT_EQ(hc.getSnsUsersRegistry().size(), 0);
}

TEST(UC6_Tests, RejectDuplicatePhoneAndSNSNumber) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);

    EXPECT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));

    EXPECT_FALSE(sc.registerSNSUser("SNS002", "Ana", "Rua B", "1991-01-01", "912345678", "12345679"));
    EXPECT_FALSE(sc.registerSNSUser("SNS001", "Pedro", "Rua C", "1992-01-01", "912345679", "12345680"));

    EXPECT_EQ(hc.getSnsUsersRegistry().size(), 1);
}

TEST(UC6_Tests, PersistSNSUserRegistry) {
    const std::string filename = "test_sns_users.txt";

    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUser* user = new SNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678", "Female");
    ASSERT_TRUE(hc.registerSNSUser(user));

    EXPECT_TRUE(FileManager::saveSNSUserRegistry(&hc, filename));

    HealthcareCenter loaded("Loaded Center", "Addr", "123", "email@test.com");
    EXPECT_TRUE(FileManager::loadSNSUserRegistry(&loaded, filename));

    ASSERT_EQ(loaded.getSnsUsersRegistry().size(), 1);
    EXPECT_EQ(loaded.getSnsUsersRegistry()[0]->getSnsNumber(), "SNS001");
    EXPECT_EQ(loaded.getSnsUsersRegistry()[0]->getPhone(), "912345678");

    std::remove(filename.c_str());
}

// =========================================================================
// UC7 Tests - Schedule Vaccine Administration
// =========================================================================

TEST(UC7_Tests, ScheduleAppointmentForExistingSNSUserAndVaccineType) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);

    ASSERT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    ASSERT_TRUE(vc.createVaccineType("COVID", "COVID-19", "mRNA", 30));

    EXPECT_TRUE(ac.createAppointment("SNS001", "COVID", "2026-06-09", "10:30"));

    ASSERT_EQ(hc.getAppointments().size(), 1);
    EXPECT_EQ(hc.getAppointments()[0]->getUser()->getSnsNumber(), "SNS001");
    EXPECT_EQ(hc.getAppointments()[0]->getVaccineType()->getCode(), "COVID");
    EXPECT_EQ(hc.getAppointments()[0]->getStatus(), "SCHEDULED");
}

TEST(UC7_Tests, RejectUnknownUserUnknownTypeInvalidDateTimeAndDuplicatePendingAppointment) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);

    ASSERT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    ASSERT_TRUE(vc.createVaccineType("COVID", "COVID-19", "mRNA", 30));

    EXPECT_FALSE(ac.createAppointment("SNS999", "COVID", "2026-06-09", "10:30"));
    EXPECT_FALSE(ac.createAppointment("SNS001", "FLU", "2026-06-09", "10:30"));
    EXPECT_FALSE(ac.createAppointment("SNS001", "COVID", "09-06-2026", "10:30"));
    EXPECT_FALSE(ac.createAppointment("SNS001", "COVID", "2026-06-09", "25:00"));

    EXPECT_TRUE(ac.createAppointment("SNS001", "COVID", "2026-06-09", "10:30"));
    EXPECT_FALSE(ac.createAppointment("SNS001", "COVID", "2026-06-10", "11:00"));
    EXPECT_EQ(hc.getAppointments().size(), 1);
}

// =========================================================================
// UC8 Tests - Register SNS User Arrival
// =========================================================================

TEST(UC8_Tests, RegisterArrivalForTodayMovesUserToWaitingRoom) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);

    ASSERT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    ASSERT_TRUE(vc.createVaccineType("COVID", "COVID-19", "mRNA", 30));
    ASSERT_TRUE(ac.createAppointment("SNS001", "COVID", AppointmentController::currentDate(), "10:30"));

    EXPECT_TRUE(ac.registerArrival("SNS001"));

    ASSERT_EQ(hc.getWaitingRoom().size(), 1);
    EXPECT_EQ(hc.getWaitingRoom()[0]->getSnsNumber(), "SNS001");
    EXPECT_EQ(hc.getAppointments()[0]->getStatus(), "WAITING");
}

TEST(UC8_Tests, RejectDuplicateArrivalAndUsersWithoutAppointmentToday) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);

    ASSERT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    ASSERT_TRUE(sc.registerSNSUser("SNS002", "Joao", "Rua B", "1985-05-05", "912345679", "12345679"));
    ASSERT_TRUE(vc.createVaccineType("COVID", "COVID-19", "mRNA", 30));
    ASSERT_TRUE(ac.createAppointment("SNS001", "COVID", AppointmentController::currentDate(), "10:30"));

    EXPECT_TRUE(ac.registerArrival("SNS001"));
    EXPECT_FALSE(ac.registerArrival("SNS001"));
    EXPECT_FALSE(ac.registerArrival("SNS002"));
    EXPECT_EQ(hc.getWaitingRoom().size(), 1);
}

// =========================================================================
// UC9 Tests - Consult Waiting Room
// =========================================================================

TEST(UC9_Tests, WaitingRoomIsListedInFifoOrder) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);
    NurseController nc(&hc);

    ASSERT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    ASSERT_TRUE(sc.registerSNSUser("SNS002", "Joao", "Rua B", "1985-05-05", "912345679", "12345679"));
    ASSERT_TRUE(vc.createVaccineType("COVID", "COVID-19", "mRNA", 30));
    ASSERT_TRUE(ac.createAppointment("SNS001", "COVID", AppointmentController::currentDate(), "10:30"));
    ASSERT_TRUE(ac.createAppointment("SNS002", "COVID", AppointmentController::currentDate(), "11:00"));

    ASSERT_TRUE(ac.registerArrival("SNS001"));
    ASSERT_TRUE(ac.registerArrival("SNS002"));

    std::vector<SNSUser*> waiting = nc.getWaitingRoomUsers();
    ASSERT_EQ(waiting.size(), 2);
    EXPECT_EQ(waiting[0]->getSnsNumber(), "SNS001");
    EXPECT_EQ(waiting[1]->getSnsNumber(), "SNS002");
}

// =========================================================================
// UC10 Tests - Record Vaccine Administration
// =========================================================================

TEST(UC10_Tests, RecordAdministrationMovesUserToRecoveryAndUpdatesStockAndAppointment) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);
    NurseController nc(&hc);

    ASSERT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    ASSERT_TRUE(vc.createVaccineType("COVID", "COVID-19", "mRNA", 30));
    ASSERT_TRUE(vc.registerVaccine(0, "Comirnaty", "Pfizer", "LOT123", "2027-12-31", 5));
    ASSERT_TRUE(ac.createAppointment("SNS001", "COVID", AppointmentController::currentDate(), "10:30"));
    ASSERT_TRUE(ac.registerArrival("SNS001"));

    EXPECT_TRUE(nc.recordAdministration("SNS001", "LOT123"));

    EXPECT_EQ(hc.getWaitingRoom().size(), 0);
    ASSERT_EQ(hc.getRecoveryRoom().size(), 1);
    EXPECT_EQ(hc.getRecoveryRoom()[0]->getSnsNumber(), "SNS001");
    EXPECT_EQ(hc.getInventory()[0]->getQuantity(), 4);
    EXPECT_EQ(hc.getAppointments()[0]->getStatus(), "ADMINISTERED");
    EXPECT_FALSE(hc.getAppointments()[0]->getAdministeredAt().empty());
    EXPECT_EQ(hc.getAppointments()[0]->getAdministeredLotNumber(), "LOT123");
}

TEST(UC10_Tests, RejectAdministrationForUserNotWaitingOrWrongVaccineType) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);
    NurseController nc(&hc);

    ASSERT_TRUE(sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678"));
    ASSERT_TRUE(vc.createVaccineType("COVID", "COVID-19", "mRNA", 30));
    ASSERT_TRUE(vc.createVaccineType("FLU", "Flu", "Viral Vector", 15));
    ASSERT_TRUE(vc.registerVaccine(0, "Comirnaty", "Pfizer", "LOT123", "2027-12-31", 5));
    ASSERT_TRUE(vc.registerVaccine(1, "FluShot", "AlphaMed", "LOT999", "2027-12-31", 5));
    ASSERT_TRUE(ac.createAppointment("SNS001", "COVID", AppointmentController::currentDate(), "10:30"));

    EXPECT_FALSE(nc.recordAdministration("SNS001", "LOT123"));

    ASSERT_TRUE(ac.registerArrival("SNS001"));
    EXPECT_FALSE(nc.recordAdministration("SNS001", "LOT999"));
    EXPECT_EQ(hc.getWaitingRoom().size(), 1);
    EXPECT_EQ(hc.getRecoveryRoom().size(), 0);
}

// =========================================================================
// UC11 Tests - Export Healthcare Center Reports
// =========================================================================

TEST(UC11_Tests, ExportEmployeesCreatesFile) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    EmployeeController ec(&hc);
    ExportController xc(&hc);

    ec.registerEmployee("John", "910000001", "john@med.pt", "CC001", "Nurse");
    ec.registerEmployee("Jane", "910000002", "jane@med.pt", "CC002", "Receptionist");

    EXPECT_TRUE(xc.exportEmployees("test_report_employees.csv"));

    std::ifstream file("test_report_employees.csv");
    EXPECT_TRUE(file.is_open());
    file.close();

    std::remove("test_report_employees.csv");
}

TEST(UC11_Tests, ExportEmployeesFileHasCorrectContent) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    EmployeeController ec(&hc);
    ExportController xc(&hc);

    ec.registerEmployee("John", "910000001", "john@med.pt", "CC001", "Nurse");

    EXPECT_TRUE(xc.exportEmployees("test_report_employees.csv"));

    std::ifstream file("test_report_employees.csv");
    std::string header, line;
    std::getline(file, header);
    std::getline(file, line);
    file.close();

    EXPECT_EQ(header, "Name;Phone;Email;CitizenCard;Role");
    EXPECT_NE(line.find("John"), std::string::npos);
    EXPECT_NE(line.find("910000001"), std::string::npos);
    EXPECT_NE(line.find("Nurse"), std::string::npos);

    std::remove("test_report_employees.csv");
}

TEST(UC11_Tests, ExportEmployeesReturnsFalseWhenEmpty) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    ExportController xc(&hc);

    EXPECT_FALSE(xc.exportEmployees("test_report_employees.csv"));

    std::ifstream file("test_report_employees.csv");
    EXPECT_FALSE(file.is_open());
}

TEST(UC11_Tests, ExportInventoryCreatesFile) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);
    ExportController xc(&hc);

    vc.createVaccineType("V-001", "COVID-19", "mRNA", 30);
    vc.registerVaccine(0, "Comirnaty", "Pfizer", "LOT123", "2027-12-31", 500);

    EXPECT_TRUE(xc.exportInventory("test_report_inventory.csv"));

    std::ifstream file("test_report_inventory.csv");
    EXPECT_TRUE(file.is_open());
    file.close();

    std::remove("test_report_inventory.csv");
}

TEST(UC11_Tests, ExportInventoryFileHasCorrectContent) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    VaccineController vc(&hc);
    ExportController xc(&hc);

    vc.createVaccineType("V-001", "COVID-19", "mRNA", 30);
    vc.registerVaccine(0, "Comirnaty", "Pfizer", "LOT123", "2027-12-31", 500);

    EXPECT_TRUE(xc.exportInventory("test_report_inventory.csv"));

    std::ifstream file("test_report_inventory.csv");
    std::string header, line;
    std::getline(file, header);
    std::getline(file, line);
    file.close();

    EXPECT_EQ(header, "CommercialName;Brand;LotNumber;ExpirationDate;Quantity;VaccineType");
    EXPECT_NE(line.find("Comirnaty"), std::string::npos);
    EXPECT_NE(line.find("Pfizer"), std::string::npos);
    EXPECT_NE(line.find("LOT123"), std::string::npos);
    EXPECT_NE(line.find("V-001"), std::string::npos);

    std::remove("test_report_inventory.csv");
}

TEST(UC11_Tests, ExportInventoryReturnsFalseWhenEmpty) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    ExportController xc(&hc);

    EXPECT_FALSE(xc.exportInventory("test_report_inventory.csv"));

    std::ifstream file("test_report_inventory.csv");
    EXPECT_FALSE(file.is_open());
}

TEST(UC11_Tests, ExportSNSUsersCreatesFile) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    ExportController xc(&hc);

    sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678", "Female");

    EXPECT_TRUE(xc.exportSNSUsers("test_report_sns_users.csv"));

    std::ifstream file("test_report_sns_users.csv");
    EXPECT_TRUE(file.is_open());
    file.close();

    std::remove("test_report_sns_users.csv");
}

TEST(UC11_Tests, ExportSNSUsersFileHasCorrectContent) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    ExportController xc(&hc);

    sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678", "Female");

    EXPECT_TRUE(xc.exportSNSUsers("test_report_sns_users.csv"));

    std::ifstream file("test_report_sns_users.csv");
    std::string header, line;
    std::getline(file, header);
    std::getline(file, line);
    file.close();

    EXPECT_EQ(header, "SNSNumber;Name;Address;Birthdate;Phone;CitizenCard;Sex");
    EXPECT_NE(line.find("SNS001"), std::string::npos);
    EXPECT_NE(line.find("Maria"), std::string::npos);
    EXPECT_NE(line.find("Female"), std::string::npos);

    std::remove("test_report_sns_users.csv");
}

TEST(UC11_Tests, ExportSNSUsersReturnsFalseWhenEmpty) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    ExportController xc(&hc);

    EXPECT_FALSE(xc.exportSNSUsers("test_report_sns_users.csv"));

    std::ifstream file("test_report_sns_users.csv");
    EXPECT_FALSE(file.is_open());
}

TEST(UC11_Tests, ExportAppointmentsCreatesFile) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);
    ExportController xc(&hc);

    sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678");
    vc.createVaccineType("COVID", "COVID-19", "mRNA", 30);
    ac.createAppointment("SNS001", "COVID", "2026-06-09", "10:30");

    EXPECT_TRUE(xc.exportAppointments("test_report_appointments.csv"));

    std::ifstream file("test_report_appointments.csv");
    EXPECT_TRUE(file.is_open());
    file.close();

    std::remove("test_report_appointments.csv");
}

TEST(UC11_Tests, ExportAppointmentsFileHasCorrectContent) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    SNSUserController sc(&hc);
    VaccineController vc(&hc);
    AppointmentController ac(&hc);
    ExportController xc(&hc);

    sc.registerSNSUser("SNS001", "Maria", "Rua A", "1990-01-01", "912345678", "12345678");
    vc.createVaccineType("COVID", "COVID-19", "mRNA", 30);
    ac.createAppointment("SNS001", "COVID", "2026-06-09", "10:30");

    EXPECT_TRUE(xc.exportAppointments("test_report_appointments.csv"));

    std::ifstream file("test_report_appointments.csv");
    std::string header, line;
    std::getline(file, header);
    std::getline(file, line);
    file.close();

    EXPECT_EQ(header, "DateTime;SNSNumber;UserName;VaccineType;Status");
    EXPECT_NE(line.find("SNS001"), std::string::npos);
    EXPECT_NE(line.find("Maria"), std::string::npos);
    EXPECT_NE(line.find("COVID"), std::string::npos);
    EXPECT_NE(line.find("SCHEDULED"), std::string::npos);

    std::remove("test_report_appointments.csv");
}

TEST(UC11_Tests, ExportAppointmentsReturnsFalseWhenEmpty) {
    HealthcareCenter hc("Test Center", "Addr", "123", "email@test.com");
    ExportController xc(&hc);

    EXPECT_FALSE(xc.exportAppointments("test_report_appointments.csv"));

    std::ifstream file("test_report_appointments.csv");
    EXPECT_FALSE(file.is_open());
}

// =========================================================================
// Utils Tests - Formatting and Validations
// =========================================================================

TEST(Utils_Tests, ValidateEmail) {
    EXPECT_TRUE(isValidEmail("test@example.com"));
    EXPECT_FALSE(isValidEmail("joao"));
}

TEST(Utils_Tests, ValidateDate) {
    EXPECT_TRUE(isValidDate("2026-12-31"));
    EXPECT_FALSE(isValidDate("amanha"));
    EXPECT_FALSE(isValidDate("2026/12/31"));
}

TEST(Utils_Tests, ValidatePhone) {
    EXPECT_TRUE(isValidPhone("912345678"));
    EXPECT_FALSE(isValidPhone("123456789"));
    EXPECT_FALSE(isValidPhone("91234567a"));
}

TEST(Utils_Tests, ValidateCC) {
    EXPECT_TRUE(isValidCC("12345678"));
    EXPECT_TRUE(isValidCC("12345678 1 ZZ 1"));
    EXPECT_FALSE(isValidCC("1234567"));
}
