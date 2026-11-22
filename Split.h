#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>
#include "INT.h"

using namespace std;

inline vector<char*> split(std::string& text, const char symbol)
{
	vector<char*> lines;

	if (text.empty()) return lines;


	lines.push_back(&text[0]);

	size_t length = text.size();
	for (size_t i = 0; i < length; i++)
	{
		if (text[i] == symbol)
		{
			
			continue;
			
		}

	}
	
	return lines;
}

inline const char* to_char(std::string& text)
{
	return text.c_str();
}

inline bool start_with(const string& text,const char& symbol)
{
	return !text.empty() && text.front() == symbol;
}


inline bool end_with(const string& text, const char& symbol)
{
	return !text.empty() && text.back() == symbol;
}



inline bool is_number(const string& text)
{
	for (int i = 0; i < text.size(); i++)
	{

		if (text[i] >= '0' && text[i] <= '9'||text[i]=='-' )
		{

			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}


inline int to_int(const string &value)
{
	
	if (!is_number(value)) return NULL;
	char c;
	int buf;
	double number=0;
	bool otriz = false;
	for (int i = 0; i < value.size(); i++)
	{
		if (value[i] == '-')
		{
			otriz = true;
			continue;
		}
		c = value[i];
		buf = c - 48;
		number += pow(10.0, value.size()-1-i) * buf;
	}
	if (otriz)
		return (int)number*-1;
	return (int)number;
}


template <typename T>
auto onfind(unordered_map<string_view, Variable<T>>const& map, const char* find_var)
{
	return map.find(find_var);
}

template <typename T>
inline void prepare_data(int size, std::vector<T>& output) {
	output.reserve(size);
}
template <typename T>
bool is_find(unordered_map<string_view, Variable<T>> const & map, const char* find_var)
{
	return map.find(find_var)!= map.end();
}