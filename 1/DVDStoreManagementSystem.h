//Name:Fazlı Güdül
//Section number:2
#ifndef DVDSTOREMANAGEMENTSYSTEM_H
#define DVDSTOREMANAGEMENTSYSTEM_H
#include <string>
using namespace std;

class DVDStoreManagementSystem{
    
public:
    DVDStoreManagementSystem();
    ~DVDStoreManagementSystem();
    
    void addDVD( const string serialNo, const string title, const string director );
    void removeDVD( const string serialNo );
    void addCustomer( const int customerID, const string name );
    void removeCustomer( const int customerID );
    void rentDVD( const int customerID, const string serialNo );
    void returnDVD( const int customerID, const string serialNo );
    void showAllDVDs() const;
    void showAllCustomers() const;
    void showDVD( const string serialNo ) const;
    void showCustomer( const int customerID ) const;
    void showTransactionHistory() const;
private:
    struct DVD{
        string serialNo;
        string title;
        string director;
        bool isRented;
        DVD() : serialNo(""), title(""), director(""), isRented(false) {}
    };
    struct Customer {
        int customerID;
        string name;
        int numDVDsRented;
    };
    struct Transaction {
        string serialNo;
        int customerID;
        string transactionType; // "Rental" or "Return"
    };
    
    DVD* DVDs; 
    Customer* customers; 
    Transaction* transactions; 
    
    int dvdCount; 
    int customerCount; 
    int transactionCount;
};

#endif // DVDSTOREMANAGEMENTSYSTEM_H
