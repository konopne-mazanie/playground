#include "RecordsHolder.h"

RecordsHolder::RecordsHolder(const char filename[])
{
    FILE *fp;
    char *line;
    size_t len = 0;

    fp = fopen(filename, "r");
    if (fp == nullptr)
        return;

    while (getline(&line, &len, fp) != -1)
    {
        if ((strstr(line, ";") == nullptr) || (line[strlen(line)-1] == ';')) exit(1); //corrupt dict file

        char *word = trim(strtok(line, ";"));
        char *def = trim(strtok(nullptr, ";"));
        records.emplace_back(std::make_pair(MyString(word), MyString(def)));
    }

    fclose(fp);
}

const MyString *RecordsHolder::getDefinition(const MyString &word) const
{
    for (const auto &pair : records)
    {
        if (pair.first == word) return &pair.second;
    }
    return nullptr;
}

const std::vector<const MyString*> RecordsHolder::find(const Action act, MyString term) const
{
    std::vector<const MyString*> res;
    for (const auto &pair : records)
    {
        if (performsAction(act, pair.first, term)) res.push_back(&pair.first);
    }
    return res;
}

bool RecordsHolder::isEmpty() const
{
    return records.empty();
}

bool RecordsHolder::performsAction(const Action act, const MyString &findIn, const MyString &term) const
{
    switch (act)
    {
    case Action::findStart:
        return findIn.cmpStart(term);
    case Action::findEnd:
        return findIn.cmpEnd(term);
    default:
        return findIn.cmpIn(term);
    }
}

char *RecordsHolder::trim(char *str)
{
    char *end;
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    return str;
}