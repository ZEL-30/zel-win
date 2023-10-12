#include "json/json.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace zel::json;

void testBaseType() {
    cout << "========== testBaseType ==========" << endl;

    Json v1;
    Json v2 = true;
    Json v3 = 123;
    Json v4 = 12.3;
    Json v5 = "勇士总冠军";

    cout << v2.str() << endl;
    cout << v5.str() << endl;
    cout << v3.str() << endl;
    cout << v4.str() << endl;
}

void testArray() {
    cout << "========== testArray ==========" << endl;

    Json arr;

    Json admin_object;
    admin_object["username"] = "admin";
    admin_object["password"] = "!Qw2!Qw2";

    arr.append(1.23);
    arr.append("zel");
    arr.append(false);
    for (int i = 0; i < 10; i++) {
        arr.append(admin_object);
    }

    cout << arr.str() << endl;
    arr.remove(2);
    cout << arr.str() << endl;

    arr.save("../config/user.json");

    arr.clear();
}

void testObject() {
    cout << "========== testObject ==========" << endl;

    Json obj;

    obj["name"]   = "zel";
    obj["is man"] = true;
    obj["hight"]  = 1.74;
    obj["sid"]    = 1;

    cout << obj.str() << endl;
    obj.remove("hight");
    cout << obj.str() << endl;

    obj.clear();
}

void testParser() {
    cout << "========== testParser ==========" << endl;

    Json json;
    if (!json.load("../config/test.json")) {
        printf("load json file failed\n");
    }

    std::string filename = "../config/test_json.json";
    cout << json["data"].str() << endl;
    json.remove("data");
    cout << json.str() << endl;

    json.save(filename);
    json["data"] = "test";
    json.save(filename);

    printf("paser success\n");
}

int main() {

    // testBaseType();

    // testArray();

    // testObject();

    testParser();

    return 0;
}
