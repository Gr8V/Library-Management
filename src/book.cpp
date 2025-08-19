#include <book.h>
#include <sstream>

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