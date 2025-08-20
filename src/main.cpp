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

void UserLogin();
vector<string> GetUsers(const string path);

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    users = GetUsers("../data/users.txt");
    UserLogin();
    actions(isAdmin);
    

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

void UserLogin()
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
        
        cout << "*******************************************\n";
    } while (isLogin == false);
    

}