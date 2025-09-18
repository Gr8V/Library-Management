#include <iostream>
#include "../include/book.h"
#include "../include/library.h"
#include "../include/logs.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool UserLogin(vector<User> &users, bool &isAdmin, string &username);

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

bool UserLogin(vector<User> &users, bool &isAdmin, string &username)
{
    bool isLogin = false;
    bool isValidUser = false;
    int userId = 0;
    string inputPasswd;
    const string adminPasswd = "qwerty";

    do
    {
        cout << "username: ";
        cin >> username;

        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].studentName == username)
            {
                isValidUser = true;
                userId = users[i].studentId;
            }
        }
        
        //checks if user is admin
        if (username == "admin")
        {
            cout << "password: ";
            cin >> inputPasswd;
            if (inputPasswd == adminPasswd)
            {
                cout << "Welocome Admin\n";
                isAdmin = true;
                isLogin = true;

                // login log (successful login for admin)
                loginLog("data/login_logs.csv",userId,username,"LOGIN",true, "Successful Admin Login");
            }
            else
            {
                cout << "Wrong Password.\n";

                // login log (unsuccessful login for admin)
                loginLog("data/login_logs.csv",userId,username,"LOGIN", false, "Wrong Admin Password");
            }
        }
        else if(username == " ")
        {
            cout << "UserName cannot be empty.\n";
        }
        else if(isValidUser)
        {
            cout << "Welcome " << username << '\n';
            isLogin = true;

            // login log (successful login for user)
            loginLog("data/login_logs.csv",userId,username,"LOGIN",true, "Successful User Login");
        }
        else if (!isValidUser)
        {
            cout << "Not a Valid User.\n";

            // login log (unsuccessful login for user)
            loginLog("data/login_logs.csv",userId,username,"LOGIN",false, "Not Valid User");
        }
        
        cout << "\n";
    } while (isLogin == false);
    
    return isLogin;

}