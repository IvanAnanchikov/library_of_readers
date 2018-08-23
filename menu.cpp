#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdio>        // для функции remove
#include "menu.hpp"
#include "book.hpp"
#include "reader.hpp"
using namespace std;



void menu_title(){
        cout<<"* * * * * * * * * * * * * * * * * * * * *\n";
        cout<<"* * *  CONSOLE_LIBRARY_OF_READERS  * * *\n";
        cout<<"* * * * * * * * * * * * * * * * * * * * *\n";
}
void menu_1(){
    char ch_key;
    int ReaderNumber;
    int BookNumber;
    bool Menu = true;
    while(Menu){
        menu_title();
        cout<<"This is \"TAKE A BOOK\" menu\n";
        cout<<" "<<endl;
        cout<<"> type reader's number of Library Card\n";
        cin>>ReaderNumber;
        //TODO: проверка на неправильный ввод номера читателя
        cout<<"> type book's Library Number\n";
        cin>>BookNumber;
        //TODO: проверка на неправильный ввод номера книги
        cout<<"book is taken OK\n";
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

void menu_2(){cout<<"You choose punkt 2\n";}
void menu_3(){cout<<"You choose punkt 3\n";}
void menu_4(){cout<<"You choose punkt 4\n";}
void menu_5(){//ADD READER
    char ch_key;
    int i;
    i = 5;
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
        cout<<"> type reader's Library Card Number\n";
        cin>>ReaderObject.LibraryCardNmb;
        ReaderObject.book_counts = 2;
//--------------- записываем в файл Reader --------------------------------
    ofstream file_w("reader.bin",ios::binary|ios::out|ios::app);
    if (!file_w.is_open()) {
     cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
    }
    else{
        file_w.write((char*)&ReaderObject,sizeof ReaderObject); //Записали объект в открытый файл
        file_w.clear();
        file_w.close(); //Закрыли открытый файл
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
                  cout << "This is \"DELETE READER\" menu\n";
                  cout << "Print the \"LibraryCardNumber\" of a reader you want to delete\n";
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
                      //while (!file_r.eof())
                      while (!file_r.read((char*)&ReaderObject, sizeof(Reader)).eof())
                      {                       
                        //file_r.read((char*)&ReaderObject,sizeof ReaderObject);
                        if(ReaderObject.LibraryCardNmb == IDForDeleting) {
                           cout << "READER for deleting was found\n";
                        }
                        else {vec.push_back(ReaderObject);cnt++;}
                      }
                      cout << "vec.size after pushing" << vec.size() << endl;
                      cout << "cnt: " << cnt << endl;
//                      cout << "INFORMATION ABOUT READERS:" << endl;
//                      cout << "===========================================================================" << endl;
//                      cout << "      CardNumber \t" << "FirstName \t" << "LastName \t" << "Book_counts \t" << endl;
//                      cout << "===========================================================================" << endl;
//                      for(unsigned int i = 0; i < vec.size()-1; i++) {cout << vec[i];}

                   file_r.clear();
                   file_r.close();
                  }
          //-----------------------------------------------------------------------------
          //++++++++++++++++удаляем файл+++++++++++++++++++++++++++++++
              if( remove( "reader.bin" ) != 0 )// удаление файла
                  cout << "Error deleting file reader.bin" << endl;
              else
                  cout << "File reader.bin successfully deleted" << endl;
          //++++++++++++++++удаляем файл+++++++++++++++++++++++++++++++
          //--------------- записываем в файл reader.bin всех кроме удаленного ----------
                  //fstream file_w("reader.bin",ios::binary|ios::out|ios::trunc);//trunc - уничтожить содержимое
                  ofstream file_w("reader.bin",ios::binary|ios::out|ios::app);
                  if (!file_w.is_open()) {
                   cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
                  }
                  else{
//                            for(unsigned int i = 0; i < vec.size(); i++)
//                            file_w.write((char*)&ReaderObject,sizeof ReaderObject);
                       // file_w.write((char*)&vec[i],sizeof ReaderObject);
                       //}
//                       for (auto it = vec.begin(); it != vec.end(); it++)
//                       {
//                           ReaderObject = vec.c();//at(it)
//                           file_w.write((char*)&ReaderObject,sizeof ReaderObject);
//                           //file_w.write((char*)&vec.at(it),sizeof ReaderObject);
//                       }
                       //copy(vec.begin(), vec.end(), ostream_iterator<Reader>(cout, " "));

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//                      for(std::vector<Test>::iterator i = tst.begin(); i != tst.end(); ++i)
//                      {
//                          om << i->question << " ";
//                          for(size_t j = 0; j < Test::n; ++j)
//                            om  << i-> answer[j] << " ";
//                          om << std::endl;
//                      }
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

                      for(vector<Reader>::iterator it = vec.begin(); it != vec.end(); it++)
                      {
                          file_w << it->LibraryCardNmb;
                          file_w << it->FirstName;
                          file_w << it->LastName;
                          file_w << it->book_counts;

//                                    it->LibraryCardNmb << " ";
//                          for(size_t j = 0; j < Reader::n; ++j)
//                            file_w  << i-> answer[j] << " ";
//                          file_w << std::endl;
                      }

                       //copy(vec.begin(), vec.end(), ostream_iterator<Reader>(file_w));
                       file_w.clear();
                       file_w.close(); //Закрыли открытый файл
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
//void menu_6(){cout<<"You choose punkt 6\n";}
void menu_7(){cout<<"You choose punkt 7\n";}
void menu_8(){//SHOW ALL READERS
    char ch_key;
    Reader ReaderObject;
    vector<Reader> vec;
    bool Menu = true;
    while(Menu){
        menu_title();
        cout<<"This is \"SHOW ALL READERS\" menu\n";
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    ifstream file_r("reader.bin", ios::binary);
                    char str[80];
                    cout << "===========================================================================" << endl;
                    cout << "      CardNumber \t" << "FirstName \t" << "LastName \t" << "Book_counts \t" << endl;
                    cout << "===========================================================================" << endl;
                    // Считывать и отображать строки в цикле, пока не eof
                    while (!file_r.read((char*)&ReaderObject, sizeof(Reader)).eof()) {
                        sprintf(str, "\t%d\t\t%s\t\t%s\t\t%d",
                        ReaderObject.LibraryCardNmb, ReaderObject.FirstName, ReaderObject.LastName, ReaderObject.book_counts);
                        cout << str << endl;
                    }
                    file_r.close();		    // закрыть прочитанный файл
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//--------------- считываем из файла Reader --------------------------------
//    fstream file_r("reader.bin",ios::binary|ios::in);
//    //file_r.seekg(0, file_r.end);
//    if (!file_r.is_open()) {
//     cout << "The file \"reader.bin\" cannot be opened or created..." << endl;
//    }
//    else{
//            file_r.seekp(0,file_r.beg);//ios::
//            while (!file_r.eof())
//            {
//                file_r.read((char*)&ReaderObject,sizeof ReaderObject);//Считали информацию в объект
//                vec.push_back(ReaderObject);
//            }
//            file_r.clear();
//            file_r.close(); //Закрыли открытый файл
//         //}
//    }
//    cout << "INFORMATION ABOUT READERS:" << endl;
//    cout << "===========================================================================" << endl;
//    cout << "      CardNumber \t" << "FirstName \t" << "LastName \t" << "Book_counts \t" << endl;
//    cout << "===========================================================================" << endl;
//    for(unsigned int i = 0; i < vec.size()-1; i++) {cout << vec[i];}
//    //copy(vec.begin(), vec.end(), ostream_iterator<Reader>(cout, ";"));
//    cout << endl;
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

void menu_9(){cout<<"You choose punkt 9\n";}
