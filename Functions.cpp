#include <windows.h>
#include <cctype>
#include <conio.h>
#include "Account.cpp"
#include "Flight_Passenger.cpp"
#include "Flight.cpp"

// string currentAccount = "N/A";
int accountIndex = -1;
int currentRow;
int currentCol;
vector<string> cities;
void logIn();

void readCities() {
    ifstream file("cities.txt"); 
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) { // Ensure no empty lines are added
                cities.push_back(line);
            }
        }
        file.close(); 
    } else {
        cerr << "Unable to open file 'cities.txt'" << endl; 
    }
}

int returnRole() {
    system("cls");
    cout << endl << endl;
    ifstream file("vietbay.txt"); 
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl; 
        }
        file.close(); 
    } else {
        cout << "Unable to open file" << endl; 
    }
    cout << endl << setw(75) << "Welcome To VietBay, please log-in" << endl; 
	bool valid = false;
	while (!valid) {
		string inputUsername;
	    string inputPassword;
	    cout << endl << setw(58)<< "Username: ";
	    cin >> inputUsername;
	    cout << setw(58) << "Password: ";
	    char ch;
	    while ((ch = _getch()) != 13) {
	        if (ch == 8) { 
	            if (!inputPassword.empty()) {
	                inputPassword.erase(inputPassword.size() - 1); 
	                cout << "\b \b";
	            }
	        } else {
	            inputPassword.push_back(ch);
	            cout << '*'; 
	        }
	    }
	    for (int i = 0; i < AccountList.size(); i++) {
	    	if (inputUsername == AccountList[i].getUserName() && inputPassword == AccountList[i].getPassWord()) {
	    		cout << endl << setw(67) << "Log-in successfully" << endl;
	    		valid = true;
                accountIndex = i;
                AccountList[i].Welcome();
	    		return AccountList[i].getRole();
			}
		}
		cout << endl << setw(85) << "Invalid username or password, please enter again" << endl;	
	}
    return -1;
}

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

string toLowerCase(string str) {
   transform(str.begin(), str.end(), str.begin(), ::tolower);  
   return str;
}

string toUpperCase(string str) {
   transform(str.begin(), str.end(), str.begin(), ::toupper);  
   return str;
}

string trim(const string &s) {
    auto start = s.begin();
    while (start != s.end() && isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));

    return string(start, end + 1);
}

string capitalizeFirstLetter(const string& str) {
    string result;
    toLowerCase(result);
    bool newWord = true;
    for (size_t i = 0; i < str.length(); ++i) {
        if (isalpha(str[i]) && newWord) {
            result += toupper(str[i]);
            newWord = false;
        } else if (isalpha(str[i])) {
            result += str[i];
        } else if (isspace(str[i])) {
            if (!newWord) {
                result += ' ';
                newWord = true;
            }
        }
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int checkInput(string s){
	if(s.empty()) return -1;
	for(char c:s){
		if(!isdigit(c)) 
        return -1;
	}
	if(s == "") 
        return -1;
	else if (s.length() > 2) 
        return -1;
	else return stoi(s);
}

bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || day < 1 || year < 1) return false;
    
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // Leap year check for February
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }
    
    return day <= daysInMonth[month - 1];
}

bool isValidYear(int year) {
    return (year >= 1908 || year < 2026);
}

void formatDate(string& input) {
    // Keep looping until valid input is entered
    while (true) {
        // Ask for user input
        cout << "Enter date of birth (DDMMYYYY), example 30122024 : ";
        getline(cin, input);

        // Validate the length of the input
        if (input.size() != 8) {
            cout << "Invalid date format. Please enter the date in DDMMYYYY format.\n";
            continue;  // Continue the loop if the format is incorrect
        }

        // Extract day, month, and year from the input string
        int day = stoi(input.substr(0, 2));
        int month = stoi(input.substr(2, 2));
        int year = stoi(input.substr(4, 4));

        // Check if the year is valid
        if (!isValidYear(year)) {
            cout << "Invalid birth year. Please retry.\n";
            continue;  // Continue the loop if the year is invalid
        }

        // Check if the date is valid
        if (!isValidDate(day, month, year)) {
            cout << "Invalid date. Please check the day, month, and year values.\n";
            continue;  // Continue the loop if the date is invalid
        }

        input = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
        break;  // Exit the loop once the date is valid
    }
}


void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool containsNumbers(const string& str) {
    return any_of(str.begin(), str.end(), ::isdigit);
}

void inputPassengerInfo(Flight_Passenger &passenger) {
    string name, dob;
    int seatNumber;

    // Loop until a valid name (without numbers) is provided
    while (true) {
        cout << "Enter passenger name: ";
        getline(cin, name);

        // Check if the name contains numbers
        if (containsNumbers(name)) {
            cout << "Invalid name. Passenger name should not contain numbers. Please try again.\n";
        } else if (!containsNumbers(name)) {
            name = capitalizeFirstLetter(name);
            passenger.setPassengerName(name);
            break;
        }

        // If no numbers in the name, set the passenger name
          // Exit the loop once a valid name is entered
    }

    // Format and validate the date of birth
    formatDate(dob);
    passenger.setDob(dob);

    // Set the ticket ID
    passenger.setTicketID(passenger.getFlightofPassenger().getFlightID() + passenger.getSeatNumber());
}


void printTicket(Flight_Passenger &passenger) {
    cout << "-------------------------------------" << endl;
    cout << "             FLIGHT TICKET           " << endl;
    cout << "-------------------------------------" << endl;
    passenger.Read_Passenger();
    cout << "-------------------------------------" << endl;
}

string getSeatLabel(int row, int col) {
    char colLetter = 'A' + col;  // Convert 0-based column to letter (A, B, C, etc.)
    int rowNumber = row + 1;     // Convert 0-based row to 1-based row (1, 2, 3, etc.)
    return string(1, colLetter) + to_string(rowNumber);
}



void displayCell(int row, int col, int startX, int startY, bool isSelected, bool isBooked) {
    int x = startX + col * 4;  // Calculate x position for the cell
    int y = startY + row;      // Calculate y position for the cell

    setCursorPosition(x, y);
    if (isSelected && isBooked) {
        setColor(10);            
        cout << "[";         
        setColor(7); 
        cout << "X";
        setColor(10);  
        cout << "] ";
        setColor(7);    
    } else if (isSelected) {
        setColor(10);            // Highlight color for the selected cell
        cout << "[";             // Display selected cell with indicator
        setCursorPosition(x + 2, y);
        cout << "] ";
        setColor(7);             // Reset to default color
    }  else if (isBooked) { 
        cout << "[X] ";          // Display a booked cell with 'X'
    } else { 
        cout << "[";             // Display opening bracket for unbooked cell
        setCursorPosition(x + 2, y);
        cout << "] ";
    }
}

void displaySeatGrid(int startX, int startY, int flightIndex) {
    // Print column labels (A, B, C, ...)
    setCursorPosition(startX - 3, startY - 1);
    cout << "   ";  // Indent to align with row labels
    for (int col = 0; col < cols; col++) {
        cout << " " << static_cast<char>('A' + col) << "  ";
    }
    cout << endl;

    // Print rows with row labels (1, 2, 3, ...)
    for (int row = 0; row < rows; row++) {
        setCursorPosition(startX - 4, startY + row);  // Move to the start of the row
        cout << setw(2) << (row + 1) << " ";          // Print row label
        cout << endl;
    }
}

