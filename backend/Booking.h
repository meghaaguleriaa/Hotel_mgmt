#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <string>
using namespace std;

class Booking
{
private:
    int bookingId;
    int customerId;
    int roomNumber;
    string checkInDate;
    int numberOfDays;
    string status;

public:
    // Constructors
    Booking();
    Booking(int bid, int cid, int room, string date, int days);

    // Member functions
    void createBooking();
    void displayBooking() const;
    void cancelBooking();
    void checkIn();
    void checkOut();

    // Getters
    int getBookingId() const;
    int getCustomerId() const;
    int getRoomNumber() const;
    string getStatus() const;
    string getCheckInDate() const;
    int getNumberOfDays() const;
};

#endif