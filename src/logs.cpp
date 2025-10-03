#include "../include/logs.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <fstream>

using namespace std;

void addTransaction(const string &fileName, int userID, int bookID, string action)
{
    string currentTime;
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    currentTime = string(buffer);

    ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open())
    {
        file << "\n" << userID << ", " << bookID << ", " << action << ", " << currentTime;
        file.close();
    }
    else
    {
        cout << "ERROR : Unable to log transaction. file not open.";
    }
}

void loginLog(const string &fileName, int userID, string userName, string action, bool status, string message)
{
    string currentTime;
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    currentTime = string(buffer);


    ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open())
    {
        file << "\n" << action << ", " << userID << ", " << userName << ", " << currentTime << ", " << status << ", " << message;
        if (action == "LOGOUT")
        {
            file << "\n";
        }
        
        file.close();
    }
    else
    {
        if (action == "LOGIN")
        {
            cout << "ERROR : Unable to log login. file not open.";
        }
        else if (action == "LOGOUT")
        {
            cout << "ERROR : Unable to log logout. file not open.";
        }
        
    }
}
