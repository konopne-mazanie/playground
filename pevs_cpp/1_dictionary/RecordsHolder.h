#pragma once

#include <vector>
#include <utility>
#include <fstream>

#include "MyString.h"

class RecordsHolder
{
private:
    std::vector<std::pair<MyString, MyString>> records;

public:
    enum Action {
        findStart = 1,
        findEnd = 2,
        findIn = 3
    };

    RecordsHolder(const char fileName[]);

    const std::vector<const MyString*> find(const Action act, MyString term) const;
    const MyString* getDefinition(const MyString& word) const;
    bool isEmpty() const;

private:
    bool performsAction(const Action act, const MyString& findIn,  const MyString& term) const;
    char *trim(char *str);
};