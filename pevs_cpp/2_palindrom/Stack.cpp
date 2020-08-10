#include "Stack.h"

namespace pevs {
    Stack::Stack()
    {
        data = std::make_unique<char[]>(MAX_LENGHT);
        data[0] = '\0';
        lenght = 0;
    }

    bool Stack::push(const char& chr)
    {
        if (lenght == MAX_LENGHT - 1) return false;
        data[lenght] = chr;
        lenght++;
        data[lenght] = '\0';
        return true;
    }

	char Stack::pop()
    {
        char ret = '\0';
        if (lenght > 0) {
            lenght--;
            ret = data[lenght];
            data[lenght] = '\0';
        }
        return ret;
    }

    char Stack::popFront() {
        char ret = data[0]; //in case of empty stack \0
        for (int i = 0; i < lenght; i++) {
            data[i] = data[i+1];
        }
        return ret;
    }

    char Stack::get(const int pos) const
    {
       return (lenght > 0) ? data[(pos > lenght - 1) ? lenght : pos] : '\0';
    }

    char Stack::getFront(const int pos) const
    {
       return (pos > lenght - 1) ? '\0' : data[(lenght == 0) ? data[0] : lenght-1-pos];
    }

    const char* Stack::toString() const
    {
        return data.get();
    }

    auto Stack::toReverseString() const -> std::array<char, MAX_LENGHT>
    {
        std::array<char, MAX_LENGHT> ret;
        for (int i = 0; i <= lenght; i++) ret[i] = getFront(i); //store also \0 to end
        return ret; //kopy elYzn, aspon dufam
    }
}