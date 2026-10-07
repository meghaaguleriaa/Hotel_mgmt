#ifndef HOTELEXCEPTION_H
#define HOTELEXCEPTION_H

#include <iostream>
#include <string>
using namespace std;

class HotelException
{
private:
    string message;

public:
    HotelException(string msg)
    {
        message = msg;
    }

    void displayMessage()
    {
        cout << "\nError: " << message << endl;
    }
};

#endif