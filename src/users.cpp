#include "../include/users.h"
#include "../include/book.h"
#include <sstream>
#include <fstream>


int safeStoi(const string &s, int defaultVal)
{
    if (s.empty()) return defaultVal;
    try {
        return stoi(s);
    } catch (...) {
        return defaultVal; // fallback if s is not a number
    }
}


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
        
        user.book1Id = safeStoi(tokens[2]);
        user.book2Id = safeStoi(tokens[3]);
        user.book3Id = safeStoi(tokens[4]);
        user.book4Id = safeStoi(tokens[5]);
        user.book5Id = safeStoi(tokens[6]);
        
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

    file << "studentId,studentName,book1Id,book2Id,book3Id,book4Id,book5Id\n";

    for (const auto &user : users)
    {

        file << user.studentId << ","
            << user.studentName << ","
            << user.book1Id << ","
            << user.book2Id << ","
            << user.book3Id << ","
            << user.book4Id << ","
            << user.book5Id << '\n';
        }
    file.close();
}

void addTransaction(const string &fileName, int userID, int bookID, string action){
    //format
    //userID, bookID, action, timestamp
    //1,15, BORROW, 2025-09-06 14:32
}