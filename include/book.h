#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <vector>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    int units;
    vector<string> genres;
    vector<string> borrowHistory;
};

vector<string> split(const string &s, char delimiter);

#endif