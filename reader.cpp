#include "reader.hpp"
//std::ostream& operator<<(std::ostream & stream, const Reader & obj){
// stream << obj.LibraryCardNmb << ';' << obj.FirstName << ';' << obj.LastName << \
// ';' << obj.book_counts << '\n';
// return stream;
//}

std::ostream& operator<<(std::ostream & stream, const Reader & obj){
 stream << "\t" << obj.LibraryCardNmb << "\t|\t" << obj.FirstName << "\t|\t"<< obj.LastName << "\t|\t"
 << obj.book_counts << "\n";
 return stream;
}
