
#include <iostream>
#include <string>
#include <winsock2.h>
#include <fstream>

#include "Customer.h"

using namespace std;


string getRequestBody(string request)
{
    size_t position = request.find("\r\n\r\n");

    if (position != string::npos)
    {
        return request.substr(position + 4);
    }

    return "";
}


string getValue(string body, string key)
{
    string searchKey = key + "=";

    size_t start = body.find(searchKey);

    if (start == string::npos)
    {
        return "";
    }

    start = start + searchKey.length();

    size_t end = body.find("&", start);

    if (end == string::npos)
    {
        return body.substr(start);
    }

    return body.substr(start, end - start);
}


string createResponse(string content)
{
    string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
        "Content-Length: " + to_string(content.length()) + "\r\n"
        "\r\n" +
        content;

    return response;
}


string getCustomers()
{
    ifstream file("..\\data\\customers.txt");

    if (!file.is_open())
    {
        return "";
    }

    string line;
    string result = "";

    while (getline(file, line))
    {
        result += line + "\n";
    }

    file.close();

    return result;
}


string getRooms()
{
    ifstream file("..\\data\\rooms.txt");

    if (!file.is_open())
    {
        return "";
    }

    string line;
    string result = "";

    while (getline(file, line))
    {
        result += line + "\n";
    }

    file.close();

    return result;
}


string getBookings()
{
    ifstream file("..\\data\\bookings.txt");

    if (!file.is_open())
    {
        return "";
    }

    string line;
    string result = "";

    while (getline(file, line))
    {
        result += line + "\n";
    }

    file.close();

    return result;
}

string getFoodOrders()
{
    ifstream file("..\\data\\food_orders.txt");

    if (!file.is_open())
    {
        return "";
    }

    string line;
    string result = "";

    while (getline(file, line))
    {
        result += line + "\n";
    }

    file.close();

    return result;
}


void updateRoomStatus(string roomNumber, string newStatus)
{
    ifstream file("..\\data\\rooms.txt");

    if (!file.is_open())
    {
        cout << "Could not open rooms file." << endl;
        return;
    }

    string line;
    string result = "";

    while (getline(file, line))
    {
        string currentRoom =
            line.substr(0, line.find("|"));

        if (currentRoom == roomNumber)
        {
            size_t first = line.find("|");
            size_t second = line.find("|", first + 1);

            string roomType =
                line.substr(
                    first + 1,
                    second - first - 1
                );

            size_t third = line.find("|", second + 1);

            string price =
                line.substr(
                    second + 1,
                    third - second - 1
                );

            result +=
                roomNumber + "|" +
                roomType + "|" +
                price + "|" +
                newStatus + "\n";
        }
        else
        {
            result += line + "\n";
        }
    }

    file.close();

    ofstream output("..\\data\\rooms.txt");

    if (output.is_open())
    {
        output << result;
        output.close();

        cout << "Room status updated successfully!" << endl;
    }
    else
    {
        cout << "Could not update rooms file." << endl;
    }
}


