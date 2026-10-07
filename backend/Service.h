#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>
using namespace std;

class Service
{
private:
    int serviceId;
    int customerId;
    string serviceName;
    double price;
    int quantity;

public:
    Service();
    Service(int id, int cid, string name, double p, int qty = 1);

    void addService();
    void displayService() const;
    double calculateTotal() const;

    int getServiceId() const;
    int getCustomerId() const;
    string getServiceName() const;
};

#endif