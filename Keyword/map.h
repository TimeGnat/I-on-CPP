#pragma once
#include <unordered_map>
#include <functional>
#include <iostream>
#include <string>
#include "INT.h"

using namespace std;
extern string output_buffer;

extern unordered_map<string_view, function<void(const string_view&)>> commands;

extern vector <const char*> keyword;
template <typename T>
extern unordered_map<string_view, function<void(const char*, T) >> variables_reg;

extern unordered_map<string_view, DataType> all_variables;
extern unordered_map<string_view, Variable<bool>> bool_variables;
extern unordered_map<string_view, Variable<int>> int_variables;