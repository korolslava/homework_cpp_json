#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <map>
using json = nlohmann::json;
using namespace std;

int main()
{
	map<string, string> phoneInfo;
	phoneInfo["Oleg"] = "123-456";
	phoneInfo["Ivan"] = "987-654";

	json jPhoneInfo = phoneInfo;
	phoneInfo = jPhoneInfo.get<map<string, string>>();
	ofstream out("file.json");
	out << setw(4) << jPhoneInfo << endl;

	ifstream in("file.json");
	if (!in) {
		cerr << "No file.json" << endl;
		return 1;
	}

	json jPhoneInfoIn;
	in >> jPhoneInfoIn;
	phoneInfo = jPhoneInfoIn.get<map<string, string>>();
	for (const auto& [name, phone] : phoneInfo) {
		cout << name << " : " << phone << endl;
	}

	return 0;   
}