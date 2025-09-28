#include "../include/library.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;


void actions(const bool isAdmin, vector<Book> &books, vector<User> &users, const string &username)
{
    int userId = 0;
    for (int i = 0; i < users.size(); i++)
        {
            if (users[i].userName == username)
            {
                userId = users[i].userId;
            }
        }

    cout << "*********************************\n";
    cout << "*************Actions*************\n";
    cout << "*********************************\n";
    if (isAdmin)
    {
        adminActions(books, users, username, userId);
    }
    else if (!isAdmin)
    {
        userActions(books, users, username, userId);
    }
}
void adminActions(vector<Book> &books, vector<User> &users, const string &username, const int &userId)
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
    cout << "[9] Show Logs\n";
    cout << "[10] Logout\n";
    cout << "[11] Quit\n";
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
        showLogs();
        break;
    case 10:
        // login log (successful admin logout)
        loginLog("data/login_logs.csv",userId,username,"LOGOUT",true, "Successful Admin Logout");
        cout << "\n<<<<<LOGGING OUT>>>>>\n";
        start();
        break;
    case 11:
        // login log (successful admin logout)
        loginLog("data/login_logs.csv",userId,username,"LOGOUT",true, "Successful Admin Logout");
        cout << "\n<<<<<EXITING PROGRAM>>>>>\n";
        std::exit(0); 
        break;
    default:
        cout << "Input Error: Enter a digit between 1-8.";
        break;
    }
}
void userActions(vector<Book> &books, vector<User> &users, const string &username, const int &userId)
{
    int userInput = 0;

    cout << "[1] Borrow Book\n";
    cout << "[2] Return Book\n";
    cout << "[3] View All Book\n";
    cout << "[4] Search/Filter Books\n";
    cout << "[5] Logout\n";
    cout << "[6] Quit\n";
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
        // login log (successful user logout)
        loginLog("data/login_logs.csv",userId,username,"LOGOUT",true, "Successful User Logout");
        cout << "\n<<<<<LOGGING OUT>>>>>\n";
        start();
        break;
    case 6:
        // login log (successful user logout)
        loginLog("data/login_logs.csv",userId,username,"LOGOUT",true, "Successful User Logout");
        cout << "\n<<<<<EXITING PROGRAM>>>>>\n";
        std::exit(0); 
        break;
    default:
        cout << "Input Error: Enter a digit between 1-3.";
        break;
    }
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
        vector<int> borrowedBookIDs;
        for (size_t i = 0; i < users.size(); i++)
        {
            if (users[i].userName == username)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (j < users[i].BorrowedBooks.size() && users[i].BorrowedBooks[j].bookId != 0)
                    {
                        borrowedBookIDs.push_back(users[i].BorrowedBooks[j].bookId);
                    }
                    
                }
                
            }
        }
        

        for (int i = 0; i < books.size(); i++)
        {
            for (int id : borrowedBookIDs)
            {
                if (books[i].bookId == id)
                {
                    booksSearched.push_back(books[i]);
                    break;
                }
                
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
    string tempUserPasswd = sha256("Library@123");
    //Get New User
    string newUserName;
    cout << "Enter Name Of New User: ";
    cin >> newUserName;

    //check if user already exists
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].userName == newUserName)
        {
            cout << "ERROR : User Already Exists.";
            return;
        }
        
    }

    User newUser;
    newUser.userId = (users[users.size()-1].userId)+1;
    newUser.userName = newUserName;
    newUser.hashedPasswd = tempUserPasswd;
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
        if (users[i].userId == userIdToRemove)
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
        cout << users[i].userName<< ", ID=" << users[i].userId << '\n';
    }
    cout << "*************************";
}
void showOverdueUsers(vector<User> &users)
{
    //gets current date
    string currentDate;
    time_t now = time(nullptr);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&now));
    currentDate = string(buffer);

    //displays overdue users
    for (size_t i = 0; i < users.size(); i++)
    {
        for (size_t j = 0; j < users[i].BorrowedBooks.size(); j++)
        {
            if (users[i].BorrowedBooks[j].dueDate < currentDate)
            {
                cout << "UserName : " << users[i].userName << '\n';
                cout << "OverDue Book ID : " << users[i].BorrowedBooks[j].bookId
                    << "\n\n";
            }
            
        }
        
        
    }
    
}
void showLogs()
{
    int whatToDo;
    cout << "\nWhich Logs Do You Want To see --> \n";
    cout << "[1] Transactions Logs\n";
    cout << "[2] Loging Logs\n";
    cin >> whatToDo;
    if (whatToDo == 1)
    {
        ifstream file("data/transactions.csv");
        if(!file.is_open())
        {
            cout << "FATAL ERROR : Could Not Open transactions.csv";
            return;
        }
        string line;
        while (getline(file, line))
        {
            if(line.empty()) continue;
            cout << line << '\n';
        }
        
    }
    else if(whatToDo == 2)
    {
        ifstream file("data/login_logs.csv");
        if(!file.is_open())
        {
            cout << "FATAL ERROR : Could Not Open login_logs.csv";
            return;
        }
        string line;
        while (getline(file, line))
        {
            if(line.empty()) continue;
            cout << line << '\n';
        }
    }
    else
    {
        cout << "Input Out Of Range";
    }
}

