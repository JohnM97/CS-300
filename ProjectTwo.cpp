#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string title;
    vector<string> prerequisites;

    Course(string id = "", string t = "") : courseId(id), title(t) {}
};

// Hash Table for storing courses
unordered_map<string, Course> courseTable;

// Function to load courses from a file into the hash table
void loadCourses(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string courseId, title, prereq;

        getline(stream, courseId, ',');
        getline(stream, title, ',');

        Course course(courseId, title);
        while (getline(stream, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courseTable[courseId] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

// Function to print all courses in alphanumeric order
void printAllCourses() {
    vector<string> keys;
    for (const auto& pair : courseTable) {
        keys.push_back(pair.first);
    }

    sort(keys.begin(), keys.end());

    cout << "\nCourses in alphanumeric order:" << endl;
    for (const string& key : keys) {
        cout << key << ": " << courseTable[key].title << endl;
    }
}

// Function to print course details, including prerequisites
void printCourseDetails(const string& courseId) {
    if (courseTable.find(courseId) == courseTable.end()) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = courseTable[courseId];
    cout << "\nCourse ID: " << course.courseId << endl;
    cout << "Title: " << course.title << endl;
    cout << "Prerequisites: ";

    if (course.prerequisites.empty()) {
        cout << "None" << endl;
    }
    else {
        for (const string& prereq : course.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    }
}

// Main menu function
void displayMenu() {
    int choice = 0;
    string filePath, courseId;

    while (choice != 9) {
        cout << "\nMenu:" << endl;
        cout << "1. Load Courses" << endl;
        cout << "2. Print All Courses" << endl;
        cout << "3. Print Course Details" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the file path: ";
            cin >> filePath;
            loadCourses(filePath);
            break;

        case 2:
            printAllCourses();
            break;

        case 3:
            cout << "Enter the course ID: ";
            cin >> courseId;
            printCourseDetails(courseId);
            break;

        case 9:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
