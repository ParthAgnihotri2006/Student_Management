#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// --- SAFE INPUT HELPER FUNCTIONS ---

// Function to safely take integer input
int getInt(const string& prompt) {
    string line;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value) {
            return value;
        }
        
    }
}

// Function to safely take marks between 0 and 100
float getMarks(const string& prompt) {
    string line;
    float value;
    while (true) {
        cout << prompt;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && value >= 0 && value <= 100) {
            return value;
        }
        cout << ">> Invalid marks! Please enter between 0 and 100.\n";
    }
}

// Function to safely take non-empty string
string getString(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if (!line.empty()) {
            return line;
        }
        cout << ">> Name cannot be empty. Try again.\n";
    }
}

// --- STUDENT CLASS ---
class Student {
public:
    int rollNo;
    string name;
    float marks;
    char grade;

    void calculateGrade() {
        if (marks >= 90) grade = 'A';
        else if (marks >= 75) grade = 'B';
        else if (marks >= 60) grade = 'C';
        else if (marks >= 40) grade = 'D';
        else grade = 'F';
    }

    void input() {
        rollNo = getInt("Enter Roll No: ");
        name = getString("Enter Name: ");
        marks = getMarks("Enter Marks (0-100): ");
        calculateGrade();
    }

    void display() const {
        cout << left << setw(10) << rollNo
             << setw(20) << name
             << setw(10) << fixed << setprecision(2) << marks
             << setw(8) << grade << endl;
    }
};

// --- MAIN FUNCTION ---
int main() {
    vector<Student> students;
    int choice = 0;

    do {
        cout << "\n=====================================\n";
        cout << "   STUDENT RECORD MANAGEMENT SYSTEM  \n";
        cout << "=====================================\n";
        cout << "1. Add New Student\n";
        cout << "2. View All Records\n";
        cout << "3. Search by Roll Number\n";
        cout << "4. Delete Student Record\n";
        cout << "5. Exit\n";
        cout << "-------------------------------------\n";
        
        choice = getInt("Enter your choice (1-5): ");

        switch (choice) {
            case 1: {
                cout << "\n--- Add New Student ---\n";
                Student s;
                s.input();
                students.push_back(s);
                cout << "\n[SUCCESS] Student record added successfully!\n";
                break;
            }
            case 2: {
                if (students.empty()) {
                    cout << "\n[INFO] No records found!\n";
                    break;
                }
                cout << "\n" << left << setw(10) << "Roll No"
                     << setw(20) << "Name"
                     << setw(10) << "Marks"
                     << setw(8) << "Grade" << endl;
                cout << string(48, '-') << endl;
                for (const auto& s : students) {
                    s.display();
                }
                break;
            }
            case 3: {
                if (students.empty()) {
                    cout << "\n[INFO] No records found!\n";
                    break;
                }
                int roll = getInt("Enter Roll No to search: ");
                bool found = false;
                for (const auto& s : students) {
                    if (s.rollNo == roll) {
                        cout << "\n--- Student Found ---\n";
                        cout << left << setw(10) << "Roll No"
                             << setw(20) << "Name"
                             << setw(10) << "Marks"
                             << setw(8) << "Grade" << endl;
                        cout << string(48, '-') << endl;
                        s.display();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\n[ERROR] Student with Roll No " << roll << " not found.\n";
                }
                break;
            }
            case 4: {
                if (students.empty()) {
                    cout << "\n[INFO] No records found!\n";
                    break;
                }
                int roll = getInt("Enter Roll No to delete: ");
                bool deleted = false;
                for (auto it = students.begin(); it != students.end(); ++it) {
                    if (it->rollNo == roll) {
                        students.erase(it);
                        cout << "\n[SUCCESS] Record deleted successfully!\n";
                        deleted = true;
                        break;
                    }
                }
                if (!deleted) {
                    cout << "\n[ERROR] Student with Roll No " << roll << " not found.\n";
                }
                break;
            }
            case 5:
                cout << "\nThank you for using the system. Goodbye!\n";
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please select 1, 2, 3, 4, or 5.\n";
        }
    } while (choice != 5);

    return 0;
}
