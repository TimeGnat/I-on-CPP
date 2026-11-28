#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "Token.h"
#include "Erroe.h"
#include"Keyword/cout.h"
#include "Keyword/map.h"
#include "Split.h"
#include "AST.h"
#include <thread>
#include <algorithm>
#include <functional>
#include <future>  
using namespace std;
inline bool is_true(string_view str)
{
	
	if (str == "false")
		return false;
	else if (str == "true")
		return true;
	else
		return NULL;
}

class Parser
{
	vector<const char*> values;
	vector<TokenType>types;
	Token Token;

public:
	Parser() {
		thread t1(prepare_data<const char*>, values.size()/100*40, ref(values));
		thread t2(prepare_data<TokenType>, values.size() / 100 * 40, ref(types));
		t1.join();
		t2.join();
		int_variables.reserve(values.size() / 100 * 40);
	}

	void poluch(const TokenType& token, const char* value)
	{

		values.emplace_back(value);
		types.emplace_back(token);
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
			if (!values[i]) continue;

			// --- 1. Обработка команд (cout / вызовы) ---
			if ((i + 2 < values.size()) && (commands.find(values[i]) != commands.end()) && (types[i] == TokenType::KEYWORD))
			{
				if (i + 2 < values.size() && types[i] == TokenType::KEYWORD)
				{
					if (types[i + 2] == TokenType::LITERAL_STRING)
						commands[values[i]](values[i + 2]);
					else if (types[i + 2] == TokenType::IDENTIFIER)
					{
						auto ittype = all_variables.find(values[i + 2]);
						if (ittype != all_variables.end())
						{

							DataType type = ittype->second;
							switch (type)
							{
							case DataType::Int:
								commands[values[i]]("\""+to_string(int_variables.find(values[i + 2])->second.value)+"\"");
								break;
							case DataType::Float:
								
								break;
							case DataType::Double:
								break;

								break;
							case DataType::BOOL:
									commands[values[i]]("\"" + to_string(bool_variables.find(values[i + 2])->second.value) + "\"");
									break;
							default:
								cout << id_not_find(values[i + 2]);
								return;
								break;
							}
						}
					}
				}
			}

			// --- 2. Объявление переменных ---
			if ((i - 2 >= 0) &&
				(types[i] == TokenType::TYPE_NAME))
			{
				auto it = all_variables.find(values[i - 2]);
				if (it == all_variables.end())
				{
					if (strcmp(values[i], "int")==0)
					{
						int a = 0;
						if (types[i + 2] == TokenType::NUMBER || types[i + 2] == TokenType::IDENTIFIER && (i + 2 < values.size()))
						{
							
							int r = 0;
							string exp = "";
							exp.reserve(128);

							for (int j = i + 2; j < values.size() - 1; j++)
							{
								if (!values[j]) break;
								if (types[j] == TokenType::IDENTIFIER)
								{
									auto inner_it = int_variables.find(values[j]);
									if (inner_it != int_variables.end())
										exp += to_string(inner_it->second.value);
									else
										exp += "0";
								}
								else
								{
									exp += values[j];
								}
								r++;
							}
							RecursiveDescentParser pars(exp);
							a = (int)pars.parse();
							variables_reg<int>[values[i]](values[i - 2], a);
							i += r - 1;
						}
						else if (types[i + 2] == TokenType::KEYWORD && strcmp(values[i + 2], "cin") == 0)
						{
							cout << output_buffer;
							output_buffer = "";
							cin >> a;
							variables_reg<int>[values[i]](values[i - 2], a);
						}
						else if ((types[i] == TokenType::TYPE_NAME) && (i + 2 >= values.size()) && (i - 2 >= 0))
							variables_reg<int>[values[i]](values[i - 2], int{});

					}
					else if (strcmp(values[i], "bool") == 0)
					{
						bool a;
						if (types[i + 2] == TokenType::LITERAL_BOOL || types[i + 2] == TokenType::IDENTIFIER && (i + 2 < values.size()))
						{
							a = is_true(values[i + 2]);
							variables_reg<bool>[values[i]](values[i - 2], a);
						
						}
						else if (types[i + 2] == TokenType::KEYWORD && strcmp(values[i + 2], "cin") == 0)
						{
							cout << output_buffer;
							output_buffer = "";
							cin >> a;
							variables_reg<bool>[values[i]](values[i - 2], a);
						}
						else if ((types[i] == TokenType::TYPE_NAME) && (i + 2 >= values.size()) && (i - 2 >= 0))
							variables_reg<bool>[values[i]](values[i - 2], bool{});
					}
				}
			}
			


			else if ((types[i] == TokenType::TYPE_NAME) && i - 2 == -1)
			{
				cout << syntax_error(to_string(Token.line)) + "\n";
				break;
			}


			if (types[i] == TokenType::IDENTIFIER)
			{
				auto ittype = all_variables.find(values[i]);
				

				if (i + 1 < values.size() && types[i + 1] == TokenType::OPERATOR && values[i + 1] && strcmp(values[i + 1], "=") == 0)
				{
					if (ittype != all_variables.end())
					{
						DataType type = ittype->second;
						switch (type)
						{
						case DataType::Int:
							i = call_int(values[i], i);
							break;
						case DataType::Float:
							break;
						case DataType::Double:
							break;
							break;
						case DataType::BOOL:
							call_bool(values[i], i);
							break;
						default:
							cout << id_not_find(values[i]);
							break;
						}
					}
				}
			}
		}
		Token.line = 1;
	}
	int call_int(string_view str, int i)
	{
		auto it = int_variables.find(str);
		int r = 0;
		if (i + 2 < values.size() && (is_number(values[i + 2]) || types[i + 2] == TokenType::KEYWORD || types[i + 2] == TokenType::IDENTIFIER))
		{
			int a = 0;
			if (types[i + 2] == TokenType::KEYWORD && strcmp(values[i + 2], "cin") == 0)
			{
				cout << output_buffer;
				output_buffer = "";
				cin >> a;
			}
			else
			{
				string exp = "";
				exp.reserve(128); // Оптимизация
				for (int j = i + 2; j < values.size() - 1; j++)
				{
					if (!values[j]) break;
					if (types[j] == TokenType::IDENTIFIER)
					{
						auto inner_it = int_variables.find(values[j]);
						if (inner_it != int_variables.end())
							exp += to_string(inner_it->second.value);
						else
							exp += "0";
					}
					else
					{
						exp += values[j];
					}
					r++;
				}
				RecursiveDescentParser pars(exp);
				a = (int)pars.parse();
			}

			// Оптимизировано: запись через итератор без повторного поиска по ключу
			it->second.value = a;
			if (r > 0) return i += r - 1;
		}
		else
		{
			if (i + 2 < values.size())
				cout << type_error(values[i], values[i + 2], "int");
		}
	}
	void call_bool(string_view str, int i)
	{
		auto it = bool_variables.find(str);
		int r = 0;
		if (i + 2 < values.size() && (is_true(values[i + 2])!=NULL || types[i + 2] == TokenType::KEYWORD || types[i + 2] == TokenType::IDENTIFIER))
		{
			string a;
			if (types[i + 2] == TokenType::KEYWORD && strcmp(values[i + 2], "cin") == 0)
			{
				cout << output_buffer;
				output_buffer = "";
				cin >> a;
			}
			else
			{
				a = values[i + 2];
			}

			// Оптимизировано: запись через итератор без повторного поиска по ключу
			it->second.value = is_true(a);
		}
		else
		{
			if (i + 2 < values.size())
				cout << type_error(values[i], values[i + 2], "bool");
		}
	}
};