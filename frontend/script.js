
 function showSection(sectionId)
{
    // Hide all sections
    var sections = document.getElementsByClassName("section");

    for (var i = 0; i < sections.length; i++)
    {
        sections[i].classList.remove("active-section");
    }

    // Show selected section
    var selectedSection = document.getElementById(sectionId);

    if (selectedSection)
    {
        selectedSection.classList.add("active-section");
    }

    // Remove active from all sidebar buttons
    var buttons = document.getElementsByClassName("nav-item");

    for (var i = 0; i < buttons.length; i++)
    {
        buttons[i].classList.remove("active");
    }

    // Make clicked button active
    event.currentTarget.classList.add("active");

    // Change page title
    var pageTitle = document.getElementById("page-title");

    if (sectionId == "dashboard")
    {
        pageTitle.innerText = "Dashboard";
    }
    else if (sectionId == "customers")
    {
        pageTitle.innerText = "Customers";
    }
    else if (sectionId == "rooms")
    {
        pageTitle.innerText = "Rooms";
    }
    else if (sectionId == "bookings")
    {
        pageTitle.innerText = "Bookings";
    }
    else if (sectionId == "food")
    {
        pageTitle.innerText = "Food & Services";
    }
    else if (sectionId == "billing")
    {
        pageTitle.innerText = "Billing";
    }
    else if (sectionId == "employees")
    {
        pageTitle.innerText = "Employees";
    }
}
            function showCustomerForm()
            {
                document.getElementById("customer-form").style.display = "block";
            }


            function hideCustomerForm()
            {
                document.getElementById("customer-form").style.display = "none";
            }
            function addCustomer(event)
                {
                event.preventDefault();

                var id = document.getElementById("customerId").value;
                var name = document.getElementById("customerName").value;
                var phone = document.getElementById("customerPhone").value;
                var email = document.getElementById("customerEmail").value;
                var address = document.getElementById("customerAddress").value;
                var proof = document.getElementById("customerProof").value;

                var data =
                    "id=" + encodeURIComponent(id) +
                    "&name=" + encodeURIComponent(name) +
                    "&phone=" + encodeURIComponent(phone) +
                    "&email=" + encodeURIComponent(email) +
                    "&address=" + encodeURIComponent(address) +
                    "&proof=" + encodeURIComponent(proof);

                fetch("http://localhost:8080/add-customer",
                {
                    method: "POST",

                    headers:
                    {
                        "Content-Type": "application/x-www-form-urlencoded"
                    },

                    body: data
                })
                .then(function(response)
                {
                    return response.text();
                })
                .then(function(result)
                {
                    console.log(result);

                   
                    document.querySelector("#customer-form form").reset();

                    hideCustomerForm();
                    loadcustomers();
                    updateDashboard();

                    alert("Customer added successfully!");
                })
                .catch(function(error)
                {
                    console.log(error);

                    alert("Could not connect to C++ server.");
                });
                }
            function addRoom(event)
            {
                event.preventDefault();

                var roomNumber =
                    document.getElementById("roomNumber").value;

                var roomType =
                    document.getElementById("roomType").value;

                var price =
                    document.getElementById("roomPrice").value;

                var data =
                    "roomNumber=" + encodeURIComponent(roomNumber) +
                    "&roomType=" + encodeURIComponent(roomType) +
                    "&price=" + encodeURIComponent(price);

                fetch("http://localhost:8080/add-room",
                {
                    method: "POST",

                    headers:
                    {
                        "Content-Type": "application/x-www-form-urlencoded"
                    },

                    body: data
                })
                .then(function(response)
                {
                    return response.text();
                })
                .then(function(result)
                {
                    console.log(result);

                    var roomList =
                        document.getElementById("roomList");

                    var room = document.createElement("div");

                    room.className = "room-card";

                    room.innerHTML =
                        "<h3>Room " + roomNumber + "</h3>" +
                        "<p><strong>Type:</strong> " + roomType + "</p>" +
                        "<p><strong>Price/Night:</strong> Rs. " + price + "</p>" +
                        "<p class='room-status'>Available</p>";

                    roomList.appendChild(room);

                    document.querySelector("#room-form form").reset();

                    hideRoomForm();

                    updateDashboard();

                    alert("Room added successfully!");
                })
                .catch(function(error)
                {
                    console.log(error);

                    alert("Could not connect to C++ server.");
                });
            }


                            

            
            function showBookingForm()
            {
            document.getElementById("booking-form").style.display = "block";
            }

            function hideBookingForm()
            {
            document.getElementById("booking-form").style.display = "none";
            }
            function addBooking(event)
            {
                event.preventDefault();

                var bookingId =
                    document.getElementById("bookingId").value;

                var customerId =
                    document.getElementById("bookingCustomerId").value;

                var roomNumber =
                    document.getElementById("bookingRoomNumber").value;

                var checkInDate =
                    document.getElementById("checkInDate").value;

                var days =
                    document.getElementById("bookingDays").value;

                var data =
                    "bookingId=" + encodeURIComponent(bookingId) +
                    "&customerId=" + encodeURIComponent(customerId) +
                    "&roomNumber=" + encodeURIComponent(roomNumber) +
                    "&checkInDate=" + encodeURIComponent(checkInDate) +
                    "&days=" + encodeURIComponent(days);

                fetch("http://localhost:8080/add-booking",
                {
                    method: "POST",

                    headers:
                    {
                        "Content-Type":
                            "application/x-www-form-urlencoded"
                    },

                    body: data
                })
                .then(function(response)
                {
                    return response.text();
                })
                .then(function(result)
                {
                    console.log(result);

                    document.querySelector("#booking-form form").reset();

                    hideBookingForm();

                    loadBookings();

                    updateDashboard();

                    alert("Booking created successfully!");
                })
                .catch(function(error)
                {
                    console.log(error);

                    alert("Could not connect to C++ server.");
                });
            }
            function loadBookings()
            {
                Promise.all([
                    fetch("http://localhost:8080/bookings").then(function(response)
                    {
                        return response.text();
                    }),

                    fetch("http://localhost:8080/customers").then(function(response)
                    {
                        return response.text();
                    }),

                    fetch("http://localhost:8080/rooms").then(function(response)
                    {
                        return response.text();
                    })
                ])
                .then(function(results)
                {
                    var bookingData = results[0];
                    var customerData = results[1];
                    var roomData = results[2];

                    var bookingList =
                        document.getElementById("bookingList");

                    bookingList.innerHTML = "";

                    var customers = {};

                    if (customerData.trim() != "")
                    {
                        var customerLines =
                            customerData.trim().split("\n");

                        for (var i = 0; i < customerLines.length; i++)
                        {
                            var customerValues =
                                customerLines[i].split("|");

                            if (customerValues.length >= 2)
                            {
                                customers[customerValues[0]] =
                                    customerValues[1];
                            }
                        }
                    }

                    var rooms = {};

                    if (roomData.trim() != "")
                    {
                        var roomLines =
                            roomData.trim().split("\n");

                        for (var i = 0; i < roomLines.length; i++)
                        {
                            var roomValues =
                                roomLines[i].split("|");

                            if (roomValues.length >= 3)
                            {
                                rooms[roomValues[0]] =
                                    roomValues[1];
                            }
                        }
                    }

                    if (bookingData.trim() == "")
                    {
                        bookingList.innerHTML =
                            '<div class="empty-state">' +
                            '<h3>No bookings created yet</h3>' +
                            '<p>Create a booking to see the reservation details here.</p>' +
                            '</div>';

                        updateDashboard();

                        return;
                    }

                    var lines =
                        bookingData.trim().split("\n");

                    for (var i = 0; i < lines.length; i++)
                    {
                        var values =
                            lines[i].split("|");

                        if (values.length < 6)
                        {
                            continue;
                        }

                        var bookingId = values[0];
                        var customerId = values[1];
                        var roomNumber = values[2];
                        var checkInDate = values[3];
                        var days = values[4];
                        var status = values[5];

                        var guestName =
                            customers[customerId] || "Unknown Guest";

                        var roomType =
                            rooms[roomNumber] || "Unknown Room";

                        var booking =
                            document.createElement("div");

                        booking.className = "customer-item";

                        booking.innerHTML =
                            "<h4>Booking #" + bookingId + "</h4>" +
                            "<p><strong>Guest:</strong> " +
                            guestName + "</p>" +
                            "<p><strong>Customer ID:</strong> " +
                            customerId + "</p>" +
                            "<p><strong>Room:</strong> " +
                            roomNumber + "</p>" +
                            "<p><strong>Room Type:</strong> " +
                            roomType + "</p>" +
                            "<p><strong>Check-in Date:</strong> " +
                            checkInDate + "</p>" +
                            "<p><strong>Number of Days:</strong> " +
                            days + "</p>" +
                            "<p><strong>Status:</strong> " +
                            status + "</p>";

                        bookingList.appendChild(booking);
                    }

                    updateDashboard();
                })
                .catch(function(error)
                {
                    console.log("Could not load bookings:", error);
                });
            }


                            
            function cancelBooking(button)
            {
            var booking = button.parentElement;

            
            var statusText = booking.querySelector("p:last-of-type");

            statusText.innerHTML = "<strong>Status:</strong> Cancelled";

            button.remove();

            alert("Booking cancelled successfully!");
            updateDashboard();
            }

            function showFoodForm()
{
document.getElementById("food-form").style.display = "block";
}

