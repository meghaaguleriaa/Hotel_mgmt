#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <algorithm>

#include "Customer.h"
#include "Room.h"
#include "Booking.h"
#include "FoodOrder.h"
#include "Service.h"
#include "Bill.h"
#include "Employee.h"

using namespace std;
class HotelManager;
class Hotel
{
private:
    // STL containers
    vector<Customer> customers;
    vector<Room> rooms;
    vector<Booking> bookings;
    vector<FoodOrder> foodOrders;
    list<Service> services;
    vector<Bill> bills;

    // Map for quick room lookup
    map<int, Room> roomMap;

    // Stack for recent activities
    stack<string> recentActivities;

    // Employee pointers for runtime polymorphism
    vector<Employee*> employees;
    friend class HotelManager;
    
public:
    void saveCustomers();
    void loadCustomers();
    void saveRooms();
    void loadRooms();
    void saveBookings();
    void loadBookings();
    void saveBills();
    void loadBills();
    // Constructor
    Hotel();

    // Customer functions
    void addCustomer();
    void showCustomers();

    // Room functions
    void addRoom();
    void showRooms();
    void sortRoomsByPrice();

    // Booking functions
    void createBooking();
    void showBookings();
    void checkInBooking();
    void checkOutBooking();
    void cancelBooking();
    void generateBill(int bookingIndex);
    
    // Food functions
    void addFoodOrder();

    // Service functions
    void addService();

    // Employee functions
    void addEmployees();
    void showEmployees();

    // Activity functions
    void showRecentActivity();

    // Destructor
    ~Hotel();
};

#endif