void seatCursorSelect(int startX, int startY, int flightIndex, Flight_Passenger& passenger) {
    currentRow = 0;   
    currentCol = 0; 
    int prevRow = currentRow, prevCol = currentCol;
    bool selected = false;

    // Initial display of all seats
    displaySeatGrid(startX, startY, flightIndex);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            displayCell(i, j, startX, startY, (i == currentRow && j == currentCol), FlightList[flightIndex].getSeat(i, j));
        }
    }

    while (!selected) {
        char ch = _getch(); 
        prevRow = currentRow;
        prevCol = currentCol;

        switch (ch) {
            case 72: // Up arrow key
                if (currentRow > 0) currentRow--;
                break;
            case 80: // Down arrow key
                if (currentRow < rows - 1) currentRow++;
                break;
            case 75: // Left arrow key
                if (currentCol > 0) currentCol--;
                break;
            case 77: // Right arrow key
                if (currentCol < cols - 1) currentCol++;
                break;
            case 13: // Enter key (attempt to select)
                if (FlightList[flightIndex].getSeat(currentRow, currentCol) == true) {
                    // Seat is already booked, prompt the user to select a different seat
                    setCursorPosition(76, startY + rows + 2);   
                    cout << "Seat (" << getSeatLabel(currentRow, currentCol) << ") is already booked. Please choose another seat." << endl;
                } else if (currentRow < 4 && passenger.getSeatClass() == 0) {
                    setCursorPosition(74, startY + rows + 2);   
                    cout << "Seat (" << getSeatLabel(currentRow, currentCol) << ") is for Business Tickets. Please choose seat from 5-10." << endl;
                } else if (currentRow >= 4 && passenger.getSeatClass() == 1) {
                    setCursorPosition(74, startY + rows + 2);   
                    cout << "Seat (" << getSeatLabel(currentRow, currentCol) << ") is for Economy Tickets. Please choose seat from 1-4." << endl;
                } else {
                    // Seat is available, confirm the selection
                    selected = true;
                }
                break;
            default:
                break;
        } 

        // Update the display if the cursor has moved to a new cell
        if (prevRow != currentRow || prevCol != currentCol) {
            displayCell(prevRow, prevCol, startX, startY, false, FlightList[flightIndex].getSeat(prevRow, prevCol)); 
            displayCell(currentRow, currentCol, startX, startY, true, FlightList[flightIndex].getSeat(currentRow, currentCol));
        }
    }
    
    // Confirm the selected seat
    setCursorPosition(55, startY + rows + 2);  
    cout << "                                                                                                                          ";
    setCursorPosition(90, startY + rows + 2);   
    cout << "You selected seat " << getSeatLabel(currentRow, currentCol) << endl;
    passenger.setSeatNumber(getSeatLabel(currentRow, currentCol));
}

void selectSeat(int flightIndex, Flight_Passenger& passenger) {
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth, consoleHeight; 
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        consoleWidth = 80;  
        consoleHeight = 25;  
    }

    int startX = (consoleWidth - cols * 4) / 2;   
    int startY = (consoleHeight - rows) / 2;     
    setCursorPosition(startX - 10, startY - 2);   
    cout << "Please select seat for flight " << FlightList[flightIndex].getFlightID();
    seatCursorSelect(93, startY, flightIndex, passenger);
    setCursorPosition(90, startY + rows + 3);
    cout << "Press any key to continue...";
    _getch();
    system("cls");
}

int arrowSelect(int MAX_OPTION) {
    bool selected = false;
	int current = 1;
    int x = 41, y = 4;        
    int prevX = x, prevY = y;    
    setColor(10);
    while (!selected) {
        setCursorPosition(prevX, prevY);
        cout << "   "; 
        setCursorPosition(prevX + 36, prevY);
        cout << "   "; 
		
		if (current == 1) {
			setCursorPosition(x , y);
		    cout << ">>>";
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
		if (current == MAX_OPTION) {
			setCursorPosition(x , y);
		    cout << ">>>";
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
        char ch = _getch();
        prevX = x; 
        prevY = y;
        switch (ch) {
            case 72:
                if (current > 1) {
                	current-= 1;
                    y-=2;	
				}
                break;
            case 80: 
                if (current < MAX_OPTION) {
                	current+= 1;
                	y+=2;
				}
                break;
            case 13:
            	selected = true;
            	break;
            default:
                break;
        }
        setCursorPosition(x, y);
        cout << ">>>";
        setCursorPosition(x + 36, y);
        cout << "<<<";
    }
    setColor(7);
    setCursorPosition(0, 0); 
    return current;
}

void drawMenuBox(int x, int y, int width, int height) {
    setCursorPosition(x, y);
    cout << char(201);  
    for (int i = 0; i < width - 2; i++) {
        cout << char(205); 
    }
    cout << char(187);    
    for (int i = 0; i < height - 2; i++) {
        setCursorPosition(x, y + i + 1);
        cout << char(186);
        setCursorPosition(x + width - 1, y + i + 1);
        cout << char(186); 
    }
    setCursorPosition(x, y + height - 1);
    cout << char(200);   
    for (int i = 0; i < width - 2; i++) {
        cout << char(205); 
    }
    cout << char(188);    
}

void drawButton(int x, int y, string label, bool isSelected){
	setCursorPosition(x, y);
	if(isSelected){
		setColor(10);
		cout << "[ " << label << " ]";
		setColor(7);
	} else{
		cout << "[ " << label << " ]";
	}
}


void displayFlightTable() {
    int x = 2, y = 2;
    int rowHeight = 2;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << right << setw(11) << "FlightID"
         << setw(18) << "AirlineBrand"
         << setw(18) << "EconomyPrice"
         << setw(19) << "BusinessPrice"
         << setw(19) << "DepartureTime"
         << setw(17) << "ArrivalTime"
         << setw(16) << "Departure"
         << setw(16) << "Arrival|"<< endl;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    for (int i = 0; i < FlightList.size(); i++) {       
        FlightList[i].Display_Flight();
        cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    }
}

void displayMenu(int x, int y) {
   drawMenuBox(x, y, 50, 13); 
    setCursorPosition(x + 15, y + 2);
    cout << "My tickets";
    setCursorPosition(x + 15, y + 4);
    cout << "Book ticket"; 
    setCursorPosition(x + 15, y + 6);
    cout << "Cancel ticket"; 
    setCursorPosition(x + 15, y + 8);
    cout << "Exchange ticket";  
    setCursorPosition(x + 15, y + 10);
    cout << "Exit"; 
}

void displayBenefitsTable() {
    cout << "+----------------------------------------+----------------------------------------+" << endl;
    cout << "| " << "\033[1;31m" << "ECONOMY BENEFITS" << "\033[0m" << setw(25) << "| " << "\033[1;31m" << "BUSINESS BENEFITS" << "\033[0m" << setw(23) << "|" << endl;
    cout << "+----------------------------------------+----------------------------------------+" << endl;

    cout << "| " << "Affordable ticket price" << setw(18) << "| " << "Spacious seats with extra legroom" << setw(7) << "|" << endl;
    cout << "| " << "Standard legroom" << setw(25) << "| " << "Complimentary gourmet meals" << setw(13) << "|" << endl;
    cout << "| " << "Complimentary snacks" << setw(21) << "| " << "Exclusive lounge access" << setw(17) << "|" << endl;
    cout << "| " << "Access to basic entertainment" << setw(12) << "| " << "Premium in-flight entertainment" << setw(9) << "|" << endl;

    cout << "+----------------------------------------+----------------------------------------+" << endl;
}

void selectTicketType(int flightIndex, Flight_Passenger& passenger) {
	string ticketType;
    bool inputed = false;
	displayBenefitsTable();
	cout << endl << "Please select type of plane ticket (0: Economy, 1: Business): ";
	while(!inputed) {
        getline(cin, ticketType);
        if (ticketType.empty()) {
            continue;
        }
        int check = checkInput(ticketType);
        if (check == 0) {
            passenger.setSeatClass(check);
            passenger.setTicketPrice(FlightList[flightIndex].getEconomyPrice());
            cout << "You selected Economy class ticket!!!" << endl;
            cout << "Price: " << FlightList[flightIndex].getEconomyPrice() << endl;
            inputed = true;
            break;
        } else if (check == 1) {
            passenger.setSeatClass(check);
            passenger.setTicketPrice(FlightList[flightIndex].getBusinessPrice());
            cout << "You selected Business class ticket!!!" << endl;
            cout << "Price: " << FlightList[flightIndex].getBusinessPrice() << endl;
            inputed = true;
            break;
        } else if (check != 0 && check != 1) {
            cout << "Invalid selection. PLease select again (0 for Economy or 1 for Business): ";
        }
    }
}

void selectFlights() {
    string flightID;
    bool flightFound = false;
    displayFlightTable();  
    cout << endl;
    cout << "Enter Flight ID: ";

    while (!flightFound) {
        cin >> flightID;  
        flightID = trim(flightID);  
        flightID = toLowerCase(flightID); 

        int flightIndex = -1;
        for (int i = 0; i < FlightList.size(); i++) {
            if (toLowerCase(FlightList[i].getFlightID()) == flightID) {
                flightFound = true;
                flightIndex = i;
                break;
            }
        }

        if (flightFound) {
            cout << endl << endl;
            system("cls");
        
            Flight_Passenger passenger;
            passenger.setFlightofPassenger(FlightList[flightIndex]);
            selectTicketType(flightIndex, passenger);  
            selectSeat(flightIndex, passenger);
            inputPassengerInfo(passenger);
            printTicket(passenger);
            FlightList[flightIndex].setSeatMap(currentRow, currentCol, true);
            setupNewSeatMap(FlightList[flightIndex].getCurrentSeatFile(), FlightList[flightIndex]);
            appendToPassengerList(FlightList[flightIndex].getCurrentPassengerFile(), passenger);
            addTicket(AccountList[accountIndex].getUserName(), passenger.getTicketID());
            
        } else {
            cout << "Invalid flight ID. Please enter again: ";
        }
    }
}

void splitString(const string& input, string& part1, string& part2) {
    size_t splitIndex = 0;

    // Find the index where the split occurs
    for (size_t i = 0; i < input.length(); i++) {
        if (isalpha(input[i]) && i > 0 && isdigit(input[i - 1])) {
            splitIndex = i;
            break;
        }
    }
    part1 = input.substr(0, splitIndex);
    part2 = input.substr(splitIndex);
}

int seatCodeToNumber(const string& seatCode, int& colNumber, int& rowNumber) {
    if (seatCode.length() != 2) {
        cerr << "Invalid seat code length. Expected 2 characters like 'D5'." << endl;
        return -1; // Return an error code
    }

    char rowChar = toupper(seatCode[0]); // Ensure uppercase for consistency
    char colChar = seatCode[1];         // Column part should already be numeric

    // Validate the row character
    if (rowChar < 'A' || rowChar > 'E') {
        cerr << "Invalid row character. Expected A-E." << endl;
        return -1; // Return an error code
    }

    // Validate the column character
    if (colChar < '1' || colChar > '5') {
        cerr << "Invalid column number. Expected 1-5." << endl;
        return -1; // Return an error code
    }

    // Convert row character to a number (A=1, B=2, ..., E=5)
    colNumber = rowChar - 'A' + 1 - 1;

    // Convert column character to an integer
    rowNumber = colChar - '0' - 1;

    // Combine row and column into a single integer (e.g., D5 -> 45)
    return rowNumber * 10 + colNumber;
}

string findLineWithID(const string& filename, const string& idToFind) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            // Extract the first field before the first '|'
            size_t delimiterPos = line.find('|');
            if (delimiterPos != string::npos) {
                string idInLine = line.substr(0, delimiterPos);

                // Trim the ID from the line (remove leading/trailing whitespace)
                idInLine.erase(idInLine.find_last_not_of(" \t\n\r\f\v") + 1);
                idInLine.erase(0, idInLine.find_first_not_of(" \t\n\r\f\v"));

                // Compare the trimmed ID with idToFind
                if (idInLine == idToFind) {
                    file.close();
                    return line; // Return the matching line
                }
            }
        }
        file.close();
        cout << "ID not found in file." << endl;
    } else {
        cout << "Unable to open the file." << endl;
    }

    return ""; // Return an empty string if the ID is not found
}



