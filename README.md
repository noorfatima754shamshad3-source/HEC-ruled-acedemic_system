# HEC-ruled-acedemic_system
C++ console-based GPA management system following HEC Pakistan standards with complete student registration, semester tracking, SGPA/CGPA calculation, and Bell Curve grade prediction. Built with OOP concepts including classes, inheritance, file handling, and exception handling for robust academic performance management.
#  HEC Academic Performance & GPA Management System

##  Overview

A comprehensive **C++ console-based application** developed for Pakistani universities following the **Higher Education Commission (HEC) Pakistan grading policy**. This system provides complete academic management with accurate **SGPA (Semester GPA)** and **CGPA (Cumulative GPA)** calculation, **Bell Curve grade prediction**, and comprehensive student record management.

Unlike simple GPA calculators, this is a complete academic management tool that handles semester records, subject management, grade tracking, and performance analytics throughout a student's academic journey.

---

##  Key Features

###  Student Management
- **Student Registration** with complete profile creation
- **Secure Login System** with 3-attempt protection
- **Unique Student ID** auto-generation
- **Profile Management** with all academic details

###  Academic Management
- **Semester Creation** (1-12 semesters)
- **Subject Management** (Add, Update, Delete)
- **Credit Hours Management** (1-6 credits)
- **Marks Entry** with total, obtained, and highest marks
- **Attendance Tracking** (optional)

###  GPA & CGPA Calculation
- **SGPA Calculation** using HEC grade points
- **CGPA Calculation** across all semesters
- **Grade Point Analysis** with credit hour weighting
- **Academic Standing** determination
- **Dean's List** eligibility check (CGPA ≥ 3.50)
- **Scholarship Eligibility** (CGPA ≥ 3.30)

###  Advanced Features
- **Bell Curve Grade Prediction** (Relative Grading)
- **GPA Predictor** for future semesters
- **Academic Performance Analysis** with statistics
- **Best/Worst Semester** identification
- **Performance Trends** analysis

###  Reporting & Export
- **Detailed Semester Reports** with subject-wise grades
- **Complete Academic Transcript**
- **Export to Text File** (report.txt)
- **Professional Report Formatting**
- **Grade Distribution Analysis**

---

##  Technical Implementation

### Object-Oriented Design
- **Classes**: Student, Subject, Semester, GradeCalculator
- **Inheritance**: Base classes with specialized derived classes
- **Polymorphism**: Virtual functions for flexible operations
- **Encapsulation**: Private data with public interfaces
- **Abstraction**: Clean separation of concerns
- **Composition**: Semester contains Subjects
- **Aggregation**: Student contains Semesters

### Key Components
 Project Structure
├── Student Class - Complete student profile & management
├── Subject Class - Subject details & grade calculation
├── Semester Class - Semester management & SGPA calculation
├── GradeCalculator - HEC grading policy implementation
├── BellCurvePredictor - Relative grading prediction
├── ReportGenerator - Professional report generation
├── Validator - Comprehensive input validation
├── FileManager - Data persistence & file handling
├── Authentication - Login & registration system
└── Dashboard - Main user interface & navigation


### File Handling
- **students.txt** - All student records
- **semester.txt** - Semester-wise data
- **subjects.txt** - Subject details
- **grades.txt** - Grade records
- **report_[username].txt** - Individual academic reports

---

##  HEC Grading Policy Implementation

| Grade | Percentage | Grade Points | Description |
|-------|-----------|--------------|-------------|
| A     | 85-100%   | 4.00         | Excellent   |
| A-    | 80-84%    | 3.67         | Very Good   |
| B+    | 75-79%    | 3.33         | Good        |
| B     | 70-74%    | 3.00         | Above Average |
| B-    | 65-69%    | 2.67         | Average     |
| C+    | 61-64%    | 2.33         | Below Average |
| C     | 58-60%    | 2.00         | Satisfactory |
| C-    | 54-57%    | 1.67         | Pass        |
| D+    | 50-53%    | 1.33         | Pass        |
| D     | 45-49%    | 1.00         | Pass        |
| F     | Below 45% | 0.00         | Fail        |

---

