#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
using namespace std;

// Function template
template <class T>
void displayValue(T value)
{
    cout << "Value: " << value << endl;
}

// Function template for finding an item
template <class T>
bool findValue(vector<T> values, T target)
{
    for (int i = 0; i < values.size(); i++)
    {
        if (values[i] == target)
        {
            return true;
        }
    }

    return false;
}


// Class template
template <class T>
class HotelCollection
{
private:
    vector<T> items;

public:
    void addItem(T item)
    {
        items.push_back(item);
    }

    void displayItems()
    {
        for (int i = 0; i < items.size(); i++)
        {
            cout << items[i] << endl;
        }
    }

    int getSize()
    {
        return items.size();
    }
};

#endif