int main()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Winsock initialization failed." << endl;
        return 1;
    }


    SOCKET serverSocket =
        socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed." << endl;

        WSACleanup();

        return 1;
    }


    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);


    if (bind(
        serverSocket,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress)
    ) == SOCKET_ERROR)
    {
        cout << "Binding failed." << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }


    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        cout << "Listening failed." << endl;

        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }


    cout << "Hotel Management Server started!" << endl;
    cout << "Server running on http://localhost:8080" << endl;
    cout << "Waiting for connection..." << endl;


    while (true)
    {
        SOCKET clientSocket =
            accept(serverSocket, NULL, NULL);

        if (clientSocket == INVALID_SOCKET)
        {
            cout << "Connection failed." << endl;
            continue;
        }


        char buffer[8192] = {0};

        int received =
            recv(
                clientSocket,
                buffer,
                sizeof(buffer) - 1,
                0
            );


        if (received > 0)
        {
            string request(buffer);

            cout << "\nRequest received from frontend."
                 << endl;


            if (request.find("OPTIONS") == 0)
            {
                string response =
                    "HTTP/1.1 200 OK\r\n"
                    "Access-Control-Allow-Origin: *\r\n"
                    "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                    "Access-Control-Allow-Headers: Content-Type\r\n"
                    "Content-Length: 0\r\n"
                    "\r\n";

                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }


            else if (request.find("GET /customers") == 0)
            {
                string customers =
                    getCustomers();

                string response =
                    createResponse(customers);

                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }


            else if (request.find("POST /add-customer") == 0)
            {
                string body =
                    getRequestBody(request);

                string id =
                    getValue(body, "id");

                string name =
                    getValue(body, "name");

                string phone =
                    getValue(body, "phone");

                string email =
                    getValue(body, "email");

                string address =
                    getValue(body, "address");

                string proof =
                    getValue(body, "proof");


                cout << "\nCustomer received:" << endl;

                cout << "ID      : "
                     << id << endl;

                cout << "Name    : "
                     << name << endl;

                cout << "Phone   : "
                     << phone << endl;

                cout << "Email   : "
                     << email << endl;

                cout << "Address : "
                     << address << endl;

                cout << "Proof   : "
                     << proof << endl;


                ofstream file(
                    "..\\data\\customers.txt",
                    ios::app
                );


                if (file.is_open())
                {
                    file << id << "|"
                         << name << "|"
                         << phone << "|"
                         << email << "|"
                         << address << "|"
                         << proof << endl;

                    file.close();

                    cout <<
                        "Customer saved to file successfully!"
                        << endl;
                }
                else
                {
                    cout <<
                        "Could not open customer file."
                        << endl;
                }


                string response =
                    createResponse(
                        "Customer received by C++ server!"
                    );


                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }


            else if (request.find("POST /add-room") == 0)
            {
                string body =
                    getRequestBody(request);

                string roomNumber =
                    getValue(body, "roomNumber");

                string roomType =
                    getValue(body, "roomType");

                string price =
                    getValue(body, "price");


                cout << "\nRoom received:" << endl;

                cout << "Room Number : "
                     << roomNumber << endl;

                cout << "Room Type   : "
                     << roomType << endl;

                cout << "Price       : "
                     << price << endl;


                ofstream file(
                    "..\\data\\rooms.txt",
                    ios::app
                );


                if (file.is_open())
                {
                    file << roomNumber << "|"
                         << roomType << "|"
                         << price << "|"
                         << "Available"
                         << endl;

                    file.close();

                    cout <<
                        "Room saved to file successfully!"
                        << endl;
                }
                else
                {
                    cout <<
                        "Could not open room file."
                        << endl;
                }


                string response =
                    createResponse(
                        "Room received by C++ server!"
                    );


                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }


            else if (request.find("GET /rooms") == 0)
            {
                string rooms =
                    getRooms();

                string response =
                    createResponse(rooms);

                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }


            else if (request.find("GET /bookings") == 0)
            {
                string bookings =
                    getBookings();

                string response =
                    createResponse(bookings);

                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }
                else if (request.find("GET /food-orders") != string::npos)
                {
                    string foodOrders =
                        getFoodOrders();

                    string response =
                        createResponse(foodOrders);

                    send(
                        clientSocket,
                        response.c_str(),
                        response.length(),
                        0
                    );
                }



            else if (request.find("POST /add-booking") == 0)
            {
                string body =
                    getRequestBody(request);

                string bookingId =
                    getValue(body, "bookingId");

                string customerId =
                    getValue(body, "customerId");

                string roomNumber =
                    getValue(body, "roomNumber");

                string checkInDate =
                    getValue(body, "checkInDate");

                string days =
                    getValue(body, "days");


                cout << "\nBooking received:" << endl;

                cout << "Booking ID   : "
                     << bookingId << endl;

                cout << "Customer ID  : "
                     << customerId << endl;

                cout << "Room Number  : "
                     << roomNumber << endl;

                cout << "Check-in     : "
                     << checkInDate << endl;

                cout << "Days         : "
                     << days << endl;


                ofstream file(
                    "..\\data\\bookings.txt",
                    ios::app
                );


                if (file.is_open())
                {
                    file << bookingId << "|"
                         << customerId << "|"
                         << roomNumber << "|"
                         << checkInDate << "|"
                         << days << "|"
                         << "Booked"
                         << endl;

                    file.close();

                    cout <<
                        "Booking saved to file successfully!"
                        << endl;

                    updateRoomStatus(
                        roomNumber,
                        "Booked"
                    );
                }
                else
                {
                    cout <<
                        "Could not open booking file."
                        << endl;
                }


                string response =
                    createResponse(
                        "Booking received by C++ server!"
                    );


                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }
      
else if (request.find("POST /add-food-order") != string::npos){
    string body =
        getRequestBody(request);


    string orderId =
        getValue(body, "orderId");

    string customerId =
        getValue(body, "customerId");

    string roomNumber =
        getValue(body, "roomNumber");

    string foodItem =
        getValue(body, "foodItem");

    string quantity =
        getValue(body, "quantity");

    string price =
        getValue(body, "price");

    string total =
        getValue(body, "total");


    cout << "\nFood order received:" << endl;

    cout << "Order ID    : "
         << orderId << endl;

    cout << "Customer ID : "
         << customerId << endl;

    cout << "Room Number : "
         << roomNumber << endl;

    cout << "Food Item   : "
         << foodItem << endl;

    cout << "Quantity    : "
         << quantity << endl;

    cout << "Price       : "
         << price << endl;

    cout << "Total       : "
         << total << endl;


    ofstream file(
        "..\\data\\food_orders.txt",
        ios::app
    );


    if (file.is_open())
    {
        file << orderId << "|"
             << customerId << "|"
             << roomNumber << "|"
             << foodItem << "|"
             << quantity << "|"
             << price << "|"
             << total
             << endl;

        file.close();

        cout <<
            "Food order saved to file successfully!"
            << endl;
    }
    else
    {
        cout <<
            "Could not open food orders file."
            << endl;
    }


    string response =
        createResponse(
            "Food order received by C++ server!"
        );


    send(
        clientSocket,
        response.c_str(),
        response.length(),
        0
    );
}
else if (request.find("POST /add-service") != string::npos)
{
    string body =
        getRequestBody(request);

    string serviceId =
        getValue(body, "serviceId");

    string customerId =
        getValue(body, "customerId");

    string roomNumber =
        getValue(body, "roomNumber");

    string serviceName =
        getValue(body, "serviceName");

    string quantity =
        getValue(body, "quantity");

    string price =
        getValue(body, "price");

    string total =
        getValue(body, "total");


    cout << "\nService received:" << endl;

    cout << "Service ID  : "
         << serviceId << endl;

    cout << "Customer ID : "
         << customerId << endl;

    cout << "Room Number : "
         << roomNumber << endl;

    cout << "Service     : "
         << serviceName << endl;

    cout << "Quantity    : "
         << quantity << endl;

    cout << "Price       : "
         << price << endl;

    cout << "Total       : "
         << total << endl;


    ofstream file(
        "..\\data\\services.txt",
        ios::app
    );


    if (file.is_open())
    {
        file << serviceId << "|"
             << customerId << "|"
             << roomNumber << "|"
             << serviceName << "|"
             << quantity << "|"
             << price << "|"
             << total
             << endl;

        file.close();

        cout <<
            "Service saved to file successfully!"
            << endl;
    }
    else
    {
        cout <<
            "Could not open services file."
            << endl;
    }


    string response =
        createResponse(
            "Service received by C++ server!"
        );


    send(
        clientSocket,
        response.c_str(),
        response.length(),
        0
    );
}
 

            else if (request.find("POST /add-bill") == 0)
            {
                string body =
                    getRequestBody(request);


                string billId =
                    getValue(body, "billId");

                string customerId =
                    getValue(body, "customerId");

                string bookingId =
                    getValue(body, "bookingId");

                string roomCharges =
                    getValue(body, "roomCharges");

                string foodCharges =
                    getValue(body, "foodCharges");

                string serviceCharges =
                    getValue(body, "serviceCharges");

                string total =
                    getValue(body, "total");


                cout << "\nBill received:" << endl;

                cout << "Bill ID        : "
                     << billId << endl;

                cout << "Customer ID    : "
                     << customerId << endl;

                cout << "Booking ID     : "
                     << bookingId << endl;

                cout << "Room Charges   : "
                     << roomCharges << endl;

                cout << "Food Charges   : "
                     << foodCharges << endl;

                cout << "Service Charges: "
                     << serviceCharges << endl;

                cout << "Total          : "
                     << total << endl;


                ofstream file(
                    "..\\data\\bills.txt",
                    ios::app
                );


                if (file.is_open())
                {
                    file << billId << "|"
                         << customerId << "|"
                         << bookingId << "|"
                         << roomCharges << "|"
                         << foodCharges << "|"
                         << serviceCharges << "|"
                         << total
                         << endl;

                    file.close();

                    cout <<
                        "Bill saved to file successfully!"
                        << endl;
                }
                else
                {
                    cout <<
                        "Could not open bills file."
                        << endl;
                }


                string response =
                    createResponse(
                        "Bill received by C++ server!"
                    );


                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }


            else
            {
                string response =
                    createResponse(
                        "Hotel server is working!"
                    );


                send(
                    clientSocket,
                    response.c_str(),
                    response.length(),
                    0
                );
            }
        }


        closesocket(clientSocket);
    }


    closesocket(serverSocket);

    WSACleanup();

    return 0;
}