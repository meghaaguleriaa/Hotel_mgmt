#include "Hotel.h"
#include "Manager.h"
#include "Receptionist.h"
#include "Housekeeper.h"
#include <fstream>
#include "HotelException.h"
// Constructor
Hotel::Hotel()
{
    cout << "\nHotel Management System Started.\n";

    loadCustomers();
    loadRooms();
    loadBookings();
    loadBills();
}

// Add customer
void Hotel::addCustomer()
{
    Customer customer;

    customer.addCustomer();

    customers.push_back(customer);

    recentActivities.push("New customer added.");
}

// Display customers
void Hotel::showCustomers()
{
    if (customers.empty())
    {
        cout << "\nNo customers found.\n";
        return;
    }

    cout << "\n========== CUSTOMER LIST ==========\n";

    vector<Customer>::iterator it;

    for (it = customers.begin(); it != customers.end(); ++it)
    {
        it->displayCustomer();
    }
}

// Add room
void Hotel::addRoom()
{
    int number;
    string type;
    double price;

    cout << "\nEnter Room Number: ";
    cin >> number;

    cin.ignore();

    cout << "Enter Room Type: ";
    getline(cin, type);

    cout << "Enter Price per Night: ";
    cin >> price;

    Room room(number, type, price);

    rooms.push_back(room);

    // Add room to map
    roomMap[number] = room;

    saveRooms();

    recentActivities.push("New room added.");

    cout << "\nRoom added successfully!\n";
}

// Display rooms
void Hotel::showRooms()
{
    if (rooms.empty())
    {
        cout << "\nNo rooms found.\n";
        return;
    }

    cout << "\n========== ROOM LIST ==========\n";

    vector<Room>::iterator it;

    for (it = rooms.begin(); it != rooms.end(); ++it)
    {
        it->displayRoom();
    }
}

// Create booking
void Hotel::createBooking()
{
    try
    {
        Booking booking;

        booking.createBooking();

        if (booking.getNumberOfDays() <= 0)
        {
            throw HotelException("Number of days must be greater than 0.");
        }

        bool roomFound = false;

        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms[i].getRoomNumber() == booking.getRoomNumber())
            {
                roomFound = true;

                if (rooms[i].isAvailable())
                {
                    rooms[i].updateStatus("Booked");

                    bookings.push_back(booking);

                    saveBookings();
                    saveRooms();

                    recentActivities.push("New booking created.");

                    cout << "\nBooking successful!";
                }
                else
                {
                    throw HotelException("Room is already booked.");
                }

                break;
            }
        }

        if (!roomFound)
        {
            throw HotelException("Room not found.");
        }
    }
    catch (HotelException& e)
    {
        e.displayMessage();
    }
}

// Display bookings
void Hotel::showBookings()
{
    if (bookings.empty())
    {
        cout << "\nNo bookings found.\n";
        return;
    }

    cout << "\n========== BOOKING LIST ==========\n";

    vector<Booking>::iterator it;

    for (it = bookings.begin(); it != bookings.end(); ++it)
    {
        it->displayBooking();
    }
}

// Check-in booking
void Hotel::checkInBooking()
{
    int bookingId;

    cout << "\nEnter Booking ID for check-in: ";
    cin >> bookingId;

    bool found = false;

    for (int i = 0; i < bookings.size(); i++)
    {
        if (bookings[i].getBookingId() == bookingId)
        {
            found = true;

            if (bookings[i].getStatus() == "Booked")
            {
                bookings[i].checkIn();

                saveBookings();

                cout << "\nCheck-in completed successfully.\n";
            }
            else
            {
                cout << "\nCustomer cannot check in for this booking.\n";
            }

            break;
        }
    }

    if (!found)
    {
        cout << "\nBooking not found.\n";
    }
}

