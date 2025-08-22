#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void actions(const bool isAdmin, vector<Book> &books, vector<string> &users)
{
    if (isAdmin)
    {
        adminActions(books, users);
    }
    else if (!isAdmin)
    {
        userActions(books);
    }
    
    
}
void adminActions(vector<Book> &books, vector<string> &users)
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
        addbook(books);
        break;
    case 2:
        editbooks(books);
        break;
    case 3:
        searchbooks(books);
        break;
    case 4:
        viewAllBooks(books);
        break;
    case 5:
        addUser(users);
        break;
    case 6:
        removeUser(users);
        break;
    case 7:
        viewAllUsers(users);
        break;
    case 8:
        showOverdueUsers(users);
        break;
    default:
        cout << "Input Error: Enter a digit between 1-8.";
        break;
    }
}
void userActions(vector<Book> &books)
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
        borrowBook(books);
        break;
    case 2:
        viewAllBooks(books);
        break;
    case 3:
        returnBook(books);
        break;
    default:
        cout << "Input Error: Enter a digit between 1-3.";
        break;
    }
}

//admin functions
void addbook(vector<Book> &books)
{
    cout << "Adding A Book";
}
void editbooks(vector<Book> &books)
{
    cout << "Editing A Book";
}
void searchbooks(vector<Book> &books)
{
    cout << "Searching A Book";
}
void addUser(vector<string> &users)
{
    cout << "Adding A User";
}
void removeUser(vector<string> &users)
{
    cout << "Removing A User";
}
void viewAllUsers(vector<string> &users)
{
    cout << "Viewing All Users";
}
void showOverdueUsers(vector<string> &users)
{
    cout << "Showing Overdue Users";
}

//user functions
void borrowBook(vector<Book> &books)
{
    cout << "Borrowing A Book";
}
void returnBook(vector<Book> &books)
{
    cout << "Returning A Book";
}

//common functions
void viewAllBooks(vector<Book> &books)
{
    cout << "Viewing All Book";
}