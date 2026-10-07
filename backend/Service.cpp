#include "Service.h"

Service::Service()
{
    serviceId = 0;
    customerId = 0;
    serviceName = "";
    price = 0;
    quantity = 1;
}

Service::Service(int id, int cid, string name, double p, int qty)
{
    serviceId = id;
    customerId = cid;
    serviceName = name;
    price = p;
    quantity = qty;
}

void Service::addService()
{
    cout << "\nEnter Service ID: ";
    cin >> serviceId;

    cout << "Enter Customer ID: ";
    cin >> customerId;

    cin.ignore();

    cout << "Enter Service Name: ";
    getline(cin, serviceName);

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Quantity: ";
    cin >> quantity;

    cout << "\nService added successfully!\n";
}

void Service::displayService() const
{
    cout << "\n-----------------------------";
    cout << "\nService ID   : " << serviceId;
    cout << "\nCustomer ID  : " << customerId;
    cout << "\nService Name : " << serviceName;
    cout << "\nPrice        : Rs. " << price;
    cout << "\nQuantity     : " << quantity;
    cout << "\nTotal        : Rs. " << calculateTotal();
    cout << "\n-----------------------------\n";
}

double Service::calculateTotal() const
{
    return price * quantity;
}

int Service::getServiceId() const
{
    return serviceId;
}

int Service::getCustomerId() const
{
    return customerId;
}

string Service::getServiceName() const
{
    return serviceName;
}