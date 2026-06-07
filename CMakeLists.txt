cmake_minimum_required(VERSION 4.0.2)
project(fsoft2026_1DD_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/model src/controller src/view)

set(COMMON_SOURCES
    src/model/Employee.cpp
    src/model/Vaccine.cpp
    src/model/VaccineType.cpp
    src/model/HealthcareCenter.cpp
    src/controller/EmployeeController.cpp
    src/controller/VaccineController.cpp
    src/model/SNSUser.cpp
    src/model/CenterAdministrator.cpp
    src/model/Receptionist.cpp
    src/model/Nurse.cpp
    src/model/FileManager.cpp
    src/view/Utils.cpp
)

add_executable(fsoft2026_1DD_1
    src/main.cpp
    src/view/MainMenu.cpp
    ${COMMON_SOURCES}
)

# Fetch and build GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ProjectTester
    ProjectTester/main_test.cpp
    ${COMMON_SOURCES}
)

# Link GoogleTest to the testing executable
target_link_libraries(ProjectTester gtest_main)

include(GoogleTest)
gtest_discover_tests(ProjectTester)