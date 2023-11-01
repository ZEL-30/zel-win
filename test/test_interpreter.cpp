#include <parser/parser.h>
#include <parser/value.h>
using namespace script::interpreter;

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    ifstream fin;
    // fin.open("../script/Authenticate212.txt");
    fin.open("../script/test.txt");
    // fin.open("/Users/zel/Workspaces/C++/zel/script/test.txt");
    if (fin.fail()) {
        throw std::logic_error("open script failed.");
    }

    stringstream ss;
    ss << fin.rdbuf();
    string source = ss.str();

    Parser parser(source);
    auto   v_ast_nodes = parser.parse();

    for (int i = 0; i < v_ast_nodes.size(); i++) {
        cout << v_ast_nodes[i]->str() << endl;
    }
}
