#pragma once

#include <cstring>
#include <iostream>
#include <ostream>
#include <memory>

class MyString
{
private:
	std::unique_ptr<char[]> chars;
	int lenght;

public:
	MyString(const char init[]);
	bool operator==(const MyString& second) const;
	bool operator!=(const MyString& second) const;
	friend std::ostream& operator << (std::ostream& out, const MyString& mstr);
	MyString(const MyString &second);

	void print() const;
	bool cmpStart(const MyString &s) const;
	bool cmpEnd(const MyString &s) const;
	bool cmpIn(const MyString &s) const;
};