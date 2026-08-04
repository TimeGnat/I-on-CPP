#include"Keyword/map.h"
#include "INT.h"
#include "Split.h"
#include "Error.h"

unordered_map<string, Varible> variables;
unordered_map<string, function<void(string)>> commands{

	{"cout", [](string text) {
		text.erase(0,1);
		text.erase(text.length() - 1, 1);

		cout << text << "\n"; }}

};

unordered_map<string, function<void(string, string)>>variables_reg{
	{"int",[](string name,string value) 
	{Varible var;
	if (!is_number(value))
	{
		cout << type_error();
	}
	else
	{
		var.type = "int";
		var.value = value;
		variables.emplace(name, var);
	}
	}
	}
};