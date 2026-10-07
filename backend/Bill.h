#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <iomanip>
using namespace std;

class Bill
{
private:
    int billId;
    int customerId;
    double roomCharges;
    double foodCharges;
    double serviceCharges;
    double total;

public:
    // Constructor
    Bill();

    // Function overloading
    void calculateBill();
    void calculateBill(double food);
    void calculateBill(double food, double service);

    // Display bill
    void displayBill() const;

    // Operator overloading
    Bill operator+(const Bill& other);

    // Friend function
    friend double calculateTotal(const Bill& bill);

    // Setters
    void setBillId(int id);
    void setCustomerId(int id);
    void setRoomCharges(double amount);
    void setFoodCharges(double amount);
    void setServiceCharges(double amount);

    // Getter
    double getTotal() const;
};

#endif