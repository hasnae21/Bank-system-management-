
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BankRecord {
protected:
    int accountNumber;
    double balance;
    string firstName;
    string lastName;

public:
    // Constructors and Destructor
    BankRecord() : accountNumber(0), balance(0.0) {}
    BankRecord(int accNum, const string& fName, const string& lName, double bal): accountNumber(accNum), firstName(fName), lastName(lName), balance(bal) {}
    BankRecord(const BankRecord& other): accountNumber(other.accountNumber), firstName(other.firstName),lastName(other.lastName), balance(other.balance) {}
    ~BankRecord() {}

    // Member Functions to get Data from user
    void readData() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter First Name: ";
        cin >> firstName;
        cout << "Enter Last Name: ";
        cin >> lastName;
        cout << "Enter Balance: $";
        cin >> balance;
    }

    // Member Functions to display Data to the user
    void showData() const {
        cout << "Account Number: " << accountNumber
             << ", Name: " << firstName << " " << lastName
             << ", Balance: $" << balance << endl;
    }

    // Pure Virtual Function for File Handling
    virtual void writeToFile(ofstream& outFile) const = 0;
    virtual void readFromFile(ifstream& inFile) = 0;
};

class BankRecordManager : public BankRecord {
private:
    string fileName = "bank_records.txt";

public:
    BankRecordManager(){}
    BankRecordManager(const BankRecord& BR) : BankRecord(BR) {}

    void writeToFile(ofstream& outFile) const {
        outFile << accountNumber << " " << firstName << " " << lastName << " " << balance << endl;
    }
    void readFromFile(ifstream& inFile) {
        inFile >> accountNumber >> firstName >> lastName >> balance;
    }

    // ADD A NEW BANK RECORD TO THE FILE (CREATE)
    void addRecord() {
        ofstream outFile(fileName, ios::app); // OPEN FILE(outFile) TO WRITE
        if (outFile.is_open()) {
            readData();         // GET DATA FROM THE USER
            writeToFile(outFile); // STORE IN THE FILE
            outFile.close();

            cout << "Record added successfully!" << endl;
        } else
            cout << "Error opening file for writing." << endl;
    }
    
    // SHOW ALL RECORDS DATA FROM THE FILE (DISPLAY)
	void showRecords() {
        ifstream inFile(fileName); // OPEN FILE(inFile) TO READ
        if (inFile.is_open()) {
            cout << "\nBank Records => \n";
            
            int totalRecords = 0;
            while (inFile >> accountNumber >> firstName >> lastName >> balance) {
                totalRecords++;
                showData(); 
            }
            cout << "\nThe total number of bank records in the file is : " << totalRecords << "\n\n";
            inFile.close();
        } else
            cout << "Error opening file for reading." << endl;
    }	
	
    // SHOW THE RECORD DATA OF A CORRESPONDING recordNumber FROM THE FILE (DISPLAY)
    bool searchRecord(int recordNumber) {
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            cout << "\nSearching for record => ";
            while (inFile >> accountNumber >> firstName >> lastName >> balance) {
                if (accountNumber == recordNumber) {
                    cout << "Record found!\n";
                    inFile.close();
                    return true;
                }
            }
            inFile.close();
            cout << "Record not found!\n";
            return false;
        } else {
            cerr << "Error opening file for reading." << endl;
            return false;
        }
    }
    
    // DELETE THE RECORD FROM File
    void deleteRecord(int recordNumber) {
        ifstream inFile(fileName);
        ofstream tempFile("temp.txt", ios::app);

        if (inFile.is_open() && tempFile.is_open()) {
            cout << "\nDeleting record => ";
            bool recordDeleted = false;

            while (inFile >> accountNumber >> firstName >> lastName >> balance) {
                if (accountNumber == recordNumber) {
                    cout << "Record deleted successfully!\n";
                    recordDeleted = true;
                } else {
                    tempFile << accountNumber << " "
                             << firstName << " "
                             << lastName << " "
                             << balance << endl;
                }
            }

            inFile.close();
            tempFile.close();
            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());

            if (!recordDeleted) {
                cout << "Record not found!\n";
            }
        } else {
            cout << "Error opening files for reading/writing." << endl;
        }
    }
    
	// EDIT THE RECORD FROM File
    void editRecord(int recordNumber) {
		ifstream inFile(fileName); // OPEN FILE(inFile) TO READ
	    ofstream tempFile("temp.txt", ios::app); // OPEN FILE(outFile) TO WRITE
        if (inFile.is_open() && tempFile.is_open()) {
        	cout << "\nUpdating record => \n";
            bool recordUpdated = false;
        	
        	while (inFile >> accountNumber >> firstName >> lastName >> balance) {
                if (accountNumber == recordNumber) {
                    recordUpdated = true;
		            readData();         // GET DATA Updated FROM THE USER
		            writeToFile(tempFile); // STORE IN THE FILE         
                } else {
                    tempFile << accountNumber << " "
                             << firstName << " "
                             << lastName << " "
                             << balance << endl;
                }
            }
            
            inFile.close();
            tempFile.close();
            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());

            if (!recordUpdated) {
                cout << "Record not found!\n";
            }
            cout << "Record modified successfully!" << endl;
        } else
            cout << "Error opening file for writing." << endl;     
    }
    
	~BankRecordManager() {}
};

int main() {
    BankRecordManager recordManager;
    int choice, recordNumber;

    do {
        cout << "\nBanking Record System\n";
        cout << "1. Add Record\n";
        cout << "2. Show Records\n";
        cout << "3. Search Record\n";
        cout << "4. Edit Record\n";
        cout << "5. Delete Record\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                recordManager.addRecord();
                break;
            case 2:
                recordManager.showRecords();
                break;
            case 3:
                cout << "Enter Record Number to Search: ";
                cin >> recordNumber;
                recordManager.searchRecord(recordNumber);
				break;
            case 4:
            	recordManager.showRecords();
                cout << "Enter Record Number to Edit: ";
                cin >> recordNumber;
                recordManager.editRecord(recordNumber);
                break;
            case 5:
                cout << "Enter Record Number to Delete: ";
                cin >> recordNumber;
                recordManager.deleteRecord(recordNumber);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
