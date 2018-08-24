#include <QCoreApplication>
#include <iostream>
#include <conio.h>
#include <cstdio>        // для функции remove
#include "menu.hpp"
#include "book.hpp"
#include "reader.hpp"
using namespace std;


//----------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char ch_key;
    bool MainMenu = true;

    while(MainMenu){
       /* 1 Взять книгу читателю 2 вернуть книгу
        * 3 добавить книгу 		 4 удалить книгу
        * 5 добавить читателя 	 6 удалить читателя
        * 7 показать книги 		 8 показать читателей
        * 9 найти книгу          10 подробная информация о читателе
        */
        menu_title();
        cout<<"...press any key to continue...\n";
        cout<<" "<<endl;
        cout<<"1 - take a book \n";
        cout<<"2 - give a book back\n";
        cout<<"3 - Add a Book\n";
        cout<<"4 - Delete a Book\n";
        cout<<"5 - Add Reader\n";
        cout<<"6 - Delete Reader\n";
        cout<<"7 - Show all Books\n";
        cout<<"8 - Show all Readers\n";
        cout<<"9 - find a book\n";
        cout<<"ESC - quit\n"<<" "<<endl;
        switch((ch_key = _getch()))
        {
        case '1':
            menu_1();
            break;
        case '2':
            menu_2();
            break;
        case '3':
            menu_3();
            break;
        case '4':
            menu_4();
            break;
        case '5':
            menu_5();
            break;
        case '6':
            menu_6();
            break;
        case '7':
            menu_7();
            break;
        case '8':
            menu_8();
            break;
        case '9':
            menu_9();
            break;
        case ESC:
            MainMenu = false;
            cout<<"Exiting from program. Bye!\n";
            break;
        default:
            cout<<"Unsupported key was pressed\n";
            break;
        }
    }
   // system("pause");
    //return 0;
    return a.exec();
}
