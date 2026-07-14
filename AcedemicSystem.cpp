#include "AcedemicSystem.h"
#include <sstream>
#include <cctype>
#include <random>

// Global Color Functions Implementation
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    setColor(WHITE);
}

void clearScreen() {
    system("cls");
}

void displayHeader(const string& title) {
    clearScreen();
    setColor(CYAN);
    cout << "==================================================\n";
    cout << "     HEC ACADEMIC PERFORMANCE & GPA SYSTEM        \n";
    cout << "==================================================\n";
    setColor(LIGHT_BLUE);
    cout << ">> " << title << " <<\n";
    setColor(WHITE);
    cout << "------------------------------------------\n";
    cout << "Date & Time: " << getCurrentDateTime() << "\n\n";
}
void displayFooter() {
    setColor(GRAY);
    cout << "\n--------------------------------------------------------------------\n";
    cout << "  HEC Academic Performance & GPA Management System v1.0\n";
    cout << "  Developed for Higher Education Commission Pakistan\n";
    resetColor();
}

void displayLoading() {
    setColor(YELLOW);
    cout << "Loading";
    for (int i = 0; i < 3; i++) {
        Sleep(300);
        cout << ".";
    }
    cout << "\n";
    resetColor();
    Sleep(200);
}

void pauseScreen() {
    setColor(GRAY);
    cout << "\nPress any key to continue...";
    getch();
    resetColor();
}

void displaySuccess(const string& message) {
    setColor(GREEN);
    cout << "✓ " << message << "\n";
    resetColor();
}

void displayError(const string& message) {
    setColor(RED);
    cout << "✗ " << message << "\n";
    resetColor();
}

void displayWarning(const string& message) {
    setColor(YELLOW);
    cout << "⚠ " << message << "\n";
    resetColor();
}

void displayInfo(const string& message) {
    setColor(LIGHT_BLUE);
    cout << "ℹ " << message << "\n";
    resetColor();
}

string getCurrentDateTime() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %I:%M:%S %p", localtime(&now));
    return string(buf);
}

bool isValidEmail(const string& email) {
    regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    return regex_match(email, pattern);
}

bool isValidName(const string& name) {
    if (name.length() < 3 || name.length() > 50) return false;
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return true;
}

