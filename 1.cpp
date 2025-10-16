#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

int main()
{
    ifstream in("file.json");
    if (!in) { cerr << "Error opening file for reading" << endl; return 1; }

    json students;
    try {
        in >> students;
    } catch (const json::parse_error &e) {
        cerr << "Error parsing JSON file: " << e.what() << endl;
        return 1;
    }

    if (!students.is_array()) {
        cerr << "Error parsing JSON file: root is not an array" << endl;
        return 1;
    }

    double sumAges = 0.0;
    int count = 0;

    for (const auto &item : students) {
        if (!item.is_object()) continue;

        string name = "";
        int age = 0;

        if (item.contains("name") && item["name"].is_string())
            name = item["name"].get<string>();

        if (item.contains("age") && item["age"].is_number())
            age = item["age"].get<int>();

        cout << "Name: " << name << " | Age: " << age << endl;

        sumAges += age;
        ++count;
    }

    if (count > 0) {
        double average = sumAges / count;
        cout << fixed << setprecision(2);
        cout << "Average age: " << average << endl;
    } else {
        cout << "No users found in JSON." << endl;
    }
    return 0;
}
