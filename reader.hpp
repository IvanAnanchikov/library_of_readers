#ifndef READER_HPP
#define READER_HPP
#include <string>
#include <iostream>
#include <fstream>
class Reader{
public:
    int LibraryCardNmb;
//    std::string LastName;
//    std::string FirstName;
    char FirstName[16];
    char LastName[16];
    char Passport[16];
    int book_counts;
    //Reader (int a, std::string b, std::string c){LibraryCardNmb = a; LastName = b; FirstName = c;}
    //Reader(){std::cout << "plain constructor of reader" << std::endl;}
   // friend std::ostream& operator<<(std::ostream &, const Reader &);
};

#endif // READER_HPP
