#pragma once
#include <unordered_map>
#include <functional>
#include <iostream>
#include <string>
#include "INT.h"

using namespace std;
extern unordered_map<string, function<void(string)>> commands;
extern unordered_map<string, function<void(string, string)>> variables_reg;
extern unordered_map<string, Varible> variables;