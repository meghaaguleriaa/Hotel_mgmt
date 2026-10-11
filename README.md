# Hotel Management System

A C++ based Hotel Management System with a web frontend designed to simplify hotel operations. The system allows users to manage customers, rooms, bookings, food orders, hotel services, and billing through a simple web interface.

## About the Project

The Hotel Management System is a college project developed to demonstrate Object-Oriented Programming (OOP), file handling, and communication between a web frontend and a C++ backend.

The frontend provides an interface for users to interact with the system, while the C++ backend processes requests and stores records in text files.

## Features

* **Customer Management:** Add and manage customer information.
* **Room Management:** Add rooms and view room details, prices, and availability.
* **Booking Management:** Create bookings and view reservation details.
* **Food Order Management:** Record food orders and calculate their total cost.
* **Hotel Services:** Record additional hotel services and their charges.
* **Billing System:** Generate bills using room charges, food charges, and service charges.
* **File Handling:** Store and retrieve records using text files.
* **Web Interface:** Interact with the system through an HTML, CSS, and JavaScript frontend.

## Technologies Used

| Technology     | Purpose                                          |
| -------------- | ------------------------------------------------ |
| C++            | Backend logic and request processing             |
| HTML           | Frontend structure                               |
| CSS            | Frontend styling                                 |
| JavaScript     | Form handling and communication with the backend |
| Winsock        | HTTP server and frontend-backend communication   |
| File Handling  | Persistent storage using `.txt` files            |
| Git and GitHub | Version control and source code management       |

## Project Structure

```text
HotelMgmt/
│
├── backend/
│   ├── main.cpp
│   ├── server.cpp
│   ├── Customer.cpp
│   ├── Customer.h
│   ├── Room.cpp
│   ├── Room.h
│   ├── Booking.cpp
│   ├── Booking.h
│   ├── FoodOrder.cpp
│   ├── FoodOrder.h
│   ├── Service.cpp
│   ├── Service.h
│   ├── Bill.cpp
│   ├── Bill.h
│   ├── Employee.cpp
│   ├── Employee.h
│   ├── Manager.cpp
│   ├── Manager.h
│   ├── Receptionist.cpp
│   ├── Receptionist.h
│   ├── Housekeeper.cpp
│   ├── Housekeeper.h
│   ├── Hotel.cpp
│   ├── Hotel.h
│   ├── HotelManager.cpp
│   ├── HotelManager.h
│   ├── Utilities.h
│   ├── HotelException.h
│   └── README.md
│
├── frontend/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
├── data/
│   ├── customers.txt
│   ├── rooms.txt
│   ├── bookings.txt
│   ├── food_orders.txt
│   ├── services.txt
│   └── bills.txt
│
└── .gitignore
```

## Prerequisites

Before running the project, make sure you have:

* Windows operating system
* A C++ compiler such as MinGW GCC
* Python installed
* A modern web browser

## How to Run the Project

### 1. Clone the Repository

Open PowerShell or a terminal and run:

```bash
git clone https://github.com/meghaaguleriaa/Hotel_mgmt.git
```

Navigate to the project directory:

```bash
cd Hotel_mgmt
```

### 2. Compile the C++ Server

Navigate to the backend folder:

```powershell
cd backend
```

Compile the server using:

```powershell
g++ server.cpp Customer.cpp Room.cpp -o server.exe -lws2_32
```

### 3. Start the C++ Server

Run:

```powershell
.\server.exe
```

The server should start on:

```text
http://localhost:8080
```

Keep this terminal open while using the application.

### 4. Start the Frontend

Open a **second terminal** and navigate to the frontend folder:

```powershell
cd frontend
```

Start a local Python HTTP server:

```powershell
python -m http.server 5500
```

### 5. Open the Application

Open your browser and visit:

```text
http://localhost:5500
```

You can now access the Hotel Management System through the web interface.

## How It Works

The project uses a simple client-server architecture.

1. The user enters information through the web interface.
2. JavaScript collects the form data.
3. The frontend sends an HTTP request to the C++ server.
4. The C++ server processes the request using Winsock.
5. The backend reads or updates the appropriate text file.
6. The server sends a response to the frontend.
7. The frontend displays the relevant information.

## Data Storage

The project uses text files for persistent storage instead of a database.

Records are stored in pipe-separated format (`|`). For example:

```text
101|Megha|9876543210|megha@example.com|Pune|Aadhar
```

The C++ backend uses file handling operations to read and write records.

## Object-Oriented Programming Concepts

The project demonstrates key C++ concepts, including:

* **Classes and Objects:** Represent hotel entities such as customers, rooms, bookings, and bills.
* **Encapsulation:** Organize data and related operations within classes.
* **Inheritance:** Model employee roles using base and derived classes.
* **Constructors:** Initialize objects.
* **File Handling:** Store and retrieve information using files.
* **Exception Handling:** Handle exceptional situations using the project's exception-related code.

## Learning Outcomes

Through this project, we gained practical experience in:

* Applying Object-Oriented Programming concepts in C++.
* Implementing file handling for persistent data storage.
* Developing a web interface using HTML, CSS, and JavaScript.
* Connecting a frontend to a C++ backend.
* Handling HTTP requests using Winsock.
* Organizing a multi-file C++ project.
* Using Git and GitHub for version control.

## Future Improvements

* Integrate a database such as MySQL or PostgreSQL.
* Add user authentication and role-based access.
* Improve booking cancellation and room availability updates.
* Add enhanced validation and error handling.
* Improve billing and service management.

## Repository

GitHub: https://github.com/meghaaguleriaa/Hotel_mgmt

## Conclusion

The Hotel Management System demonstrates how C++, Object-Oriented Programming, file handling, and web technologies can work together to manage common hotel operations. It provides a practical foundation for understanding backend development, client-server communication, and software project organization.
