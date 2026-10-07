#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
using namespace std;

class Employee
{
protected:
    int employeeId;
    string name;
    double salary;

public:
    // Constructors
    Employee();
    Employee(int id, string n, double s);

    // Pure virtual function
    virtual void displayRole() = 0;

    // Virtual function
    virtual void displayEmployee();

    // Virtual destructor
    virtual ~Employee();
};

#endif