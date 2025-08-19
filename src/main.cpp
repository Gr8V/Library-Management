#include <iostream>
#include <string>

using namespace std;

string users[] = {"student1", "student2", "student3", "student4", "student5", "student6", "student7"};
bool isAdmin = false;

void UserLogin();

int main()
{
    UserLogin();


    cout << '\n';
    return 0;
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
        for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++)
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