#include <iostream>
#include "../include/library.h"
#include "../include/auth.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    bool isAdmin = false;
    string username;
    int userId = 0;

    //Load Data
    vector<User> users = loadUsers("data/users.csv");
    bool isLogin = UserLogin(users, isAdmin, username);
    vector<Book> books = loadBooks("data/books.csv");


    while (true)
    {
        if (isLogin)
        {
            if (actions(isAdmin, books, users, username))
            {
                cout << "Exiting Program";
                break;
            }
            
        }
    }
    

    //Save Data
    writeBooks("data/books.csv", books);
    writeUsers("data/users.csv", users);
    // login log (successful logout)
    for (int i = 0; i < users.size(); i++)
        {
            if (users[i].studentName == username)
            {
                userId = users[i].studentId;
            }
        }
    loginLog("data/login_logs.csv",userId,username,"LOGOUT",true, "Successful Logout");
    cout << '\n';
    return 0;
}