#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
using namespace std;

vector<string> split(const string &s, char delimiter);
int safeStoi(const string &s, int defaultVal = 0);

void titleCase(string &title);
int fineCalculator(const string &dueDate);

std::string trim(const std::string& s);

#endif
