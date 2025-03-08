#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

using namespace std;

class Account {
private:
    string username;
    string password;
    int role;
    vector<string> myTickets;

public:
    Account(string a, string b, int i);
    string getUserName();
    string getPassWord();
    int getRole() const;
    void Welcome();
    string getMyTickets(int i) const;          // Get the tickets
    vector<string>& returnMyTickets();         
    int getMyTicketsSize() const;
    void setMyTickets(const vector<string>& tickets); // Set the tickets
};

void Read_Accounts();
void updateAccountFile(const vector<string>& lines);
void addTicket(const string& username, const string& newTicket);
void deleteTicket(const string& username, const string& ticketToRemove);

#endif
