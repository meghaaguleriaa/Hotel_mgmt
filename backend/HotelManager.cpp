#include "HotelManager.h"

void HotelManager::showHotelData(Hotel& hotel)
{
    cout << "\nTotal Customers: "
         << hotel.customers.size();

    cout << "\nTotal Rooms: "
         << hotel.rooms.size();

    cout << "\nTotal Bookings: "
         << hotel.bookings.size();

    cout << endl;
}