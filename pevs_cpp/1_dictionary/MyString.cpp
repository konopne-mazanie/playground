#include "MyString.h"

MyString::MyString(const char init[])
{
    lenght = strlen(init);
    chars = std::make_unique<char[]>(lenght + 1);
    strcpy(chars.get(), init);
}

bool MyString::operator==(const MyString &second) const
{
    if (lenght != second.lenght)
        return false;
    return strcmp(chars.get(), second.chars.get()) == 0;
}

bool MyString::operator!=(const MyString &second) const
{
    return !(*this == second);
}

std::ostream& operator<< (std::ostream& out, const MyString& mstr)
{
    out << mstr.chars.get();
    return out;
}

MyString::MyString(const MyString &second)
{
    lenght = second.lenght;
    chars = std::make_unique<char[]>(lenght + 1);
    strcpy(chars.get(), second.chars.get());
}

bool MyString::cmpStart(const MyString &s) const
{
    int j = 0;
    for (int i = 0; i < s.lenght; i++, j++)
    {
        if ((j == lenght) || (this->chars[j] != s.chars[i]))
            return false;
    }
    return true;
}

bool MyString::cmpEnd(const MyString &s) const
{
    int j = lenght - 1;
    for (int i = s.lenght - 1; i >= 0; i--, j--)
    {
        if ((j == -1) || (this->chars[j] != s.chars[i])) return false;
    }
    return true;
}

bool MyString::cmpIn(const MyString &s) const
{
    return strstr(chars.get(), s.chars.get()) != nullptr;
}