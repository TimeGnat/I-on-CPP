#pragma once
#include <iostream>
#include "Token.h"
#include <vector>
#include <string>
using namespace std;
class AST
{
	vector	<TokenType> Tokens;
	vector <string> values;

public:
	void AST_start(vector <TokenType>& type, vector <string>& values)
	{
		this->Tokens = type;
		this->values = values;
	}
private:
	
};
class Node
{
public:
	virtual ~Node() = default;
};

template <typename T>
class ArgumentNode :public Node
{
public:
	T value;
};
template <typename T>



class FunctionNode : public Node
{
public:
	std::string name;
	vector <ArgumentNode<T>> arguments;
};

class Plus : Node
{
	Node argument1;
	Node argument2;
	double value;
	
};

class Min : public Node
{
	Node argument1;
	Node argument2;
	double value;
};

class Multi : public Node
{
	Node argument1;
	Node argument2;
	double value;

};
class Number : public Node
{
	double value;
};
struct Expression :public Node
{
	char symbol;
	vector<Node> node;

};

#include <cctype>
#include <stdexcept>

class RecursiveDescentParser {
    std::string text;
    size_t pos = 0;

    char peek() {
        while (pos < text.size() && std::isspace(text[pos])) {
            pos++;
        }
        return (pos < text.size()) ? text[pos] : '\0';
    }

    char get() {
        char c = peek();
        if (c != '\0') pos++;
        return c;
    }

    double parseExpression() {
        double result = parseTerm();

        while (peek() == '+' || peek() == '-') {
            char op = get();
            double right = parseTerm();

            if (op == '+') result += right;
            else result -= right;
        }
        return result;
    }

    double parseTerm() {
        double result = parseFactor();

        while (peek() == '*' || peek() == '/') {
            char op = get();
            double right = parseFactor();

            if (op == '*') {
                result *= right;
            }
            else {
                if (right == 0) throw std::runtime_error("Division by zero!");
                result /= right;
            }
        }
        return result;
    }

    double parseFactor() {
        char next = peek();

        // 1. Исправление: Добавляем обработку унарного минуса
        if (next == '-') {
            get(); // поглощаем '-'
            return -parseFactor(); // инвертируем знак следующего множителя
        }

        // 2. Исправление: Добавляем обработку унарного плюса (например, +5)
        if (next == '+') {
            get(); // поглощаем '+'
            return parseFactor();
        }

        if (next == '(') {
            get();
            double result = parseExpression();
            if (get() != ')') {
                throw std::runtime_error("Expected closing parenthesis ')'");
            }
            return result;
        }

        if (std::isdigit(next) || next == '.') {
            size_t bytesRead = 0;
            // Передаем подстроку начиная с актуальной позиции после peek()
            double value = std::stod(text.substr(pos), &bytesRead);
            pos += bytesRead;
            return value;
        }

        // Если дошли сюда, формируем понятную ошибку
        if (next == '\0') {
            throw std::runtime_error("Unexpected end of expression");
        }
        throw std::runtime_error(std::string("Unexpected character: '") + next + "'");
    }

public:
    explicit RecursiveDescentParser(std::string expression) : text(std::move(expression)) {}

    double parse() {
        pos = 0;
        // Проверка на пустую строку перед началом
        if (peek() == '\0') {
            throw std::runtime_error("Empty expression");
        }

        double result = parseExpression();
        if (peek() != '\0') {
            throw std::runtime_error("End of text expected, but found extra characters: '" + std::string(1, peek()) + "'");
        }
        return result;
    }
};
