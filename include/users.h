#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <vector>
using namespace std;

struct BorrwedBookData {
    int bookId;
    string borrowDate;
    string dueDate;
};

struct User {
    int studentId;
    string studentName;
    vector<BorrwedBookData> BorrowedBooks;
};

int safeStoi(const string &s, int defaultVal = 0);
vector<User> loadUsers(const string &filename);
void writeUsers(const string &filename, const vector<User> &users);

void addTransaction(const string &fileName, int userID, int bookID, string action);

#endif