// Check-out booking
void Hotel::checkOutBooking()
{
    int bookingId;

    cout << "\nEnter Booking ID for check-out: ";
    cin >> bookingId;

    bool found = false;

    for (int i = 0; i < bookings.size(); i++)
    {
        if (bookings[i].getBookingId() == bookingId)
        {
            found = true;

            if (bookings[i].getStatus() == "Checked-In")
            {
                int roomNumber = bookings[i].getRoomNumber();

                bookings[i].checkOut();

                // Generate final bill
                generateBill(i);

                // Make the room available again
                for (int j = 0; j < rooms.size(); j++)
                {
                    if (rooms[j].getRoomNumber() == roomNumber)
                    {
                        rooms[j].updateStatus("Available");
                        break;
                    }
                }

                saveBookings();
                saveRooms();

                recentActivities.push("Customer checked out.");

                cout << "\nCheck-out completed successfully.\n";
                cout << "Room " << roomNumber << " is now available.\n";
            }
            else
            {
                cout << "\nCustomer cannot check out for this booking.\n";
            }

            break;
        }
    }

    if (!found)
    {
        cout << "\nBooking not found.\n";
    }
}
void Hotel::cancelBooking()
{
    int bookingId;

    cout << "\nEnter Booking ID to cancel: ";
    cin >> bookingId;

    bool found = false;

    for (int i = 0; i < bookings.size(); i++)
    {
        if (bookings[i].getBookingId() == bookingId)
        {
            found = true;

            if (bookings[i].getStatus() == "Booked")
            {
                int roomNumber = bookings[i].getRoomNumber();

                bookings[i].cancelBooking();

                // Make room available again
                for (int j = 0; j < rooms.size(); j++)
                {
                    if (rooms[j].getRoomNumber() == roomNumber)
                    {
                        rooms[j].updateStatus("Available");
                        break;
                    }
                }

                saveBookings();
                saveRooms();

                recentActivities.push("Booking cancelled.");

                cout << "\nBooking cancelled successfully.\n";
                cout << "Room " << roomNumber << " is now available.\n";
            }
            else
            {
                cout << "\nThis booking cannot be cancelled.\n";
            }

            break;
        }
    }

    if (!found)
    {
        cout << "\nBooking not found.\n";
    }
}


// Generate bill
void Hotel::generateBill(int bookingIndex)
{
    int roomNumber = bookings[bookingIndex].getRoomNumber();
    int numberOfDays = bookings[bookingIndex].getNumberOfDays();
    int customerId = bookings[bookingIndex].getCustomerId();

    double roomPrice = 0;
    double foodCharges = 0;
    double serviceCharges = 0;

    // Find room price
    for (int i = 0; i < rooms.size(); i++)
    {
        if (rooms[i].getRoomNumber() == roomNumber)
        {
            roomPrice = rooms[i].getPrice();
            break;
        }
    }

    // Calculate room charges
    double roomCharges = roomPrice * numberOfDays;

    // Calculate food charges for this customer
    for (int i = 0; i < foodOrders.size(); i++)
    {
        if (foodOrders[i].getCustomerId() == customerId)
        {
            foodCharges += foodOrders[i].calculateTotal();
        }
    }

    // Calculate service charges for this customer
    list<Service>::iterator it;

    for (it = services.begin(); it != services.end(); ++it)
    {
        if (it->getCustomerId() == customerId)
        {
            serviceCharges += it->calculateTotal();
        }
    }

    Bill bill;

    bill.setBillId(bills.size() + 1);
    bill.setCustomerId(customerId);
    bill.setRoomCharges(roomCharges);

    // Add food and service charges
    bill.calculateBill(foodCharges, serviceCharges);

    bills.push_back(bill);

    saveBills();
    cout << "\n========== FINAL BILL ==========\n";

    bill.displayBill();

    cout << "\nBill generated successfully.\n";
}

// Add food order
void Hotel::addFoodOrder()
{
    FoodOrder order;

    order.addFood();

    foodOrders.push_back(order);

    recentActivities.push("Food order added.");
}

// Add hotel service
void Hotel::addService()
{
    Service service;

    service.addService();

    services.push_back(service);

    recentActivities.push("Hotel service added.");
}

// Compare rooms by price
bool compareRoomPrice(Room a, Room b)
{
    return a.getPrice() < b.getPrice();
}

// Add employees
void Hotel::addEmployees()
{
    // Dynamic objects

    Employee* manager =
        new Manager(
            101,
            "Rahul",
            50000,
            "Administration"
        );

    Employee* receptionist =
        new Receptionist(
            102,
            "Priya",
            30000
        );

    Employee* housekeeper =
        new Housekeeper(
            103,
            "Aman",
            25000
        );

    employees.push_back(manager);
    employees.push_back(receptionist);
    employees.push_back(housekeeper);

    cout << "\nEmployees added successfully.\n";
}

// Display employees
void Hotel::showEmployees()
{
    if (employees.empty())
    {
        cout << "\nNo employees found.\n";
        return;
    }

    cout << "\n========== EMPLOYEE LIST ==========\n";

    vector<Employee*>::iterator it;

    for (it = employees.begin(); it != employees.end(); ++it)
    {
        (*it)->displayRole();
        cout << "\n";
    }
}

// Display recent activities
void Hotel::showRecentActivity()
{
    if (recentActivities.empty())
    {
        cout << "\nNo recent activities.\n";
        return;
    }

    cout << "\n========== RECENT ACTIVITIES ==========\n";

    stack<string> temp = recentActivities;

    while (!temp.empty())
    {
        cout << "- " << temp.top() << endl;
        temp.pop();
    }
}

// Destructor
Hotel::~Hotel()
{
    for (int i = 0; i < employees.size(); i++)
    {
        delete employees[i];
    }

    cout << "\nHotel object destroyed.\n";
}

