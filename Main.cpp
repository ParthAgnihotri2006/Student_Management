#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// --- CLASS: Student ---
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
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks (out of 100): ";
        cin >> marks;
        calculateGrade();
    }

    void display() {
        cout << left << setw(10) << rollNo
             << setw(25) << name
             << setw(10) << marks
             << setw(5) << grade << endl;
    }
};

// --- FILE OPERATIONS ---
void saveToFile(vector<Student>& students) {
    ofstream file("students.dat", ios::binary);
    int size = students.size();
    file.write((char*)&size, sizeof(size));
    for (auto& s : students) {
        file.write((char*)&s, sizeof(Student));
    }
    file.close();
}

void loadFromFile(vector<Student>& students) {
    ifstream file("students.dat", ios::binary);
    if (!file) return;
    int size;
    file.read((char*)&size, sizeof(size));
    students.resize(size);
    for (int i = 0; i < size; i++) {
        file.read((char*)&students[i], sizeof(Student));
    }
    file.close();
}

// --- MAIN MENU ---
int main() {
    vector<Student> students;
    loadFromFile(students);
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search by Roll No\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student s;
                s.input();
                students.push_back(s);
                saveToFile(students);
                cout << "✅ Student added successfully!\n";
                break;
            }
            case 2: {
                if (students.empty()) {
                    cout << "No records found.\n";
                    break;
                }
                cout << "\n" << left << setw(10) << "Roll No"
                     << setw(25) << "Name"
                     << setw(10) << "Marks"
                     << setw(5) << "Grade" << endl;
                cout << string(50, '-') << endl;
                for (auto& s : students) s.display();
                break;
            }
            case 3: {
                int roll;
                cout << "Enter Roll No to search: ";
                cin >> roll;
                bool found = false;
                for (auto& s : students) {
                    if (s.rollNo == roll) {
                        s.display();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "❌ Student not found.\n";
                break;
            }
            case 4: {
                int roll;
                cout << "Enter Roll No to delete: ";
                cin >> roll;
                bool deleted = false;
                for (auto it = students.begin(); it != students.end(); ++it) {
                    if (it->rollNo == roll) {
                        students.erase(it);
                        saveToFile(students);
                        cout << "🗑 Student deleted.\n";
                        deleted = true;
                        break;
                    }
                }
                if (!deleted) cout << "❌ Student not found.\n";
                break;
            }
            case 5:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
