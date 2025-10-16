#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <map>
#include <string>

using json = nlohmann::json;
using namespace std;

int main()
{
    map<string, map<string, int>> grades;
    ifstream in("grades.json");
    if (!in.is_open()) {
        cerr << "Could not open the file!" << endl;
        return 1;
    }
    json j;
    in >> j;
    grades = j.get<map<string, map<string, int>>>();
    for (const auto& [name, courses] : grades) {
        int sum = 0;
        size_t count = 0;
        for (const auto& [course, grade] : courses) {
            sum += grade;
            ++count;
        }
        cout << name << " → Avg: ";
        if (count == 0) {
            cout << 0;
        } else if (sum % count == 0) {
            cout << (sum / static_cast<int>(count));
        } else {
            cout << fixed << setprecision(1) << (static_cast<double>(sum) / count) << defaultfloat;
        }
        cout << '\n';
    }

    return 0;
}