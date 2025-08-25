#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void titleCase(string &title)
{
        //turns first char of every word to upper case
        bool cap = true;
        for (char &c : title) {
        if (isspace(c)) cap = true;
        else if (cap) { c = toupper(c); cap = false; }
    }
}

bool actions(const bool isAdmin, vector<Book> &books, vector<string> &users)
{
    cout << "*********************************\n";
    cout << "*************Actions*************\n";
    cout << "*********************************\n";
    if (isAdmin)
    {
        if (adminActions(books, users))
        {
            return true;
        }
        
    }
    else if (!isAdmin)
    {
        if (userActions(books))
        {
            return true;
        }
        
    }
    
    return false;
}
bool adminActions(vector<Book> &books, vector<string> &users)
{
    int userInput = 0;

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
    cout << "[9] Quit\n";
    cout << "What Action Do You Want To Perform: ";
    cin >> userInput;
    cout << '\n';
    cout << "**************************\n";
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
    case 9:
        return true;
        break;
    default:
        cout << "Input Error: Enter a digit between 1-8.";
        break;
    }
    return false;
}
bool userActions(vector<Book> &books)
{
    int userInput = 0;

    cout << "[1] Borrow Book\n";
    cout << "[2] View All Book\n";
    cout << "[3] Return Book\n";
    cout << "[4] Quit\n";
    cout << "What Action Do You Want To Perform: ";
    cin >> userInput;
    cout << '\n';
    cout << "**************************\n";
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
    case 4:
        return true;
        break;
    default:
        cout << "Input Error: Enter a digit between 1-3.";
        break;
    }
    return false;
}

//admin functions
void addbook(vector<Book> &books)
{
    Book newBook;
    cout << "Enter Title : ";
    getline(cin >> ws, newBook.title);
    titleCase(newBook.title);

    cout << "Enter Author : ";
    getline(cin, newBook.author);
    titleCase(newBook.author);

    cout << "Enter Year : ";
    cin >> newBook.year;

    cout << "Enter Units : ";
    cin >> newBook.units;
    
    //genres
    int genreNum = 1;
    string garbage;
    getline(cin, garbage);
    while (true)
    {
        string genre;
        cout << "Enter Genre-" << genreNum << " (leave blank to stop): ";
        getline(cin, genre);
        if (genre.empty())
        {
            break;
        }
        
        newBook.genres.push_back(genre);
        genreNum++;
    }
    string his;
    newBook.borrowHistory.push_back("None");
    books.push_back(newBook);
    cout << "Adding A Book";

    //Save Data
    writeBooks("data/books.csv", books);
}
void editbooks(vector<Book> &books)
{
    Book bookToEdit;
    int indexEdited = -1;
    string bookTitle;
    int toEdit;
    cout << "Enter Title Of Book To Edit : ";
    getline(cin >> ws, bookTitle);
    titleCase(bookTitle);
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].title == bookTitle)
        {
            bookToEdit = books[i];
            indexEdited = i;
        }
    }
    if (indexEdited == -1)
    {
        cout << "Book Not Found";
        return;
    }

    cout << "What Do You Want To Edit?\n";
    cout << "[1] title\n";
    cout << "[2] author\n";
    cout << "[3] year\n";
    cout << "[4] units\n";
    cout << "[5] genre\n";
    cout << ">>";
    cin >> toEdit;
    cout << "***********************\n";
    string titleEdit, authorEdit;
    int yearEdit, unitsEdit;
    switch (toEdit)
    {
    case 1:
        cout << "Enter New Title : ";
        getline(cin >> ws, titleEdit);
        titleCase(titleEdit);
        bookToEdit.title = titleEdit;
        break;
    case 2:
        cout << "Enter New Author Name : ";
        getline(cin >> ws, authorEdit);
        titleCase(authorEdit);
        bookToEdit.author = authorEdit;
        break;
    case 3:
        cout << "Enter New Publishing Year : ";
        cin >> yearEdit;
        bookToEdit.year = yearEdit;
        break;
    case 4:
        cout << "Enter Units : ";
        cin >> unitsEdit;
        bookToEdit.units = unitsEdit;
        break;
    case 5:
        int genEdit;
        int genToRemove;
        cout << "What Do You Want To Do\n";
        cout << "[1] Add Genre\n";
        cout << "[2] Remove Genre\n";
        cout << ">>";
        cin >> genEdit;
        switch (genEdit)
        {
        case 1:
            bool enteringGen;
            do
            {
                string newGen;
                cout << "Enter New Genre : ";
                cin >> newGen;
                bookToEdit.genres.push_back(newGen);
            } while (enteringGen);
            
            break;
        case 2:
            cout << "GENRES -->\n";
            for (int i = 0; i < bookToEdit.genres.size(); i++)
            {
                cout << "[" << i+1 << "]" << bookToEdit.genres[i] << '\n';
            }
            cout << "Which Do You Want To Remove : ";
            cin >> genToRemove;
            bookToEdit.genres.erase(bookToEdit.genres.begin()+(genToRemove-1));
            break;
        default:
            cout << "Invalid Input";
            break;
        }
        break;
    default:
        break;
    }

    books[indexEdited] = bookToEdit;
    cout << "Editing A Book";

    //Save Data
    writeBooks("data/books.csv", books);
}
void searchbooks(vector<Book> &books)
{
    Book bookToSearch;
    string bookTitle;

    cout << "Enter Title Of Book To Search : ";
    getline(cin >> ws, bookTitle);
    titleCase(bookTitle);
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].title == bookTitle)
        {
            bookToSearch = books[i];
        }
    }
    if (bookToSearch.title == "" && bookToSearch.author == "")
    {
        cout << "Book Not Found!!!\n";
    }
    else
    {
        cout << "Book Found: " << bookToSearch.title << " by " << bookToSearch.author << ".\n";
        cout << "            Published in the year " << bookToSearch.year << ".\n";
        cout << "            Genres: ";
        for (int i = 0; i < bookToSearch.genres.size(); i++)
        {
            cout << bookToSearch.genres[i];
            if(i != bookToSearch.genres.size()-1) cout << ", ";
        }
        
        cout << '\n';
        cout << "            Units Availabe: " << bookToSearch.units << ".\n";
        cout << "            Borrowed By: ";
        for (int i = 0; i < bookToSearch.borrowHistory.size(); i++)
        {
            cout << bookToSearch.borrowHistory[i];
            if(i != bookToSearch.borrowHistory.size()-1) cout << ", ";
        }
        cout << '\n';
    }
}
void addUser(vector<string> &users)
{
    //Get New User
    string newUser;
    cout << "Enter Name Of New User: ";
    cin >> newUser;

    //appends new user
    string text;
    ifstream ReadFile("data/users.txt");
    if (ReadFile.is_open())
    {
        getline(ReadFile >> ws, text);
        ReadFile.close();
    }
    else
    {
        cout << "Failed to open file for reading!\n";
        return;
    }
    text+=","+newUser;

    //Write to file
    ofstream WriteFile("data/users.txt");
    if (WriteFile.is_open())
    {
        WriteFile << text;
        WriteFile.close();
        cout << "User Added!";
    }
    else
    {
        cout << "Failed to open file for writing!\n";
    }
    users.push_back(newUser);
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

    //Save Data
    writeBooks("data/books.csv", books);
}
void returnBook(vector<Book> &books)
{
    cout << "Returning A Book";

    //Save Data
    writeBooks("data/books.csv", books);
}

//common functions
void viewAllBooks(vector<Book> &books)
{
    cout << "Viewing All Book";
}