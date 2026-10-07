#include "Booking.h"

// Default constructor
Booking::Booking()
{
    bookingId = 0;
    customerId = 0;
    roomNumber = 0;
    checkInDate = "";
    numberOfDays = 0;
    status = "Pending";
}

// Parameterized constructor
Booking::Booking(int bid, int cid, int room,
                 string date, int days)
{
    bookingId = bid;
    customerId = cid;
    roomNumber = room;
    checkInDate = date;
    numberOfDays = days;
    status = "Booked";
}

// Create a booking
void Booking::createBooking()
{
    cout << "\nEnter Booking ID: ";
    cin >> bookingId;

    cout << "Enter Customer ID: ";
    cin >> customerId;

    cout << "Enter Room Number: ";
    cin >> roomNumber;

    cin.ignore();

    cout << "Enter Check-in Date: ";
    getline(cin, checkInDate);

    cout << "Enter Number of Days: ";
    cin >> numberOfDays;

    status = "Booked";

    cout << "\nBooking created successfully!\n";
}

// Display booking details
void Booking::displayBooking() const
{
    cout << "\n-----------------------------";
    cout << "\nBooking ID    : " << bookingId;
    cout << "\nCustomer ID   : " << customerId;
    cout << "\nRoom Number   : " << roomNumber;
    cout << "\nCheck-in Date : " << checkInDate;
    cout << "\nNumber of Days: " << numberOfDays;
    cout << "\nStatus        : " << status;
    cout << "\n-----------------------------\n";
}

// Cancel booking
void Booking::cancelBooking()
{
    if (status == "Booked" || status == "Pending")
    {
        status = "Cancelled";
        cout << "\nBooking cancelled successfully!\n";
    }
    else
    {
        cout << "\nBooking cannot be cancelled.\n";
    }
}

// Check in customer
void Booking::checkIn()
{
    if (status == "Booked")
    {
        status = "Checked-In";
        cout << "\nCustomer checked in successfully!\n";
    }
    else
    {
        cout << "\nCustomer cannot check in.\n";
    }
}

// Check out customer
void Booking::checkOut()
{
    if (status == "Checked-In")
    {
        status = "Checked-Out";
        cout << "\nCustomer checked out successfully!\n";
    }
    else
    {
        cout << "\nCustomer cannot check out.\n";
    }
}

// Get booking ID
int Booking::getBookingId() const
{
    return bookingId;
}

// Get customer ID
int Booking::getCustomerId() const
{
    return customerId;
}

// Get room number
int Booking::getRoomNumber() const
{
    return roomNumber;
}

// Get booking status
string Booking::getStatus() const
{
    return status;
}
string Booking::getCheckInDate() const
{
    return checkInDate;
}

int Booking::getNumberOfDays() const
{
    return numberOfDays;
}