function hideFoodForm()
{
document.getElementById("food-form").style.display = "none";
}

function addFoodOrder(event)
{
event.preventDefault();


var orderId = document.getElementById("foodOrderId").value;
var customerId = document.getElementById("foodCustomerId").value;
var item = document.getElementById("foodItem").value;
var price = document.getElementById("foodPrice").value;
var quantity = document.getElementById("foodQuantity").value;

var total = price * quantity;

var foodList = document.getElementById("foodList");

var emptyState = foodList.querySelector(".empty-state");

if (emptyState)
{
    emptyState.remove();
}

var food = document.createElement("div");

food.className = "customer-item";

food.innerHTML =
    "<h4>" + item + "</h4>" +
    "<p><strong>Order ID:</strong> " + orderId + "</p>" +
    "<p><strong>Customer ID:</strong> " + customerId + "</p>" +
    "<p><strong>Price:</strong> ₹" + price + "</p>" +
    "<p><strong>Quantity:</strong> " + quantity + "</p>" +
    "<p><strong>Total:</strong> ₹" + total + "</p>";

foodList.appendChild(food);

document.querySelector("#food-form form").reset();

hideFoodForm();

alert("Food order added successfully!");


}

function showServiceForm()
{
document.getElementById("service-form").style.display = "block";
}

