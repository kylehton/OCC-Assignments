#include <iostream>
// using unordered_map since avg time complexity for simple lookups is O(1)
// also, ordering is not needed for use case
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    // map for {course number, room number}
    unordered_map<string, string> courseRooms = {
        {"CS101", "Room 3004"},
        {"CS102", "Room 4501"},
        {"CS103", "Room 6755"},
        {"NT110", "Room 1244"},
        {"CM241", "Room 1411"}
    };

    // map for {course number, instructor}
    unordered_map<string, string> courseInstructors = {
        {"CS101", "Haynes"},
        {"CS102", "Alvarado"},
        {"CS103", "Rich"},
        {"NT110", "Burke"},
        {"CM241", "Lee"}
    };

    // map for {course number, meeting time}
    unordered_map<string, string> courseTimes = {
        {"CS101", "8:00 a.m."},
        {"CS102", "9:00 a.m."},
        {"CS103", "10:00 a.m."},
        {"NT110", "11:00 a.m."},
        {"CM241", "1:00 p.m."}
    };

    string courseNum;

    // print available course numbers
    cout << "Available courses:" << endl;
    cout << "-------------------" << endl;
    // Iterate through courseRooms to print course numbers
    // using reference to avoid copying
    // using const to prevent modifying value
    for (const auto& course : courseRooms) {
        cout << course.first << endl;
    }

    cout << "Enter a course number (e.g., CS101): ";
    cin >> courseNum;

    // Check if course exists in the maps
    // if so, prints the course details
    // since using unordered map, hash lookup time of O(1)
    if (courseRooms.find(courseNum) != courseRooms.end()) {
        cout << "Course: " << courseNum << endl;
        cout << "Room: " << courseRooms[courseNum] << endl;
        cout << "Instructor: " << courseInstructors[courseNum] << endl;
        cout << "Meeting Time: " << courseTimes[courseNum] << endl;
    } else {
        cout << "Course not found." << endl;
    }

    return 0;
}
