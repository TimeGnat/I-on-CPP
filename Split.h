#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

inline vector<string> split(const string& text, char symbol)
{
	vector<string> lines;
	string line;
	char ch = ' ';
	for (int i = 0; i<=text.size(); i++)
	{
		ch = text[i];
		line.push_back(ch);
		if ((ch == symbol ) or (i==text.size()))
		{
			lines.push_back(line);
			line.clear();
		}
	}
	return lines;

}

inline bool start_with(const string& text, char symbol)
{
	return !text.empty() && text.front() == symbol;
}

inline bool end_with(const string& text, char symbol)
{
	return !text.empty() && text.back() == symbol;
}
inline bool is_number(const string& text)
{
	for (int i = 0; text.size(); i++)
	{
		if (text[i] > '0' && text[i] < '9')
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
	int number=0;
	for (int i = 0; i < value.size(); i++)
	{
		c = value[i];
		buf = c - 48;
		number += pow(10.0, i) * buf;
	}
	return number;
}