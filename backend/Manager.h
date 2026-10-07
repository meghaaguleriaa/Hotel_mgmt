#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

// Second base class
class Department
{
protected:
    string departmentName;

public:
    Department(string dept);
};

class Manager : public Employee, public Department
{
public:
    Manager(int id, string n, double s, string dept);

    void displayRole() override;
};

#endif