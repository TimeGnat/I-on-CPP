#pragma once
#include <iostream>

#include <string>
#include <vector>
#include "Token.h"
#include"Keyword/cout.h"
#include "Keyword/map.h"
using namespace std;

class Lexer
{
	vector<string> values;
	vector<TokenType>types;


public:
	void poluch(TokenType token, string value)
	{
		values.push_back(value);
		types.push_back(token);
		if (token == TokenType::END_STR)
		{
			obr();
			types.clear();
			values.clear();
		}
	
	}
private:
	void obr()
	{
		for (int i = 0; i < values.size(); i++)
		{
			if ((i + 2 < values.size()) && (commands.find(values[i]) != commands.end()) && (types[i]==TokenType::KEYWORD))
			{
				
				if (types[i + 2] == TokenType::LITERAL_STRING)
					commands[values[i]](values[i + 2]);
				else if (types[i + 2] == TokenType::IDENTIFIER)
					commands[values[i]]("\""+variables[values[i + 2]].value+ "\"");
					
			}
			if ((types[i] == TokenType::TYPE_NAME) && (i + 2 < values.size()) && (variables_reg.find(values[i]) != variables_reg.end())&&(i-2>=0))
				variables_reg[values[i]](values[i - 2], values[i + 2]);
			
		}
	}
};

