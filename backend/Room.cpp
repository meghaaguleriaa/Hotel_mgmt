#include "Room.h"

// Default constructor
Room::Room()
{
    roomNumber = 0;
    roomType = "";
    price = 0;
    status = "Available";
}

// Parameterized constructor
Room::Room(int number, string type, double p)
{
    roomNumber = number;
    roomType = type;
    price = p;
    status = "Available";
}

// Display room details
void Room::displayRoom() const
{
    cout << "\n-----------------------------";
    cout << "\nRoom Number : " << roomNumber;
    cout << "\nRoom Type   : " << roomType;
    cout << "\nPrice/Night : Rs. " << price;
    cout << "\nStatus      : " << status;
    cout << "\n-----------------------------\n";
}

// Check whether room is available
bool Room::isAvailable() const
{
    if (status == "Available")
    {
        return true;
    }

    return false;
}

// Update room status
void Room::updateStatus(string newStatus)
{
    status = newStatus;
}

// Get room number
int Room::getRoomNumber() const
{
    return roomNumber;
}

// Get room price
double Room::getPrice() const
{
    return price;
}

// Get room status
string Room::getStatus() const
{
    return status;
}
string Room::getRoomType() const
{
    return roomType;
}