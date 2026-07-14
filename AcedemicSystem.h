#ifndef ACADEMIC_SYSTEM_H
#define ACADEMIC_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <regex>
#include <stdexcept>
#include <limits>
#include <conio.h>
#include <windows.h>

using namespace std;

// Color Constants
enum ConsoleColor {
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

// Global Functions
void setColor(int color);
void resetColor();
void clearScreen();
void displayHeader(const string& title);
void displayFooter();
void displayLoading();
void pauseScreen();
void displaySuccess(const string& message);
void displayError(const string& message);
void displayWarning(const string& message);
void displayInfo(const string& message);
string getCurrentDateTime();
bool isValidEmail(const string& email);
bool isValidName(const string& name);
bool isValidPassword(const string& password);
string trim(const string& str);
void clearInputBuffer();

// Forward Declarations
class Subject;
class Semester;
class Student;
class GradeCalculator;
class GPAController;
class BellCurvePredictor;
class ReportGenerator;
class Validator;
class FileManager;
class Authentication;
class Dashboard;

#endif