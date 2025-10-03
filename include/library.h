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

void actions(const bool isAdmin, vector<Book> &books, vector<User> &users, const string &username);
void adminActions(vector<Book> &books, vector<User> &users, const string &username, const int &userId);
void userActions(vector<Book> &books, vector<User> &users, const string &username, const int &userId);

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
void changePassword(vector<User> &users, const string &username, const int &userId);

//common functions
void viewAllBooks(vector<Book> &books);



#endif