#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Lexer.h"
#include "Split.h"


class Parser
{
	string text = "";
	Token token;
	Lexer lexer;

public: 
    void SetText(string text)
	{
		this->text= text;
	}
    void pars()
          
	{
          
		  vector<string> str = split(text, ';');
		  for(int i = 0; i<str.size(); i++)
		  {
			  pars_str(str[i]);
			  peredach();
			  token.clear_tokens();
			  
		  }
	}


    void pars_str(string line)
    {
        vector<string> tokens;
        string current = "";
        bool inString = false;

        for (int j = 0; j < line.size(); j++)
        {
            char c = line[j];

            if (c == '"')
            {
                if (!inString)
                {
                    if (!current.empty())
                    {

                        tokens.push_back(current);
                        current = "";
                    }
                    inString = true;
                    current.push_back(c);

                }
                else
                {

                    current.push_back(c);
                    tokens.push_back(current);
                    current = "";
                    inString = false;
                }
                continue;
            }

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
                        tokens.push_back(current);
                        current = "";
                    }

                    if (j + 1 < line.length())
                    {
                        char next = line[j + 1];
                        if ((c == '>' && next == '>') ||
                            (c == '<' && next == '<') ||
                            (c == '=' && next == '=') ||
                            (c == '!' && next == '=') ||
                            (c == '&' && next == '&') ||
                            (c == '|' && next == '|'))
                        {
                        string buf;
                        buf = c;
                        buf += next;
                        tokens.push_back(buf);
                        j++;
                        continue;
                    }
                }

                tokens.push_back(string(1, c));
            }
            else if (c == '.' || c == '(' || c == ')' || c == ';' || c == ',' ||
                c == '{' || c == '}' || c == '[' || c == ']')
            {
                if (!current.empty())
                {
                    tokens.push_back(current);
                    current = "";
                }
                tokens.push_back(string(1, c));
            }
            else if (c == ' ')
            {
                if (!current.empty())
                {
                    tokens.push_back(current);
                    current = "";
                }
            }
            else
            {
                current += c;
            }

        }
    }

          if (!current.empty())
              tokens.push_back(current);

          token.clear_tokens();

          for (int i = 0; i < tokens.size(); i++)
          {
              
              toker(tokens[i]);
          }
      }
	private:
		void toker(string tok)
		{
			
			
			if (tok == "cout" || tok == "endl")
				
				token.SaveToken(TokenType::KEYWORD, tok);
			else if (tok == "(" || tok ==")")
				token.SaveToken(TokenType::BRACKET, tok);
			else if (tok == ">>")
				token.SaveToken(TokenType::OPERATOR, tok);
			else if (start_with(tok, '"') && end_with(tok, '"'))
			{
				token.SaveToken(TokenType::LITERAL_STRING, tok);
			}
			else if (tok == ";")
			{
				token.SaveToken(TokenType::END_STR, tok);
			}
			else if (tok == ".") token.SaveToken(TokenType::POINT, tok);
			else if (tok == "int" || tok == "bool") token.SaveToken(TokenType::TYPE_NAME, tok);
			else if (tok == "cin" || tok == "if" || tok == "while") token.SaveToken(TokenType::KEYWORD, tok);
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
              
			  lexer.poluch(token.types[i], token.values[i]);
		  }
	  }

};

