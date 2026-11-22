#include"Keyword/map.h"
#include "INT.h"
#include "Split.h"
#include "Erroe.h"
#include <cstdlib>
#include <string_view>
#include <algorithm>
string output_buffer = "";
vector <char const*> keyword = { "cin", "cout", "int" , "bool"};

unordered_map<string_view, Variable<int>> int_variables;
unordered_map<string_view, Variable<bool>> bool_variables;
unordered_map<string_view, function<void(const string_view&)>> commands = {

	{"cout", [](string_view text) {
		if (text.length() >= 2) {
			output_buffer += text.substr(1, text.length() - 2);
			output_buffer+= +"\n";
		}},
	}

};

unordered_map <string_view, DataType> all_variables;
template <typename T>
unordered_map<string_view, function<void(const char*, T)>>variables_reg = {
	{"int",[](const char* name,int value= NULL)
		{
		if (find(keyword.begin(), keyword.end(),name) != keyword.end())
		{
			cout << error_id();
			exit(EXIT_FAILURE);
			return ;
		}
		if (all_variables.find(name) != all_variables.end())
		{
			exists(name);
			exit(EXIT_FAILURE);
			return;
		}
		
			Variable<int> var;
			cout << output_buffer;

			output_buffer.clear();
			var.value = value;
			var.type = DataType::Int;
			int_variables.emplace(name, var);
			all_variables.emplace(name, DataType::Int);
		}
	},
	{ "bool", [](const char* name, bool value = NULL)
	{
		if (find(keyword.begin(), keyword.end(),name) != keyword.end())
		{
			cout << error_id();
			exit(EXIT_FAILURE);
			return;
		}
		if (all_variables.find(name)!= all_variables.end())
		{

			exists(name);
			exit(EXIT_FAILURE);
			return;
		}
		Variable<bool> var;
		cout << output_buffer;

		output_buffer.clear();
		var.value = value;
		var.type = DataType::BOOL;
		bool_variables.emplace(name, var);
		all_variables.emplace(name, DataType::BOOL);
	}

	}

};
template unordered_map<string_view, function<void(const char*, int)>> variables_reg<int>;
template unordered_map<string_view, function<void(const char*, bool)>> variables_reg<bool>;