#ifndef READER_HPP
#define READER_HPP
//#include <string>
#include <iostream>
#include <fstream>
class Reader{
public:
    int LibraryCardNmb;
    char FirstName[16];
    char LastName[16];
    char Passport[16];
    int book_counts;
    int book_IDs[4];
};

#endif // READER_HPP
