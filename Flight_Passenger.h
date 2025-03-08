#ifndef FLIGHT_PASSENGER_H
#define FLIGHT_PASSENGER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Flight.h"
#include "Account.h"
using namespace std;

class Flight_Passenger {
private:
    Flight *belongsToFlight = nullptr;
    string ticket_id;
    string passenger_name;
    string dob;
    string seat_number;
    int seat_class;
    int ticket_price;

public:
    Flight_Passenger();
    Flight_Passenger(string ticket_id, string passenger_name, string dob, string seat_number, int seat_class, int ticket_price, Flight &flight);

    void setPassengerName(const string& name) { passenger_name = name; }
    void setDob(const string& dateOfBirth) { dob = dateOfBirth; }
    void setSeatNumber(string seat) { seat_number = seat; }
    void setSeatClass(int sClass) { seat_class = sClass; }
    void setTicketPrice(int price) { ticket_price = price; }
    void setTicketID(string id);
    string getPassengerName() const { return passenger_name; }
    string getDob() const { return dob; }
    string getSeatNumber() const { return seat_number; }
    int getSeatClass() const { return seat_class; }
    string getTicketID() const { return ticket_id; }
    int getTicketPrice() const { return ticket_price; }
    Flight getFlightofPassenger() const { return *belongsToFlight; };
    void setFlightofPassenger(Flight &flight);
    void Read_Passenger();
};

#endif
