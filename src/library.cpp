#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void actions(const bool isAdmin)
{
    if (isAdmin)
    {
        void adminActions();
    }
    else if (!isAdmin)
    {
        void userActions();
    }
    
    
}
void adminActions()
{
    cout << "*********************************";
    cout << "*************Actions*************";
    cout << "*********************************";
    cout << "BOOKS -->";
    cout << "[1] Add Book";
    cout << "[2] Edit Book";
    cout << "[3] Search Book";
    cout << "[4] View All Books";
    cout << "USERS -->";
    cout << "[5] Add User";
    cout << "[6] Remove User";
    cout << "[7] View All Users";
    cout << "[8] Show Overdue Users";
    cout << "What Action Do You Want To Perform: ";
}
void userActions()
{
    cout << "*********************************";
    cout << "*************Actions*************";
    cout << "*********************************";
    cout << "[1] Borrow Book";
    cout << "[2] View All Book";
    cout << "[3] Return Book";
    cout << "[4] Add Users";
    cout << "What Action Do You Want To Perform: ";
}
