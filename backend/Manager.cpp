#include "Manager.h"

// Department constructor
Department::Department(string dept)
{
    departmentName = dept;
}

// Manager constructor
Manager::Manager(int id, string n, double s, string dept)
    : Employee(id, n, s), Department(dept)
{
}

// Function overriding
void Manager::displayRole()
{
    cout << "\nRole       : Manager";
    cout << "\nDepartment : " << departmentName;

    displayEmployee();
}