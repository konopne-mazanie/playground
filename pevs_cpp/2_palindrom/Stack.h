#pragma once

#include <cstring>
#include <memory>

namespace pevs {
	class Stack
	{
	private:
		std::unique_ptr<char[]> data;
		int lenght;

	public:
		static const int MAX_LENGHT = 30;

		Stack();
		//Namiesto toho aby sme obracali neustale obsah prveho zasobnika proste
		//data vratime v opacnom poradi, na co sluzi popFront a getFront,
		//podobnu metodu ako popFront najdeme v roznych jazykoch.
		//Get funkcie nemazu data - umoznia nam opakovat volby v menu bez
		//vlozenia rovnakych dat znovu.
		bool push(const char& chr);
		char pop();
		char popFront();
		char get(const int pos) const;
		char getFront(const int pos) const;
		const char* toString() const;
		std::array<char, MAX_LENGHT> toReverseString() const;
	};
}