#include "FoodOrder.h"

// Default constructor
FoodOrder::FoodOrder()
{
    orderId = 0;
    customerId = 0;
    itemName = "";
    price = 0;
    quantity = 1;
}

// Parameterized constructor
FoodOrder::FoodOrder(int id, int cid, string item,
                     double p, int qty)
{
    orderId = id;
    customerId = cid;
    itemName = item;
    price = p;
    quantity = qty;
}

// Add food order
void FoodOrder::addFood()
{
    cout << "\nEnter Order ID: ";
    cin >> orderId;

    cout << "Enter Customer ID: ";
    cin >> customerId;

    cin.ignore();

    cout << "Enter Food Item: ";
    getline(cin, itemName);

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "\nFood order added successfully!\n";
}

// Display order
void FoodOrder::displayOrder() const
{
    cout << "\n-----------------------------";
    cout << "\nOrder ID    : " << orderId;
    cout << "\nCustomer ID : " << customerId;
    cout << "\nFood Item   : " << itemName;
    cout << "\nPrice       : Rs. " << price;
    cout << "\nQuantity    : " << quantity;
    cout << "\nTotal       : Rs. " << calculateTotal();
    cout << "\n-----------------------------\n";
}

// Calculate food total
double FoodOrder::calculateTotal() const
{
    return price * quantity;
}

// Get order ID
int FoodOrder::getOrderId() const
{
    return orderId;
}

// Get customer ID
int FoodOrder::getCustomerId() const
{
    return customerId;
}