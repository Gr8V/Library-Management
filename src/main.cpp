#include <iostream>
#include "../include/book.h"
#include "../include/library.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> users;
bool isAdmin = false;

bool UserLogin();
vector<string> GetUsers(const string path);

int main()
{
    users = GetUsers("data/users.txt");
    bool isLogin = UserLogin();
    if (isLogin) actions(isAdmin);


    vector<Book> books = loadBooks("data/books.csv");


    //Ending tasks
    writeBooks("data/books.csv", books);
    cout << '\n';
    return 0;
}

vector<string> GetUsers(const string path)
{
    string text;
    vector<string> users;
    ifstream ReadFile(path);
    getline(ReadFile, text);
    return split(text, ',');
}

bool UserLogin()
{
    bool isLogin = false;
    bool isValidUser = false;
    string username;
    string inputPasswd;
    const string adminPasswd = "qwerty";

    do
    {
        cout << "username: ";
        cin >> username;

        //checks if user is in the users[] global array
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i] == username)
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