//user functions
void borrowBook(vector<Book> &books, vector<User> &users, const string &username)
{
    const int DAYS_CAN_BORROW_FOR = 15;

    int borrowBookId;
    int indexToBorrow;
    int indexOfUser;
    Book bookToBorrow;
    User currentUser;
    //get user
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].userName == username)
        {
            currentUser = users[i];
            indexOfUser = i;
        }
    }

    //check if user can borrow(hasn't already borrowed 5 books)
    if (currentUser.BorrowedBooks.size() >= 5)
    {
        cout << "You have already borrowed " << currentUser.BorrowedBooks.size()
            << " Books. You Cannot Borrow More.";
        return;
    }
    

    //user input for bookId
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
    //checks if book is out of stock
    if (bookToBorrow.units == 0)
    {
        cout << "The Book Is Out Of Stock\n\n";
        return;
    }

    //Gets current date and due date
    string currentDate;
    time_t now = time(nullptr);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&now));
    currentDate = string(buffer);
    
    string dueDate;
    now += DAYS_CAN_BORROW_FOR * 24 * 60 * 60;
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&now));
    dueDate = string(buffer);

    //borrow book
    BorrwedBookData currentBorrowingBookData;
    currentBorrowingBookData.bookId = borrowBookId;
    currentBorrowingBookData.borrowDate = currentDate;
    currentBorrowingBookData.dueDate = dueDate;
    currentUser.BorrowedBooks.push_back(currentBorrowingBookData);

    bookToBorrow.units--;
    
    //Save Data
    users[indexOfUser] = currentUser;
    books[indexToBorrow] = bookToBorrow;
    writeUsers("data/users.csv", users);
    writeBooks("data/books.csv", books);

    addTransaction("data/transactions.csv", currentUser.userId, bookToBorrow.bookId, "BORROW");
}
void returnBook(vector<Book> &books, vector<User> &users, const string &username)
{
    int indexOfUser;
    int indexOfBook;
    Book bookToReturn;
    User currentUser;
    int indexOfBorrowed;

    //gets user
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].userName == username)
        {
            currentUser = users[i];
            indexOfUser = i;
        }
    }

    //checks if user hasn't borrowed any books yet
    if (currentUser.BorrowedBooks.size() == 0)
    {
        cout << "You Haven't Borrowed Any Books Yet.\n";
        return;
    }
    

    cout << "Which Book Do You Want To Return -->\n";
    //prints the name of all the books borrowed
    for (size_t i = 0; i < currentUser.BorrowedBooks.size(); i++)
    {
        cout << "[" << i+1 << "] ";
        string bookname;
        for (size_t j = 0; j < books.size(); j++)
        {
            if (books[j].bookId == currentUser.BorrowedBooks[i].bookId)
            {
                bookname = books[j].title;
            }
        }
        cout << bookname << '\n';
    }
    
    //gets user input
    cout << ">> ";
    cin >> indexOfBorrowed;
    indexOfBorrowed--;

    //calulates fine(if any)
    int fine = fineCalculator(currentUser.BorrowedBooks[indexOfBorrowed].dueDate);
    if (fine != 0)
    {
        cout << "You are over the due date!!!!\n";
        cout << "Submit the fine amout of Rs." << fine << '\n';
    }
    
    

    //gets the book from books database
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].bookId == currentUser.BorrowedBooks[indexOfBorrowed].bookId)
        {
            bookToReturn = books[i];
            indexOfBook = i;
        }
        
    }
    currentUser.BorrowedBooks.erase(currentUser.BorrowedBooks.begin()+indexOfBorrowed);
    bookToReturn.units++;
    



    //Save Data
    users[indexOfUser] = currentUser;
    books[indexOfBook] = bookToReturn;
    writeUsers("data/users.csv", users);
    writeBooks("data/books.csv", books);

    addTransaction("data/transactions.csv", currentUser.userId, bookToReturn.bookId, "RETURN");
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