function hideServiceForm()
{
document.getElementById("service-form").style.display = "none";
}

function addHotelService(event)
{
event.preventDefault();

var serviceId = document.getElementById("serviceId").value;
var customerId = document.getElementById("serviceCustomerId").value;
var serviceName = document.getElementById("serviceName").value;
var price = document.getElementById("servicePrice").value;
var quantity = document.getElementById("serviceQuantity").value;

var total = price * quantity;

var serviceList = document.getElementById("serviceList");

var emptyState = serviceList.querySelector(".empty-state");

if (emptyState)
{
    emptyState.remove();
}

var service = document.createElement("div");

service.className = "customer-item";

service.innerHTML =
    "<h4>" + serviceName + "</h4>" +
    "<p><strong>Service ID:</strong> " + serviceId + "</p>" +
    "<p><strong>Customer ID:</strong> " + customerId + "</p>" +
    "<p><strong>Price:</strong> ₹" + price + "</p>" +
    "<p><strong>Quantity:</strong> " + quantity + "</p>" +
    "<p><strong>Total:</strong> ₹" + total + "</p>";

serviceList.appendChild(service);

document.querySelector("#service-form form").reset();

hideServiceForm();

alert("Hotel service added successfully!");

}
function showBillForm()
{
document.getElementById("bill-form").style.display = "block";
}

