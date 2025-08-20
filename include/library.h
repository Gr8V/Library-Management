#ifndef LIBRARY_H
#define LIBRARY_H

#include "../include/book.h"
#include <vector>
#include <string>
using namespace std;

void actions(const bool isAdmin);
void adminActions();
void userActions();

//admin functions
void addbook(string bookName);
void editbooks();
void searchbooks();
void addUsers();

//user functions
void borrowBook();


#endif