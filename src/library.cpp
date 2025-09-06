#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

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

bool actions(const bool isAdmin, vector<Book> &books, vector<User> &users, const string &username)
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
        if (userActions(books, users, username))
        {
            return true;
        }
        
    }
    
    return false;
}
bool adminActions(vector<Book> &books, vector<User> &users)
{
    int userInput = 0;

    cout << "BOOKS -->\n";
    cout << "[1] Add Book\n";
    cout << "[2] Edit Book\n";
    cout << "[3] Search/Filter Books\n";
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
        searchAndFilterbooks(books, users, "admin");
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
bool userActions(vector<Book> &books, vector<User> &users, const string &username)
{
    int userInput = 0;

    cout << "[1] Borrow Book\n";
    cout << "[2] Return Book\n";
    cout << "[3] View All Book\n";
    cout << "[4] Search/Filter Books\n";
    cout << "[5] Quit\n";
    cout << "What Action Do You Want To Perform: ";
    cin >> userInput;
    cout << '\n';
    cout << "**************************\n";
    switch (userInput)
    {
    case 1:
        borrowBook(books, users, username);
        break;
    case 2:
        returnBook(books, users, username);
        break;
    case 3:
        viewAllBooks(books);
        break;
    case 4:
        searchAndFilterbooks(books, users, username);
        break;
    case 5:
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
    int prevBookId = books[books.size()-1].bookId;
    newBook.bookId = prevBookId+1;
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
void searchAndFilterbooks(vector<Book> &books, vector<User> &users, const string &username)
{
    vector<Book> booksSearched;
    int howToSearch;
    
    cout << "How Do You Want To Search/Filter --> \n";
    cout << "[1] by Title\n";
    cout << "[2] by Author\n";
    cout << "[3] by BookID\n";
    cout << "[4] by Genre\n";
    cout << "[5] by Year\n";
    cout << "[6] show Avaiable\n";
    cout << "[7] show Borrowed(By User)\n";
    cout << ">>";
    cin >> howToSearch;
    cout << "\n\n";

    switch (howToSearch)
    {
    case 1:{
        string bookTitle;
        cout << "Enter Title: ";
        getline(cin >> ws, bookTitle);
        titleCase(bookTitle);
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].title == bookTitle)
            {
                booksSearched.push_back(books[i]);
            }
        }
        break;
    }
    case 2:{
        string bookAuthor;
        cout << "Enter Author: ";
        getline(cin >> ws, bookAuthor);
        titleCase(bookAuthor);
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].author == bookAuthor)
            {
                booksSearched.push_back(books[i]);
            }
        }
        break;
    }
    case 3:{
        int bookID;
        cout << "Enter BookID: ";
        cin >> bookID;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].bookId == bookID)
            {
                booksSearched.push_back(books[i]);
            }
        }
        break;
    }
    case 4:{
        string bookGenre;
        cout << "Enter Genre: ";
        getline(cin >> ws, bookGenre);
        titleCase(bookGenre);
        for (int i = 0; i < books.size(); i++)
        {
            for(auto genre: books[i].genres)
            {
                if (genre == bookGenre)
                {
                    booksSearched.push_back(books[i]);
                }
                
            }
        }
        break;
    }
    case 5:{
        int bookYear;
        cout << "Enter Year: ";
        cin >> bookYear;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].year == bookYear)
            {
                booksSearched.push_back(books[i]);
            }
        }
        break;
    }
    case 6:{
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].units != 0)
            {
                booksSearched.push_back(books[i]);
            }
        }
        break;
    }
    case 7:{
        int borrowedBookIDs[5];
        for (size_t i = 0; i < users.size(); i++)
        {
            if (users[i].studentName == username)
            {
                borrowedBookIDs[0] = users[i].book1Id;
                borrowedBookIDs[1] = users[i].book2Id;
                borrowedBookIDs[2] = users[i].book3Id;
                borrowedBookIDs[3] = users[i].book4Id;
                borrowedBookIDs[4] = users[i].book5Id;
            }
        }
        

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].bookId == borrowedBookIDs[0])
            {
                booksSearched.push_back(books[i]);
            }
            else if (books[i].bookId == borrowedBookIDs[1])
            {
                booksSearched.push_back(books[i]);
            }
            else if (books[i].bookId == borrowedBookIDs[2])
            {
                booksSearched.push_back(books[i]);
            }
            else if (books[i].bookId == borrowedBookIDs[3])
            {
                booksSearched.push_back(books[i]);
            }
            else if (books[i].bookId == borrowedBookIDs[4])
            {
                booksSearched.push_back(books[i]);
            }
            
        }
        break;
    }
    default:
        break;
    }

    for(auto book : booksSearched)
    {
        cout << "\n";
        cout << book.title << " by " << book.author << ".\n";
        cout << "Published in the year " << book.year << ".\n";
        cout << "Genres: ";
        for (int i = 0; i < book.genres.size(); i++)
        {
            cout << book.genres[i];
            if(i != book.genres.size()-1) cout << ", ";
        }
        
        cout << '\n';
        cout << "Units Availabe: " << book.units << ".\n";
        cout << "BookId : " << book.bookId << '\n';
        cout << '\n';
    }
}
void addUser(vector<User> &users)
{
    //Get New User
    string newUserName;
    cout << "Enter Name Of New User: ";
    cin >> newUserName;

    //check if user already exists
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].studentName == newUserName)
        {
            cout << "ERROR : User Already Exists.";
            return;
        }
        
    }

    User newUser;
    newUser.studentId = (users[users.size()-1].studentId)+1;
    newUser.studentName = newUserName;
    newUser.book1Id = 0;
    newUser.book2Id = 0;
    newUser.book3Id = 0;
    newUser.book4Id = 0;
    newUser.book5Id = 0;
    
    users.push_back(newUser);

    //Save Data
    writeUsers("data/users.csv", users);
}
void removeUser(vector<User> &users)
{
    int userIdToRemove;
    User userToRemove;
    bool wrongInput = false;
    cout << "Enter User ID To Remove : ";
    cin >> userIdToRemove;
    

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].studentId == userIdToRemove)
        {
            users.erase(users.begin()+i);
            cout << "User Removed Successfully";
        }
    }
    
    //Save Data
    writeUsers("data/users.csv", users);
}
void viewAllUsers(vector<User> &users)
{
    //View Users
    cout << "USERS -->\n";
    
    for (size_t i = 0; i < users.size(); i++)
    {
        cout << users[i].studentName << ", ID=" << users[i].studentId << '\n';
    }
    cout << "*************************";
}
void showOverdueUsers(vector<User> &users)
{
    cout << "Showing Overdue Users";
}

