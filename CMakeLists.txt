cmake_minimum_required(VERSION 4.0.2)
project(fsoft2026_1DD_1)

set(CMAKE_CXX_STANDARD 14)


include_directories(src/model src/controller src/view)



add_executable(fsoft2026_1DD_1
        src/main.cpp
        src/model/Employee.h
        src/model/Employee.cpp
        src/model/Vaccine.cpp
        src/model/Vaccine.h
        src/model/HealthcareCenter.cpp
        src/model/HealthcareCenter.h
        src/controller/EmployeeController.cpp
        src/controller/EmployeeController.h
        src/controller/VaccineController.cpp
        src/controller/VaccineController.h
        src/view/MainMenu.cpp
        src/view/MainMenu.h
        src/view/Utils.cpp
        src/view/Utils.h
)