// Save customers
void Hotel::saveCustomers()
{
    ofstream file("..\\data\\customers.txt");

    if (!file)
    {
        cout << "\nUnable to open customer file.\n";
        return;
    }

    vector<Customer>::iterator it;

    for (it = customers.begin(); it != customers.end(); ++it)
    {
        file << it->getCustomerId() << "|"
             << it->getName() << "|"
             << it->getPhone() << "|"
             << it->getEmail() << "|"
             << it->getAddress() << "|"
             << it->getIdProof() << endl;
    }

    file.close();

    cout << "\nCustomer data saved successfully.\n";
}

// Save rooms
void Hotel::saveRooms()
{
    ofstream file("..\\data\\rooms.txt");

    if (!file)
    {
        cout << "\nUnable to open room file.\n";
        return;
    }

    vector<Room>::iterator it;

    for (it = rooms.begin(); it != rooms.end(); ++it)
    {
        file << it->getRoomNumber() << "|"
             << it->getRoomType() << "|"
             << it->getPrice() << "|"
             << it->getStatus() << endl;
    }

    file.close();

    cout << "\nRoom data saved successfully.\n";
}

void Hotel::saveBills()
{
    ofstream file("..\\data\\bills.txt");

    if (!file)
    {
        cout << "\nUnable to open bill file.\n";
        return;
    }

    vector<Bill>::iterator it;

    for (it = bills.begin(); it != bills.end(); ++it)
    {
        file << it->getTotal() << endl;
    }

    file.close();

    cout << "\nBill data saved successfully.\n";
}

// Load rooms
void Hotel::loadRooms()
{
    ifstream file("..\\data\\rooms.txt");

    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string data[4];

        size_t position = 0;
        int index = 0;

        while ((position = line.find('|')) != string::npos)
        {
            data[index] = line.substr(0, position);
            line.erase(0, position + 1);
            index++;
        }

        data[index] = line;

        int number = stoi(data[0]);
        string type = data[1];
        double price = stod(data[2]);
        string status = data[3];

        Room room(number, type, price);

        room.updateStatus(status);

        rooms.push_back(room);

        roomMap[number] = room;
    }

    file.close();

    cout << "\nRoom data loaded successfully.\n";
}

// Load customers
void Hotel::loadCustomers()
{
    ifstream file("..\\data\\customers.txt");

    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        int id;
        string name;
        string phone;
        string email;
        string address;
        string idProof;

        size_t position = 0;
        string data[6];
        int index = 0;

        while ((position = line.find('|')) != string::npos)
        {
            data[index] = line.substr(0, position);
            line.erase(0, position + 1);
            index++;
        }

        data[index] = line;

        id = stoi(data[0]);
        name = data[1];
        phone = data[2];
        email = data[3];
        address = data[4];
        idProof = data[5];

        Customer customer(
            id,
            name,
            phone,
            email,
            address,
            idProof
        );

        customers.push_back(customer);
    }

    file.close();

    cout << "\nCustomer data loaded successfully.\n";
}

// Save bookings
void Hotel::saveBookings()
{
    ofstream file("..\\data\\bookings.txt");

    if (!file)
    {
        cout << "\nUnable to open booking file.\n";
        return;
    }

    vector<Booking>::iterator it;

    for (it = bookings.begin(); it != bookings.end(); ++it)
    {
        file << it->getBookingId() << "|"
             << it->getCustomerId() << "|"
             << it->getRoomNumber() << "|"
             << it->getCheckInDate() << "|"
             << it->getNumberOfDays() << "|"
             << it->getStatus() << endl;
    }

    file.close();

    cout << "\nBooking data saved successfully.\n";
}

// Load bookings
void Hotel::loadBookings()
{
    ifstream file("..\\data\\bookings.txt");

    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        string data[6];

        size_t position = 0;
        int index = 0;

        while ((position = line.find('|')) != string::npos)
        {
            data[index] = line.substr(0, position);
            line.erase(0, position + 1);
            index++;
        }

        data[index] = line;

        int bookingId = stoi(data[0]);
        int customerId = stoi(data[1]);
        int roomNumber = stoi(data[2]);
        string checkInDate = data[3];
        int numberOfDays = stoi(data[4]);
        string status = data[5];

        Booking booking(
            bookingId,
            customerId,
            roomNumber,
            checkInDate,
            numberOfDays
        );

        if (status == "Checked-In")
        {
            booking.checkIn();
        }
        else if (status == "Checked-Out")
        {
            booking.checkIn();
            booking.checkOut();
        }
        else if (status == "Cancelled")
        {
            booking.cancelBooking();
        }

        bookings.push_back(booking);
    }

    file.close();

    cout << "\nBooking data loaded successfully.\n";
}