bool isValidPassword(const string& password) {
    if (password.length() < 8) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ============================================================================
// SUBJECT CLASS
// ============================================================================
class Subject {
private:
    string code;
    string name;
    int creditHours;
    float obtainedMarks;
    float totalMarks;
    float highestMarks;
    float attendance;
    string grade;
    float gradePoints;

public:
    Subject() : creditHours(0), obtainedMarks(0), totalMarks(100), 
                highestMarks(0), attendance(0), gradePoints(0) {}
    
    Subject(string c, string n, int ch, float om, float tm, float hm, float att = 0) 
        : code(c), name(n), creditHours(ch), obtainedMarks(om), totalMarks(tm),
          highestMarks(hm), attendance(att), gradePoints(0) {}
    
    // Getters
    string getCode() const { return code; }
    string getName() const { return name; }
    int getCreditHours() const { return creditHours; }
    float getObtainedMarks() const { return obtainedMarks; }
    float getTotalMarks() const { return totalMarks; }
    float getHighestMarks() const { return highestMarks; }
    float getAttendance() const { return attendance; }
    string getGrade() const { return grade; }
    float getGradePoints() const { return gradePoints; }
    
    // Setters
    void setCode(const string& c) { code = c; }
    void setName(const string& n) { name = n; }
    void setCreditHours(int ch) { creditHours = ch; }
    void setObtainedMarks(float om) { obtainedMarks = om; }
    void setTotalMarks(float tm) { totalMarks = tm; }
    void setHighestMarks(float hm) { highestMarks = hm; }
    void setAttendance(float att) { attendance = att; }
    void setGrade(const string& g) { grade = g; }
    void setGradePoints(float gp) { gradePoints = gp; }
    
    // Calculate Grade based on HEC Policy
    void calculateGrade() {
        float percentage = (obtainedMarks / totalMarks) * 100;
        
        if (percentage >= 85) { grade = "A"; gradePoints = 4.00; }
        else if (percentage >= 80) { grade = "A-"; gradePoints = 3.67; }
        else if (percentage >= 75) { grade = "B+"; gradePoints = 3.33; }
        else if (percentage >= 70) { grade = "B"; gradePoints = 3.00; }
        else if (percentage >= 65) { grade = "B-"; gradePoints = 2.67; }
        else if (percentage >= 61) { grade = "C+"; gradePoints = 2.33; }
        else if (percentage >= 58) { grade = "C"; gradePoints = 2.00; }
        else if (percentage >= 54) { grade = "C-"; gradePoints = 1.67; }
        else if (percentage >= 50) { grade = "D+"; gradePoints = 1.33; }
        else if (percentage >= 45) { grade = "D"; gradePoints = 1.00; }
        else { grade = "F"; gradePoints = 0.00; }
    }
    
    void display() const {
        cout << left << setw(12) << code 
             << setw(25) << name 
             << setw(10) << creditHours
             << setw(12) << fixed << setprecision(1) << obtainedMarks
             << setw(10) << grade
             << setw(10) << fixed << setprecision(2) << gradePoints << endl;
    }
    
    // File operations
    void saveToFile(ofstream& file) const {
        file << code << "|" << name << "|" << creditHours << "|" 
             << obtainedMarks << "|" << totalMarks << "|" 
             << highestMarks << "|" << attendance << "|" 
             << grade << "|" << gradePoints << endl;
    }
    
    bool loadFromFile(ifstream& file) {
        string line;
        if (!getline(file, line)) return false;
        
        stringstream ss(line);
        getline(ss, code, '|');
        getline(ss, name, '|');
        ss >> creditHours;
        ss.ignore();
        ss >> obtainedMarks;
        ss.ignore();
        ss >> totalMarks;
        ss.ignore();
        ss >> highestMarks;
        ss.ignore();
        ss >> attendance;
        ss.ignore();
        getline(ss, grade, '|');
        ss >> gradePoints;
        return true;
    }
};

// ============================================================================
// SEMESTER CLASS
// ============================================================================
class Semester {
private:
    int semesterNumber;
    vector<Subject> subjects;
    float sgpa;
    float totalCreditHours;
    float totalQualityPoints;
    
public:
    Semester() : semesterNumber(0), sgpa(0), totalCreditHours(0), totalQualityPoints(0) {}
    Semester(int num) : semesterNumber(num), sgpa(0), totalCreditHours(0), totalQualityPoints(0) {}
    
    // Getters
    int getSemesterNumber() const { return semesterNumber; }
    float getSGPA() const { return sgpa; }
    float getTotalCreditHours() const { return totalCreditHours; }
    float getTotalQualityPoints() const { return totalQualityPoints; }
    const vector<Subject>& getSubjects() const { return subjects; }
    
    // Subject Management
    void addSubject(const Subject& subject) {
        subjects.push_back(subject);
    }
    
    Subject* findSubject(const string& code) {
        for (auto& subject : subjects) {
            if (subject.getCode() == code) {
                return &subject;
            }
        }
        return nullptr;
    }
    
    bool removeSubject(const string& code) {
        for (auto it = subjects.begin(); it != subjects.end(); ++it) {
            if (it->getCode() == code) {
                subjects.erase(it);
                return true;
            }
        }
        return false;
    }
    
    bool updateSubject(const string& code, const Subject& updatedSubject) {
        for (auto& subject : subjects) {
            if (subject.getCode() == code) {
                subject = updatedSubject;
                return true;
            }
        }
        return false;
    }
    
    // Calculate SGPA
    void calculateSGPA() {
        if (subjects.empty()) {
            sgpa = 0;
            totalCreditHours = 0;
            totalQualityPoints = 0;
            return;
        }
        
        totalCreditHours = 0;
        totalQualityPoints = 0;
        
        for (auto& subject : subjects) {
            subject.calculateGrade();
            totalCreditHours += subject.getCreditHours();
            totalQualityPoints += subject.getCreditHours() * subject.getGradePoints();
        }
        
        if (totalCreditHours > 0) {
            sgpa = totalQualityPoints / totalCreditHours;
        } else {
            sgpa = 0;
        }
    }
  void display() const {
    setColor(CYAN);
    cout << "\n========================================\n";
    cout << "  SEMESTER " << semesterNumber << " DETAILS\n";
    cout << "========================================\n";
    
    if (subjects.empty()) {
        setColor(YELLOW);
        cout << "  No subjects found in this semester\n";
    } else {
        setColor(WHITE);
        cout << "Code    Subject              CH  Marks  Grade  GP\n";
        cout << "----------------------------------------\n";
        
        for (const auto& subject : subjects) {
            cout << left 
                 << setw(7) << subject.getCode() << " "
                 << setw(18) << subject.getName() << " "
                 << setw(3) << subject.getCreditHours() << "  "
                 << setw(5) << fixed << setprecision(1) << subject.getObtainedMarks() << "  "
                 << setw(5) << subject.getGrade() << "  "
                 << setw(4) << fixed << setprecision(2) << subject.getGradePoints() << "\n";
        }
    }
    
    cout << "----------------------------------------\n";
    setColor(LIGHT_GREEN);
    cout << "Total Credit Hours: " << totalCreditHours << "\n";
    cout << "Total Quality Points: " << fixed << setprecision(2) << totalQualityPoints << "\n";
    cout << "Semester GPA (SGPA): " << fixed << setprecision(3) << sgpa << "\n";
    setColor(CYAN);
    cout << "========================================\n";
    resetColor();
}
    // File operations
    void saveToFile(ofstream& file) const {
        file << semesterNumber << "|" << subjects.size() << "|" 
             << sgpa << "|" << totalCreditHours << "|" << totalQualityPoints << endl;
        for (const auto& subject : subjects) {
            subject.saveToFile(file);
        }
    }
    
    bool loadFromFile(ifstream& file) {
        string line;
        if (!getline(file, line)) return false;
        
        stringstream ss(line);
        string sizeStr;
        
        ss >> semesterNumber;
        ss.ignore();
        getline(ss, sizeStr, '|');
        int size = stoi(sizeStr);
        ss >> sgpa;
        ss.ignore();
        ss >> totalCreditHours;
        ss.ignore();
        ss >> totalQualityPoints;
        
        subjects.clear();
        for (int i = 0; i < size; i++) {
            Subject subject;
            if (subject.loadFromFile(file)) {
                subjects.push_back(subject);
            }
        }
        return true;
    }
};

// ============================================================================
// STUDENT CLASS
// ============================================================================
class Student {
private:
    string studentID;
    string fullName;
    string regNumber;
    string universityName;
    string department;
    string degreeProgram;
    int currentSemester;
    string email;
    string username;
    string password;
    vector<Semester> semesters;
    float cgpa;
    
public:
    Student() : currentSemester(0), cgpa(0) {}
    
    // Getters
    string getStudentID() const { return studentID; }
    string getFullName() const { return fullName; }
    string getRegNumber() const { return regNumber; }
    string getUniversityName() const { return universityName; }
    string getDepartment() const { return department; }
    string getDegreeProgram() const { return degreeProgram; }
    int getCurrentSemester() const { return currentSemester; }
    string getEmail() const { return email; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    float getCGPA() const { return cgpa; }
    const vector<Semester>& getSemesters() const { return semesters; }
    
    // Setters
    void setStudentID(const string& id) { studentID = id; }
    void setFullName(const string& name) { fullName = name; }
    void setRegNumber(const string& reg) { regNumber = reg; }
    void setUniversityName(const string& uni) { universityName = uni; }
    void setDepartment(const string& dept) { department = dept; }
    void setDegreeProgram(const string& prog) { degreeProgram = prog; }
    void setCurrentSemester(int sem) { currentSemester = sem; }
    void setEmail(const string& e) { email = e; }
    void setUsername(const string& u) { username = u; }
    void setPassword(const string& p) { password = p; }
    
    // Semester Management
    void addSemester(const Semester& semester) {
        semesters.push_back(semester);
        currentSemester = semester.getSemesterNumber();
    }
    
    Semester* findSemester(int semesterNumber) {
        for (auto& semester : semesters) {
            if (semester.getSemesterNumber() == semesterNumber) {
                return &semester;
            }
        }
        return nullptr;
    }
    
    bool hasSemester(int semesterNumber) const {
        for (const auto& semester : semesters) {
            if (semester.getSemesterNumber() == semesterNumber) {
                return true;
            }
        }
        return false;
    }
    
    // Calculate CGPA
    void calculateCGPA() {
        if (semesters.empty()) {
            cgpa = 0;
            return;
        }
        
        float totalQualityPoints = 0;
        float totalCreditHours = 0;
        
        for (const auto& semester : semesters) {
            totalQualityPoints += semester.getTotalQualityPoints();
            totalCreditHours += semester.getTotalCreditHours();
        }
        
        if (totalCreditHours > 0) {
            cgpa = totalQualityPoints / totalCreditHours;
        } else {
            cgpa = 0;
        }
    }
    void displayInfo() const {
    setColor(CYAN);
    cout << "\n========================================\n";
    cout << "        STUDENT INFORMATION\n";
    cout << "========================================\n";
    setColor(WHITE);
    cout << "Student ID:      " << studentID << "\n";
    cout << "Full Name:       " << fullName << "\n";
    cout << "Registration #:  " << regNumber << "\n";
    cout << "University:      " << universityName << "\n";
    cout << "Department:      " << department << "\n";
    cout << "Program:         " << degreeProgram << "\n";
    cout << "Current Semester:" << currentSemester << "\n";
    cout << "Email:           " << email << "\n";
    cout << "Username:        " << username << "\n";
    cout << "----------------------------------------\n";
    setColor(LIGHT_GREEN);
    cout << "CGPA:            " << fixed << setprecision(3) << cgpa << "\n";
    cout << "Total Semesters: " << semesters.size() << "\n";
    setColor(CYAN);
    cout << "========================================\n";
    resetColor();
}
    // File operations
    void saveToFile(ofstream& file) const {
        file << studentID << "|" << fullName << "|" << regNumber << "|"
             << universityName << "|" << department << "|" << degreeProgram << "|"
             << currentSemester << "|" << email << "|" << username << "|" << password << "|"
             << cgpa << "|" << semesters.size() << endl;
        
        for (const auto& semester : semesters) {
            semester.saveToFile(file);
        }
    }
    
    bool loadFromFile(ifstream& file) {
        string line;
        if (!getline(file, line)) return false;
        
        stringstream ss(line);
        string sizeStr;
        
        getline(ss, studentID, '|');
        getline(ss, fullName, '|');
        getline(ss, regNumber, '|');
        getline(ss, universityName, '|');
        getline(ss, department, '|');
        getline(ss, degreeProgram, '|');
        ss >> currentSemester;
        ss.ignore();
        getline(ss, email, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        ss >> cgpa;
        ss.ignore();
        getline(ss, sizeStr, '|');
        int size = stoi(sizeStr);
        
        semesters.clear();
        for (int i = 0; i < size; i++) {
            Semester semester;
            if (semester.loadFromFile(file)) {
                semesters.push_back(semester);
            }
        }
        return true;
    }
};

// ============================================================================
// GRADE CALCULATOR CLASS
// ============================================================================
class GradeCalculator {
public:
    static string calculateGrade(float marks, float totalMarks) {
        float percentage = (marks / totalMarks) * 100;
        
        if (percentage >= 85) return "A";
        else if (percentage >= 80) return "A-";
        else if (percentage >= 75) return "B+";
        else if (percentage >= 70) return "B";
        else if (percentage >= 65) return "B-";
        else if (percentage >= 61) return "C+";
        else if (percentage >= 58) return "C";
        else if (percentage >= 54) return "C-";
        else if (percentage >= 50) return "D+";
        else if (percentage >= 45) return "D";
        else return "F";
    }
    
    static float getGradePoints(const string& grade) {
        if (grade == "A") return 4.00;
        else if (grade == "A-") return 3.67;
        else if (grade == "B+") return 3.33;
        else if (grade == "B") return 3.00;
        else if (grade == "B-") return 2.67;
        else if (grade == "C+") return 2.33;
        else if (grade == "C") return 2.00;
        else if (grade == "C-") return 1.67;
        else if (grade == "D+") return 1.33;
        else if (grade == "D") return 1.00;
        else return 0.00;
    }
    
    static string getGradeDescription(const string& grade) {
        if (grade == "A") return "Excellent";
        else if (grade == "A-") return "Very Good";
        else if (grade == "B+") return "Good";
        else if (grade == "B") return "Above Average";
        else if (grade == "B-") return "Average";
        else if (grade == "C+") return "Below Average";
        else if (grade == "C") return "Satisfactory";
        else if (grade == "C-") return "Pass";
        else if (grade == "D+") return "Pass";
        else if (grade == "D") return "Pass";
        else return "Fail";
    }
};

// ============================================================================
// BELL CURVE PREDICTOR CLASS
// ============================================================================
class BellCurvePredictor {
private:
    float highestMarks;
    float studentMarks;
    float totalMarks;
    
public:
    BellCurvePredictor() : highestMarks(0), studentMarks(0), totalMarks(100) {}
    
    void setData(float hm, float sm, float tm) {
        highestMarks = hm;
        studentMarks = sm;
        totalMarks = tm;
    }
    
    string predictGrade() const {
        if (highestMarks <= 0 || studentMarks <= 0 || totalMarks <= 0) {
            return "N/A";
        }
        
        float percentage = (studentMarks / highestMarks) * 100;
        
        if (percentage >= 95) return "A";
        else if (percentage >= 88) return "A-";
        else if (percentage >= 80) return "B+";
        else if (percentage >= 72) return "B";
        else if (percentage >= 65) return "B-";
        else if (percentage >= 58) return "C+";
        else if (percentage >= 50) return "C";
        else if (percentage >= 45) return "C-";
        else if (percentage >= 40) return "D+";
        else if (percentage >= 35) return "D";
        else return "F";
    }
    
    float predictGradePoints() const {
        string grade = predictGrade();
        return GradeCalculator::getGradePoints(grade);
    }
    
    string getPerformanceCategory() const {
        string grade = predictGrade();
        if (grade == "A" || grade == "A-") return "Outstanding";
        else if (grade == "B+" || grade == "B") return "Good";
        else if (grade == "B-" || grade == "C+") return "Satisfactory";
        else if (grade == "C" || grade == "C-") return "Below Average";
        else if (grade == "D+" || grade == "D") return "Pass";
        else return "Fail";
    }
};

// ============================================================================
// REPORT GENERATOR CLASS
// ============================================================================
class ReportGenerator {
public:
    static bool generateReport(const Student& student) {
        string filename = "report_" + student.getUsername() + ".txt";
        ofstream file(filename);
        
        if (!file.is_open()) {
            displayError("Unable to create report file!");
            return false;
        }
        file << "==================================================\n";
        file << "     HEC ACADEMIC PERFORMANCE REPORT              \n";
        file << "         OFFICIAL TRANSCRIPT                      \n";
        file << "==================================================\n\n";

                 file << "STUDENT INFORMATION\n";
        file << "------------------------------------------\n";
        file << "Student ID:      " << student.getStudentID() << "\n";
        file << "Full Name:       " << student.getFullName() << "\n";
        file << "Registration #:  " << student.getRegNumber() << "\n";
        file << "University:      " << student.getUniversityName() << "\n";
        file << "Department:      " << student.getDepartment() << "\n";
        file << "Program:         " << student.getDegreeProgram() << "\n";
        file << "Current Semester:" << student.getCurrentSemester() << "\n";
        file << "CGPA:            " << fixed << setprecision(3) << student.getCGPA() << "\n\n";

               file << "SEMESTER RESULTS\n";
    file << "------------------------------------------\n";
        
        const auto& semesters = student.getSemesters();
        for (const auto& semester : semesters) {
            file << "\nSEMESTER " << semester.getSemesterNumber() << "\n";
            file << "--------------------------------------------------------------------\n";
            file << left << setw(12) << "Code"
                 << setw(25) << "Subject Name"
                 << setw(6) << "CH"
                 << setw(10) << "Marks"
                 << setw(8) << "Grade"
                 << setw(8) << "GP" << "\n";
            file << "--------------------------------------------------------------------\n";
            
            for (const auto& subject : semester.getSubjects()) {
                file << left << setw(12) << subject.getCode()
                     << setw(25) << subject.getName()
                     << setw(6) << subject.getCreditHours()
                     << setw(10) << fixed << setprecision(1) << subject.getObtainedMarks()
                     << setw(8) << subject.getGrade()
                     << setw(8) << fixed << setprecision(2) << subject.getGradePoints() << "\n";
            }
            
            file << "--------------------------------------------------------------------\n";
            file << "Total Credit Hours: " << semester.getTotalCreditHours() << "\n";
            file << "Semester GPA (SGPA): " << fixed << setprecision(3) << semester.getSGPA() << "\n\n";
        }
        
        file << "\nAcademic Summary:\n";
        file << "========================================================================\n";
        
        float highestGPA = 0, lowestGPA = 999;
        int bestSemester = 0, worstSemester = 0;
        
        for (const auto& semester : semesters) {
            float sgpa = semester.getSGPA();
            if (sgpa > highestGPA) {
                highestGPA = sgpa;
                bestSemester = semester.getSemesterNumber();
            }
            if (sgpa < lowestGPA) {
                lowestGPA = sgpa;
                worstSemester = semester.getSemesterNumber();
            }
        }
        
        file << "Highest GPA:       " << fixed << setprecision(3) << highestGPA 
             << " (Semester " << bestSemester << ")\n";
        file << "Lowest GPA:        " << fixed << setprecision(3) << lowestGPA 
             << " (Semester " << worstSemester << ")\n";
        file << "Total Semesters:   " << semesters.size() << "\n";
        file << "Overall CGPA:      " << fixed << setprecision(3) << student.getCGPA() << "\n";
        
        // Determine Academic Standing
        float cgpa = student.getCGPA();
        string standing;
        if (cgpa >= 3.50) standing = "Excellent - Dean's List";
        else if (cgpa >= 3.00) standing = "Good";
        else if (cgpa >= 2.50) standing = "Satisfactory";
        else if (cgpa >= 2.00) standing = "Marginal";
        else standing = "Probation";
        
        file << "Academic Standing: " << standing << "\n";
        
        if (cgpa >= 3.50) {
            file << "Status:           ★ Dean's List ★\n";
        }
        file << "\nReport Generated: " << getCurrentDateTime() << "\n";
file << "==================================================\n";
file << "         END OF ACADEMIC REPORT                   \n";
file << "==================================================\n";
        file.close();
        displaySuccess("Report generated successfully: " + filename);
        return true;
    }
};

// ============================================================================
// VALIDATOR CLASS
// ============================================================================
class Validator {
public:
    static bool validateMenuInput(const string& input, int maxOption) {
        if (input.empty()) return false;
        for (char c : input) {
            if (!isdigit(c)) return false;
        }
        int option = stoi(input);
        return option >= 1 && option <= maxOption;
    }
    
    static bool validateCreditHours(int ch) {
        return ch >= 1 && ch <= 6;
    }
    
    static bool validateMarks(float marks, float totalMarks) {
        return marks >= 0 && marks <= totalMarks;
    }
    
    static bool validateSubjectCode(const string& code) {
        return !code.empty() && code.length() >= 3;
    }
    
    static bool validateSubjectName(const string& name) {
        return !name.empty() && name.length() >= 2;
    }
    
    static bool isDuplicateUsername(const string& username, const vector<Student>& students) {
        for (const auto& student : students) {
            if (student.getUsername() == username) {
                return true;
            }
        }
        return false;
    }
    
    static bool isDuplicateRegNumber(const string& regNumber, const vector<Student>& students) {
        for (const auto& student : students) {
            if (student.getRegNumber() == regNumber) {
                return true;
            }
        }
        return false;
    }
};

// ============================================================================
// FILE MANAGER CLASS
// ============================================================================
class FileManager {
public:
    static bool saveStudents(const vector<Student>& students) {
        try {
            ofstream file("students.txt");
            if (!file.is_open()) {
                throw runtime_error("Unable to open students.txt for writing");
            }
            
            file << students.size() << endl;
            for (const auto& student : students) {
                student.saveToFile(file);
            }
            
            file.close();
            return true;
        } catch (const exception& e) {
            displayError("File Error: " + string(e.what()));
            return false;
        }
    }
    
    static bool loadStudents(vector<Student>& students) {
        try {
            ifstream file("students.txt");
            if (!file.is_open()) {
                return false;
            }
            
            students.clear();
            string line;
            if (!getline(file, line)) {
                return false;
            }
            
            int size = stoi(line);
            for (int i = 0; i < size; i++) {
                Student student;
                if (student.loadFromFile(file)) {
                    students.push_back(student);
                }
            }
            
            file.close();
            return true;
        } catch (const exception& e) {
            displayError("File Error: " + string(e.what()));
            return false;
        }
    }
    
    static bool semesterExists(int semesterNumber, const vector<Semester>& semesters) {
        for (const auto& semester : semesters) {
            if (semester.getSemesterNumber() == semesterNumber) {
                return true;
            }
        }
        return false;
    }
};

// ============================================================================
// AUTHENTICATION CLASS
// ============================================================================
class Authentication {
private:
    vector<Student>& students;
    Student* currentStudent;
    int loginAttempts;
    
public:
    Authentication(vector<Student>& s) : students(s), currentStudent(nullptr), loginAttempts(0) {}
    
    bool registerStudent() {
        clearScreen();
        displayHeader("Student Registration");
        
        try {
            Student newStudent;
            string input;
            
            // Generate Student ID
            int nextID = students.size() + 1;
            newStudent.setStudentID("STU" + string(5 - to_string(nextID).length(), '0') + to_string(nextID));
            
            // Full Name
            do {
                cout << "Full Name: ";
                getline(cin, input);
                input = trim(input);
                if (!isValidName(input)) {
                    displayError("Invalid name! Use only alphabets and spaces (3-50 characters)");
                }
            } while (!isValidName(input));
            newStudent.setFullName(input);
            
            // Registration Number
            do {
                cout << "Registration Number: ";
                getline(cin, input);
                input = trim(input);
                if (input.empty()) {
                    displayError("Registration number cannot be empty!");
                } else if (Validator::isDuplicateRegNumber(input, students)) {
                    displayError("Registration number already exists!");
                }
            } while (input.empty() || Validator::isDuplicateRegNumber(input, students));
            newStudent.setRegNumber(input);
            
            // University Name
            do {
                cout << "University Name: ";
                getline(cin, input);
                input = trim(input);
                if (input.length() < 3) {
                    displayError("University name must be at least 3 characters!");
                }
            } while (input.length() < 3);
            newStudent.setUniversityName(input);
            
            // Department
            do {
                cout << "Department: ";
                getline(cin, input);
                input = trim(input);
                if (!isValidName(input)) {
                    displayError("Department name must contain only alphabets and spaces!");
                }
            } while (!isValidName(input));
            newStudent.setDepartment(input);
            
            // Degree Program
            do {
                cout << "Degree Program: ";
                getline(cin, input);
                input = trim(input);
                if (input.empty()) {
                    displayError("Degree program cannot be empty!");
                }
            } while (input.empty());
            newStudent.setDegreeProgram(input);
            
            // Semester
            int semester;
            do {
                cout << "Current Semester (1-12): ";
                getline(cin, input);
                if (!Validator::validateMenuInput(input, 12)) {
                    displayError("Invalid semester! Enter a number between 1 and 12.");
                }
            } while (!Validator::validateMenuInput(input, 12));
            semester = stoi(input);
            newStudent.setCurrentSemester(semester);
            
            // Email
            do {
                cout << "Email Address: ";
                getline(cin, input);
                input = trim(input);
                if (!isValidEmail(input)) {
                    displayError("Invalid email format! Example: student@university.com");
                }
            } while (!isValidEmail(input));
            newStudent.setEmail(input);
            
            // Username
            do {
                cout << "Username (5-20 characters, no spaces): ";
                getline(cin, input);
                input = trim(input);
                if (input.length() < 5 || input.length() > 20 || input.find(' ') != string::npos) {
                    displayError("Username must be 5-20 characters with no spaces!");
                } else if (Validator::isDuplicateUsername(input, students)) {
                    displayError("Username already exists!");
                }
            } while (input.length() < 5 || input.length() > 20 || 
                    input.find(' ') != string::npos ||
                    Validator::isDuplicateUsername(input, students));
            newStudent.setUsername(input);
            
            // Password
            string password, confirmPassword;
            do {
                cout << "Password (8+ chars, uppercase, lowercase, digit, special): ";
                getline(cin, password);
                if (!isValidPassword(password)) {
                    displayError("Password must meet all requirements!");
                }
            } while (!isValidPassword(password));
            
            do {
                cout << "Confirm Password: ";
                getline(cin, confirmPassword);
                if (password != confirmPassword) {
                    displayError("Passwords do not match!");
                }
            } while (password != confirmPassword);
            newStudent.setPassword(password);
            
            students.push_back(newStudent);
            
            if (FileManager::saveStudents(students)) {
                displaySuccess("Registration successful!");
                displayInfo("Your Student ID: " + newStudent.getStudentID());
                displayInfo("Username: " + newStudent.getUsername());
            }
            
            pauseScreen();
            return true;
            
        } catch (const exception& e) {
            displayError("Registration failed: " + string(e.what()));
            pauseScreen();
            return false;
        }
    }
    
    bool login() {
        clearScreen();
        displayHeader("Student Login");
        
        try {
            string username, password;
            loginAttempts = 0;
            
            while (loginAttempts < 3) {
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                
                for (auto& student : students) {
                    if (student.getUsername() == username && student.getPassword() == password) {
                        currentStudent = &student;
                        displaySuccess("Login successful!");
                        displayInfo("Welcome, " + student.getFullName() + "!");
                        pauseScreen();
                        return true;
                    }
                }
                
                loginAttempts++;
                int remaining = 3 - loginAttempts;
                if (remaining > 0) {
                    displayError("Invalid credentials! " + to_string(remaining) + " attempts remaining.");
                }
            }
            
            displayError("Account locked! Too many failed attempts.");
            pauseScreen();
            return false;
            
        } catch (const exception& e) {
            displayError("Login error: " + string(e.what()));
            pauseScreen();
            return false;
        }
    }
    
    void logout() {
        currentStudent = nullptr;
        loginAttempts = 0;
        displayInfo("Logged out successfully.");
        pauseScreen();
    }
    
    Student* getCurrentStudent() const {
        return currentStudent;
    }
};

// ============================================================================
// DASHBOARD CLASS
// ============================================================================
class Dashboard {
private:
    Student* student;
    Authentication* auth;
    
public:
    Dashboard(Student* s, Authentication* a) : student(s), auth(a) {}
    
    void display() {
        if (!student) {
            displayError("No student logged in!");
            return;
        }
        
        int choice;
        do {
            clearScreen();
            displayHeader("Student Dashboard");
            
            setColor(LIGHT_GREEN);
            cout << "  Welcome, " << student->getFullName() << "!\n";
            cout << "  Student ID: " << student->getStudentID() << "\n";
            cout << "  CGPA: " << fixed << setprecision(3) << student->getCGPA() << "\n\n";
            resetColor();
            
        setColor(CYAN);
cout << "========================================\n";
cout << "        DASHBOARD MENU\n";
cout << "========================================\n";
setColor(WHITE);
cout << " 1.  Add Semester\n";
cout << " 2.  Add Subjects\n";
cout << " 3.  Calculate Semester GPA (SGPA)\n";
cout << " 4.  Calculate CGPA\n";
cout << " 5.  GPA Predictor\n";
cout << " 6.  Grade Predictor (Bell Curve)\n";
cout << " 7.  Academic Performance Report\n";
cout << " 8.  View Previous Semesters\n";
cout << " 9.  Update Subject Record\n";
cout << "10.  Delete Subject\n";
cout << "11.  HEC Grading Scale\n";
cout << "12.  Export GPA Report\n";
cout << "13.  Logout\n";
setColor(CYAN);
cout << "========================================\n";
resetColor();
            
            cout << "\nEnter your choice: ";
            string input;
            getline(cin, input);
            
            if (!Validator::validateMenuInput(input, 13)) {
                displayError("Invalid choice! Please enter a number between 1 and 13.");
                pauseScreen();
                continue;
            }
            
            choice = stoi(input);
            
            switch (choice) {
                case 1: addSemester(); break;
                case 2: addSubjects(); break;
                case 3: calculateSGPA(); break;
                case 4: calculateCGPA(); break;
                case 5: gpaPredictor(); break;
                case 6: gradePredictor(); break;
                case 7: academicReport(); break;
                case 8: viewSemesters(); break;
                case 9: updateSubject(); break;
                case 10: deleteSubject(); break;
                case 11: displayGradingScale(); break;
                case 12: exportReport(); break;
                case 13: logout(); break;
            }
            
        } while (choice != 13);
    }
    
private:
    void addSemester() {
        clearScreen();
        displayHeader("Add Semester");
        
        try {
            int semesterNumber;
            string input;
            
            cout << "Enter Semester Number: ";
            getline(cin, input);
            
            if (!Validator::validateMenuInput(input, 12)) {
                displayError("Invalid semester number! (1-12)");
                pauseScreen();
                return;
            }
            
            semesterNumber = stoi(input);
            
            if (student->hasSemester(semesterNumber)) {
                displayError("Semester " + to_string(semesterNumber) + " already exists!");
                pauseScreen();
                return;
            }
            
            Semester newSemester(semesterNumber);
            student->addSemester(newSemester);
            
            displaySuccess("Semester " + to_string(semesterNumber) + " added successfully!");
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error adding semester: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void addSubjects() {
        clearScreen();
        displayHeader("Add Subjects");
        
        try {
            string input;
            int semesterNumber;
            
            cout << "Enter Semester Number: ";
            getline(cin, input);
            
            if (!Validator::validateMenuInput(input, 12)) {
                displayError("Invalid semester number!");
                pauseScreen();
                return;
            }
            
            semesterNumber = stoi(input);
            Semester* semester = student->findSemester(semesterNumber);
            
            if (!semester) {
                displayError("Semester " + to_string(semesterNumber) + " not found!");
                pauseScreen();
                return;
            }
            
            char addMore;
            do {
                clearScreen();
                displayHeader("Add Subjects - Semester " + to_string(semesterNumber));
                
                Subject subject;
                string code, name;
                int creditHours;
                float obtainedMarks, totalMarks, highestMarks, attendance;
                
                // Subject Code
                do {
                    cout << "Subject Code: ";
                    getline(cin, code);
                    code = trim(code);
                    if (code.empty() || code.length() < 3) {
                        displayError("Subject code must be at least 3 characters!");
                    } else if (semester->findSubject(code) != nullptr) {
                        displayError("Subject code already exists in this semester!");
                    }
                } while (code.empty() || code.length() < 3 || semester->findSubject(code) != nullptr);
                subject.setCode(code);
                
                // Subject Name
                do {
                    cout << "Subject Name: ";
                    getline(cin, name);
                    name = trim(name);
                    if (name.length() < 2) {
                        displayError("Subject name must be at least 2 characters!");
                    }
                } while (name.length() < 2);
                subject.setName(name);
                
                // Credit Hours
                do {
                    cout << "Credit Hours (1-6): ";
                    getline(cin, input);
                    if (!Validator::validateMenuInput(input, 6)) {
                        displayError("Credit hours must be between 1 and 6!");
                    }
                } while (!Validator::validateMenuInput(input, 6));
                creditHours = stoi(input);
                subject.setCreditHours(creditHours);
                
                // Total Marks
                do {
                    cout << "Total Marks: ";
                    getline(cin, input);
                    try {
                        totalMarks = stof(input);
                        if (totalMarks <= 0) {
                            displayError("Total marks must be greater than 0!");
                        }
                    } catch (...) {
                        displayError("Invalid input! Enter a number.");
                    }
                } while (totalMarks <= 0);
                subject.setTotalMarks(totalMarks);
                
                // Obtained Marks
                do {
                    cout << "Obtained Marks: ";
                    getline(cin, input);
                    try {
                        obtainedMarks = stof(input);
                        if (obtainedMarks < 0 || obtainedMarks > totalMarks) {
                            displayError("Obtained marks must be between 0 and " + to_string(totalMarks) + "!");
                        }
                    } catch (...) {
                        displayError("Invalid input! Enter a number.");
                    }
                } while (obtainedMarks < 0 || obtainedMarks > totalMarks);
                subject.setObtainedMarks(obtainedMarks);
                
                // Highest Marks
                do {
                    cout << "Highest Marks in Class: ";
                    getline(cin, input);
                    try {
                        highestMarks = stof(input);
                        if (highestMarks < 0 || highestMarks > totalMarks) {
                            displayError("Highest marks must be between 0 and " + to_string(totalMarks) + "!");
                        } else if (highestMarks < obtainedMarks) {
                            displayError("Highest marks cannot be less than obtained marks!");
                        }
                    } catch (...) {
                        displayError("Invalid input! Enter a number.");
                    }
                } while (highestMarks < 0 || highestMarks > totalMarks || highestMarks < obtainedMarks);
                subject.setHighestMarks(highestMarks);
                
                // Attendance (Optional)
                cout << "Attendance Percentage (optional, press Enter to skip): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        attendance = stof(input);
                        if (attendance >= 0 && attendance <= 100) {
                            subject.setAttendance(attendance);
                        }
                    } catch (...) {
                        // Ignore invalid attendance
                    }
                }
                
                semester->addSubject(subject);
                displaySuccess("Subject '" + name + "' added successfully!");
                
                cout << "\nAdd another subject? (Y/N): ";
                cin >> addMore;
                clearInputBuffer();
                addMore = toupper(addMore);
                
            } while (addMore == 'Y');
            
            FileManager::saveStudents({*student});
            displaySuccess("All subjects saved successfully!");
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error adding subjects: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void calculateSGPA() {
        clearScreen();
        displayHeader("Calculate Semester GPA");
        
        try {
            string input;
            int semesterNumber;
            
            cout << "Enter Semester Number: ";
            getline(cin, input);
            
            if (!Validator::validateMenuInput(input, 12)) {
                displayError("Invalid semester number!");
                pauseScreen();
                return;
            }
            
            semesterNumber = stoi(input);
            Semester* semester = student->findSemester(semesterNumber);
            
            if (!semester) {
                displayError("Semester " + to_string(semesterNumber) + " not found!");
                pauseScreen();
                return;
            }
            
            if (semester->getSubjects().empty()) {
                displayError("No subjects found in this semester!");
                pauseScreen();
                return;
            }
            
            semester->calculateSGPA();
            semester->display();
            
            FileManager::saveStudents({*student});
            displaySuccess("SGPA calculated successfully!");
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error calculating SGPA: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void calculateCGPA() {
        clearScreen();
        displayHeader("Calculate CGPA");
        
        try {
            if (student->getSemesters().empty()) {
                displayError("No semesters found!");
                pauseScreen();
                return;
            }
            
            // Calculate SGPA for all semesters first
            for (auto& semester : student->getSemesters()) {
                // We need non-const access, so we use const_cast
                // In a real implementation, we'd have a better way
                const_cast<Semester&>(semester).calculateSGPA();
            }
            
            student->calculateCGPA();
            setColor(CYAN);
cout << "\n========================================\n";
cout << "        CGPA CALCULATION\n";
cout << "========================================\n";
setColor(WHITE);
cout << "Semester | GPA    | Credits | Quality Points\n";
cout << "----------------------------------------\n";
            float totalCH = 0, totalQP = 0;
            for (const auto& semester : student->getSemesters()) {
                cout << "│ " << setw(8) << semester.getSemesterNumber() 
                     << " │ " << setw(6) << fixed << setprecision(3) << semester.getSGPA()
                     << " │ " << setw(12) << semester.getTotalCreditHours()
                     << " │ " << setw(14) << fixed << setprecision(2) << semester.getTotalQualityPoints()
                     << " │\n";
                totalCH += semester.getTotalCreditHours();
                totalQP += semester.getTotalQualityPoints();
            }
            
            cout << "========================================================================\n";
            setColor(LIGHT_GREEN);
            cout << "│ Total Credit Hours: " << setw(34) << totalCH << " │\n";
            cout << "│ Total Quality Points: " << setw(32) << fixed << setprecision(2) << totalQP << " │\n";
            cout << "│ Overall CGPA: " << setw(42) << fixed << setprecision(3) << student->getCGPA() << " │\n";
            setColor(CYAN);
            cout << "==========================================================================\n";
            resetColor();
            
            FileManager::saveStudents({*student});
            displaySuccess("CGPA calculated successfully!");
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error calculating CGPA: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void gpaPredictor() {
        clearScreen();
        displayHeader("GPA Predictor");
        
        try {
            string input;
            int semesterNumber;
            
            cout << "Enter Semester Number to predict: ";
            getline(cin, input);
            
            if (!Validator::validateMenuInput(input, 12)) {
                displayError("Invalid semester number!");
                pauseScreen();
                return;
            }
            
            semesterNumber = stoi(input);
            Semester* semester = student->findSemester(semesterNumber);
            
            if (!semester) {
                displayError("Semester " + to_string(semesterNumber) + " not found!");
                pauseScreen();
                return;
            }
            
            if (semester->getSubjects().empty()) {
                displayError("No subjects found in this semester!");
                pauseScreen();
                return;
            }
            setColor(CYAN);
cout << "\n========================================\n";
cout << "        GPA PREDICTOR\n";
cout << "========================================\n";
setColor(WHITE);
cout << "Subject Code | Expected Grade | Credits | Predicted GP\n";
cout << "----------------------------------------\n";
            
            float predictedTotalQP = 0;
            float predictedTotalCH = 0;
            
            for (const auto& subject : semester->getSubjects()) {
                string grade;
                float gp;
                
                cout << "│ " << left << setw(12) << subject.getCode() << " │ ";
                cout << "Enter expected grade for " << subject.getName() << ": ";
                getline(cin, grade);
                grade = trim(grade);
                
                gp = GradeCalculator::getGradePoints(grade);
                
                cout << "│ " << left << setw(12) << subject.getCode()
                     << " │ " << setw(13) << grade
                     << " │ " << setw(11) << subject.getCreditHours()
                     << " │ " << setw(12) << fixed << setprecision(2) << gp
                     << " │\n";
                
                predictedTotalQP += subject.getCreditHours() * gp;
                predictedTotalCH += subject.getCreditHours();
            }
            
            float predictedSGPA = predictedTotalCH > 0 ? predictedTotalQP / predictedTotalCH : 0;
            
            cout << "========================================================================\n";
            setColor(LIGHT_GREEN);
            cout << "│ Predicted SGPA: " << setw(38) << fixed << setprecision(3) << predictedSGPA << " │\n";
            setColor(CYAN);
            cout << "==========================================================================\n";
            resetColor();
            
            displayInfo("Note: This is a prediction based on expected grades.");
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error in GPA predictor: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void gradePredictor() {
        clearScreen();
        displayHeader("Grade Predictor (Bell Curve)");
        
        try {
            BellCurvePredictor predictor;
            string input;
            float highestMarks, studentMarks, totalMarks;
            
            cout << "Enter Total Marks: ";
            getline(cin, input);
            totalMarks = stof(input);
            
            cout << "Enter Highest Marks in Class: ";
            getline(cin, input);
            highestMarks = stof(input);
            if (highestMarks > totalMarks) {
                displayError("Highest marks cannot exceed total marks!");
                pauseScreen();
                return;
            }
            
            cout << "Enter Student's Obtained Marks: ";
            getline(cin, input);
            studentMarks = stof(input);
            if (studentMarks > highestMarks) {
                displayError("Student marks cannot exceed highest marks!");
                pauseScreen();
                return;
            }
            
            predictor.setData(highestMarks, studentMarks, totalMarks);
            
            setColor(CYAN);
            cout << "\n========================================\n";
            cout << "        BELL CURVE PREDICTION\n";
            cout << "========================================\n";
            setColor(WHITE);
            cout << "Highest Marks:   " << left << setw(30) << fixed << setprecision(1) << highestMarks << "\n";
            cout << "Student Marks:   " << left << setw(30) << fixed << setprecision(1) << studentMarks << "\n";
            cout << "Total Marks:     " << left << setw(30) << fixed << setprecision(1) << totalMarks << "\n";
            cout << "========================================\n";
            setColor(LIGHT_GREEN);
            cout << "│ Predicted Grade: " << left << setw(30) << predictor.predictGrade() << "│\n";
            cout << "│ Grade Points:    " << left << setw(30) << fixed << setprecision(2) << predictor.predictGradePoints() << "│\n";
            cout << "│ Performance:     " << left << setw(30) << predictor.getPerformanceCategory() << "│\n";
            setColor(CYAN);
            cout << "=========================================================================\n";
            resetColor();
            
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error in grade predictor: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void academicReport() {
        clearScreen();
        displayHeader("Academic Performance Report");
        
        try {
            if (student->getSemesters().empty()) {
                displayError("No academic data available!");
                pauseScreen();
                return;
            }
            
            // Calculate all SGPA and CGPA
            for (auto& semester : student->getSemesters()) {
                const_cast<Semester&>(semester).calculateSGPA();
            }
            student->calculateCGPA();
            
            float highestGPA = 0, lowestGPA = 999;
            int bestSemester = 0, worstSemester = 0;
            float totalCH = 0;
            int totalSubjects = 0;
            
            for (const auto& semester : student->getSemesters()) {
                float sgpa = semester.getSGPA();
                if (sgpa > highestGPA) {
                    highestGPA = sgpa;
                    bestSemester = semester.getSemesterNumber();
                }
                if (sgpa < lowestGPA) {
                    lowestGPA = sgpa;
                    worstSemester = semester.getSemesterNumber();
                }
                totalCH += semester.getTotalCreditHours();
                totalSubjects += semester.getSubjects().size();
            }
            
            setColor(CYAN);
cout << "\n========================================\n";
cout << "        ACADEMIC PERFORMANCE\n";
cout << "========================================\n";
setColor(WHITE);
cout << "Student:         " << student->getFullName() << "\n";
cout << "Student ID:      " << student->getStudentID() << "\n";
cout << "Program:         " << student->getDegreeProgram() << "\n";
cout << "----------------------------------------\n";
setColor(LIGHT_GREEN);
cout << "Highest GPA:     " << fixed << setprecision(3) << highestGPA 
     << " (Sem " << bestSemester << ")\n";
cout << "Lowest GPA:      " << fixed << setprecision(3) << lowestGPA
     << " (Sem " << worstSemester << ")\n";
cout << "Best Semester:   Semester " << bestSemester << "\n";
cout << "Weakest Semester: Semester " << worstSemester << "\n";
cout << "Total Credits:   " << totalCH << "\n";
cout << "Total Subjects:  " << totalSubjects << "\n";
cout << "Overall CGPA:    " << fixed << setprecision(3) << student->getCGPA() << "\n";
cout << "----------------------------------------\n";
            // Academic Standing
            float cgpa = student->getCGPA();
            string standing;
            if (cgpa >= 3.50) standing = "Excellent - Dean's List ★";
            else if (cgpa >= 3.00) standing = "Good";
            else if (cgpa >= 2.50) standing = "Satisfactory";
            else if (cgpa >= 2.00) standing = "Marginal";
            else standing = "Probation";
            
            setColor(cgpa >= 3.50 ? GREEN : (cgpa >= 2.00 ? YELLOW : RED));
            cout << "│ Academic Standing:" << left << setw(36) << standing << "│\n";
            
            // Scholarship Eligibility
            if (cgpa >= 3.30) {
                setColor(GREEN);
                cout << "│ Scholarship:     " << left << setw(36) << "Eligible ★" << "│\n";
            } else {
                setColor(YELLOW);
                cout << "│ Scholarship:     " << left << setw(36) << "Not Eligible" << "│\n";
            }
            
            setColor(CYAN);
            cout << "=========================================================================\n";
            resetColor();
            
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error generating academic report: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void viewSemesters() {
        clearScreen();
        displayHeader("Previous Semester Records");
        
        try {
            const auto& semesters = student->getSemesters();
            
            if (semesters.empty()) {
                displayError("No previous semesters found!");
                pauseScreen();
                return;
            }
            
            for (const auto& semester : semesters) {
                semester.display();
                cout << "\n";
            }
            
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error viewing semesters: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void updateSubject() {
        clearScreen();
        displayHeader("Update Subject Record");
        
        try {
            string input;
            int semesterNumber;
            
            cout << "Enter Semester Number: ";
            getline(cin, input);
            
            if (!Validator::validateMenuInput(input, 12)) {
                displayError("Invalid semester number!");
                pauseScreen();
                return;
            }
            
            semesterNumber = stoi(input);
            Semester* semester = student->findSemester(semesterNumber);
            
            if (!semester) {
                displayError("Semester " + to_string(semesterNumber) + " not found!");
                pauseScreen();
                return;
            }
            
            string code;
            cout << "Enter Subject Code to update: ";
            getline(cin, code);
            code = trim(code);
            
            Subject* subject = semester->findSubject(code);
            if (!subject) {
                displayError("Subject not found!");
                pauseScreen();
                return;
            }
            
            displayInfo("Current subject details:");
            cout << "Code: " << subject->getCode() << "\n";
            cout << "Name: " << subject->getName() << "\n";
            cout << "Credit Hours: " << subject->getCreditHours() << "\n";
            cout << "Obtained Marks: " << subject->getObtainedMarks() << "\n";
            cout << "Total Marks: " << subject->getTotalMarks() << "\n";
            cout << "Highest Marks: " << subject->getHighestMarks() << "\n";
            cout << "\n";
            
            Subject updatedSubject = *subject;
            string updateInput;
            
            // Update name
            cout << "New Subject Name (Enter to keep current): ";
            getline(cin, updateInput);
            if (!updateInput.empty() && updateInput.length() >= 2) {
                updatedSubject.setName(updateInput);
            }
            
            // Update credit hours
            cout << "New Credit Hours (1-6, Enter to keep current): ";
            getline(cin, updateInput);
            if (!updateInput.empty() && Validator::validateMenuInput(updateInput, 6)) {
                updatedSubject.setCreditHours(stoi(updateInput));
            }
            
            // Update obtained marks
            cout << "New Obtained Marks (Enter to keep current): ";
            getline(cin, updateInput);
            if (!updateInput.empty()) {
                float marks = stof(updateInput);
                if (marks >= 0 && marks <= subject->getTotalMarks()) {
                    updatedSubject.setObtainedMarks(marks);
                }
            }
            
            // Update highest marks
            cout << "New Highest Marks (Enter to keep current): ";
            getline(cin, updateInput);
            if (!updateInput.empty()) {
                float marks = stof(updateInput);
                if (marks >= updatedSubject.getObtainedMarks() && marks <= subject->getTotalMarks()) {
                    updatedSubject.setHighestMarks(marks);
                }
            }
            
            semester->updateSubject(code, updatedSubject);
            FileManager::saveStudents({*student});
            
            displaySuccess("Subject updated successfully!");
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error updating subject: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void deleteSubject() {
        clearScreen();
        displayHeader("Delete Subject");
        
        try {
            string input;
            int semesterNumber;
            
            cout << "Enter Semester Number: ";
            getline(cin, input);
            
            if (!Validator::validateMenuInput(input, 12)) {
                displayError("Invalid semester number!");
                pauseScreen();
                return;
            }
            
            semesterNumber = stoi(input);
            Semester* semester = student->findSemester(semesterNumber);
            
            if (!semester) {
                displayError("Semester " + to_string(semesterNumber) + " not found!");
                pauseScreen();
                return;
            }
            
            string code;
            cout << "Enter Subject Code to delete: ";
            getline(cin, code);
            code = trim(code);
            
            Subject* subject = semester->findSubject(code);
            if (!subject) {
                displayError("Subject not found!");
                pauseScreen();
                return;
            }
            
            cout << "\nSubject: " << subject->getName() << " (" << code << ")\n";
            cout << "Are you sure you want to delete this subject? (Y/N): ";
            char confirm;
            cin >> confirm;
            clearInputBuffer();
            
            if (toupper(confirm) == 'Y') {
                if (semester->removeSubject(code)) {
                    FileManager::saveStudents({*student});
                    displaySuccess("Subject deleted successfully!");
                } else {
                    displayError("Failed to delete subject!");
                }
            } else {
                displayInfo("Deletion cancelled.");
            }
            
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error deleting subject: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void displayGradingScale() {
        clearScreen();
        displayHeader("HEC Grading Scale");
        
        setColor(CYAN);
        cout << "\n=========================================================================\n";
        cout << "                    HEC GRADING POLICY                            │\n";
        cout << "=========================================================================\n";
        setColor(WHITE);
        cout << "│ Grade │ Percentage │ Grade Points │ Description                  │\n";
        cout << "=========================================================================\n";
        
        vector<pair<string, pair<string, pair<float, string>>>> grades = {
            {"A", {"85-100", {4.00, "Excellent"}}},
            {"A-", {"80-84", {3.67, "Very Good"}}},
            {"B+", {"75-79", {3.33, "Good"}}},
            {"B", {"70-74", {3.00, "Above Average"}}},
            {"B-", {"65-69", {2.67, "Average"}}},
            {"C+", {"61-64", {2.33, "Below Average"}}},
            {"C", {"58-60", {2.00, "Satisfactory"}}},
            {"C-", {"54-57", {1.67, "Pass"}}},
            {"D+", {"50-53", {1.33, "Pass"}}},
            {"D", {"45-49", {1.00, "Pass"}}},
            {"F", {"Below 45", {0.00, "Fail"}}}
        };
        
        for (const auto& grade : grades) {
            cout << "│ " << setw(5) << grade.first 
                 << " │ " << setw(10) << grade.second.first
                 << " │ " << setw(12) << fixed << setprecision(2) << grade.second.second.first
                 << " │ " << setw(25) << grade.second.second.second << " │\n";
        }
        
        setColor(CYAN);
        cout << "=========================================================================\n";
        resetColor();
        
        cout << "\nNote: Minimum passing grade is D (45%)\n";
        cout << "Dean's List: CGPA >= 3.50\n";
        cout << "Scholarship Eligibility: CGPA >= 3.30\n";
        
        pauseScreen();
    }
    
    void exportReport() {
        clearScreen();
        displayHeader("Export GPA Report");
        
        try {
            if (student->getSemesters().empty()) {
                displayError("No data available to export!");
                pauseScreen();
                return;
            }
            
            // Calculate all GPA before exporting
            for (auto& semester : student->getSemesters()) {
                const_cast<Semester&>(semester).calculateSGPA();
            }
            student->calculateCGPA();
            
            if (ReportGenerator::generateReport(*student)) {
                displaySuccess("Report exported successfully!");
            }
            
            pauseScreen();
            
        } catch (const exception& e) {
            displayError("Error exporting report: " + string(e.what()));
            pauseScreen();
        }
    }
    
    void logout() {
        auth->logout();
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    setColor(CYAN);
    cout << "=========================================================================\n";
    cout << "              HEC ACADEMIC PERFORMANCE & GPA                   \n";
    cout << "                   MANAGEMENT SYSTEM                          \n";
    cout << "=========================================================================\n";
    cout << "  Initializing system...\n";
    resetColor();
    
    displayLoading();
    
    vector<Student> students;
    FileManager::loadStudents(students);
    
    Authentication auth(students);
    Dashboard* dashboard = nullptr;
    
    int choice;
    do {
        clearScreen();
        displayHeader("Main Menu");
        
        setColor(CYAN);
        cout << "=========================================================================\n";
        cout << "                          MAIN MENU                                \n";
        cout << "=========================================================================\n";
        setColor(WHITE);
        cout << "  1.  Student Registration                                        \n";
        cout << "  2.  Student Login                                               \n";
        cout << "  3.  Academic Dashboard                                          \n";
        cout << "  4.  About HEC Grading System                                    \n";
        cout << "  5.  Exit                                                        \n";
        setColor(CYAN);
        cout << "=========================================================================\n";
        resetColor();
        
        cout << "\nEnter your choice: ";
        string input;
        getline(cin, input);
        
        if (!Validator::validateMenuInput(input, 5)) {
            displayError("Invalid choice! Please enter a number between 1 and 5.");
            pauseScreen();
            continue;
        }
        
        choice = stoi(input);
        
        switch (choice) {
            case 1:
                auth.registerStudent();
                break;
            case 2:
                if (auth.login()) {
                    dashboard = new Dashboard(auth.getCurrentStudent(), &auth);
                }
                break;
            case 3:
                if (auth.getCurrentStudent()) {
                    dashboard = new Dashboard(auth.getCurrentStudent(), &auth);
                    dashboard->display();
                    delete dashboard;
                    dashboard = nullptr;
                } else {
                    displayError("Please login first!");
                    pauseScreen();
                }
                break;
            case 4:
                clearScreen();
                displayHeader("About HEC Grading System");
                cout << "\nHEC Grading System Overview:\n\n";
                cout << "The Higher Education Commission (HEC) Pakistan grading policy\n";
                cout << "is a standardized system used across all Pakistani universities.\n\n";
                cout << "Key Features:\n";
                cout << "• Percentage-based grading system\n";
                cout << "• Grade point scale from 0.00 to 4.00\n";
                cout << "• Minimum passing grade: D (45%)\n";
                cout << "• Dean's List: CGPA >= 3.50\n";
                cout << "• Scholarship eligibility: CGPA >= 3.30\n\n";
                cout << "Grade Distribution:\n";
                cout << "• A (85-100%): Excellent - 4.00 points\n";
                cout << "• A- (80-84%): Very Good - 3.67 points\n";
                cout << "• B+ (75-79%): Good - 3.33 points\n";
                cout << "• B (70-74%): Above Average - 3.00 points\n";
                cout << "• B- (65-69%): Average - 2.67 points\n";
                cout << "• C+ (61-64%): Below Average - 2.33 points\n";
                cout << "• C (58-60%): Satisfactory - 2.00 points\n";
                cout << "• C- (54-57%): Pass - 1.67 points\n";
                cout << "• D+ (50-53%): Pass - 1.33 points\n";
                cout << "• D (45-49%): Pass - 1.00 points\n";
                cout << "• F (Below 45%): Fail - 0.00 points\n";
                pauseScreen();
                break;
            case 5:
                displayInfo("Thank you for using HEC Academic Performance & GPA Management System!");
                displayInfo("Goodbye!");
                break;
        }
        
    } while (choice != 5);
    
    displayFooter();
    return 0;
}