#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void actions(const bool isAdmin)
{
    if (isAdmin)
    {
        adminActions();
    }
    else if (!isAdmin)
    {
        userActions();
    }
    
    
}
void adminActions()
{
    int userInput = 0;

    cout << "*********************************\n";
    cout << "*************Actions*************\n";
    cout << "*********************************\n";
    cout << "BOOKS -->\n";
    cout << "[1] Add Book\n";
    cout << "[2] Edit Book\n";
    cout << "[3] Search Book\n";
    cout << "[4] View All Books\n";
    cout << "USERS -->\n";
    cout << "[5] Add User\n";
    cout << "[6] Remove User\n";
    cout << "[7] View All Users\n";
    cout << "[8] Show Overdue Users\n";
    cout << "What Action Do You Want To Perform: ";
    cin >> userInput;
    switch (userInput)
    {
    case 1:
        addbook();
        break;
    case 2:
        editbooks();
        break;
    case 3:
        searchbooks();
        break;
    case 4:
        viewAllBooks();
        break;
    case 5:
        addUser();
        break;
    case 6:
        removeUser();
        break;
    case 7:
        viewAllUsers();
        break;
    case 8:
        showOverdueUsers();
        break;
    default:
        cout << "Input Error: Enter a digit between 1-8.";
        break;
    }
}
void userActions()
{
    int userInput = 0;

    cout << "*********************************\n";
    cout << "*************Actions*************\n";
    cout << "*********************************\n";
    cout << "[1] Borrow Book\n";
    cout << "[2] View All Book\n";
    cout << "[3] Return Book\n";
    cout << "What Action Do You Want To Perform: ";
    cin >> userInput;

    switch (userInput)
    {
    case 1:
        borrowBook();
        break;
    case 2:
        viewAllBooks();
        break;
    case 3:
        returnBook();
        break;
    default:
        cout << "Input Error: Enter a digit between 1-3.";
        break;
    }
}

//admin functions
void addbook()
{
    cout << "Adding A Book";
}
void editbooks()
{
    cout << "Editing A Book";
}
void searchbooks()
{
    cout << "Searching A Book";
}
void addUser()
{
    cout << "Adding A User";
}
void removeUser()
{
    cout << "Removing A User";
}
void viewAllUsers()
{
    cout << "Viewing All Users";
}
void showOverdueUsers()
{
    cout << "Showing Overdue Users";
}

//user functions
void borrowBook()
{
    cout << "Borrowing A Book";
}
void returnBook()
{
    cout << "Returning A Book";
}

//common functions
void viewAllBooks()
{
    cout << "Viewing All Book";
}