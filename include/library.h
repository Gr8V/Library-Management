#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include <vector>
#include <string>
using namespace std;

void actions(const bool isAdmin);
void adminActions();
void userActions();

//admin functions
void addbook();
void editbooks();
void searchbooks();

void addUser();
void removeUser();
void viewAllUsers();
void showOverdueUsers();

//user functions
void borrowBook();
void returnBook();

//common functions
void viewAllBooks();



#endif