#include "Flight_Passenger.h"

Flight_Passenger::Flight_Passenger()
    : belongsToFlight(nullptr),
      ticket_id("N/A"), 
      passenger_name("Unknown"), 
      dob("01-01-1970"), 
      seat_number("N/A"), 
      seat_class(0), 
      ticket_price(0) 
{
}

Flight_Passenger::Flight_Passenger(string ticket_id, string passenger_name, string dob, string seat_number, int seat_class, int ticket_price, Flight &flight) 
    : ticket_id(ticket_id), passenger_name(passenger_name), dob(dob), seat_number(seat_number),
      seat_class(seat_class), ticket_price(ticket_price), belongsToFlight(&flight)
{
}

void Flight_Passenger::setFlightofPassenger(Flight &flight) {
    this->belongsToFlight = &flight;
}


void appendToPassengerList(const string& filename, const Flight_Passenger& passenger) {
    ofstream file(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << "\n"; // Add a blank line before appending new passenger details
        file << passenger.getTicketID() << "|" 
             << passenger.getFlightofPassenger().getFlightID() << "|" 
             << passenger.getPassengerName() << "|" 
             << passenger.getDob() << "|" 
             << passenger.getSeatClass() << "|" 
             << passenger.getSeatNumber() << "|" 
             << passenger.getTicketPrice() << "|" 
             << passenger.getFlightofPassenger().getDepartureDestination() << "|" 
             << passenger.getFlightofPassenger().getArrivalDestination() << "|" 
             << passenger.getFlightofPassenger().getDepartureTime() << "|" 
             << passenger.getFlightofPassenger().getArrivalTime();  
        file.close(); // Close the file
    } else {
        cout << "Unable to open the file for appending." << endl;
    }
}


void Flight_Passenger::setTicketID(string id) {
    this->ticket_id = id;
}

void Flight_Passenger::Read_Passenger() {
    cout << "Ticket ID      : " << getTicketID() << endl;
    cout << "Flight ID      : " << getFlightofPassenger().getFlightID() << endl;
    cout << "Passenger Name : " << getPassengerName() << endl;
    cout << "Date of Birth  : " << getDob() << endl;
    cout << "Seat Number    : " << getSeatNumber() << endl;
    cout << "Seat Class     : " << (getSeatClass() == 0 ? "Economy" : "Business") << endl;
    cout << "Departure Time : " << getFlightofPassenger().getDepartureTime() << endl;
    cout << "Arrival Time   : " << getFlightofPassenger().getArrivalTime() << endl;
    cout << "Departure Dest : " << getFlightofPassenger().getDepartureDestination() << endl;
    cout << "Arrival Dest   : " << getFlightofPassenger().getArrivalDestination() << endl;
}