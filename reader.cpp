#include "reader.hpp"
std::ostream& operator<<(std::ostream & stream, const Reader & obj){
 stream << obj.LibraryCardNmb << ';' << obj.FirstName << ';' << obj.LastName << \
 ';' << obj.book_counts << '\n';
 return stream;
}

//reader::reader()
//{

//}
