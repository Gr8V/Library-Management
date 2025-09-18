#ifndef LOGS_H
#define LOGS_H

#include <iostream>
#include <vector>
using namespace std;

void addTransaction(const string &fileName, int userID, int bookID, string action);
void loginLog(const string &fileName, int userID, string userName, string action, bool status, string message);

#endif