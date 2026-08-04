#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
enum TokenType
{

    IDENTIFIER,           // Названия переменных/функций
    TYPE_NAME,            // int, str, bool
    CLASS_NAME,           // Имена классов
    FUNCTION_NAME,        // Имена функций

    // Ключевые слова  
    KEYWORD,              // if, other if, while, for
    MODIFIER,             // private, public, protected
    DECLARATION,          // func, class, enum class

    // Литералы
    LITERAL_INT,          // 42, 100, 0
    LITERAL_FLOAT,        // 3.14, 2.71
    LITERAL_STRING,       // "Hello I"
    LITERAL_CHAR,         // 'A', 'x'
    LITERAL_BOOL,        // true, false
    NUMBER,

    // Операторы
    OPERATOR,             // +, -, *, /, =
    COMPARISON,           // ==, !=, >, <
    LOGICAL,              // &&, ||, !

    // Специальные
    MEMORY_DIRECTIVE,     // memory, port, asm
    OPTIONAL_PARAM,       // optional
    DEFAULT_KEYWORD,      // default
    PRIVATE_TO,           // private to

    // Разделители
    DELIMITER,
    END_STR, // ., ,, ;, :, ->
    POINT,
    BRACKET,              // {}, [], ()

    // Новые уникальные
    OTHER_IF_BLOCK,       // other if { }
    PARAMETRIZED_BLOCK,   // other if (x) { }
    AUTO_INCREMENT,       // Скрытый инкремент в while
    TYPE_DECLARATION,
    None
};

class Token
{
public:
    int line = 0, column = 0;
    TokenType type = TokenType::None;

    vector<TokenType> types;
    vector<string> values;

    void SaveToken(TokenType type, string value)
    {
        types.push_back(type);
        values.push_back(value);
    }
    void clear_tokens()
    {
        types.clear();
        values.clear();
        line = 0;
        column = 0;
    }
};