void populateFromLine(Flight_Passenger& passenger, const string& line, const Flight& associatedFlight) {
    stringstream ss(line);
    string word;
    vector<string> fields;

    while (getline(ss, word, '|')) {
        word.erase(remove(word.begin(), word.end(), ';'), word.end());
        word.erase(remove(word.begin(), word.end(), '|'), word.end());
        if (!word.empty()) {
            fields.push_back(word);
        }
    }

    if (fields.size() == 11) {
        try {
            passenger.setTicketID(fields[0]);
            passenger.setPassengerName(fields[2]);
            passenger.setDob(fields[3]);
            passenger.setSeatNumber(fields[5]);
            passenger.setSeatClass(stoi(fields[4])); // Convert string to int
            passenger.setTicketPrice(stoi(fields[6])); // Convert string to int
            passenger.setFlightofPassenger(const_cast<Flight&>(associatedFlight));
        } catch (const exception& e) {
            cout << "Error parsing line: " << e.what() << endl;
        }
    } else {
        cout << "Invalid line format: " << line << " (expected 11 fields, got " << fields.size() << ")" << endl;
    }
}




void showMyTickets() {
    system("cls");
    string flightID;
    string seatNumber;
    int flightIndex;
    string passengerLine;

    cout << "MY TICKETS" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << right << setw(11) << "TicketID"
         << setw(18) << "FlightID"
         << setw(25) << "PassengerName"
         << setw(17) << "DOB"
         << setw(21) << "SeatNumber"
         << setw(17) << "SeatClass"
         << setw(19) << "TicketPrice"
         << setw(20) << "DepartureTime"
         << setw(20) << "ArrivalTime"
         << setw(20) << "DepartureDest"
         << setw(20) << "ArrivalDest" << "|" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    // Loop through all tickets associated with the account
    for (int i = 0; i < AccountList[accountIndex].getMyTicketsSize(); i++) {
        string ticketID = AccountList[accountIndex].getMyTickets(i); // Get the user's ticket ID
        string flightID, seatNumber;

        // Extract flightID and seatNumber from the ticket string
        splitString(ticketID, flightID, seatNumber);

        bool flightFound = false; // Flag to track if flight is found

        // Search through the FlightList to find the corresponding flight ID
        for (int j = 0; j < FlightList.size(); j++) {
            if (toLowerCase(FlightList[j].getFlightID()) == toLowerCase(flightID)) {
                flightFound = true;
                flightIndex = j; // Store the index of the matching flight

                // Find the line corresponding to this ticket ID in the flight's passenger file
                passengerLine = findLineWithID(FlightList[flightIndex].getCurrentPassengerFile(), ticketID);
                
                if (!passengerLine.empty()) { // If the line is found
                    // Create a Flight_Passenger object and populate it
                    Flight_Passenger passenger;
                    populateFromLine(passenger, passengerLine, FlightList[flightIndex]);

                    // Output the passenger ticket details in a formatted way
                    cout << "|" << setw(10) << passenger.getTicketID() 
                        << setw(17) << passenger.getFlightofPassenger().getFlightID()
                        << setw(27) << passenger.getPassengerName() 
                        << setw(20) << passenger.getDob()
                        << setw(14) << passenger.getSeatNumber() 
                        << setw(20) << (passenger.getSeatClass() == 0 ? "Economy" : "Business")
                        << setw(17) << passenger.getTicketPrice()
                        << setw(19) << passenger.getFlightofPassenger().getDepartureTime()
                        << setw(20) << passenger.getFlightofPassenger().getArrivalTime()
                        << setw(20) << passenger.getFlightofPassenger().getDepartureDestination()
                        << setw(24) << passenger.getFlightofPassenger().getArrivalDestination() 
                        << "|" << endl;
                    cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
                } else {
                    cout << "Ticket ID " << ticketID << " not found in passenger file for flight " << flightID << "." << endl;
                }
                break; // Exit the loop as the matching flight is found
            }
        }
        if (!flightFound) {
            cout << "Flight ID " << flightID << " not found in the flight list for ticket ID " << ticketID << "." << endl;
        }
    }
}


