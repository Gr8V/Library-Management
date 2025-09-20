#ifndef USERS_H
#define USERS_H

#include "utils.h"
#include <iostream>
#include <vector>
using namespace std;

struct BorrwedBookData {
    int bookId;
    string borrowDate;
    string dueDate;
};

struct User {
    int userId;
    string userName;
    vector<BorrwedBookData> BorrowedBooks;
    string role;
    string hashedPasswd;
};

vector<User> loadUsers(const string &filename);
void writeUsers(const string &filename, const vector<User> &users);

#endif