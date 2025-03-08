#include "Account.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>


using namespace std;

// Global vector
vector<Account> AccountList;

// Constructor implementation
Account::Account(string a, string b, int i) {
    username = a;
    password = b;
    role = i;
}

// Getter implementations
string Account::getUserName() { 
    return username; 
}

string Account::getPassWord() { 
    return password; 
}

int Account::getRole() const { 
    return role; 
}

void Account::Welcome() {
    if (role == 1) {
        cout << setw(61) << "Welcome Admin " << username << endl;  
    } else {
        cout << setw(61) << "Welcome User " << username << endl;  
    }
    cout << "\n" << setw(77) << "Press any key to continue to website" << endl;
    system("pause > nul");  
}

string Account::getMyTickets(int i) const {
    return myTickets[i];
}

int Account::getMyTicketsSize() const {
    return myTickets.size();
}

// Setter for myTickets
void Account::setMyTickets(const vector<string>& tickets) {
    this->myTickets = tickets;
}

vector<string>& Account::returnMyTickets() {
    return myTickets;
}

void Read_Accounts() {
    ifstream file("accounts.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            int i = 0;
            string info[3];
            stringstream ss(line);
            string word;

            vector<string> tickets; // To store tickets for the current account
            
            // Extract the first three fields (username, password, role)
            while (i < 3 && ss >> word) {
                word.erase(remove(word.begin(), word.end(), ';'), word.end());
                word.erase(remove(word.begin(), word.end(), '|'), word.end());
                if (!word.empty()) {
                    info[i] = word;
                    i++;
                }
            }

            // Extract remaining words as tickets
            while (i >= 3 && ss >> word) {
                word.erase(remove(word.begin(), word.end(), ';'), word.end());
                word.erase(remove(word.begin(), word.end(), '|'), word.end());
                if (!word.empty()) {
                    tickets.push_back(word);
                    i++;
                }
            }

            
            try {
                int role = stoi(info[2]);
                Account newAccount(info[0], info[1], role);

                // Use the setter to assign tickets
                newAccount.setMyTickets(tickets);

                AccountList.push_back(newAccount);
            } catch (const exception& e) {
                cout << "Error converting role to integer: " << e.what() << endl;
            }
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void removeDelimiters(string& str, const set<char>& delimiters) {
    str.erase(remove_if(str.begin(), str.end(), [&delimiters](char c) {
        return delimiters.find(c) != delimiters.end();
    }), str.end());
}

void updateAccountFile(const vector<string>& lines) {
    ofstream file("accounts.txt", ios::trunc); // Open in truncate mode to overwrite
    if (file.is_open()) {
        for (const string& line : lines) {
            file << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open accounts.txt for writing." << endl;
    }
}

// Function to add a ticket to a user's account
void addTicket(const string& username, const string& newTicket) {
    ifstream file("accounts.txt");
    vector<string> lines;
    bool ticketAdded = false;

    // Define delimiters to be removed
    set<char> delimiters = {';', '|', ',', '.'};

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string user;
            ss >> user;
            
            // Remove delimiters from the username if any
            removeDelimiters(user, delimiters);

            if (user == username) {
                // Remove delimiters from the new ticket before adding
                string cleanTicket = newTicket;
                removeDelimiters(cleanTicket, delimiters);

                line += "| " + cleanTicket; // Add the cleaned ticket to the line
                ticketAdded = true;
            }

            lines.push_back(line); // Store the (potentially modified) line
        }
        file.close();

        if (ticketAdded) {
            updateAccountFile(lines); // Update the file with modified data
            for (auto& account : AccountList) {
                if (account.getUserName() == username) {
                    vector<string>& tickets = account.returnMyTickets(); // Access the vector
                    tickets.push_back(newTicket); // Add the new ticket to the vector
                    break;
                }
            }
        } else {
            cout << "User not found." << endl;
        }
    } else {
        cout << "Unable to open accounts.txt." << endl;
    }
}

// Function to delete a ticket from a user's account
void deleteTicket(const string& username, const string& ticketToDelete) {
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

            if (user == username) {
                // Find and remove the ticket along with extra spaces or delimiters
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

                ticketDeleted = true;
            }

            lines.push_back(line); // Store the (potentially modified) line
        }
        file.close();

        if (ticketDeleted) {
            updateAccountFile(lines); // Update the file with modified data
            for (auto& account : AccountList) {
                if (account.getUserName() == username) {
                    vector<string>& tickets = account.returnMyTickets(); // Use a new method to get a mutable reference
                    auto it = find(tickets.begin(), tickets.end(), ticketToDelete);
                    if (it != tickets.end()) {
                        tickets.erase(it); // Remove the ticket from memory
                    }
                    break;
                }
            }
        } else {
            cout << "Ticket not found or user not found." << endl;
        }
    } else {
        cout << "Unable to open accounts.txt." << endl;
    }
}