//user functions
void borrowBook(vector<Book> &books, vector<User> &users, const string &username)
{
    int borrowBookId;
    int indexToBorrow;
    int indexOfUser;
    Book bookToBorrow;
    User currentUser;
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].studentName == username)
        {
            currentUser = users[i];
            indexOfUser = i;
        }
    }
    cout << "Enter The Id Of Book You Want To Borrow : ";
    cin >> borrowBookId;

    //gets book to borrow
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].bookId == borrowBookId)
        {
            bookToBorrow = books[i];
            indexToBorrow = i;
        }
    }

    if (bookToBorrow.units == 0)
    {
        cout << "The Book Is Out Of Stock\n\n";
        return;
    }
    

    if (currentUser.book1Id == 0)
    {
        currentUser.book1Id = bookToBorrow.bookId;
        bookToBorrow.units--;
    }
    else if (currentUser.book2Id == 0)
    {
        currentUser.book2Id = bookToBorrow.bookId;
        bookToBorrow.units--;
    }
    else if (currentUser.book3Id == 0)
    {
        currentUser.book3Id = bookToBorrow.bookId;
        bookToBorrow.units--;
    }
    else if (currentUser.book4Id == 0)
    {
        currentUser.book4Id = bookToBorrow.bookId;
        bookToBorrow.units--;
    }
    else if (currentUser.book5Id == 0)
    {
        currentUser.book5Id = bookToBorrow.bookId;
        bookToBorrow.units--;
    }
    else
    {
        cout << "You Already Borrowed 5 Books\n";
        cout << "You Can't Borrow Any More Books Till You Return Any Other Books";
    }
    
    //Save Data
    users[indexOfUser] = currentUser;
    books[indexToBorrow] = bookToBorrow;
    writeUsers("data/users.csv", users);
    writeBooks("data/books.csv", books);
}
void returnBook(vector<Book> &books, vector<User> &users, const string &username)
{
    int indexOfUser;
    int indexOfBook;
    Book bookToReturn;
    User currentUser;
    int userInput;

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].studentName == username)
        {
            currentUser = users[i];
            indexOfUser = i;
        }
    }

    if (currentUser.book1Id == 0 && currentUser.book2Id == 0 && currentUser.book3Id == 0 &&
        currentUser.book4Id == 0 && currentUser.book5Id == 0)
    {
        cout << "You Haven't Borrowed Any Books Yet.\n";
        return;
    }
    

    cout << "Which Book Do You Want To Return -->\n";
    //prints the name of all the books borrwoed
    for (int i = 0; i < 5; i++)
    {
        cout << "[" << i+1 << "] ";
        switch (i)
        {
            case 0:
                if (currentUser.book1Id != 0)
                {
                    string bookname;
                    for (size_t i = 0; i < books.size(); i++)
                    {
                        if (books[i].bookId == currentUser.book1Id)
                        {
                            bookname = books[i].title;
                        }
                    }
                    cout << bookname;
                }
                else
                {
                    cout << "None";
                }
                cout << '\n';
                break;
            case 1:
                if (currentUser.book2Id != 0)
                {
                    string bookname;
                    for (size_t i = 0; i < books.size(); i++)
                    {
                        if (books[i].bookId == currentUser.book2Id)
                        {
                            bookname = books[i].title;
                        }
                    }
                    cout << bookname;
                }
                else
                {
                    cout << "None";
                }
                cout << '\n';
                break;
            case 2:
                if (currentUser.book3Id != 0)
                {
                    string bookname;
                    for (size_t i = 0; i < books.size(); i++)
                    {
                        if (books[i].bookId == currentUser.book3Id)
                        {
                            bookname = books[i].title;
                        }
                    }
                    cout << bookname;
                }
                else
                {
                    cout << "None";
                }
                cout << '\n';
                break;
            case 3:
                if (currentUser.book4Id != 0)
                {
                    string bookname;
                    for (size_t i = 0; i < books.size(); i++)
                    {
                        if (books[i].bookId == currentUser.book4Id)
                        {
                            bookname = books[i].title;
                        }
                    }
                    cout << bookname;
                }
                else
                {
                    cout << "None";
                }
                cout << '\n';
                break;
            case 4:
                if (currentUser.book5Id != 0)
                {
                    string bookname;
                    for (size_t i = 0; i < books.size(); i++)
                    {
                        if (books[i].bookId == currentUser.book5Id)
                        {
                            bookname = books[i].title;
                        }
                    }
                    cout << bookname;
                }
                else
                {
                    cout << "None";
                }
                cout << '\n';
                break;
            default:
                break;
        }
        
    }
    cout << ">> ";
    cin >> userInput;
    //gets the book from books database
    switch (userInput)
    {
    case 1:
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].bookId == currentUser.book1Id)
            {
                bookToReturn = books[i];
                indexOfBook = i;
            }
        }
        currentUser.book1Id = 0;
        bookToReturn.units++;
        break;
    case 2:
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].bookId == currentUser.book2Id)
            {
                bookToReturn = books[i];
                indexOfBook = i;
            }
        }
        currentUser.book2Id = 0;
        bookToReturn.units++;
        break;
    case 3:
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].bookId == currentUser.book3Id)
            {
                bookToReturn = books[i];
                indexOfBook = i;
            }
        }
        currentUser.book3Id = 0;
        bookToReturn.units++;
        break;
    case 4:
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].bookId == currentUser.book4Id)
            {
                bookToReturn = books[i];
                indexOfBook = i;
            }
        }
        currentUser.book4Id = 0;
        bookToReturn.units++;
        break;
    case 5:
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].bookId == currentUser.book5Id)
            {
                bookToReturn = books[i];
                indexOfBook = i;
            }
        }
        currentUser.book5Id = 0;
        bookToReturn.units++;
        break;
    default:
        break;
    }
    



    //Save Data
    users[indexOfUser] = currentUser;
    books[indexOfBook] = bookToReturn;
    writeUsers("data/users.csv", users);
    writeBooks("data/books.csv", books);
}

//common functions
void viewAllBooks(vector<Book> &books)
{
    for (size_t i = 0; i < books.size(); i++)
    {
        cout << "ID - " << books[i].bookId << '\n';
        cout << "Title - " << books[i].title << '\n';
        cout << "Author - " << books[i].author << '\n';
        cout << "Genres - ";
        for (auto genre:books[i].genres)
        {
            cout << genre << ';';
        }
        cout << '\n';
        cout << "Units - " << books[i].units << '\n';
        cout << "Published In - " << books[i].year << '\n';
        cout << "******************************************\n";
    }
    
}