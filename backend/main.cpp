#include <iostream>
#include "Hotel.h"

using namespace std;

int main()
{
    Hotel hotel;

    int choice;

    while (true)
    {
        cout << "\n========================================";
        cout << "\n       HOTEL MANAGEMENT SYSTEM";
        cout << "\n========================================";

        cout << "\n1. Add Customer";
        cout << "\n2. Show Customers";
        cout << "\n3. Add Room";
        cout << "\n4. Show Rooms";
        cout << "\n5. Create Booking";
        cout << "\n6. Show Bookings";
        cout << "\n7. Check-in";
        cout << "\n8. Check-out";
        cout<< "\n9. Add Food Order";
        cout << "\n10. Cancel Booking";
        cout << "\n11. Add Hotel Service";
        cout << "\n12. Show Employees";
        cout << "\n13. Cancel Booking";
        cout << "\n14. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1)
        {
            hotel.addCustomer();
        }
        else if (choice == 2)
        {
            hotel.showCustomers();
        }
        else if (choice == 3)
        {
            hotel.addRoom();
        }
        else if (choice == 4)
        {
            hotel.showRooms();
        }
        else if (choice == 5)
        {
            hotel.createBooking();
        }
        else if (choice == 6)
        {
            hotel.showBookings();
        }
        else if (choice == 7)
        {
            hotel.checkInBooking();
        }
        else if (choice == 8)
        {
            hotel.checkOutBooking();
        }
        else if (choice == 9)
        {
            hotel.cancelBooking();
            
        }
        else if (choice == 10)
        {
            hotel.addFoodOrder();
            
        }
        else if (choice == 11)
        {
            hotel.addService();
            
            
        }
        else if (choice == 12)
        {
            hotel.addEmployees();
            hotel.showEmployees();

            
        }
         else if (choice == 13)
        {
            cout << "\nThank you for using Hotel Management System!\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}