#include <iostream>
#include "../include/book.h"
#include "../include/library.h"
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
    cout << '\n';
    return 0;
}

bool UserLogin(vector<User> &users, bool &isAdmin, string &username)
{
    bool isLogin = false;
    bool isValidUser = false;
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
            }
            else
            {
                cout << "Wrong Password.\n";
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
        }
        else if (!isValidUser)
        {
            cout << "Not a Valid User.\n";
        }
        
        cout << "\n";
    } while (isLogin == false);
    
    return isLogin;

}