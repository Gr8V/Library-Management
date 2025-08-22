#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include <vector>
#include <string>
using namespace std;

void actions(const bool isAdmin, vector<Book> &books, vector<string> &users);
void adminActions(vector<Book> &books, vector<string> &users);
void userActions(vector<Book> &books);

//admin functions
void addbook(vector<Book> &books);
void editbooks(vector<Book> &books);
void searchbooks(vector<Book> &books);

void addUser(vector<string> &users);
void removeUser(vector<string> &users);
void viewAllUsers(vector<string> &users);
void showOverdueUsers(vector<string> &users);

//user functions
void borrowBook(vector<Book> &books);
void returnBook(vector<Book> &books);

//common functions
void viewAllBooks(vector<Book> &books);



#endif