function hideBillForm()
{
document.getElementById("bill-form").style.display = "none";
}

function generateBill(event)
{
    event.preventDefault();

    var billId =
        document.getElementById("billId").value;

    var customerId =
        document.getElementById("billCustomerId").value;

    var bookingId =
        document.getElementById("billBookingId").value;

    var roomCharges =
        Number(
            document.getElementById("roomCharges").value
        );

    var serviceCharges =
        Number(
            document.getElementById("serviceCharges").value
        );


    fetch("http://localhost:8080/food-orders")
    .then(function(response)
    {
        return response.text();
    })

    .then(function(foodData)
    {
        var foodCharges = 0;

        var lines =
            foodData.trim().split(/\r?\n/);


        for (var i = 0; i < lines.length; i++)
        {
            if (lines[i].trim() === "")
            {
                continue;
            }


            var parts =
                lines[i].split("|");


            if (parts.length >= 7)
            {
                var orderCustomerId =
                    parts[1].trim();

                var orderTotal =
                    Number(parts[6].trim());


                if (
                    orderCustomerId ===
                    String(customerId).trim()
                )
                {
                    foodCharges =
                        foodCharges + orderTotal;
                }
            }
        }


        var total =
            roomCharges +
            foodCharges +
            serviceCharges;


        var data =
            "billId=" +
            encodeURIComponent(billId) +

            "&customerId=" +
            encodeURIComponent(customerId) +

            "&bookingId=" +
            encodeURIComponent(bookingId) +

            "&roomCharges=" +
            encodeURIComponent(roomCharges) +

            "&foodCharges=" +
            encodeURIComponent(foodCharges) +

            "&serviceCharges=" +
            encodeURIComponent(serviceCharges) +

            "&total=" +
            encodeURIComponent(total);


        return fetch(
            "http://localhost:8080/add-bill",
            {
                method: "POST",

                headers:
                {
                    "Content-Type":
                        "application/x-www-form-urlencoded"
                },

                body: data
            }
        )
        .then(function(response)
        {
            return response.text();
        })
        .then(function(result)
        {
            console.log(result);


            var billList =
                document.getElementById("billList");


            var emptyState =
                billList.querySelector(".empty-state");


            if (emptyState)
            {
                emptyState.parentElement.remove();
            }


            var bill =
                document.createElement("div");


            bill.className =
                "content-card billing-card";


            bill.innerHTML =

                "<div class='card-header'>" +

                    "<div>" +

                        "<h3>Hotel Bill</h3>" +

                        "<p>Bill ID: " +
                        billId +
                        "</p>" +

                    "</div>" +

                "</div>" +


                "<div class='bill-details'>" +

                    "<p><strong>Customer ID:</strong> " +
                    customerId +
                    "</p>" +

                    "<p><strong>Booking ID:</strong> " +
                    bookingId +
                    "</p>" +

                    "<hr>" +

                    "<p>Room Charges <span>₹" +
                    roomCharges.toFixed(2) +
                    "</span></p>" +

                    "<p>Food Charges <span>₹" +
                    foodCharges.toFixed(2) +
                    "</span></p>" +

                    "<p>Service Charges <span>₹" +
                    serviceCharges.toFixed(2) +
                    "</span></p>" +

                    "<hr>" +

                    "<h3>TOTAL <span>₹" +
                    total.toFixed(2) +
                    "</span></h3>" +

                "</div>";


            billList.appendChild(bill);


            document
                .querySelector("#bill-form form")
                .reset();


            hideBillForm();


            updateDashboard();


            alert(
                "Bill generated successfully!"
            );
        });
    })


    .catch(function(error)
    {
        console.log(error);

        alert(
            "Could not connect to C++ server."
        );
    });
}
function updateDashboard()
{
var customers = document.querySelectorAll("#customerTable .customer-item");

var rooms = document.querySelectorAll("#roomList .room-card");

var bookings = document.querySelectorAll("#bookingList .customer-item");

var bills = document.querySelectorAll("#billList .billing-card");

var availableRoomCount = 0;
var activeBookingCount = 0;

for (var i = 0; i < rooms.length; i++)
{
    var status = rooms[i].querySelector(".room-status");

    if (status && status.innerText == "Available")
    {
        availableRoomCount++;
    }
}

for (var j = 0; j < bookings.length; j++)
{
    var bookingText = bookings[j].innerText;

    if (bookingText.includes("Status: Booked"))
    {
        activeBookingCount++;
    }
}

document.getElementById("totalCustomers").innerText =
    customers.length;

document.getElementById("availableRooms").innerText =
    availableRoomCount;

document.getElementById("activeBookings").innerText =
    activeBookingCount;

document.getElementById("totalBills").innerText =
    bills.length;


}
updateDashboard();
function testCppConnection()
{
fetch("http://localhost:8080")
.then(function(response)
{
return response.text();
})
.then(function(data)
{
alert(data);
})
.catch(function(error)
{
alert("Could not connect to C++ server.");
console.log(error);
});
}
function loadRooms()
{
    Promise.all([
        fetch("http://localhost:8080/rooms").then(function(response)
        {
            return response.text();
        }),

        fetch("http://localhost:8080/bookings").then(function(response)
        {
            return response.text();
        }),

        fetch("http://localhost:8080/customers").then(function(response)
        {
            return response.text();
        })
    ])
    .then(function(results)
    {
        var roomData = results[0];
        var bookingData = results[1];
        var customerData = results[2];

        var roomList =
            document.getElementById("roomList");

        roomList.innerHTML = "";

        var bookings = [];

        if (bookingData.trim() != "")
        {
            var bookingLines = bookingData.trim().split("\n");

            for (var i = 0; i < bookingLines.length; i++)
            {
                var bookingValues = bookingLines[i].split("|");

                if (bookingValues.length >= 6)
                {
                    bookings.push(bookingValues);
                }
            }
        }

        var customers = {};

        if (customerData.trim() != "")
        {
            var customerLines = customerData.trim().split("\n");

            for (var i = 0; i < customerLines.length; i++)
            {
                var customerValues = customerLines[i].split("|");

                if (customerValues.length >= 6)
                {
                    customers[customerValues[0]] = customerValues[1];
                }
            }
        }

        if (roomData.trim() == "")
        {
            roomList.innerHTML =
                '<div class="empty-state">' +
                '<h3>No rooms added yet</h3>' +
                '<p>Add a room to see it here.</p>' +
                '</div>';

            updateDashboard();

            return;
        }

        var roomLines = roomData.trim().split("\n");

        for (var i = 0; i < roomLines.length; i++)
        {
            var values = roomLines[i].split("|");

            if (values.length < 4)
            {
                continue;
            }

            var roomNumber = values[0];
            var roomType = values[1];
            var price = values[2];
            var status = values[3];

            var guestName = "";
            var guestId = "";

            for (var j = 0; j < bookings.length; j++)
            {
                if (
                    bookings[j][2] == roomNumber &&
                    bookings[j][5] == "Booked"
                )
                {
                    guestId = bookings[j][1];
                    guestName = customers[guestId] || "Unknown Guest";

                    break;
                }
            }

            var room = document.createElement("div");

            room.className = "room-card";

            room.innerHTML =
                "<h3>Room " + roomNumber + "</h3>" +
                "<p><strong>Type:</strong> " + roomType + "</p>" +
                "<p><strong>Price/Night:</strong> Rs. " + price + "</p>" +
                "<p class='room-status'>" + status + "</p>";

            if (status == "Booked" && guestName != "")
            {
                room.innerHTML +=
                    "<p><strong>Guest:</strong> " +
                    guestName + "</p>" +
                    "<p><strong>Customer ID:</strong> " +
                    guestId + "</p>";
            }

            roomList.appendChild(room);
        }

        updateDashboard();
    })
    .catch(function(error)
    {
        console.log("Could not load rooms:", error);
    });
}