void removeLineWithID(const string& filename, const string& idToFind) {
    ifstream file(filename);
    string line;
    bool found = false;
    vector<string> lines;

    if (file.is_open()) {
        // Process all lines in the file
        while (getline(file, line)) {
            // Check if the current line contains the ID to delete
            if (line.find(idToFind) != string::npos) {
                found = true;
                continue; // Skip adding this line to the result (delete it)
            }
            // Add the line to the list of lines to keep
            lines.push_back(line);
        }
        file.close();

        // Write back the updated content only if the ID was found
        if (found) {
            ofstream outputFile(filename, ios::trunc);
            if (outputFile.is_open()) {
                for (size_t i = 0; i < lines.size(); ++i) {
                    outputFile << lines[i];
                    if (i < lines.size() - 1) {
                        outputFile << endl; // Avoid an extra newline at the end
                    }
                }
                outputFile.close();
            } else {
                cout << "Unable to open file for writing." << endl;
            }
        } else {
            cout << "ID not found in the file." << endl;
        }
    } else {
        cout << "Unable to open the file." << endl;
    }
}



void ExchangeTicket() {
    system("cls");
    string input;
    string flightID;
    string seatNumber;
    int flightIndex;
    int colNumber, rowNumber;
    bool validInput = false;

    // Show the user's tickets
    showMyTickets();

    while (!validInput) {
        cin.ignore();
        cout << "Enter the ticket ID you want to exchange: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Ticket ID cannot be empty. Please try again." << endl;
            continue; // Retry
        }

        // Convert the input ticket ID to lowercase for comparison
        splitString(input, flightID, seatNumber);
        flightID = toLowerCase(flightID);

        // Check if the ticket ID is exactly 7 characters long
        if (input.length() == 7) {
            // Check if the ticket belongs to the user
            bool ticketBelongsToUser = false;
            for (int i = 0; i < AccountList[accountIndex].getMyTicketsSize(); i++) {
                if (toLowerCase(AccountList[accountIndex].getMyTickets(i)) == input) {
                    ticketBelongsToUser = true;
                    break;
                }
            }

            if (!ticketBelongsToUser) {
                cout << "The ticket ID does not belong to you. Please enter a valid ticket ID." << endl;
                continue;
            }

            // Find the flight and validate the ticket ID
            for (int i = 0; i < FlightList.size(); i++) {
                if (toLowerCase(FlightList[i].getFlightID()) == flightID) {
                    flightIndex = i;

                    // Check if the seat code is valid
                    if (seatCodeToNumber(seatNumber, colNumber, rowNumber) == -1) {
                        cout << "Invalid input, the ticket does not exist." << endl;
                        break;
                    } else {
                        // Check if the seat is occupied
                        if (FlightList[flightIndex].getSeat(rowNumber, colNumber) == true) {
                            validInput = true;
                            break;
                        } else {
                            cout << "The seat for the given ticket ID is not occupied. Invalid ticket." << endl;
                            break;
                        }
                    }
                }
            }
        } else {
            cout << "Invalid input. Please enter a ticket ID with exactly 7 characters." << endl;
        }
    }

    // Convert the ticket ID back to uppercase
    input = toUpperCase(input);

    // Remove the passenger from the file and update the seat map
    removeLineWithID(FlightList[flightIndex].getCurrentPassengerFile(), input);
    FlightList[flightIndex].setSeatMap(rowNumber, colNumber, false);
    setupNewSeatMap(FlightList[flightIndex].getCurrentSeatFile(), FlightList[flightIndex]);
    deleteTicket(AccountList[accountIndex].getUserName(), input);

    cout << "Your ticket has been terminated. Press any key to continue to book a new ticket." << endl;
    system("pause");
    system("cls");

    // Call the function to allow the user to book a new flight
    selectFlights();
}


void CancelTicket() {
    system("cls");
    string input;
    string flightID;
    string seatNumber;
    int flightIndex;
    int colNumber, rowNumber;
    bool validInput = false;

    showMyTickets(); // Display the user's tickets

    while (!validInput) {
        cin.ignore();
        cout << "Enter ticket ID which you want to cancel: ";
        getline(cin, input);

        // Check if the input is empty
        if (input.empty()) {
            cout << "Ticket ID cannot be empty. Please try again." << endl;
            continue; // Retry
        }

        splitString(input, flightID, seatNumber);
        flightID = toLowerCase(flightID);

        // Ensure the input has exactly 7 characters
        if (input.length() != 7) {
            cout << "Invalid input. Please enter a ticket ID with exactly 7 characters." << endl;
            continue; // Retry
        }

        bool flightFound = false;

        for (int i = 0; i < FlightList.size(); i++) {
            if (toLowerCase(FlightList[i].getFlightID()) == flightID) {
                flightIndex = i;
                flightFound = true;

                // Validate seat number
                if (seatCodeToNumber(seatNumber, colNumber, rowNumber) == -1) {
                    cout << "Invalid input, ticket does not exist." << endl;
                    break; // Retry
                }

                // Check if the seat is occupied
                if (!FlightList[flightIndex].getSeat(rowNumber, colNumber)) {
                    cout << "This ticket is not valid or the seat is not occupied." << endl;
                    break; // Retry
                }

                // Verify if the ticket belongs to the user
                string ticketID = toUpperCase(input);
                auto& myTickets = AccountList[accountIndex].returnMyTickets();
                if (find(myTickets.begin(), myTickets.end(), ticketID) == myTickets.end()) {
                    cout << "Invalid input, this ticket is not associated with your account." << endl;
                    break; // Retry
                }

                // All validations passed
                validInput = true;
                break;
            }
        }

        if (!flightFound) {
            cout << "Invalid input, flight ID does not exist." << endl;
        }
    }

    if (validInput) {
        input = toUpperCase(input);

        // Remove ticket from flight's passenger file
        removeLineWithID(FlightList[flightIndex].getCurrentPassengerFile(), input);

        // Update the seat map
        FlightList[flightIndex].setSeatMap(rowNumber, colNumber, false);
        setupNewSeatMap(FlightList[flightIndex].getCurrentSeatFile(), FlightList[flightIndex]);

        // Delete ticket from user's account
        deleteTicket(AccountList[accountIndex].getUserName(), input);

        cout << "Your ticket has been canceled." << endl;
    }
}



void Exit() {
    setCursorPosition(25, 17);  
    cout << endl << setw(90) << "Exiting account, press any key to return to Log-in screen" << endl;
    system("pause > nul");  
}

void UserChoice() {
    int number;
    bool exitMenu = false;
    while (!exitMenu) {
        system("cls");  
        displayMenu(35, 2);  
        setCursorPosition(25, 15);  
        cout << setw(28) << "\033[1;31m" << "Please select your option" << "\033[0m"; 
        number = arrowSelect(5);

        switch (number) {
            case 1:
                showMyTickets();
                break;
            case 2:
                selectFlights();
                break;
            case 3:
                CancelTicket();
                break;
            case 4:
                ExchangeTicket();  
                break;
            case 5:
                exitMenu = true;  
                Exit();
                break;
            default:
                cout << setw(60) << "Invalid choice. Please choose again!!!" << endl;
                break;
        }
        if (!exitMenu) {
            cout << endl << setw(40) << "Press any key to return to the menu..." << endl;
            system("pause > nul");  
        }
    }
    accountIndex = -1;
    logIn();
}

