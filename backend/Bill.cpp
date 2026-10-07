#include "Bill.h"

// Default constructor
Bill::Bill()
{
    billId = 0;
    customerId = 0;
    roomCharges = 0;
    foodCharges = 0;
    serviceCharges = 0;
    total = 0;
}

// Calculate only room bill
void Bill::calculateBill()
{
    total = roomCharges;
}

// Calculate room + food bill
void Bill::calculateBill(double food)
{
    foodCharges = food;
    total = roomCharges + foodCharges;
}

// Calculate room + food + service bill
void Bill::calculateBill(double food, double service)
{
    foodCharges = food;
    serviceCharges = service;

    total = roomCharges + foodCharges + serviceCharges;
}

// Display bill
void Bill::displayBill() const
{
    cout << "\n========================================";
    cout << "\n              HOTEL BILL";
    cout << "\n========================================";

    cout << "\nBill ID          : " << billId;
    cout << "\nCustomer ID      : " << customerId;

    cout << "\n----------------------------------------";

    cout << "\nRoom Charges     : Rs. "
         << fixed << setprecision(2) << roomCharges;

    cout << "\nFood Charges     : Rs. "
         << fixed << setprecision(2) << foodCharges;

    cout << "\nService Charges  : Rs. "
         << fixed << setprecision(2) << serviceCharges;

    cout << "\n----------------------------------------";

    cout << "\nTOTAL            : Rs. "
         << fixed << setprecision(2) << total;

    cout << "\n========================================\n";
}

// Operator + overloading
Bill Bill::operator+(const Bill& other)
{
    Bill result;

    result.billId = billId;
    result.customerId = customerId;

    result.roomCharges = roomCharges + other.roomCharges;
    result.foodCharges = foodCharges + other.foodCharges;
    result.serviceCharges = serviceCharges + other.serviceCharges;

    result.total = result.roomCharges
                 + result.foodCharges
                 + result.serviceCharges;

    return result;
}

// Friend function
double calculateTotal(const Bill& bill)
{
    return bill.roomCharges
         + bill.foodCharges
         + bill.serviceCharges;
}

// Setters
void Bill::setBillId(int id)
{
    billId = id;
}

void Bill::setCustomerId(int id)
{
    customerId = id;
}

void Bill::setRoomCharges(double amount)
{
    roomCharges = amount;
}

void Bill::setFoodCharges(double amount)
{
    foodCharges = amount;
}

void Bill::setServiceCharges(double amount)
{
    serviceCharges = amount;
}

// Getter
double Bill::getTotal() const
{
    return total;
}