function loadCustomers()
{
    fetch("http://localhost:8080/customers")
        .then(function(response)
        {
            return response.text();
        })
        .then(function(data)
        {
            if (data.trim() == "")
            {
                return;
            }

            var customerTable =
                document.getElementById("customerTable");
                customerTable.innerHTML = "";
            var emptyState =
                customerTable.querySelector(".empty-state");

            if (emptyState)
            {
                emptyState.remove();
            }

            var lines = data.trim().split("\n");

            for (var i = 0; i < lines.length; i++)
            {
                var values = lines[i].split("|");

                if (values.length < 6)
                {
                    continue;
                }

                var customer = document.createElement("div");

                customer.className = "customer-item";

                customer.innerHTML =
                    "<h4>" + values[1] + "</h4>" +
                    "<p><strong>Customer ID:</strong> " + values[0] + "</p>" +
                    "<p><strong>Phone:</strong> " + values[2] + "</p>" +
                    "<p><strong>Email:</strong> " + values[3] + "</p>" +
                    "<p><strong>Address:</strong> " + values[4] + "</p>" +
                    "<p><strong>ID Proof:</strong> " + values[5] + "</p>";

                customerTable.appendChild(customer);
            }

            updateDashboard();
        })
        .catch(function(error)
        {
            console.log("Could not load customers:", error);
        });
}
 function showRoomForm()
{
    document.getElementById("room-form").style.display = "block";
}

