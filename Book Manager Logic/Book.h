#pragma once
#include "pch.h"
#include <string>

class Book {
public:
    int id;
    std::string name;

    Book(int id, const std::string& name);
};
