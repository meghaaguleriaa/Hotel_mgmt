#include "Receptionist.h"

// Receptionist constructor
Receptionist::Receptionist(int id, string n, double s)
    : Employee(id, n, s)
{
}

// Function overriding
void Receptionist::displayRole()
{
    cout << "\nRole : Receptionist";

    displayEmployee();
}