function hideRoomForm()
{
    document.getElementById("room-form").style.display = "none";
}




function showFoodForm()
{
    document.getElementById("food-form").style.display = "block";
}


function hideFoodForm()
{
    document.getElementById("food-form").style.display = "none";
}


function addFoodOrder(event)
{
    event.preventDefault();

    var orderId =
        document.getElementById("foodOrderId").value;

    var customerId =
        document.getElementById("foodCustomerId").value;

    var roomNumber =
        document.getElementById("foodRoomNumber").value;

    var foodItem =
        document.getElementById("foodItem").value;

    var quantity =
        Number(document.getElementById("foodQuantity").value);

    var price =
        Number(document.getElementById("foodPrice").value);

    var total =
        quantity * price;


    var data =
        "orderId=" + encodeURIComponent(orderId) +
        "&customerId=" + encodeURIComponent(customerId) +
        "&roomNumber=" + encodeURIComponent(roomNumber) +
        "&foodItem=" + encodeURIComponent(foodItem) +
        "&quantity=" + encodeURIComponent(quantity) +
        "&price=" + encodeURIComponent(price) +
        "&total=" + encodeURIComponent(total);


    fetch("http://localhost:8080/add-food-order",
    {
        method: "POST",

        headers:
        {
            "Content-Type":
                "application/x-www-form-urlencoded"
        },

        body: data
    })


    .then(function(response)
    {
        return response.text();
    })


    .then(function(result)
    {
        console.log(result);


        var foodOrderList =
            document.getElementById("foodOrderList");


        var emptyState =
            foodOrderList.querySelector(".empty-state");


        if (emptyState)
        {
            emptyState.parentElement.remove();
        }


        var order =
            document.createElement("div");


        order.className =
            "content-card billing-card";


        order.innerHTML =

            "<div class='card-header'>" +

                "<div>" +

                    "<h3>" +
                    foodItem +
                    "</h3>" +

                    "<p>Order ID: " +
                    orderId +
                    "</p>" +

                "</div>" +

            "</div>" +


            "<div class='bill-details'>" +

                "<p><strong>Customer ID:</strong> " +
                customerId +
                "</p>" +

                "<p><strong>Room Number:</strong> " +
                roomNumber +
                "</p>" +

                "<p><strong>Quantity:</strong> " +
                quantity +
                "</p>" +

                "<p><strong>Price:</strong> ₹" +
                price.toFixed(2) +
                "</p>" +

                "<hr>" +

                "<h3>TOTAL <span>₹" +
                total.toFixed(2) +
                "</span></h3>" +

            "</div>";


        foodOrderList.appendChild(order);


        document
            .querySelector("#food-form form")
            .reset();


        hideFoodForm();


        alert("Food order added successfully!");
    })


    .catch(function(error)
    {
        console.log(error);

        alert("Could not connect to C++ server.");
    });
}

 
function showServiceForm()
{
    document.getElementById("service-form").style.display = "block";
}


