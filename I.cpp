#include <iostream>
#include <cstdio>
#include <fstream>
#include "Parser.h"

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    ifstream file("C:\\Users\\nekra\\Desktop\\I on C++\\I\\x64\\Debug\\example.i");
    if (!file.is_open())
    {
        cout << "File is not found";
        return 0;
    }
    string txt="";
    string text = "";
    while (getline(file, txt)) { text += txt;  continue; }
    Parser parser;
    parser.SetText(text);
    parser.pars();
}
