#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <sstream> // Для эффективной склейки

inline std::string type_error(std::string_view var, std::string_view value, std::string_view type)
{
    std::string result;
    // Резервируем память один раз, чтобы избежать перевыделений
    result.reserve(var.size() + value.size() + type.size() + 22);
    result.append(var).append(": Failed to convert ").append(value).append(" to ").append(type).append("\n");
    return result;
}

inline std::string id_not_find(std::string_view name)
{
    std::string result;
    result.reserve(name.size() + 14);
    result.append(name).append(": is not found\n");
    return result;
}

inline std::string syntax_error(std::string_view line)
{
    std::string result;
    result.reserve(line.size() + 19);
    result.append("Line ").append(line).append(": Error Sintax");
    return result;
}

inline std::string exists(std::string_view name)
{
    std::string result;
    result.reserve(name.size() + 16);
    result.append(name).append(": already exists");
    return result;
}

// Эту функцию вообще не нужно пересоздавать в куче! 
// Она возвращает string_view на статическую строку в скомпилированном коде.
inline std::string_view error_id()
{
    return "A keyword cannot be an identifier";
}