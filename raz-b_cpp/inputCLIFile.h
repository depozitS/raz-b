#pragma once
#include <variant>
#include <string>

std::variant<int, std::string> typedInput();

template <typename T>
T correctInput();

template<>
int correctInput<int>();

template<>
std::string correctInput<std::string>();