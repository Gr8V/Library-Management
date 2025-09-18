#ifndef BOOK_H
#define BOOK_H

#include "utils.h"
#include <iostream>
#include <vector>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    int units;
    vector<string> genres;
    int bookId;
};

vector<Book> loadBooks(const string &filename);
void writeBooks(const string &filename, const vector<Book> &books);

#endif