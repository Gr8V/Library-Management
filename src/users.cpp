#include "../include/users.h"
#include <sstream>
#include <ctime>
#include <fstream>


vector<User> loadUsers(const string &filename)
{
    vector<User> users;
    ifstream file(filename);
    if(!file.is_open())
    {
        cout << "FATAL ERROR : Could Not Open Books.csv";
        return users;
    }

    string line;
    getline(file >> ws, line); // discard header line
    while (getline(file >> ws, line))
    {
        if (line.empty()) continue;
        
        vector<string> tokens = split(line, ',');
        if(tokens.size() < 7) continue;

        
        User user;
        user.studentId = safeStoi(tokens[0]);
        user.studentName = tokens[1];
        
        for (int i = 1; i <= 5; i++)
        {
            vector<string> temp = split(tokens[i+1], ';');
            BorrwedBookData borrowedBook;
            borrowedBook.bookId = safeStoi(temp.at(0));
            borrowedBook.borrowDate = temp.at(1);
            borrowedBook.dueDate = temp.at(2);
            if (borrowedBook.bookId != 0)
            {
                user.BorrowedBooks.push_back(borrowedBook);
            }
            
        }
        users.push_back(user);
    }

    return users;
}

void writeUsers(const string &filename, const vector<User> &users)
{
    ofstream file(filename);
    if(!file.is_open())
    {
        cout << "FATAL ERROR : Could Not Open Books.csv For Writing";
        return;
    }

    file << "studentId,studentName,book1,book2,book3Id,book4,book5\n";

    for (const auto &user : users)
    {
        file << user.studentId << "," << user.studentName;
        for (int i = 0; i < 5; i++)
        {
            file << ",";
            if (i < user.BorrowedBooks.size())
            {
                const auto &b = user.BorrowedBooks[i];
                file << b.bookId << ";" << b.borrowDate << ";" << b.dueDate;
            }
            else
            {
                file << "0;0;0";
            }
            
            
        }
        file << "\n";
    }
    file.close();
}