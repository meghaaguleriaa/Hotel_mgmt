#ifndef FOODORDER_H
#define FOODORDER_H

#include <iostream>
#include <string>
using namespace std;

class FoodOrder
{
private:
    int orderId;
    int customerId;
    string itemName;
    double price;
    int quantity;

public:
    // Constructors
    FoodOrder();
    FoodOrder(int id, int cid, string item, double p, int qty = 1);

    // Member functions
    void addFood();
    void displayOrder() const;
    double calculateTotal() const;

    // Getters
    int getOrderId() const;
    int getCustomerId() const;
};

#endif