#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cctype>

using namespace std;

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int safeStoi(const string &s, int defaultVal)
{
    if (s.empty()) return defaultVal;
    try {
        return stoi(s);
    } catch (...) {
        return defaultVal; // fallback if s is not a number
    }
}

void titleCase(string &title)
{
        //turns first char of every word to upper case
        bool cap = true;
        for (char &c : title) {
        if (isspace(c)) cap = true;
        else if (cap) { c = toupper(c); cap = false; }
    }
}

int fineCalculator(const string &dueDate)
{
    const int FINE_PER_DAY = 10;

    //calculates current date
    string currentDate;
    time_t now = time(nullptr);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&now));
    currentDate = string(buffer);
    
    //if before due date
    if (currentDate <= dueDate)
    {
        return 0;
    }
    
    //if after due date
    tm tmCurrent = {}, tmDue = {};

    istringstream(currentDate) >> get_time(&tmCurrent, "%Y-%m-%d");
    tmCurrent.tm_hour = 0; tmCurrent.tm_min = 0; tmCurrent.tm_sec = 0;

    istringstream(dueDate) >> get_time(&tmDue, "%Y-%m-%d");
    tmDue.tm_hour = 0; tmDue.tm_min = 0; tmDue.tm_sec = 0;
    
    time_t timeCurrent = mktime(&tmCurrent);
    time_t timeDue = mktime(&tmDue);

    int daysBetween = abs(difftime(timeCurrent, timeDue)) / (60*60*24);

    return daysBetween*FINE_PER_DAY;
}

std::string trim(const std::string& s)
{
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    if (start == s.size()) {
        return ""; // string is all whitespace
    }

    size_t end = s.size() - 1;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end]))) {
        --end;
    }

    return s.substr(start, end - start + 1);
}