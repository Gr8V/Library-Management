#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include "users.h"
#include "logs.h"
#include <vector>

using namespace std;

string sha256(const string unhashedPassword);

bool UserLogin(vector<User> &users, bool &isAdmin, string &username, int &userId);


#endif