function hideServiceForm()
{
    document.getElementById("service-form").style.display = "none";
}


function addService(event)
{
    event.preventDefault();

    var serviceId =
        document.getElementById("serviceId").value;

    var customerId =
        document.getElementById("serviceCustomerId").value;

    var roomNumber =
        document.getElementById("serviceRoomNumber").value;

    var serviceName =
        document.getElementById("serviceName").value;

    var quantity =
        Number(
            document.getElementById("serviceQuantity").value
        );

    var price =
        Number(
            document.getElementById("servicePrice").value
        );

    var total =
        quantity * price;


    var data =
        "serviceId=" +
        encodeURIComponent(serviceId) +

        "&customerId=" +
        encodeURIComponent(customerId) +

        "&roomNumber=" +
        encodeURIComponent(roomNumber) +

        "&serviceName=" +
        encodeURIComponent(serviceName) +

        "&quantity=" +
        encodeURIComponent(quantity) +

        "&price=" +
        encodeURIComponent(price) +

        "&total=" +
        encodeURIComponent(total);


    fetch("http://localhost:8080/add-service",
    {
        method: "POST",

        headers:
        {
            "Content-Type":
                "application/x-www-form-urlencoded"
        },

        body: data
    })
    .then(function(response)
    {
        return response.text();
    })
    .then(function(result)
    {
        console.log(result);


        var serviceList =
            document.getElementById("serviceList");


        var emptyState =
            serviceList.querySelector(".empty-state");


        if (emptyState)
        {
            emptyState.parentElement.remove();
        }


        var service =
            document.createElement("div");


        service.className =
            "content-card billing-card";


        service.innerHTML =

            "<div class='card-header'>" +

                "<div>" +

                    "<h3>" +
                    serviceName +
                    "</h3>" +

                    "<p>Service ID: " +
                    serviceId +
                    "</p>" +

                "</div>" +

            "</div>" +


            "<div class='bill-details'>" +

                "<p><strong>Customer ID:</strong> " +
                customerId +
                "</p>" +

                "<p><strong>Room Number:</strong> " +
                roomNumber +
                "</p>" +

                "<p><strong>Quantity:</strong> " +
                quantity +
                "</p>" +

                "<p><strong>Price:</strong> ₹" +
                price.toFixed(2) +
                "</p>" +

                "<hr>" +

                "<h3>TOTAL <span>₹" +
                total.toFixed(2) +
                "</span></h3>" +

            "</div>";


        serviceList.appendChild(service);


        document
            .querySelector("#service-form form")
            .reset();


        hideServiceForm();


        alert(
            "Service added successfully!"
        );
    })
    .catch(function(error)
    {
        console.log(error);

        alert(
            "Could not connect to C++ server."
        );
    });
}
document.addEventListener("DOMContentLoaded", function()
{
    loadCustomers();
    loadRooms();
    loadBookings();
});