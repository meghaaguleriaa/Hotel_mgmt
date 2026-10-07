#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
using namespace std;

class Customer
{
private:
    int customerId;
    string name;
    string phone;
    string email;
    string address;
    string idProof;

public:

    
    // Constructors
    Customer();
    Customer(int id, string n, string p, string e, string a, string proof);
    Customer(const Customer& other);
    // Member functions
    void addCustomer();
    void displayCustomer() const;
    void updateCustomer();

    // Getter
    int getCustomerId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;
    string getAddress() const;
    string getIdProof() const;
    // Operator overloading
    friend ostream& operator<<(ostream& out, const Customer& c);
    friend istream& operator>>(istream& in, Customer& c);
};

#endif
