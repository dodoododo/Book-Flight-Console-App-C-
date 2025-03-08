#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
const int rows = 10;
const int cols = 5;

class Flight {
private:
    string flight_id;
    int airline_brand_id;
    int economy_price;
    int business_price;
    string departure_time;
    string arrival_time;
    string departure_destination;
    string arrival_destination;
    bool seatMap[rows][cols];
    string currentSeatFile;
    string currentPassengerFile;
public:
    Flight();
    Flight(string flight_id, int airline_brand_id, int economy_price, int business_price, 
           string departure_time, string arrival_time, string departure_destination, string arrival_destination);

    string getFlightID() const { return flight_id; }
    int getAirlineBrandID() const { return airline_brand_id; }
    int getEconomyPrice() const { return economy_price; }
    int getBusinessPrice() const { return business_price; }
    string getDepartureTime() const { return departure_time; }
    string getArrivalTime() const { return arrival_time; }
    string getDepartureDestination() const { return departure_destination; }
    string getArrivalDestination() const { return arrival_destination; }   
    bool getSeat(int row, int col) const&;   
    void setSeatMap(int row, int col, bool status);
    void setEconomyPrice(int newPrice);
    void setBusinessPrice(int newPrice);
    void setDepartureTime(string newTime);
    void setArrivalTime(string newTime);
    string getCurrentSeatFile() const { return currentSeatFile; };
    string getCurrentPassengerFile() const { return currentPassengerFile; };
    void Display_Flight();
    void Create_Flight();
    void Read_Flights();
};
void appendToFlightList(const Flight& flight);

#endif
