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
    ifstream in("products.json");
    if (!in.is_open()) {
        cerr << "Could not open products.json!" << endl;
        return 1;
    }

    json j;
    in >> j;

    if (!j.is_array()) {
        cerr << "Expected a JSON array of products." << endl;
        return 1;
    }

    json expensive = json::array();

    for (const auto& item : j) {
        if (item.contains("price") && item["price"].is_number()) {
            double price = item["price"].get<double>();
            if (price > 20) {
                expensive.push_back(item);
                if (item.contains("name") && item["name"].is_string()) {
                    cout << item["name"].get<string>() << " -> " << price << '\n';
                } else {
                    cout << "(unnamed) -> " << price << '\n';
                }
            }
        }
    }

    ofstream out("expensive.json");
    if (!out.is_open()) {
        cerr << "Could not open expensive.json for writing!" << endl;
        return 1;
    }
    out << setw(4) << expensive << endl;

    return 0;
}