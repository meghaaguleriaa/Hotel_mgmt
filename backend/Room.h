#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
using namespace std;

class Room
{
private:
    int roomNumber;
    string roomType;
    double price;
    string status;

public:
    // Constructors
    Room();
    Room(int number, string type, double p);

    // Member functions
    void displayRoom() const;
    bool isAvailable() const;
    void updateStatus(string newStatus);

    // Inline function
    inline double calculateCharge(int days)
    {
        return price * days;
    }

    // Getters
    int getRoomNumber() const;
    double getPrice() const;
    string getStatus() const;
    string getRoomType() const;
};

#endif