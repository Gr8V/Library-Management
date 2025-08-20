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
    cout << "Discarded header: " << line << endl;

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
