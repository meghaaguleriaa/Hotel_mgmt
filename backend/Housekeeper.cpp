#include "Housekeeper.h"

// Housekeeper constructor
Housekeeper::Housekeeper(int id, string n, double s)
    : Employee(id, n, s)
{
}

// Function overriding
void Housekeeper::displayRole()
{
    cout << "\nRole : Housekeeper";

    displayEmployee();
}