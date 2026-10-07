#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "Employee.h"

class Receptionist : public Employee
{
public:
    Receptionist(int id, string n, double s);

    void displayRole() override;
};

#endif