#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include "users.h"
#include "utils.h"
#include "logs.h"
#include "auth.h"
#include <vector>
#include <string>
using namespace std;

bool actions(const bool isAdmin, vector<Book> &books, vector<User> &users, const string &username);
bool adminActions(vector<Book> &books, vector<User> &users);
bool userActions(vector<Book> &books, vector<User> &users, const string &username);

//admin functions
void addbook(vector<Book> &books);
void editbooks(vector<Book> &books);
void searchAndFilterbooks(vector<Book> &books, vector<User> &users, const string &username);

void addUser(vector<User> &users);
void removeUser(vector<User> &users);
void viewAllUsers(vector<User> &users);
void showOverdueUsers(vector<User> &users);
void showLogs();

//user functions
void borrowBook(vector<Book> &books, vector<User> &users, const string &username);
void returnBook(vector<Book> &books, vector<User> &users, const string &username);

//common functions
void viewAllBooks(vector<Book> &books);



#endif