void displayAdminMenu(int x, int y) {
    drawMenuBox(x, y, 50, 15); 
    setCursorPosition(x + 11, y + 2);
    cout << "Add Flight";  
    setCursorPosition(x + 11, y + 4);
    cout << "Delete Flight"; 
    setCursorPosition(x + 11, y + 6);
    cout << "Show Revenue and Flight Info"; 
    setCursorPosition(x + 11, y + 8);
    cout << "Change Flight Info"; 
    setCursorPosition(x + 11, y + 10);
    cout << "Delete Customer From Flight"; 
    setCursorPosition(x + 11, y + 12);
    cout << "Exit"; 
}

void AddFlight() {
    system("cls");
    bool exit = false;
    string flight_id, departure_location, arrival_location;
    int airline_brand_id, economy_price, business_price; 
    string departure_time, arrival_time;
    cin.ignore();
    cout << "Enter Flight ID: ";
    getline(cin, flight_id);  
    flight_id = toUpperCase(flight_id);
    
    cout << "Enter Airline Brand ID: ";
    cin >> airline_brand_id;

    cin.ignore();
    cout << "Enter Economy Price: ";
    while (true) {
        string input;
        getline(cin, input);  // Read input as a string

        // Check if the input is a valid number
        try {
            economy_price = stoi(input);  // Try to convert the string to an integer
            if (economy_price < 0) {
                cout << "Price cannot be negative! Please enter a valid number for the economy price: ";
            } else {
                break;  // Exit the loop if the conversion is successful and price is valid
            }
        } catch (const invalid_argument& e) {
            cout << "Invalid input! Please enter a valid number for the economy price: ";
        }
    }

    // -----
    cin.ignore();
    cout << "Enter Business Price: ";

    while (true) {
        
        string input;
        getline(cin, input);  // Read input as a string

        // Check if the input is a valid number
        try {
            business_price = stoi(input);  // Try to convert the string to an integer
            if (business_price < 0) {
                cout << "Price cannot be negative! Please enter a valid number for the business price: ";
            } else {
                break;  // Exit the loop if the conversion is successful and price is valid
            }
        } catch (const invalid_argument& e) {
            cout << "Invalid input! Please enter a valid number for the business price: ";
        }
    }

    
    cin.ignore();
    cout << "Enter Departure Time (e.g., 10:00): ";
    while (true) {
        getline(cin, departure_time);

        // Validate time format (assuming HH:MM format)
        if (departure_time.length() == 5 && departure_time[2] == ':') {
            // Check if the hour and minute are valid
            int hours = stoi(departure_time.substr(0, 2));
            int minutes = stoi(departure_time.substr(3, 2));

            if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
                break;
            } else {
                cout << "Invalid time! Please enter a valid Departure Time in HH:MM format: ";
            }
        } else {
            cout << "Invalid time format! Please enter the Departure Time in HH:MM format: ";
        }
    }


    cin.ignore();
    cout << "Enter Arrival Time (e.g., 12:30): ";
    while (true) {
        getline(cin, arrival_time);

        // Validate time format (assuming HH:MM format)
        if (arrival_time.length() == 5 && arrival_time[2] == ':') {
            // Check if the hour and minute are valid
            int hours = stoi(arrival_time.substr(0, 2));
            int minutes = stoi(arrival_time.substr(3, 2));

            if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
                break;
            } else {
                cout << "Invalid time! Please enter a valid Arrival Time in HH:MM format: ";
            }
        } else {
            cout << "Invalid time format! Please enter the Arrival Time in HH:MM format: ";
        }
    }



    cout << "Enter Departure Location: ";
    while (true) {
        getline(cin, departure_location);  
        departure_location = capitalizeFirstLetter(trim(departure_location));
        bool valid = false;
        for (const auto &city : cities) {
            if (capitalizeFirstLetter(trim(city)) == departure_location) { // Normalize city names
                valid = true;
                break;
            }
        }      
        if (valid) {
            break;
        } else {
            cout << "Invalid location. Enter a valid departure location: ";
        }
    }


    cout << "Enter Arrival Location: ";
    while (true) {
        getline(cin, arrival_location);  
        arrival_location = capitalizeFirstLetter(trim(arrival_location));
        bool valid = false;
        for (const auto &city : cities) {
            if (capitalizeFirstLetter(trim(city)) == arrival_location) { // Normalize city names
                if (arrival_location == departure_location) {
                    cout << "Arrival location cannot be the same as the departure location. Enter again: ";
                    valid = false;
                } else {
                    valid = true;
                }
                break;
            }
        }
        if (valid) {
            break;
        } else if (arrival_location != departure_location) {
            cout << "Invalid location. Please enter a valid arrival location: ";
        }
    }


    FlightList.push_back(Flight(flight_id, airline_brand_id, economy_price, business_price, departure_time, arrival_time, departure_location, arrival_location)); 
    cout << "NEW FLIGHT: " << endl;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << right << setw(11) << "FlightID"
         << setw(18) << "AirlineBrand"
         << setw(18) << "EconomyPrice"
         << setw(19) << "BusinessPrice"
         << setw(19) << "DepartureTime"
         << setw(17) << "ArrivalTime"
         << setw(16) << "Departure"
         << setw(16) << "Arrival|"<< endl;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    FlightList[FlightList.size() - 1].Display_Flight();
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    appendToFlightList(FlightList[FlightList.size() - 1]);
}

void DeleteFlight() {
    system("cls");
    string flightID;
    bool flightFound = false;

    displayFlightTable();
    cout << endl;
    cout << "Enter Flight ID to delete: ";

    while (!flightFound) {
        cin >> flightID;
        flightID = trim(flightID);  
        flightID = toLowerCase(flightID);

        // Iterate through the FlightList to find the flight to delete
        for (int i = 0; i < FlightList.size(); i++) {
            if (toLowerCase(FlightList[i].getFlightID()) == flightID) {  
                string flightFileID = FlightList[i].getFlightID();
                string seatFile = FlightList[i].getCurrentSeatFile();
                string passengerFile = FlightList[i].getCurrentPassengerFile();

                // Iterate through each account in AccountList
                for (auto& account : AccountList) {
                    vector<string>& userTickets = account.returnMyTickets();

                    // Loop through the tickets in the vector
                    for (int j = 0; j < userTickets.size(); j++) {
                        // Check if the ticket contains the flightID
                        if (userTickets[j].find(flightFileID) != string::npos) {
                            deleteTicket(account.getUserName(), userTickets[j]);  // Delete the ticket  
                            j--;  // Decrement index to stay at the current position after erase
                        }
                    }
                }

                // Mark flight as found
                flightFound = true;

                // Remove the flight from the FlightList
                FlightList.erase(FlightList.begin() + i);

                // Update files associated with the flight
                removeLineWithID("flights.txt", flightFileID);
                emptyFile(seatFile);
                emptyFile(passengerFile);

                cout << "Flight successfully deleted!\n";
                return;
            }
        }

        // If no flight is found, prompt the user to try again
        if (!flightFound) {
            cout << "Invalid flight ID. Please enter again: ";
        }
    }
}

