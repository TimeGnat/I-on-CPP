#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Split.h"
#include "Parser.h"

using namespace std;

class Lexer
{
    string text;
    Token token;
    Parser* parser = new Parser();

public:
    void SetText(const char* text)
    {
        this->text = text;
    }

    void pars()
    {
        vector<char*> str;
        token.reserve();
        str.reserve(1000);
        str = split(text, ';');

        for (int i = 0; i < str.size(); i++)
        {
            pars_str(str[i]);
            peredach();
            token.clear_tokens();
        }
    }

    
    uint8_t inString : 1;
    uint8_t inChar : 1;
    void pars_str(const string& line)
    {
        string current = "";
        current.reserve(32); 
        inString = 0;

        for (int j = 0; j < line.size(); j++)
        {
            char c = line[j];

            if (c == '"')
            {
                if (!inString)
                {
                    if (!current.empty())
                    {
                        toker(current);
                        current.clear();
                    }
                    inString = true;
                    current.push_back(c);
                }
                else
                {
                    current.push_back(c);
                    toker(current);
                    current.clear();
                    inString = false;
                }
                continue;
            }
            if (c =='\'')
            { }

            if (inString)
            {
                current += c;
            }
            else
            {
             
                if (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' ||
                    c == '>' || c == '<' || c == '!' || c == '&' || c == '|')
                {
                    if (!current.empty())
                    {
                        toker(current);
                        current.clear();
                    }

                    if (j + 1 < line.length())
                    {
                        char next = line[j + 1];

                        
                        if (c == '>' && next == '>') { toker(">>"); j++; continue; }
                        if (c == '<' && next == '<') { toker("<<"); j++; continue; }
                        if (c == '=' && next == '=') { toker("=="); j++; continue; }
                        if (c == '!' && next == '=') { toker("!="); j++; continue; }
                        if (c == '&' && next == '&') { toker("&&"); j++; continue; }
                        if (c == '|' && next == '|') { toker("||"); j++; continue; }
                        if (c == '+' && next == '+') { toker("++"); j++; continue; }
                        if (c == '-' && next == '-') { toker("--"); j++; continue; }
                        if (c == '*' && next == '*') { toker("**"); j++; continue; }

                       
                        if (c == '-' && next >= '0' && next <= '9')
                        {
                            string buf = "-";
                            buf.reserve(16);
                            for (int i = j + 1; i < line.size(); i++)
                            {
                               
                                if (line[i] >= '0' && line[i] <= '9') {
                                    buf += line[i];
                                    j++;
                                }
                                else {
                                    break;
                                }
                            }
                            toker(buf);
                            continue;
                        }
                        

                    }

                    
                    if (c == '=') toker("=");
                    else if (c == '+') toker("+");
                    else if (c == '-') toker("-");
                    else if (c == '*') toker("*");
                    else if (c == '/') toker("/");
                    else if (c == '>') toker(">");
                    else if (c == '<') toker("<");
                    else if (c == '!') toker("!");
                    else if (c == '&') toker("&");
                    else if (c == '|') toker("|");
                }
               
                else if (c == '.' || c == '(' || c == ')' || c == ';' || c == ',' ||
                    c == '{' || c == '}' || c == '[' || c == ']')
                {
                    if (!current.empty())
                    {
                        toker(current);
                        current.clear();
                    }

                    // Передаем фиксированные литералы вместо string(1, c)
                    if (c == '.') toker(".");
                    else if (c == '(') toker("(");
                    else if (c == ')') toker(")");
                    else if (c == ';') toker(";");
                    else if (c == ',') toker(",");
                    else if (c == '{') toker("{");
                    else if (c == '}') toker("}");
                    else if (c == '[') toker("[");
                    else if (c == ']') toker("]");
                }
                else if (c == ' ' || c== '\n' || c=='\r')
                {
                    if (!current.empty())
                    {
                        toker(current);
                        current.clear();
                    }
                }
                else
                {
                    current += c;
                }
            }
        }

        if (!current.empty())
        {
            toker(current);
        }
    }

private:
    void toker(const string& tok)
    {
        if (tok == "cout")
            token.SaveToken(TokenType::KEYWORD, tok);
        else if (tok == "(" || tok == ")")
            token.SaveToken(TokenType::BRACKET, tok);
        else if (tok == ">>")
            token.SaveToken(TokenType::OPERATOR, tok);
        else if (start_with(tok, '"') && end_with(tok, '"'))
        {
            token.SaveToken(TokenType::LITERAL_STRING, tok);
        }
        else if (start_with(tok, '\'')&& end_with(tok, '\''))
            token.SaveToken(TokenType::LITERAL_CHAR, tok);
        else if (tok == ";")
        {
            token.SaveToken(TokenType::END_STR, tok);
        }
        else if (tok == ".") token.SaveToken(TokenType::POINT, tok);
        else if (tok == "int" || tok == "bool" || tok=="float") token.SaveToken(TokenType::TYPE_NAME, tok);
        else if (tok == "cin" || tok == "if" || tok == "while") token.SaveToken(TokenType::KEYWORD, tok);
        else if (tok == "++" || tok == "--" || tok == "**") token.SaveToken(TokenType::WITHONE, tok);
        else if (tok == "=" || tok == "-" || tok == "+" || tok == "*" || tok == "/") token.SaveToken(TokenType::OPERATOR, tok);
        else if (tok == "true" || tok == "false") token.SaveToken(TokenType::LITERAL_BOOL, tok);
        else if (tok == "==") token.SaveToken(TokenType::COMPARISON, tok);
        else if (tok == "!") token.SaveToken(TokenType::LOGICAL, tok);
        else if (is_number(tok))
            token.SaveToken(TokenType::NUMBER, tok);
        else
            token.SaveToken(TokenType::IDENTIFIER, tok);
    }

    void peredach()
    {
        for (int i = 0; i < token.types.size(); i++)
        {
            parser->poluch(token.types[i], to_char(token.values[i]));
        }
    }
};