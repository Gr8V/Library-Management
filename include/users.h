#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <vector>
using namespace std;

struct User {
    int studentId;
    string studentName;
    int book1Id;
    int book2Id;
    int book3Id;
    int book4Id;
    int book5Id;
};

int safeStoi(const string &s, int defaultVal = 0);
vector<User> loadUsers(const string &filename);
void writeUsers(const string &filename, const vector<User> &users);

#endif