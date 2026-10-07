#ifndef HOUSEKEEPER_H
#define HOUSEKEEPER_H

#include "Employee.h"

class Housekeeper : public Employee
{
public:
    Housekeeper(int id, string n, double s);

    void displayRole() override;
};

#endif