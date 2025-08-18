#include <iostream>
#include <string>

using namespace std;

bool isAdmin = false;

void UserLogin();

int main()
{
    UserLogin();

    return 0;
}

void UserLogin()
{
    string username;
    string inputPasswd;
    const string adminPasswd = "qwerty";

    cout << "username: ";
    getline(cin, username);
    if (username == "admin")
    {
        cout << "password: ";
        cin >> inputPasswd;
        if (inputPasswd == adminPasswd)
        {
            isAdmin = true;
        }
    }
}