int oneWayArrowSelect(int MAX_OPTION) {
    bool selected = false;
	int current = 0;
    int x = 15, y = 0;        
    int prevX = x, prevY = y;    
    setColor(10);
    while (!selected) {
        setCursorPosition(prevX + 36, prevY);
        cout << "   "; 
		
		if (current == 0) {
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
		if (current == MAX_OPTION - 1) {
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
        char ch = _getch();
        prevX = x; 
        prevY = y;
        switch (ch) {
            case 72:
                if (current > 0) {
                	current-= 1;
                    y-=1;	
				}
                break;
            case 80: 
                if (current < MAX_OPTION - 1) {
                	current+= 1;
                	y+=1;
				}
                break;
            case 13:
            	selected = true;
            	break;
            default:
                break;
        }
        setCursorPosition(x + 36, y);
        cout << "<<<";
    }
    setColor(7);
    setCursorPosition(0, 0); 
    return current;
}

void showFlightInfo(int flightIndex) {
    system("cls");
    string flightID;
    string seatNumber;
    string passengerLine;

    cout << "Status and Infomation on Flight " << FlightList[flightIndex].getFlightID() << endl;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << right << setw(11) << "FlightID"
         << setw(18) << "AirlineBrand"
         << setw(18) << "EconomyPrice"
         << setw(19) << "BusinessPrice"
         << setw(19) << "DepartureTime"
         << setw(17) << "ArrivalTime"
         << setw(16) << "Departure"
         << setw(16) << "Arrival|"<< endl;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    FlightList[flightIndex].Display_Flight();
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;


    
    cout << "\nPassengers on Flight " << FlightList[flightIndex].getFlightID() << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << right << setw(11) << "TicketID"
         << setw(18) << "FlightID"
         << setw(25) << "PassengerName"
         << setw(17) << "DOB"
         << setw(21) << "SeatNumber"
         << setw(17) << "SeatClass"
         << setw(19) << "TicketPrice"
         << setw(20) << "DepartureTime"
         << setw(20) << "ArrivalTime"
         << setw(20) << "DepartureDest"
         << setw(20) << "ArrivalDest" << "|" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;

    // Open and read the passenger file associated with the flight
    ifstream file(FlightList[flightIndex].getCurrentPassengerFile());
    if (file.is_open()) {
        // Skip the first line
        getline(file, passengerLine);

        bool isFileEmpty = true; // Flag to check if there are no valid passengers

        // Process the rest of the lines
        while (getline(file, passengerLine)) {
            // Check if the line is empty
            if (passengerLine.empty()) {
                continue; // Skip empty lines
            }

            isFileEmpty = false; // File is not empty if we read a valid line

            Flight_Passenger passenger;
            populateFromLine(passenger, passengerLine, FlightList[flightIndex]);

            // Output passenger details
            cout << "|" << setw(10) << passenger.getTicketID() 
                        << setw(17) << passenger.getFlightofPassenger().getFlightID()
                        << setw(27) << passenger.getPassengerName() 
                        << setw(20) << passenger.getDob()
                        << setw(14) << passenger.getSeatNumber() 
                        << setw(20) << (passenger.getSeatClass() == 0 ? "Economy" : "Business")
                        << setw(17) << passenger.getTicketPrice()
                        << setw(19) << passenger.getFlightofPassenger().getDepartureTime()
                        << setw(20) << passenger.getFlightofPassenger().getArrivalTime()
                        << setw(20) << passenger.getFlightofPassenger().getDepartureDestination()
                        << setw(24) << passenger.getFlightofPassenger().getArrivalDestination() 
                        << "|" << endl;
            cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
        }

        file.close();

        if (isFileEmpty) {
            cout << "The passenger file for flight " << toUpperCase(flightID) << " contains no valid passenger entries." << endl;
        }
    } else {
        cout << "Unable to open passenger file for flight " << toUpperCase(flightID) << "." << endl;
    }
}


void ShowRevenue() {
    system("cls");

    // Loop through all the flights in FlightList
    for (int index = 0; index < FlightList.size(); index++) {
        int total = 0;
        int numberOfPassengers = 0;

        // Open the passenger file for the flight
        ifstream file(FlightList[index].getCurrentPassengerFile());
        if (file.is_open()) {
            string passengerLine;

            // Skip the first line (header, if any)
            getline(file, passengerLine);

            // Process each line in the passenger file
            while (getline(file, passengerLine)) {
                if (passengerLine.empty()) {
                    continue; // Skip empty lines
                }

                // Parse the passenger line (assuming this contains ticket info)
                Flight_Passenger passenger;
                populateFromLine(passenger, passengerLine, FlightList[index]);

                // If the passenger has a valid ticket
                if (!passenger.getTicketID().empty()) {
                    numberOfPassengers++;

                    // Add the ticket price to the total revenue
                    total += passenger.getTicketPrice();  // Get the ticket price from the passenger
                }
            }

            file.close();

            // Display the flight revenue information
            cout << "Flight " << FlightList[index].getFlightID() << " (" << numberOfPassengers << "/50)" << "    Total Revenue: " << total << endl;
        } else {
            cout << "Unable to open passenger file for flight " << FlightList[index].getFlightID() << "." << endl;
        }
    }
    setColor(33);
    cout << "Select Flight to see Info";
    setColor(7);
    int flightIndex = oneWayArrowSelect(FlightList.size());
    showFlightInfo(flightIndex);
}

int oneWayArrowSelectofChangeInfo(int MAX_OPTION) {
    bool selected = false;
	int current = 0;
    int x = 5, y = 2;        
    int prevX = x, prevY = y;    
    setColor(10);
    while (!selected) {
        setCursorPosition(prevX + 36, prevY);
        cout << "   "; 
		
		if (current == 0) {
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
		if (current == MAX_OPTION - 1) {
		    setCursorPosition(x + 36, y);
		    cout << "<<<";
		}
        char ch = _getch();
        prevX = x; 
        prevY = y;
        switch (ch) {
            case 72:
                if (current > 0) {
                	current-= 1;
                    y-=1;	
				}
                break;
            case 80: 
                if (current < MAX_OPTION - 1) {
                	current+= 1;
                	y+=1;
				}
                break;
            case 13:
            	selected = true;
            	break;
            default:
                break;
        }
        setCursorPosition(x + 36, y);
        cout << "<<<";
    }
    setColor(7);
    setCursorPosition(0, 0); 
    return current;
}

bool isValidInteger(const string& str) {
    try {
        stoi(str); // Attempt to convert string to integer
        return true;
    } catch (const invalid_argument&) {
        return false;
    }
}

void updatePassengerFile(const string& flightID, const string& oldDepartureTime, const string& oldArrivalTime, const string& newDepartureTime, const string& newArrivalTime, int flightIndex) {
    ifstream passengerFile(FlightList[flightIndex].getCurrentPassengerFile());
    vector<string> passengerLines;
    string line;
    bool updated = false;

    if (!passengerFile.is_open()) {
        cout << "Unable to open the passenger file!" << endl;
        return;
    }

    // Read all lines from the file
    while (getline(passengerFile, line)) {
        if (!line.empty()) { // Avoid adding blank lines
            passengerLines.push_back(line);
        }
    }
    passengerFile.close();

    // Ensure there is at least one line (the flight ID)
    if (passengerLines.empty()) {
        cout << "Passenger file is empty!" << endl;
        return;
    }

    // Skip the first line (assumed to be the flight ID)
    for (size_t i = 1; i < passengerLines.size(); i++) {
        // Split the line by '|' to process each field
        vector<string> fields;
        stringstream ss(passengerLines[i]);
        string field;
        while (getline(ss, field, '|')) {
            fields.push_back(field);
        }

        // Ensure the passenger record has exactly 11 fields
        if (fields.size() == 11) {
            fields[9] = newDepartureTime; // Update DepartureTime
            fields[10] = newArrivalTime;  // Update ArrivalTime

            // Rebuild the line with updated times
            string updatedPassenger = "";
            for (size_t j = 0; j < fields.size(); j++) {
                updatedPassenger += fields[j];
                if (j != fields.size() - 1) {
                    updatedPassenger += "|";
                }
            }

            passengerLines[i] = updatedPassenger; // Update the passenger line
            updated = true;
        }
    }

    // Write back updated passenger information
    if (updated) {
        ofstream passengerOutFile(FlightList[flightIndex].getCurrentPassengerFile());
        if (!passengerOutFile.is_open()) {
            cout << "Unable to open the passenger file for writing!" << endl;
            return;
        }

        // Write the flight ID line back first
        passengerOutFile << passengerLines[0]; // No newline after the last line

        // Write the updated passenger records
        for (size_t i = 1; i < passengerLines.size(); i++) {
            passengerOutFile << "\n" << passengerLines[i]; // Add newline only before each new record
        }

        passengerOutFile.close();
        cout << "Passenger file updated with new flight times!" << endl;
    } else {
        cout << "No passengers found with the updated flight!" << endl;
    }
}


void UpdateFlightInFile() {
    string flightID;
    bool flightFound = false;
    bool timeChanged = false;
    string input;
    string oldDepartureTime;
    string oldArrivalTime;
    int flightIndex;
    vector<string> flightLines;
    string line;
    ifstream file("flights.txt");
    if (!file.is_open()) {
        cout << "Unable to open the file!" << endl;
        return;
    }
    while (getline(file, line)) {
        flightLines.push_back(line);
    }
    file.close();
    
    displayFlightTable();  
    cout << endl;
    cout << "Enter Flight ID to change Info: ";
    while (!flightFound) {
        cin >> flightID;  
        flightID = trim(flightID);  
        flightID = toLowerCase(flightID); 

        int flightIndex = -1;
        for (int i = 0; i < FlightList.size(); i++) {
            if (toLowerCase(FlightList[i].getFlightID()) == flightID) {
                flightFound = true;
                flightIndex = i;
                break;
            }
        }
        string oldDepartureTime = FlightList[flightIndex].getDepartureTime();
        string oldArrivalTime = FlightList[flightIndex].getArrivalTime();

        if (flightFound) {
            cout << endl << endl;
            system("cls");
            cout << "Flight ID: " << FlightList[flightIndex].getFlightID() << endl;
            cout << "Airline Brand: " << FlightList[flightIndex].getAirlineBrandID() << endl;
            cout << "Economy Price: " << FlightList[flightIndex].getEconomyPrice() << endl;
            cout << "Business Price: " << FlightList[flightIndex].getBusinessPrice() << endl;
            cout << "Departure Time: " << FlightList[flightIndex].getDepartureTime() << endl;
            cout << "Arrival Time: " << FlightList[flightIndex].getArrivalTime() << endl;
            cout << "Departure Destination: " << FlightList[flightIndex].getDepartureDestination() << endl;
            cout << "Arrival Destination: " << FlightList[flightIndex].getArrivalDestination() << endl;
            setColor(33);
            cout << "Select Info to Change";
            setColor(7);
            int changeIndex = oneWayArrowSelectofChangeInfo(4) + 1;
            string newDepartureTime, newArrivalTime;


              // Flag to check if time has been changed

            switch (changeIndex) {
                case 1:
                    cin.ignore();
                    int newEconomyPrice;
                    setCursorPosition(0, 9);
                    cout << "Enter new Economy Price: ";

                    while (true) {
                        string input;
                        getline(cin, input);  // Read input as a string

                        // Check if the input is a valid number
                        try {
                            newEconomyPrice = stoi(input);  // Try to convert the string to an integer
                            if (newEconomyPrice < 0) {
                                cout << "Price cannot be negative! Please enter a valid number for the economy price: ";
                            } else {
                                break;  // Exit the loop if the conversion is successful and price is valid
                            }
                        } catch (const invalid_argument& e) {
                            cout << "Invalid input! Please enter a valid number for the economy price: ";
                        }
                    }
                    cout << "New Economy Price: " << newEconomyPrice << endl;
                    FlightList[flightIndex].setEconomyPrice(newEconomyPrice); // Update in FlightList
                    break;

                case 2:
                    cin.ignore();
                    int newBusinessPrice;
                    setCursorPosition(0, 9);
                    cout << "Enter new Business Price: ";

                    while (true) {
                        string input;
                        getline(cin, input);  // Read input as a string

                        // Check if the input is a valid number
                        try {
                            newBusinessPrice = stoi(input);  // Try to convert the string to an integer
                            if (newBusinessPrice < 0) {
                                cout << "Price cannot be negative! Please enter a valid number for the business price: ";
                            } else {
                                break;  // Exit the loop if the conversion is successful and price is valid
                            }
                        } catch (const invalid_argument& e) {
                            cout << "Invalid input! Please enter a valid number for the business price: ";
                        }
                    }
                    cout << "New Business Price: " << newBusinessPrice << endl;
                    FlightList[flightIndex].setBusinessPrice(newBusinessPrice); // Update in FlightList
                    break;

                case 3:
                    cin.ignore();
                    setCursorPosition(0, 9);
                    cout << "Enter new Departure Time (e.g., 10:00): ";

                    while (true) {
                        getline(cin, newDepartureTime);

                        // Validate time format (assuming HH:MM format)
                        if (newDepartureTime.length() == 5 && newDepartureTime[2] == ':') {
                            // Check if the hour and minute are valid
                            int hours = stoi(newDepartureTime.substr(0, 2));
                            int minutes = stoi(newDepartureTime.substr(3, 2));

                            if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
                                timeChanged = true; // Departure time changed
                                break;
                            } else {
                                cout << "Invalid time! Please enter a valid Departure Time in HH:MM format: ";
                            }
                        } else {
                            cout << "Invalid time format! Please enter the Departure Time in HH:MM format: ";
                        }
                    }
                    cout << "New Departure Time: " << newDepartureTime << endl;
                    FlightList[flightIndex].setDepartureTime(newDepartureTime); // Update in FlightList
                    break;

                case 4:
                    cin.ignore();
                    setCursorPosition(0, 9);
                    cout << "Enter new Arrival Time (e.g., 12:30): ";

                    while (true) {
                        getline(cin, newArrivalTime);

                        // Validate time format (assuming HH:MM format)
                        if (newArrivalTime.length() == 5 && newArrivalTime[2] == ':') {
                            // Check if the hour and minute are valid
                            int hours = stoi(newArrivalTime.substr(0, 2));
                            int minutes = stoi(newArrivalTime.substr(3, 2));

                            if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
                                timeChanged = true; // Arrival time changed
                                break;
                            } else {
                                cout << "Invalid time! Please enter a valid Arrival Time in HH:MM format: ";
                            }
                        } else {
                            cout << "Invalid time format! Please enter the Arrival Time in HH:MM format: ";
                        }
                    }
                    cout << "New Arrival Time: " << newArrivalTime << endl;
                    FlightList[flightIndex].setArrivalTime(newArrivalTime); // Update in FlightList
                    break;

                default:
                    cout << "Invalid option! Please try again." << endl;
                    break;
            }

            cout << "Flight After Update " << endl;
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "|" << right << setw(11) << "FlightID"
                << setw(18) << "AirlineBrand"
                << setw(18) << "EconomyPrice"
                << setw(19) << "BusinessPrice"
                << setw(19) << "DepartureTime"
                << setw(17) << "ArrivalTime"
                << setw(16) << "Departure"
                << setw(16) << "Arrival|"<< endl;
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
            FlightList[flightIndex].Display_Flight();
            cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;
        } else {
            cout << "Invalid flight ID. Please enter again: ";
        }
    }

    // Now update the flight in the text file
    // Open the file for writing
    ofstream outFile("flights.txt");
    if (!outFile.is_open()) {
        cout << "Unable to open the file for writing!" << endl;
        return;
    }

    // Update the text file with the new FlightList data
    for (size_t i = 0; i < FlightList.size(); i++) {
        stringstream flightInfo;
        flightInfo << FlightList[i].getFlightID() << "|"
                << FlightList[i].getAirlineBrandID() << "|"
                << FlightList[i].getEconomyPrice() << "|"
                << FlightList[i].getBusinessPrice() << "|"
                << FlightList[i].getDepartureTime() << "|"
                << FlightList[i].getArrivalTime() << "|"
                << FlightList[i].getDepartureDestination() << "|"
                << FlightList[i].getArrivalDestination();

        // Write each flight info to file without an extra blank line
        if (i == FlightList.size() - 1) {
            outFile << flightInfo.str();  // No newline after the last entry
        } else {
            outFile << flightInfo.str() << "\n";  // Add newline for other entries
        }
    }

    outFile.close();
    cout << "Flight information successfully updated in the file!" << endl;

    // If the time was changed, update passengers with the new flight times
    if (timeChanged) {
        updatePassengerFile(flightID, oldDepartureTime, oldArrivalTime, FlightList[flightIndex].getDepartureTime(), FlightList[flightIndex].getArrivalTime(), flightIndex);
    }
}

void deleteTicketAdmin(const string& ticketToDelete) {
    ifstream file("accounts.txt");
    vector<string> lines;
    bool ticketDeleted = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string user;
            ss >> user;

            // Remove delimiters from the username if any
            removeDelimiters(user, {';', '|', ',', '.'});

            // Find and remove the ticket from the line
            size_t ticketPos = line.find(ticketToDelete);
            while (ticketPos != string::npos) {
                // Remove spaces or delimiters around the ticket
                size_t start = (ticketPos > 1) ? ticketPos - 2 : 0; // Start removing 2 characters back
                size_t end = ticketPos + ticketToDelete.length(); // End at the ticket's last character

                // Handle edge cases for leading or trailing delimiters
                if (end < line.length() && line[end] == ' ') {
                    end++; // Include trailing space
                }
                if (start > 0 && line[start - 1] == ' ') {
                    start--; // Include leading space
                }

                line.erase(start, end - start); // Erase the ticket and surrounding spaces/delimiters
                ticketPos = line.find(ticketToDelete); // Check for the next occurrence of the ticket
            }

            // If the ticket was deleted from this line, mark it
            if (line.find(ticketToDelete) == string::npos) {
                ticketDeleted = true;
            }

            lines.push_back(line); // Store the (potentially modified) line
        }
        file.close();

        if (ticketDeleted) {
            updateAccountFile(lines); // Update the file with modified data
            // Optional: Remove the ticket from the AccountList if necessary
            for (auto& account : AccountList) {
                vector<string>& tickets = account.returnMyTickets(); // Use a new method to get a mutable reference
                auto it = find(tickets.begin(), tickets.end(), ticketToDelete);
                if (it != tickets.end()) {
                    tickets.erase(it); // Remove the ticket from memory
                }
            }
            cout << "Ticket successfully deleted." << endl;
        } else {
            cout << "Ticket not found." << endl;
        }
    } else {
        cout << "Unable to open accounts.txt." << endl;
    }
}


