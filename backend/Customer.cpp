#include "Customer.h"

// Default constructor
Customer::Customer()
{
    customerId = 0;
    name = "";
    phone = "";
    email = "";
    address = "";
    idProof = "";
}
Customer::Customer(const Customer& other)
{
    customerId = other.customerId;
    name = other.name;
    phone = other.phone;
    email = other.email;
    address = other.address;
    idProof = other.idProof;
}

// Parameterized constructor
Customer::Customer(int id, string n, string p, string e,
                   string a, string proof)
{
    customerId = id;
    name = n;
    phone = p;
    email = e;
    address = a;
    idProof = proof;
}

// Add customer
void Customer::addCustomer()
{
    cout << "\nEnter Customer ID: ";
    cin >> customerId;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Invalid Customer ID. Please enter a number: ";
        cin >> customerId;
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Phone: ";
    getline(cin, phone);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter ID Proof: ";
    getline(cin, idProof);

    cout << "\nCustomer added successfully!\n";
}


// Display customer
void Customer::displayCustomer() const
{
    cout << "\n-----------------------------";
    cout << "\nCustomer ID : " << customerId;
    cout << "\nName        : " << name;
    cout << "\nPhone       : " << phone;
    cout << "\nEmail       : " << email;
    cout << "\nAddress     : " << address;
    cout << "\nID Proof    : " << idProof;
    cout << "\n-----------------------------\n";
}

// Update customer
void Customer::updateCustomer()
{
    cin.ignore();

    cout << "\nEnter new name: ";
    getline(cin, name);

    cout << "Enter new phone: ";
    getline(cin, phone);

    cout << "Enter new email: ";
    getline(cin, email);

    cout << "Enter new address: ";
    getline(cin, address);

    cout << "Enter new ID proof: ";
    getline(cin, idProof);

    cout << "\nCustomer details updated successfully!\n";
}

// Getter
int Customer::getCustomerId() const
{
    return customerId;
}
string Customer::getName() const
{
    return name;
}

string Customer::getPhone() const
{
    return phone;
}

string Customer::getEmail() const
{
    return email;
}

string Customer::getAddress() const
{
    return address;
}

string Customer::getIdProof() const
{
    return idProof;
}
// << operator
ostream& operator<<(ostream& out, const Customer& c)
{
    out << c.customerId << " "
        << c.name << " "
        << c.phone << " "
        << c.email << " "
        << c.address << " "
        << c.idProof;

    return out;
}

// >> operator
istream& operator>>(istream& in, Customer& c)
{
    in >> c.customerId;
    in >> c.name;
    in >> c.phone;
    in >> c.email;
    in >> c.address;
    in >> c.idProof;

    return in;
}