#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include "users.h"
#include "logs.h"
#include "library.h"
#include <vector>

using namespace std;


string sha256(const string unhashedPassword);

bool UserLogin(vector<User> &users,vector<Book> &books, string &username, int &userId);

void start();

#endif