void deleteUserFromFlight() {
    string flightID;
    bool flightFound = false;
    int flightIndex = -1;
    displayFlightTable();  
    cout << endl;
    cout << "Enter Flight ID Where Passenger Is In: ";
    while (!flightFound) {
        cin >> flightID;  
        flightID = trim(flightID);  
        flightID = toLowerCase(flightID); 

        for (int i = 0; i < FlightList.size(); i++) {
            if (toLowerCase(FlightList[i].getFlightID()) == toLowerCase(flightID)) {
                flightFound = true;
                flightIndex = i;
                break;
            }
        }

        if (flightFound) {
            
        } else {
            cout << "Invalid flight ID. Please enter again: ";
        }
    }
    system("cls");
    string passengerLine;
    string input;
    string seatNumber;
    int colNumber, rowNumber;
    bool validInput = false;
    cout << "\nPassengers on Flight " << toUpperCase(flightID) << endl;
    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|" << right << setw(11) << "TicketID"
         << setw(18) << "FlightID"
         << setw(21) << "PassengerName"
         << setw(17) << "DOB"
         << setw(21) << "SeatNumber"
         << setw(17) << "SeatClass"
         << setw(20) << "DepartureTime"
         << setw(20) << "ArrivalTime"
         << setw(20) << "DepartureDest"
         << setw(20) << "ArrivalDest" << "|" << endl;
    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    ifstream file(FlightList[flightIndex].getCurrentPassengerFile());
    if (file.is_open()) {
        // Skip the first line
        getline(file, passengerLine);

        // Process the rest of the lines
        while (getline(file, passengerLine)) {
            Flight_Passenger passenger;
            populateFromLine(passenger, passengerLine, FlightList[flightIndex]);

            // Output passenger details
            cout << "|" << setw(10) << passenger.getTicketID()
                 << setw(17) << passenger.getFlightofPassenger().getFlightID()
                 << setw(23) << passenger.getPassengerName()
                 << setw(20) << passenger.getDob()
                 << setw(14) << passenger.getSeatNumber()
                 << setw(20) << (passenger.getSeatClass() == 0 ? "Economy" : "Business")
                 << setw(17) << passenger.getFlightofPassenger().getDepartureTime()
                 << setw(20) << passenger.getFlightofPassenger().getArrivalTime()
                 << setw(20) << passenger.getFlightofPassenger().getDepartureDestination()
                 << setw(24) << passenger.getFlightofPassenger().getArrivalDestination()
                 << "|" << endl;
            cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
        }
        file.close();
    } else {
        cout << "Unable to open passenger file for flight " << toUpperCase(flightID) << "." << endl;
    }
    while (!validInput) {
        cin.ignore();
        cout << "Enter Passenger's ticket id which you want to cancel: ";
        getline(cin, input);
        splitString(input, flightID, seatNumber);
        flightID = toLowerCase(flightID);
        if (input.length() == 7) {
            for (int i = 0; i < FlightList.size(); i++) {
                if (toLowerCase(FlightList[i].getFlightID()) == flightID) {
                    flightIndex = i;
                    if (seatCodeToNumber(seatNumber, colNumber, rowNumber) == -1) {
                        cout << "Invalid input, ticket doesnt exist." << endl;
                        break;
                    } else {
                        if (FlightList[flightIndex].getSeat(rowNumber, colNumber) == true) {
                            validInput = true;
                            break;
                        }
                    }
                }
            }
        } else {
            cout << "Invalid input. Please enter ticket id with exactly 7 characters." << endl;
        }
    }
    input = toUpperCase(input);
    removeLineWithID(FlightList[flightIndex].getCurrentPassengerFile(), input);
    FlightList[flightIndex].setSeatMap(rowNumber, colNumber, false);
    setupNewSeatMap(FlightList[flightIndex].getCurrentSeatFile(), FlightList[flightIndex]);
    deleteTicketAdmin(input);
    cout << "Passenger's Ticket has been canceled" << endl;
}

