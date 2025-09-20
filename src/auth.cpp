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

bool UserLogin(vector<User> &users, bool &isAdmin, string &username, int &userId)
{
    bool isLogin = false;
    bool isValidUser = false;
    userId = 0;
    User currentUser;
    string inputPasswd;
    const string adminPasswd = "qwerty";

    do
    {
        cout << "username: ";
        cin >> username;

        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].userName == username)
            {
                isValidUser = true;
                currentUser = users[i];
                userId = users[i].userId;
            }
        }
        
        cout << "password: ";
        cin >> inputPasswd;
        if (!isValidUser && username == " ")
        {
            cout << "UserName Can Not Be Empty";
        }
        else if (!isValidUser)
        {
            cout << "User Does Not Exist!!\n";
        }
        
        else if (isValidUser && sha256(inputPasswd) == currentUser.hashedPasswd)
        {
            isLogin = true;
            if (currentUser.role == "admin")
            {
                isAdmin = true;
                cout << "Welcome Admin\n";

                // login log (successful login for admin)
                loginLog("data/login_logs.csv",userId,username,"LOGIN",true, "Successful Admin Login");
            }
            else if (currentUser.role == "member")
            {
                cout << "Welcome " << currentUser.userName;
                // login log (successful login for user)
                loginLog("data/login_logs.csv",userId,username,"LOGIN",true, "Successful User Login");
            }
            
            
        }
        else
        {
            cout << "Wrong Password!!\n";
            if (currentUser.role == "admin")
            {
                // login log (unsuccessful login for admin)
                loginLog("data/login_logs.csv",userId,username,"LOGIN", false, "Wrong Admin Password");
            }
            else if (currentUser.role == "member")
            {
                // login log (unsuccessful login for user)
                loginLog("data/login_logs.csv",userId,username,"LOGIN",false, "Not Valid User");
            }
            
        }
        cout << "\n";
    } while (isLogin == false);
    
    return isLogin;

}