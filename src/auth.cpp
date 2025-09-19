#include "../include/auth.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
using namespace std;

string sha256(const string unhashedPassword)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)unhashedPassword.c_str(), unhashedPassword.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    
    return ss.str();
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