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
    bool isLogin = UserLogin(users, isAdmin, username, userId);
    vector<Book> books = loadBooks("data/books.csv");
    
    //infinite loop to run program infinitely unless exited
    while (true)
    {
        //checks if logged in
        if (isLogin)
        {
            //if actions() returns true that means the user pressed "quit"
            //if actions() returns false then the loop continues
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
    loginLog("data/login_logs.csv",userId,username,"LOGOUT",true, "Successful Logout");
    
    cout << '\n';
    return 0;
}