void AdminChoice() {
    int number;
    bool exitMenu = false;
    while (!exitMenu) {
        system("cls");  
        displayAdminMenu(35, 2);  
        setCursorPosition(25, 20);  
        cout << setw(28) << "\033[1;31m" << "Please select your option" << "\033[0m"; 
        number = arrowSelect(6);

        switch (number) {
            case 1:
                AddFlight(); 
                break;
            case 2:
                DeleteFlight(); 
                break;
            case 3:
                ShowRevenue(); 
                // showFlightInfo(); 
                break;
            case 4:
                UpdateFlightInFile();
                break;
            case 5:
                deleteUserFromFlight();
                break;
            case 6:
                exitMenu = true;  
                Exit();
                break;
            default:
                cout << setw(60) << "Invalid choice. Please choose again!!!" << endl;
                break;
        }

        if (!exitMenu) {
            cout << endl << setw(40) << "Press any key to return to the menu..." << endl;
            system("pause > nul");  
        }
    }
    accountIndex = -1;
    logIn();
}

void logIn() {
    accountIndex = -1;
    int i = returnRole();
    if (i == 0) {
        UserChoice();
	} else if (i == 1) { 
        AdminChoice();
    }
}

void initiateProgram() {
    readCities();   
    Read_Accounts();
    Read_Flights();
    logIn();
}