#include <iostream>
#include <cstdio>
#include <fstream>
#include "Parser.h"
#include <chrono>
#include "Lexer.h"
#include <thread>
#include "Split.h"
#include "Keyword/map.h"

using namespace std;
int main()
{


    auto start = std::chrono::high_resolution_clock::now();
    setlocale(LC_ALL, "Russian");
    std::string text;
    Lexer Lexer;
    {
        ifstream file("example.i", ios::binary | ios::ate);
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        if (!file.is_open())
        {
            cout << "File is not found\n";

            while (true)
            {
                string text;
                cout << "I>";
                cin >> text;
                Lexer.SetText(to_char(text));
                Lexer.pars();
            }
            return 0;
        }
        
        std::streamsize size = file.tellg();
        
        file.seekg(0, std::ios::beg);
       
        text.resize(size);

        file.read(&text[0], size);
    }
    Lexer.SetText(to_char(text));
    Lexer.pars();
    auto end = std::chrono::high_resolution_clock::now();
    cout << output_buffer;
    // Считаем разницу в миллисекундах
    std::cout << "Время выполнения: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " микросекунд\n";

}