#include "../include/auth.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
using namespace std;


string sha256(const string &unhashedPassword)
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

bool UserLogin(vector<User> &users, vector<Book> &books, string &username, int &userId)
{
    User currentUser;
    string inputPasswd;
    bool isLogin = false;
    int loginAttemps = 0;
    do
    {
        if (loginAttemps >=5)
        {
            cout << "5 failed login attemps....\n";
            cout << "Restart Application to try again.";
            break;
        }
        
        bool isValidUser = false;
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

        if (!isValidUser && username.empty())
        {
            cout << "UserName Can Not Be Empty\n";
        }
        else if (!isValidUser)
        {
            cout << "User Does Not Exist!!\n";
        }
        else if (isValidUser)
        {
            cout << "password: ";
            cin >> inputPasswd;
            if (currentUser.role == "admin" && sha256(inputPasswd) == currentUser.hashedPasswd)
            {
                isLogin = true;
                cout << "Welcome Admin\n";
                // login log (successful login for admin)
                loginLog("data/login_logs.csv",userId,username,"LOGIN",true, "Successful Admin Login");
                while (true)
                {
                    actions(true, books, users, username);
                }
            }
            else if (currentUser.role == "member" && sha256(inputPasswd) == currentUser.hashedPasswd)
            {
                isLogin = true;
                cout << "Welcome " << currentUser.userName << '\n';
                // login log (successful login for user)
                loginLog("data/login_logs.csv",userId,username,"LOGIN",true, "Successful User Login");
                while (true)
                {
                    actions(false, books, users, username);
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
                    loginLog("data/login_logs.csv",userId,username,"LOGIN",false, "Wrong User Password");
                }
            
            }
            loginAttemps++;
        }
        cout << "\n";
    } while (isLogin == false);
    
    return isLogin;

}

void start()
{
    string username;
    int userId = 0;

    //Load Data
    vector<User> users = loadUsers("data/users.csv");
    if (users.empty())
    {
        cerr << "FATAL ERROR: there are no users in the database..";
    }
    
    vector<Book> books = loadBooks("data/books.csv");
    if (books.empty())
    {
        cerr << "FATAL ERROR: there are no books in the database..";
    }
    

    //run programme
    UserLogin(users, books, username, userId);
    
    //Save Data
    writeBooks("data/books.csv", books);
    writeUsers("data/users.csv", users);

    // login log (successful logout)
    loginLog("data/login_logs.csv",userId,username,"LOGOUT",true, "Successful Logout");
    
    cout << '\n';
}