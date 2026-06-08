//
// Created by pc-andre on 4/26/26.
//

#include "Utils.h"
#include <iostream>
#include <limits>
#include <cctype>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int readInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [ERROR] Invalid option. Enter a number between "
                  << min << " and " << max << ".\n";
    }
}

bool isValidPhone(const std::string& phone) {
    if (phone.length() != 9) return false;
    if (phone[0] != '9') return false;
    for (char c : phone) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

std::string readPhone(const std::string& prompt) {
    std::string phone;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, phone);
        if (isValidPhone(phone)) return phone;
        std::cout << "  [ERROR] Invalid Phone Number. Must be exactly 9 digits starting with '9'.\n";
    }
}

bool isValidCC(const std::string& cc) {
    int digitCount = 0;
    for (char c : cc) {
        if (std::isdigit(c)) digitCount++;
    }
    return (digitCount >= 8 && cc.length() >= 8);
}

std::string readCC(const std::string& prompt) {
    std::string cc;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, cc);
        if (isValidCC(cc)) return cc;
        std::cout << "  [ERROR] Invalid Citizen Card. Must contain at least 8 digits.\n";
    }
}

bool isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return false;
    }
    return true;
}

bool isValidTime(const std::string& time) {
    if (time.length() != 5 || time[2] != ':') return false;
    for (int i = 0; i < 5; ++i) {
        if (i == 2) continue;
        if (!std::isdigit(time[i])) return false;
    }

    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(3, 2));
    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

std::string readDate(const std::string& prompt) {
    std::string date;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, date);
        if (isValidDate(date)) return date;
        std::cout << "  [ERROR] Invalid date format. Must be YYYY-MM-DD.\n";
    }
}


bool isValidEmail(const std::string& email) {
    return (email.find('@') != std::string::npos && email.find('.') != std::string::npos);
}

std::string readEmail(const std::string& prompt) {
    std::string email;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, email);
        if (isValidEmail(email)) return email;
        std::cout << "  [ERROR] Invalid Email. Must contain '@' and '.'.\n";
    }
}

void pauseConsole() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.get();
}

std::string readTime(const std::string& prompt) {
    std::string time;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, time);
        if (isValidTime(time)) return time;
        std::cout << "  [ERROR] Invalid time format. Must be HH:MM.\n";
    }
}
