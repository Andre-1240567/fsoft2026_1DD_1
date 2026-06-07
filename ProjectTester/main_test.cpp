#include <gtest/gtest.h>
#include <vector>
#include <map>

#include "HealthcareCenter.h"
#include "VaccineController.h"
#include "EmployeeController.h"
#include "VaccineType.h"
#include "Vaccine.h"
#include "Employee.h"
#include "Utils.h"

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
