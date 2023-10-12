#include "utility/ini_file.h"

#include <iostream>

using namespace zel::utility;
using namespace std;

int main() {
    IniFile ini_file;
    ini_file.load("../config/main.ini");

    const std::string &ip   = ini_file["mysql"]["ip"];
    int                port = ini_file["mysql"]["port"];

    std::cout << "ip: " << ip << "\nport: " << port << "\n";

    // cout << ini_file.Str() << endl;
    cout << "tablename: " << ini_file["mysqls"]["tablename"].str() << endl;

    ini_file.set("server", "timeout", 1000);
    ini_file.set("server", "flag", true);

    bool b = ini_file.has("server", "flag");
    bool w = ini_file.has("mysql");

    ini_file.remove("server", "flag");

    ini_file.show();

    if (!ini_file.save("../config/temp.ini")) printf("Save Failed!\n");

    return 0;
}