#include "../include/book.h"
#include <sstream>
#include <fstream>

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

vector<Book> loadBooks(const string &filename)
{
    vector<Book> books;
    ifstream file(filename);
    if(!file.is_open())
    {
        cout << "FATAL ERROR : Could Not Open Books.csv";
        return books;
    }

    string line;
    getline(file, line); // discard header line

    while (getline(file, line))
    {
        if (line.empty()) continue;

        vector<string> tokens = split(line, ',');
        if(tokens.size() < 6) continue;

        Book book;
        book.title = tokens[0];
        book.author = tokens[1];

        try {
            book.year = stoi(tokens[2]);   // safely parse
            book.units = stoi(tokens[3]);
        } catch (const exception &e) {
            cerr << "Error parsing row: " << line << endl;
            cerr << "Exception: " << e.what() << endl;
            continue;
        }

        book.genres = split(tokens[4], ';');
        book.borrowHistory = split(tokens[5], ';');

        books.push_back(book);
    }

    return books;
}

void writeBooks(const string &filename, const vector<Book> &books)
{
    ofstream file(filename);
    if(!file.is_open())
    {
        cout << "FATAL ERROR : Could Not Open Books.csv For Writing";
        return;
    }

    file << "Title,Author,Year,Units,Genres,BorrowHistory\n";

    for (const auto &book : books)
    {
        string borrowHis;
        string gen;

        for (int i = 0; i < book.genres.size(); i++)
        {
            gen+= book.genres[i];
            if(i != book.genres.size()-1) gen+=";";        
        }
        for (int i = 0; i < book.borrowHistory.size(); i++)
        {
            borrowHis+= book.borrowHistory[i];
            if(i != book.borrowHistory.size()-1) borrowHis+=";";        
        }

        file << book.title << ","
            << book.author << ","
            << book.year << ","
            << book.units << ","
            << gen << ","
            << borrowHis << '\n';
        }
    file.close();
}
