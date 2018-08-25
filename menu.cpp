#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
//#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdio>        //для функции remove
#include "menu.hpp"
#include "book.hpp"
#include "reader.hpp"
using namespace std;

void remove_reader_bin(){
    remove("reader.bin");
//    if( remove( "reader.bin" ) != 0 )
//        cout << "Error deleting file reader.bin" << endl;
//    else
//        cout << "File reader.bin successfully deleted" << endl;
}
void remove_book_bin(){
    remove("book.bin");
//    if( remove( "book.bin" ) != 0 )
//        cout << "Error deleting file book.bin" << endl;
//    else
//        cout << "File book.bin successfully deleted" << endl;
}

void menu_title(){
        cout<<"* * * * * * * * * * * * * * * * * * * * *\n";
        cout<<"* * *   CONSOLE_LIBRARY_OF_READERS  * * *\n";
        cout<<"* * * * * * * * * * * * * * * * * * * * *\n";
}
void menu_1(){//TAKE A BOOK
    char ch_key;
    int ReaderNumber;
    int BookNumber;
    Reader ReaderObject;
    vector<Reader> vec;
    Book BookObject;
    vector<Book> vec_b;
    unsigned int coincidence = 0;
    bool Menu = true;
    while(Menu){
        menu_title();
        cout<<"This is \"TAKE A BOOK\" menu\n";
        cout<<" "<<endl;
        cout<<"> type Reader's number of Library Card\n";
        cin>>ReaderNumber;      
        cout<<"> type Book's Library Number\n";
        cin>>BookNumber;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //прочитать инфу про читателя, добавить книгу, редактировать файл reader
        //--------------- считываем из файла reader.bin --------------------------------
            fstream file_r("reader.bin",ios::binary|ios::in);
            if (!file_r.is_open()) {
             cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
            }
            else{
                    vec.clear();
                    file_r.seekp(0,ios::beg);
                    while (!file_r.read((char*)&ReaderObject, sizeof(Reader)).eof())
                    {
                      if(ReaderObject.LibraryCardNmb == ReaderNumber) {
                         //проверим можно ли выдать читателю книги или у него уже взят максимум в 4 книги                          
                           if(ReaderObject.book_counts == MAX_BOOK_CNT){
                            cout << "Sorry, but You already have maximum of books." << endl;
                            //unsigned int cnt = MAX_BOOK_CNT;
                            cout << "For our library it is: " << MAX_BOOK_CNT << " books." << endl;
                            cout << "You should give back the books You have first. Thank you!" << endl;
                           }
                           else{//добавляем новую книгу и увеличиваем количество книг
                              coincidence++;
                              ReaderObject.book_IDs[ReaderObject.book_counts] = BookNumber;
                              ReaderObject.book_counts++;
                              cout << endl << "Book is taken OK\n" << endl;
                           }
                      }
                      vec.push_back(ReaderObject);
                    }
                    if(coincidence == 0){cout << "Sorry, there is no reader with such Number of Library Card" << endl;}
                    file_r.clear();
                    file_r.close();
            }


            if(coincidence > 0)
            {
             //-----------------------------------------------------------------------------
             remove_reader_bin();
             //--------------- записываем в файл reader.bin обновленную информацию ----------
                    ofstream file_w("reader.bin",ios::binary|ios::out|ios::app);
                    if (!file_w.is_open()) {
                     cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
                    }
                    else{
                          for(vector<Reader>::iterator it = vec.begin(); it != vec.end(); it++)
                          {
                            file_w.write(reinterpret_cast<char*>(&it->LibraryCardNmb), sizeof(it->LibraryCardNmb));
                            file_w.write(reinterpret_cast<char*>(&it->FirstName), sizeof(it->FirstName));
                            file_w.write(reinterpret_cast<char*>(&it->LastName), sizeof(it->LastName));
                            file_w.write(reinterpret_cast<char*>(&it->Passport), sizeof(it->Passport));
                            file_w.write(reinterpret_cast<char*>(&it->book_counts), sizeof(it->book_counts));
                            file_w.write(reinterpret_cast<char*>(&it->book_IDs), sizeof(it->book_IDs));
                          }
                          file_w.clear();
                          file_w.close();
                    }
           //----------------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //редактировать файл book, уменьшить количество книг
          //--------------- считываем из файла book.bin --------------------------------

                        fstream file_rb("book.bin",ios::binary|ios::in);
                        if (!file_rb.is_open()) {
                         cout << "The file \"book.bin\" cannot be opened or created..." << endl;
                        }
                        else{
                                vec_b.clear();
                                file_rb.seekp(0,ios::beg);
                                while (!file_rb.read((char*)&BookObject, sizeof(Book)).eof())
                                {
                                  if(BookObject.BookUniqueNumber == BookNumber){
                                     if(BookObject.Count>0){BookObject.Count--;
                                          cout << "Book with UniqueNumber " << BookNumber << \
                                                  " successfully moved to reader with LibraryCardNumber " << ReaderNumber << endl;
                                     }
                                     else{cout << "Database management error!" << endl;
                                          cout << "Unfortunately there is no available book in the database." << endl;
                                          cout << "All books with UniqueNumber " << BookObject.BookUniqueNumber << " are in reader's hands" << endl;
                                     }
                                  }
                                  vec_b.push_back(BookObject);
                                }
                                file_rb.clear();
                                file_rb.close();
                         }
                 //-----------------------------------------------------------------------------
                 remove_book_bin();
                 //--------------- записываем в файл book.bin измененную информацию ------------
                            ofstream file_wb("book.bin",ios::binary|ios::out|ios::app);
                            if (!file_wb.is_open()) {
                             cout << "The file \"book.bin\" cannot be opened or created..." << endl;
                            }
                            else{
                                  for(vector<Book>::iterator it = vec_b.begin(); it != vec_b.end(); it++)
                                  {
                                    file_wb.write(reinterpret_cast<char*>(&it->BookUniqueNumber), sizeof(it->BookUniqueNumber));
                                    file_wb.write(reinterpret_cast<char*>(&it->BookName), sizeof(it->BookName));
                                    file_wb.write(reinterpret_cast<char*>(&it->Author), sizeof(it->Author));
                                    file_wb.write(reinterpret_cast<char*>(&it->CodeISBN), sizeof(it->CodeISBN));
                                    file_wb.write(reinterpret_cast<char*>(&it->Pages), sizeof(it->Pages));
                                    file_wb.write(reinterpret_cast<char*>(&it->Year), sizeof(it->Year));
                                    file_wb.write(reinterpret_cast<char*>(&it->Publisher), sizeof(it->Publisher));
                                    file_wb.write(reinterpret_cast<char*>(&it->Count), sizeof(it->Count));
                                  }
                                  file_wb.clear();
                                  file_wb.close();
                            }
            }
           //----------------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        cout<<"> type ESC to go back to previous menu\n"<<" "<<endl;
        switch((ch_key = _getch()))
        {
        case ESC:
            Menu = false;
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
}
void menu_2(){//GIVE A BOOK BACK
    char ch_key;
    int ReaderNumber;
    int BookNumber;
    Reader ReaderObject;
    vector<Reader> vec;
    Book BookObject;
    vector<Book> vec_b;
    unsigned int coincidence = 0;
    bool Menu = true;
    while(Menu){
        menu_title();
        cout<<"This is \"GIVE A BOOK BACK\" menu\n";
        cout<<" "<<endl;
        cout<<"> type Reader's number of Library Card\n";
        cin>>ReaderNumber;
        cout<<"> type Book's Library Number\n";
        cin>>BookNumber;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //прочитать инфу про читателя, добавить книгу, редактировать файл reader
        //--------------- считываем из файла reader.bin --------------------------------
            fstream file_r("reader.bin",ios::binary|ios::in);
            if (!file_r.is_open()) {
             cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
            }
            else{
                    vec.clear();
                    file_r.seekp(0,ios::beg);
                    while (!file_r.read((char*)&ReaderObject, sizeof(Reader)).eof())
                    {
                      //проверим есть ли в базе наш читатель, который хочет вернуть книгу
                      if(ReaderObject.LibraryCardNmb == ReaderNumber) {
                            coincidence = 1;
                            //найдем место в массиве номеров книг у читателя, где находится та книга которую он сдает
                            int Given = 0;
                            for(int i = 0; i < ReaderObject.book_counts; i++){
                                if (ReaderObject.book_IDs[i] == BookNumber){ReaderObject.book_IDs[i] = 0; Given = i; break;}
                            }
                            cout << "Given+1= " << Given+1 << endl;
                            cout << "book_counts= " << ReaderObject.book_counts << endl;
                            //уберем пропуск в массиве от сданной книги
                            if((Given + 1) == ReaderObject.book_counts){//сданная была по порядку последняя в массиве (пропуска нет)
                                ReaderObject.book_counts--;
                            }
                            else{//сданная была не последняя в массиве (пропуск есть)
                                for(int i = Given+1; i < ReaderObject.book_counts; i++){
                                   ReaderObject.book_IDs[i-1] = ReaderObject.book_IDs[i];
                                   ReaderObject.book_IDs[i] = 0;
                                }
                                ReaderObject.book_counts--;
                            }
                            cout << endl << "Book is given back OK\n" << endl;
                      }
                      vec.push_back(ReaderObject);
                    }
                    file_r.clear();
                    file_r.close();
            }
            //-----------------------------------------------------------------------------
            remove_reader_bin();
            //--------------- записываем в файл reader.bin обновленную информацию ----------
                    ofstream file_w("reader.bin",ios::binary|ios::out|ios::app);
                    if (!file_w.is_open()) {
                     cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
                    }
                    else{
                          for(vector<Reader>::iterator it = vec.begin(); it != vec.end(); it++)
                          {
                            file_w.write(reinterpret_cast<char*>(&it->LibraryCardNmb), sizeof(it->LibraryCardNmb));
                            file_w.write(reinterpret_cast<char*>(&it->FirstName), sizeof(it->FirstName));
                            file_w.write(reinterpret_cast<char*>(&it->LastName), sizeof(it->LastName));
                            file_w.write(reinterpret_cast<char*>(&it->Passport), sizeof(it->Passport));
                            file_w.write(reinterpret_cast<char*>(&it->book_counts), sizeof(it->book_counts));
                            file_w.write(reinterpret_cast<char*>(&it->book_IDs), sizeof(it->book_IDs));
                          }
                          file_w.clear();
                          file_w.close();
                    }
           //----------------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //редактировать файл book, вернуть книгу в базу
          //--------------- считываем из файла book.bin --------------------------------
             if(coincidence == 1)
             {
                        fstream file_rb("book.bin",ios::binary|ios::in);
                        if (!file_rb.is_open()) {
                         cout << "The file \"book.bin\" cannot be opened or created..." << endl;
                        }
                        else{
                                vec_b.clear();
                                file_rb.seekp(0,ios::beg);
                                while (!file_rb.read((char*)&BookObject, sizeof(Book)).eof())
                                {
                                  if(BookObject.BookUniqueNumber == BookNumber){
                                     BookObject.Count++;
                                          cout << "Book with UniqueNumber " << BookNumber << \
                                                  " successfully moved from reader with LibraryCardNumber " << ReaderNumber << \
                                                  " to library shelves" << endl;
                                  }
                                  vec_b.push_back(BookObject);
                                }
                                file_rb.clear();
                                file_rb.close();
                            }
                 //-----------------------------------------------------------------------------
                 remove_book_bin();
                 //--------------- записываем в файл book.bin измененную информацию ------------
                            ofstream file_wb("book.bin",ios::binary|ios::out|ios::app);
                            if (!file_wb.is_open()) {
                             cout << "The file \"book.bin\" cannot be opened or created..." << endl;
                            }
                            else{
                                  for(vector<Book>::iterator it = vec_b.begin(); it != vec_b.end(); it++)
                                  {
                                    file_wb.write(reinterpret_cast<char*>(&it->BookUniqueNumber), sizeof(it->BookUniqueNumber));
                                    file_wb.write(reinterpret_cast<char*>(&it->BookName), sizeof(it->BookName));
                                    file_wb.write(reinterpret_cast<char*>(&it->Author), sizeof(it->Author));
                                    file_wb.write(reinterpret_cast<char*>(&it->CodeISBN), sizeof(it->CodeISBN));
                                    file_wb.write(reinterpret_cast<char*>(&it->Pages), sizeof(it->Pages));
                                    file_wb.write(reinterpret_cast<char*>(&it->Year), sizeof(it->Year));
                                    file_wb.write(reinterpret_cast<char*>(&it->Publisher), sizeof(it->Publisher));
                                    file_wb.write(reinterpret_cast<char*>(&it->Count), sizeof(it->Count));
                                  }
                                  file_wb.clear();
                                  file_wb.close();
                            }
            }
           //----------------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        cout<<"> type ESC to go back to previous menu\n"<<" "<<endl;
        switch((ch_key = _getch()))
        {
        case ESC:
            Menu = false;
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
}
void menu_3(){//ADD BOOK
    char ch_key;
    Book BookObject;
    bool Menu = true;
    while(Menu){
        menu_title();
        cout<<"This is \"ADD BOOK\" menu\n";
        cout<<" "<<endl;
        cout<<"> type book's Unique number \n";
        cin>>BookObject.BookUniqueNumber;
        cout<<"> type book's Name\n";
        cin>>BookObject.BookName;
        cout<<"> type book's Author\n";
        cin>>BookObject.Author;
        cout<<"> type book's CodeISBN\n";
        cin>>BookObject.CodeISBN;
        cout<<"> type number of book Pages \n";
        cin>>BookObject.Pages;
        cout<<"> type book's Year of publish\n";
        cin>>BookObject.Year;
        cout<<"> type book's Publisher\n";
        cin>>BookObject.Publisher;
        cout<<"> type count of book\n";
        cin>>BookObject.Count;
//--------------- записываем в файл Book --------------------------------
    ofstream file_w("book.bin",ios::binary|ios::out|ios::app);
    if (!file_w.is_open()) {
     cout << "The file \"book.bin\" cannot be opened or created..." << endl;
    }
    else{
        file_w.write(reinterpret_cast<char*>(&BookObject.BookUniqueNumber),sizeof BookObject.BookUniqueNumber);
        file_w.write(reinterpret_cast<char*>(&BookObject.BookName),sizeof BookObject.BookName);
        file_w.write(reinterpret_cast<char*>(&BookObject.Author),sizeof BookObject.Author);
        file_w.write(reinterpret_cast<char*>(&BookObject.CodeISBN),sizeof BookObject.CodeISBN);
        file_w.write(reinterpret_cast<char*>(&BookObject.Pages),sizeof BookObject.Pages);
        file_w.write(reinterpret_cast<char*>(&BookObject.Year),sizeof BookObject.Year);
        file_w.write(reinterpret_cast<char*>(&BookObject.Publisher),sizeof BookObject.Publisher);
        file_w.write(reinterpret_cast<char*>(&BookObject.Count),sizeof BookObject.Count);
        file_w.clear();
        file_w.close();
    }
//----------------------------------------------------------------------
    cout<<"> type ESC to go back to previous menu\n"<<" "<<endl;
        switch((ch_key = _getch()))
        {
        case ESC:
            Menu = false;
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
}

void menu_4(){//DELETE BOOK
    char ch_key;
    int IDForDeleting;
    Book BookObject;
    vector<Book> vec;
    bool Menu = true;
    while(Menu){
        menu_title();
        cout << "This is \"DELETE BOOK\" menu\n" << endl;
        cout << "Print the \"UniqueNumber\" of a book you want to delete\n" << endl;
        cin >> IDForDeleting;
//--------------- считываем из файла book.bin --------------------------------
    fstream file_r("book.bin",ios::binary|ios::in);
    if (!file_r.is_open()) {
     cout << "The file \"book.bin\" cannot be opened or created..." << endl;
    }
    else{
            unsigned int cnt = 0;
            vec.clear();//очистить вектор
            file_r.seekp(0,ios::beg);//перемещаем указатель позиционирования файла в начало
            cout << "vec.size after cleaning" << vec.size() << endl;
            while (!file_r.read((char*)&BookObject, sizeof(Book)).eof())
            {
              if(BookObject.BookUniqueNumber == IDForDeleting) {
                 cout << "Book for deleting was found\n";
              }
              else{vec.push_back(BookObject);
                   cnt++;
              }
            }
            cout << "vec.size after pushing" << vec.size() << endl;
            cout << "cnt: " << cnt << endl;
            file_r.clear();
            file_r.close();
        }
//-----------------------------------------------------------------------------
remove_book_bin();
//--------------- записываем в файл book.bin все книги кроме удаленной ----------
        ofstream file_w("book.bin",ios::binary|ios::out|ios::app);
        if (!file_w.is_open()) {
         cout << "The file \"book.bin\" cannot be opened or created..." << endl;
        }
        else{
              for(vector<Book>::iterator it = vec.begin(); it != vec.end(); it++)
              {
                file_w.write(reinterpret_cast<char*>(&it->BookUniqueNumber), sizeof(it->BookUniqueNumber));
                file_w.write(reinterpret_cast<char*>(&it->BookName), sizeof(it->BookName));
                file_w.write(reinterpret_cast<char*>(&it->Author), sizeof(it->Author));
                file_w.write(reinterpret_cast<char*>(&it->CodeISBN), sizeof(it->CodeISBN));
                file_w.write(reinterpret_cast<char*>(&it->Pages), sizeof(it->Pages));
                file_w.write(reinterpret_cast<char*>(&it->Year), sizeof(it->Year));
                file_w.write(reinterpret_cast<char*>(&it->Publisher), sizeof(it->Publisher));
                file_w.write(reinterpret_cast<char*>(&it->Count), sizeof(it->Count));
              }
              file_w.clear();
              file_w.close();
        }
//----------------------------------------------------------------------

    cout << "> type ESC to go back to previous menu\n" << " " << endl;
        switch((ch_key = _getch()))
        {
        case ESC:
            Menu = false;
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
}
void menu_5(){//ADD READER
    char ch_key;
    Reader ReaderObject;
    bool Menu = true;
    while(Menu){
        menu_title();
        cout<<"This is \"ADD READER\" menu\n";
        cout<<" "<<endl;
        cout<<"> type reader's First Name\n";
        cin>>ReaderObject.FirstName;
        cout<<"> type reader's Last Name\n";
        cin>>ReaderObject.LastName;
        cout<<"> type reader's Passport data\n";
        cin>>ReaderObject.Passport;
        cout<<"> type reader's Library Card Number\n";
        cin>>ReaderObject.LibraryCardNmb;
        ReaderObject.book_counts = 0;
        for(int i = 0; i < MAX_BOOK_CNT; i++){ReaderObject.book_IDs[i] = 0;}
//--------------- записываем в файл Reader --------------------------------
    ofstream file_w("reader.bin",ios::binary|ios::out|ios::app);
    if (!file_w.is_open()) {
     cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
    }
    else{
        file_w.write(reinterpret_cast<char*>(&ReaderObject.LibraryCardNmb),sizeof ReaderObject.LibraryCardNmb);
        file_w.write(reinterpret_cast<char*>(&ReaderObject.FirstName),sizeof ReaderObject.FirstName);
        file_w.write(reinterpret_cast<char*>(&ReaderObject.LastName),sizeof ReaderObject.LastName);
        file_w.write(reinterpret_cast<char*>(&ReaderObject.Passport),sizeof ReaderObject.Passport);
        file_w.write(reinterpret_cast<char*>(&ReaderObject.book_counts),sizeof ReaderObject.book_counts);
        file_w.write(reinterpret_cast<char*>(&ReaderObject.book_IDs),sizeof ReaderObject.book_IDs);
        file_w.clear();
        file_w.close();
    }
//----------------------------------------------------------------------
    cout<<"> type ESC to go back to previous menu\n"<<" "<<endl;
        switch((ch_key = _getch()))
        {
        case ESC:
            Menu = false;
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
}
void menu_6(){//DELETE READER
              char ch_key;
              int IDForDeleting;
              Reader ReaderObject;
              vector<Reader> vec;
              bool Menu = true;
              while(Menu){
                  menu_title();
                  cout << "This is \"DELETE READER\" menu\n" << endl;
                  cout << "Print the \"LibraryCardNumber\" of a reader you want to delete\n" << endl;
                  cin >> IDForDeleting;
          //--------------- считываем из файла reader.bin --------------------------------
              fstream file_r("reader.bin",ios::binary|ios::in);
              if (!file_r.is_open()) {
               cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
              }
              else{
                      unsigned int cnt = 0;
                      vec.clear();//очистить вектор
                      file_r.seekp(0,ios::beg);//перемещаем указатель позиционирования файла в начало
                      cout << "vec.size after cleaning" << vec.size() << endl;
                      while (!file_r.read((char*)&ReaderObject, sizeof(Reader)).eof())
                      {                       
                        if(ReaderObject.LibraryCardNmb == IDForDeleting) {
                           cout << "READER for deleting was found\n";
                        }
                        else{vec.push_back(ReaderObject);
                             cnt++;
                        }
                      }
                      cout << "vec.size after pushing" << vec.size() << endl;
                      cout << "cnt: " << cnt << endl;
                      file_r.clear();
                      file_r.close();
                  }
          //-----------------------------------------------------------------------------
          remove_reader_bin();
          //--------------- записываем в файл reader.bin всех кроме удаленного ----------
                  //fstream file_w("reader.bin",ios::binary|ios::out|ios::trunc);//trunc - уничтожить содержимое
                  ofstream file_w("reader.bin",ios::binary|ios::out|ios::app);
                  if (!file_w.is_open()) {
                   cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
                  }
                  else{
                        for(vector<Reader>::iterator it = vec.begin(); it != vec.end(); it++)
                        {
                          file_w.write(reinterpret_cast<char*>(&it->LibraryCardNmb), sizeof(it->LibraryCardNmb));
                          file_w.write(reinterpret_cast<char*>(&it->FirstName), sizeof(it->FirstName));
                          file_w.write(reinterpret_cast<char*>(&it->LastName), sizeof(it->LastName));
                          file_w.write(reinterpret_cast<char*>(&it->Passport), sizeof(it->Passport));
                          file_w.write(reinterpret_cast<char*>(&it->book_counts), sizeof(it->book_counts));
                          file_w.write(reinterpret_cast<char*>(&it->book_IDs), sizeof(it->book_IDs));
                        }
                        file_w.clear();
                        file_w.close();
                 }
         //----------------------------------------------------------------------

              cout << "> type ESC to go back to previous menu\n" << " " << endl;
                  switch((ch_key = _getch()))
                  {
                  case ESC:
                      Menu = false;
                      break;
                  default:
                      cout<<"Unsupported key was pressed\n";
                      break;
                  }
              }
}
void menu_7(){//SHOW ALL BOOKS
    char ch_key;
    Book BookObject;
    char str[160];
    bool Menu = true;
    while(Menu){
        menu_title();
        cout << "This is \"SHOW ALL BOOKS\" menu\n" << endl;
            fstream file_r("book.bin", ios::binary|ios::in);
            if (!file_r.is_open()){
             cout << "The file \"book.bin\" cannot be opened or created..." << endl;
            }
            else{
                    cout << "INFORMATION ABOUT BOOKS:" << endl;
                    cout << "=================================================================================================================================" << endl;
                    cout << "      UniqueNumber \t" << "BookName \t" << "Author \t\t" << "CodeISBN \t" << "Pages \t" << "Year \t" << "Publisher \t" << "Count \t" << endl;
                    cout << "=================================================================================================================================" << endl;
                    file_r.seekp(0,file_r.beg);
                    while (!file_r.read((char*)&BookObject, sizeof(Book)).eof()) {
                        sprintf(str, "\t%d\t\t%s\t\t%s\t\t%d\t\t%d\t%d\t%s\t\t%d",
                        BookObject.BookUniqueNumber, BookObject.BookName, BookObject.Author, \
                        BookObject.CodeISBN, BookObject.Pages, BookObject.Year, \
                        BookObject.Publisher,BookObject.Count);
                        cout << str << endl;
                    }
                    file_r.clear();
                    file_r.close();
            }
        cout << "> type ESC to go back to previous menu\n" << " " << endl;
        switch((ch_key = _getch()))
        {
        case ESC:
            Menu = false;
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
}
void menu_8(){//SHOW ALL READERS
    char ch_key;
    Reader ReaderObject;
    char str[160];
    bool Menu = true;
    while(Menu){
        menu_title();
        cout << "This is \"SHOW ALL READERS\" menu\n" << endl;
            fstream file_r("reader.bin", ios::binary|ios::in);
            if (!file_r.is_open()){
             cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
            }
            else{
                    cout << "INFORMATION ABOUT READERS:" << endl;
                    cout << "===============================================================================================================" << endl;
                    cout << "      CardNumber \t" << "FirstName \t" << "LastName \t" << "Passport \t" << "Book_counts \t" << "  Book_IDs  \t" << endl;
                    cout << "===============================================================================================================" << endl;
                    file_r.seekp(0,file_r.beg);
                    while (!file_r.read((char*)&ReaderObject, sizeof(Reader)).eof()) {
                        sprintf(str, "\t%d\t\t%s\t\t%s\t%s\t\t%d\t\t\t%d; %d; %d; %d",
                        ReaderObject.LibraryCardNmb, ReaderObject.FirstName, ReaderObject.LastName, \
                        ReaderObject.Passport, ReaderObject.book_counts, ReaderObject.book_IDs[0],\
                        ReaderObject.book_IDs[1],ReaderObject.book_IDs[2],ReaderObject.book_IDs[3]);
                        cout << str << endl;
                    }
                    file_r.clear();
                    file_r.close();
            }
        cout << "> type ESC to go back to previous menu\n" << " " << endl;
        switch((ch_key = _getch()))
        {
        case ESC:
            Menu = false;
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
}

void menu_9(){cout<<"You choose punkt 9\n";}
