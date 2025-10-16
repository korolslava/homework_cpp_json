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
    string login, password;
    cout << "Login: ";
    if (!getline(cin, login)) return 1;
    cout << "Password: ";
    if (!getline(cin, password)) return 1;

    ifstream in("accounts.json");
    if (!in.is_open()) {
        cerr << "Could not open accounts.json!" << endl;
        return 1;
    }

    json j;
    in >> j;

    if (!j.is_object()) {
        cerr << "Expected a JSON object of accounts." << endl;
        return 1;
    }

    bool ok = false;
    if (j.contains(login) && j[login].is_string()) {
        string expected = j[login].get<string>();
        if (expected == password) ok = true;
    }

    if (ok) cout << "Access granted" << endl;
    else cout << "Denied" << endl;

    return 0;
}