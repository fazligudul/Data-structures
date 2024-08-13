//Name:Fazlı Güdül
//Section number:2
//Student number:22002785
#include "DVDStoreManagementSystem.h"
#include <iostream>

using namespace std;


DVDStoreManagementSystem::DVDStoreManagementSystem(){
    DVDs=nullptr;
    customers=nullptr;
    transactions = nullptr;
    dvdCount=0;
    customerCount = 0;
    transactionCount = 0;
}

DVDStoreManagementSystem::~DVDStoreManagementSystem(){
    if (DVDs != nullptr) {
        delete[] DVDs;
    }
    if (customers != nullptr) {
        delete[] customers;
    }
    if (transactions != nullptr) {
        delete[] transactions;
    }
}

void DVDStoreManagementSystem:: addDVD( const string serialNo, const string title, const string director ){
    bool isDuplicate = false;
    for (int i = 0; i < dvdCount; i++) {
        if (DVDs[i].serialNo == serialNo) {
            // warning!! dvd already exist
            cout<< "Cannot add DVD. DVD with serial number " << serialNo <<" already exists."<<endl;
            isDuplicate = true;
            break;
        }
    }
    if (!isDuplicate) {
        // If can be added
        DVD *upDVDs = new DVD[dvdCount + 1];
        // Transfer old array to updated
        for (int i = 0; i < dvdCount; i++) {
            upDVDs[i] = DVDs[i];
        }

        upDVDs[dvdCount].serialNo = serialNo;
        upDVDs[dvdCount].title = title;
        upDVDs[dvdCount].director = director;
        upDVDs[dvdCount].isRented = false;

        dvdCount++;
        // Release old array
        delete[] DVDs;
        DVDs = upDVDs;
        cout << "DVD with serial number " << serialNo << " successfully added." << endl;
    }
}
    void DVDStoreManagementSystem:: removeDVD( const string serialNo ){
        bool found = false;
        int in=-1;
        
        for (int i = 0; i < dvdCount; i++) {
            if (DVDs[i].serialNo == serialNo) {
                found = true;
                in = i;
                break;
            }
        }
        if(!found){
            cout<<"Cannot remove DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
            return;
        }
        if(DVDs[in].isRented){
            cout<<"Cannot remove DVD. DVD with serial number "<<serialNo<<" is currently rented by a customer."<<endl;
            return;
        }
        // Create a new array with reduced size
        DVD* upDVDs = new DVD[dvdCount - 1];
        
        // Copy DVDs before the removed DVD
        for (int i = 0; i < in; i++) {
            upDVDs[i] = DVDs[i];
        }
        // Copy DVDs after the removed DVD
        for (int i = in; i < dvdCount - 1; i++) {
            upDVDs[i] = DVDs[i + 1];
        }
        
        // Release old array
        delete[] DVDs;
        // Update pointer to the new array
        DVDs = upDVDs;
        
        cout << "DVD with serial number " << serialNo << " successfully removed." << endl;
        dvdCount--;
        //dancing
    }
    void DVDStoreManagementSystem:: addCustomer( const int customerID, const string name ){
        // Check for duplicate customer ID
    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].customerID == customerID) {
            cout << "Cannot add customer. Customer with ID " << customerID << " already exists." << endl;
            return;
        }
    }

    // Create a new array to hold customers
    Customer* updatedCustomers = new Customer[customerCount + 1];
    
    // Copy existing customers to the new array
    for (int i = 0; i < customerCount; ++i) {
        updatedCustomers[i] = customers[i];
    }

    // Add the new customer
    updatedCustomers[customerCount].customerID = customerID;
    updatedCustomers[customerCount].name = name;
    updatedCustomers[customerCount].numDVDsRented = 0;

    // Increment the number of customers
    customerCount++;

    // Release old array and update pointer
    delete[] customers;
    customers = updatedCustomers;

    cout << "Customer with ID " << customerID << " successfully added." << endl;
        
    }
    void DVDStoreManagementSystem:: removeCustomer( const int customerID ){
        int pivot = -1;
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].customerID == customerID) {
                pivot = i;
                break;
            }
        }

        // if customer does not exist
        if (pivot == -1) {
            cout << "Cannot remove customer. Customer with ID " << customerID << " not found." << endl;
            return;
        }
        // if customer has dvds cant be removed
        if (customers[pivot].numDVDsRented > 0) {
            cout << "Cannot remove customer. Customer with ID " << customerID << " has rented DVDs." << endl;
            return;
        }
        
        // Create a new array with reduced size
        Customer* updatedCustomers = new Customer[customerCount - 1];
        
        // Copy customers before the removed customer
        for (int i = 0; i < pivot; ++i) {
            updatedCustomers[i] = customers[i];
        }
        // Copy customers after the removed customer
        for (int i = pivot; i < customerCount - 1; ++i) {
            updatedCustomers[i] = customers[i + 1];
        }
        
        // Release old array
        delete[] customers;
        // Update pointer to the new array
        customers = updatedCustomers;
        
        cout << "Customer with ID " << customerID << " successfully removed." << endl;
        customerCount--;
    }
    void DVDStoreManagementSystem:: rentDVD( const int customerID, const string serialNo ){
        int inOfDvd=-1;
        int inOfCus=-1;
        for(int i=0;i<dvdCount;i++){
            if(DVDs[i].serialNo==serialNo){
                inOfDvd=i;
                break;
            }
        }
        for(int i=0;i<customerCount;i++){
            if(customers[i].customerID==customerID){
                inOfCus=i;
                break;
            }
        }
        if(inOfDvd<0 && inOfCus<0){
            cout<<"Cannot rent DVD. Customer with ID "<<customerID<<" and DVD with serial number "<<serialNo<<" not found."<<endl;
            return;
        }
        if(inOfDvd<0){
            cout<<"Cannot rent DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
            return;
        }
        if(inOfCus<0){
            cout<<"Cannot rent DVD. Customer with ID "<<customerID<<" not found."<<endl;
            return;
        }
        if(DVDs[inOfDvd].isRented){
            cout<<"Cannot rent DVD. DVD with serial number "<<serialNo<<" is not available."<<endl;
            return;
        }
        DVDs[inOfDvd].isRented=true;
        //update customers renting number
        customers[inOfCus].numDVDsRented++;
        
        bool isDuplicate = false;
        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].serialNo == serialNo&&transactions[i].transactionType=="Rental") {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            // If can be added
            Transaction* newTransactions = new Transaction[transactionCount + 1];
            // Transfer old array to updated
            for (int i = 0; i < transactionCount; i++) {
                newTransactions[i] = transactions[i];
            }
            newTransactions[transactionCount].serialNo=serialNo;
            newTransactions[transactionCount].customerID=customerID;
            newTransactions[transactionCount].transactionType="Rental";
            transactionCount++;
            // Release old array
            delete[] transactions;
            transactions = newTransactions;
        }
        cout<<"DVD with serial number "<<serialNo<<" successfully rented by customer with ID "<<customerID<<"."<<endl;
    
    }
    void DVDStoreManagementSystem:: returnDVD( const int customerID, const string serialNo ){
        int inOfDvd=-1;
        int inOfCus=-1;
        for(int i=0;i<dvdCount;i++){
            if(DVDs[i].serialNo==serialNo){
                inOfDvd=i;
                break;
            }
        }
        for(int i=0;i<customerCount;i++){
            if(customers[i].customerID==customerID){
                inOfCus=i;
                break;
            }
        }
        if(inOfDvd<0 && inOfCus<0){
            cout<<"Cannot return DVD. Customer with ID "<<customerID<<" and DVD with serial number "<<serialNo<<" not found."<<endl;
            return;
        }
        if(inOfDvd<0){
            cout<<"Cannot return DVD. DVD with serial number "<<serialNo<<" not found."<<endl;
            return;
        }
        if(inOfCus<0){
            cout<<"Cannot return DVD. Customer with ID "<<customerID<<" not found."<<endl;
            return;
        }
        //we can check that if this customer has 
        bool isFound = false; 
        for(int i=0; i<transactionCount;i++){
            if(transactions[i].transactionType=="Rental"&&transactions[i].serialNo==serialNo&&transactions[i].customerID==customerID){
                isFound=true;
                break;
            }
        }
        if(!isFound){
            cout<<"Cannot return DVD. DVD with serial number "<<serialNo<<" not rented by customer with ID "<<customerID<<"."<<endl;
            return;
        }
        
        DVDs[inOfDvd].isRented=false;
        //update customers renting number
        customers[inOfCus].numDVDsRented--;
            
        //transaction part
        bool isDuplicate = false;
        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].serialNo == serialNo&&transactions[i].transactionType=="Return") {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            // If can be added
            Transaction* newTransactions = new Transaction[transactionCount + 1];
            // Transfer old array to updated
            for (int i = 0; i < transactionCount; i++) {
                newTransactions[i] = transactions[i];
            }
            newTransactions[transactionCount].serialNo=serialNo;
            newTransactions[transactionCount].customerID=customerID;
            newTransactions[transactionCount].transactionType="Return";
            transactionCount++;
            // Release old array
            delete[] transactions;
            transactions = newTransactions;
        }
        cout<<"DVD with serial number "<<serialNo<<" successfully returned by customer with ID "<<customerID<<"."<<endl;
    }
    void DVDStoreManagementSystem:: showAllDVDs() const{
        cout<<"DVDs in the system:"<<endl;
        if (dvdCount == 0) {
            cout << "None" <<endl;
            return;
        }

        for (int i = 0; i < dvdCount; i++) {
            cout<<"DVD: "<<DVDs[i].serialNo<<", Title: " << DVDs[i].title <<", Director: " << DVDs[i].director <<", ";
            cout<<(DVDs[i].isRented ? "Rented" : "Available") << endl;
        }
        
    }
    void DVDStoreManagementSystem:: showAllCustomers() const{
        cout<<"Customers in the system:"<<endl;
        if (customerCount == 0) {
            cout << "None" <<endl;
            return;
        }
        for(int i = 0; i < customerCount; i++){
            cout<<"Customer: "<<customers[i].customerID<<", Name: "<<customers[i].name<<", DVDs Rented: "<<customers[i].numDVDsRented<<endl;
        }
    }
    void DVDStoreManagementSystem:: showDVD( const string serialNo ) const{
        int inOfDvd=-1;
        for(int i=0;i<dvdCount;i++){
            if(DVDs[i].serialNo==serialNo){
                inOfDvd=i;
                break;
            }
        }
        if(inOfDvd<0){
            cout<<"DVD with serial number "<<serialNo<<" not found."<<endl;
            return;
        }
        cout<< "DVD: "<<serialNo<<", Title: "<<DVDs[inOfDvd].title<<", Director: "<<DVDs[inOfDvd].director<<", ";
        cout<< (DVDs[inOfDvd].isRented ? "Rented" : "Available") << endl;
    }
    void DVDStoreManagementSystem:: showCustomer( const int customerID ) const{
        int inOfCus=-1;
        for(int i=0;i<customerCount;i++){
            if(customers[i].customerID==customerID){
                inOfCus=i;
                break;
            }
        }
        if(inOfCus<0){
            cout<<"Customer with ID "<<customerID<<" not found."<<endl;
            return;
        }
        cout<<"Customer: "<<customerID<<", Name: "<<customers[inOfCus].name<<", DVDs Rented: "<<customers[inOfCus].numDVDsRented<<endl;
    }
    void DVDStoreManagementSystem:: showTransactionHistory() const{
        cout<<"Transactions in the system:"<<endl;
        if (transactionCount == 0) {
            cout << "None" <<endl;
            return;
        }
        for(int i=0;i<transactionCount;i++){
            cout<<"Transaction: "<<transactions[i].transactionType<<", Customer: "<<transactions[i].customerID<<", DVD: "<<transactions[i].serialNo<<endl;
        }
    }

