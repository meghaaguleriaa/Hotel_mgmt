#include "Employee.h"

// Default constructor
Employee::Employee()
{
    employeeId = 0;
    name = "";
    salary = 0;
}

// Parameterized constructor
Employee::Employee(int id, string n, double s)
{
    employeeId = id;
    name = n;
    salary = s;
}

// Display employee details
void Employee::displayEmployee()
{
    cout << "\nEmployee ID : " << employeeId;
    cout << "\nName        : " << name;
    cout << "\nSalary      : Rs. " << salary;
}

// Destructor
Employee::~Employee()
{
    cout << "\nEmployee object destroyed.";
}