#ifndef BOOK_HPP
#define BOOK_HPP
#include <string>

class Book{
public:
    int BookNumber;
    std::string BookName;
    Book (int a, std::string b){BookNumber = a; BookName = b;}
};

#endif // BOOK_HPP
