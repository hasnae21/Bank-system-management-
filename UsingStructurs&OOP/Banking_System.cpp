#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
using namespace std;

int main()
{
////////////////////////////////////////////////////
    FILE *fp, *ft;
    fp = fopen("clients.txt", "rb+");
    if (fp == NULL)
    {
        fp = fopen("clients.txt", "wb+");
        if (fp == NULL)
        {
            puts("Cannot open file clients.txt");
            return 0;
        }
    }
////////////////////////////////////////////////////

    struct Clients
    {
        int account_number;
        char first_name[50], last_name[50];
        long balance;
    };
    struct Clients record;
    long recsize = sizeof(record); /////////////////////////////////////////////////
    char choice, another;
    int xaccount_number;

    while (1)
    {
        system("cls"); //////////////////////////////////////////////////////////////////////

        cout << "** Account Information System **\nSelect one option below :\n\t 1-->Add record to file\n\t 2-->Show record from file\n\t 3-->Search record from file\n\t 4-->Update record\n\t 5-->Delete record\n\t 6-->Quit\n\nEnter your choice :  ";
        choice = getche();

        switch (choice)
        {
        case '1':
            fseek(fp, 0, SEEK_END); /////////////////////////////////////////////////////
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {
                cout << "\n\n";
                cout << "Enter the Account Number  :";
                cin >> record.account_number;
                cout << "Enter the Firt Name : ";
                cin >> record.first_name;
                cout << "Enter the Last Name : ";
                cin >> record.last_name;
                cout << "Enter the Balance  : ";
                cin >> record.balance;
                fwrite(&record, recsize, 1, fp); /////////////////////////////////////////
                cin.ignore();  
                /// the loop
                cout << "\nAdd Another Record (Y/N) ";
                another = getchar();
            }
            break;

        case '2':
            exit(0);

        case '3':
            rewind(fp);
            cout << "=== View the list in the Database ===\n";
            while (fread(&record, recsize, 1, fp) == 1)
            {
                cout << "\n\n" << record.first_name << setw(10) << record.last_name << setw(10) << record.account_number << setw(8) << record.balance;
            }
            system("pause");
            break;

        case '4':
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {
                cout << "\nEnter the account number of the Client :";
                cin >> xaccount_number;

                rewind(fp);  /////////////////////////////////////////////////////////////////////////////////////////
                while (fread(&record, recsize, 1, fp) == 1)
                {
                    if (record.account_number != xaccount_number)
                    {
                        cout << "\n\n";
                        cout << "Enter new Account Number     : ";
                        cin >> record.account_number;
                        cout << "Enter new the Firt Name : ";
                        cin >> record.first_name;
                        cout << "Enter new the Last Name : ";
                        cin >> record.last_name;
                        cout << "Enter new Balance   : ";
                        cin >> record.balance;

                        fseek(fp, -recsize, SEEK_CUR); /////////////////////////////////////////////////////
                        fwrite(&record, recsize, 1, fp); /////////////////////////////////////////////////////////
                        break;
                    }
                    else
                        cout << "\nError in opening! File Not Found!!";
                }
                cin.ignore(); 
                /// the loop
                cout << "\nModify Another Record (Y/N)";
                another = getchar();
            }
            break;

        case '5':
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {
                cout << "\nEnter the account number of the Clients to delete : ";
                cin >> xaccount_number;

                ft = fopen("temp.dat", "wb"); ///////////////////////////////////////////////////////////////////
                rewind(fp); //////////////////////////////////////////////////////////////////////////////////////////////
                while (fread(&record, recsize, 1, fp) == 1)
                    if (record.account_number != xaccount_number)
                    {
                        fwrite(&record, recsize, 1, ft);
                    }
                fclose(fp); fclose(ft); ///////////////////////////////////////////////////////////////////////////////
                remove("clients.txt");  /////////////////////////////////////////////////////////////////////////////
                rename("temp.dat", "clients.txt"); ///////////////////////////////////////////////////////////
                fp = fopen("clients.txt", "rb+"); ////////////////////////////////////////////////////////////////
                cin.ignore();  
                /// the loop
                cout << "\nDelete Another Record (Y/N) ";
                another = getchar();
            }
            break;

        case '6':
            fclose(fp); //////////////////////////////////////////////////////////////////////////////////////////////////
            cout << "\n\n\t OK BY! THANK YOU \n\n";
            exit(0);
        }
    }

    system("pause"); //////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}