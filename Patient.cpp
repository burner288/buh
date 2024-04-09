#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"

#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
using namespace std;

namespace seneca {

    // constructor
    Patient::Patient(int ticketNumber)
        : m_name(nullptr), m_ohipNumber(0), m_ticket(ticketNumber) {}

    // copy constructor
    Patient::Patient(const Patient& other)
        : m_name(nullptr), m_ohipNumber(0), m_ticket(other.m_ticket) {
        if (other.m_name) {
            m_name = new char[strlen(other.m_name) + 1];
            strcpy(m_name, other.m_name);
        }
        m_ohipNumber = other.m_ohipNumber;
    }

    // assignment operator
    Patient& Patient::operator=(const Patient& other) {
        if (this != &other) {
            delete[] m_name;
            m_ticket = other.m_ticket;
            if (other.m_name) {
                m_name = new char[strlen(other.m_name) + 1];
                strcpy(m_name, other.m_name);
            }
            m_ohipNumber = other.m_ohipNumber;
        }
        return *this;
    }

    // destructor
    Patient::~Patient() {
        delete[] m_name;
        m_name = nullptr;
    }

    // returns a single char (for future derived objects)
    char Patient::type() const {
        return 'W';
    }

    // compares current object with single char, 
    // returns true if values returned are identical to the single char provided
    bool Patient::operator==(char type) const {
        return this->type() == type;
    }

    // compares current object to another patient, returns true if patient is same type as other patient
    // else returns false
    bool Patient::operator==(const Patient& other) const {
        return this->type() == other.type();
    }

    // sets time of patient's ticket to current time
    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }

    // query method to retrieve time of patient's ticket
    std::string Patient::time() const {
        int hours = m_ticket.time() / 60; // calculating hours
        int minutes = m_ticket.time() % 60; // calculating minutes

        // formats time into hh:mm
        stringstream ss;
        ss << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes;

        // returns the formatted time as a string
        return ss.str();
    }

    // query method to return number of patient's ticket
    int Patient::number() const {
        return m_ticket.number();
    }

    // when patient is casted to boolean returns true if patient is valid state, 
    // otherwise returns false
    Patient::operator bool() const {
        return m_name != nullptr && m_ohipNumber >= 100000000 && m_ohipNumber <= 999999999;
    }

    // if patient is casted to const char pointer, returns address of patient's name
    Patient::operator const char* () const {
        return m_name;
    }

    // writes patient info into ostream
    std::ostream& Patient::write(std::ostream& ostr) const {
        // initializing time string in hh:mm format using time() function
        string formattedTime = this->time();

        // if patient inserted into cout,
        if (&ostr == &cout) {
            if (m_name && m_ohipNumber) {   // outputs in certain format
                ostr << m_ticket << endl;
                ostr << m_name << ", OHIP: " << m_ohipNumber << endl;
            }
            else { // else, invalid empty state validation
                ostr << "Invalid Patient Record" << endl;
            }
        }
        else if (&ostr == &clog) {  // if patient inserted into clog,
            if (m_name && m_ohipNumber) {   // outputs in certain format
                ostr << setfill('.') << left << setw(53) << m_name << m_ohipNumber << right << setfill(' ') << setw(5) << m_ticket.number() << " " << formattedTime;
            }
            else {  // else, invalid empty state validation
                ostr << "Invalid Patient Record" << endl;
            }
        }
        else {  // if neither cout or clog,
            if (m_name && m_ohipNumber) {   // outputs in certain format
                ostr << type() << "," << m_name << "," << m_ohipNumber << "," << m_ticket.number() << "," << formattedTime; // couldn't use ticket's write function because it wouldn't be formatted in hh:mm if so
            }
            else { // else, invalid empty state validation
                ostr << "Invalid Patient Record";
            }
        }
        return ostr;
    }

    // reads patient info from istream
    std::istream& Patient::read(std::istream& istr) {

        // checking if istream in invalid empty state
        if (!istr) {
            return istr;
        }

        // checks if input is from cin
        if (&istr == &cin) {
            char tempName[51];

            // prompts for name
            cout << "Name: ";

            // extracts the name from istream up to 50 characters
            istr.getline(tempName, 51);

            // deletes existing name memory and allocates new memory for name
            delete[] m_name;
            m_name = new char[strlen(tempName) + 1];

            // validates if name exceeds 50 characters
            if (strlen(tempName) > 50) {
                tempName[50] = '\0';
            }

            // copies new name
            strcpy(m_name, tempName);

            // prompts for ohip
            cout << "OHIP: ";

            // validates and extracts ohip number
            while (true) {
                int tempOHIP;
                istr >> tempOHIP;

                // same validation as menu
                if (istr.fail()) {
                    istr.clear();
                    istr.ignore(1000, '\n');
                    cerr << "Bad integer value, try again: ";
                }
                else if (istr.peek() != '\n' && isspace(istr.peek())) {
                    istr.ignore(1000, '\n');
                    cerr << "Only enter an integer, try again: ";
                }
                else if (tempOHIP < 100000000 || tempOHIP > 999999999) {
                    istr.ignore(1000, '\n');
                    cerr << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                }
                else { // breaks out of loop if ohip is valid
                    m_ohipNumber = tempOHIP;
                    break;
                }
            }

            // clearing input buffer after user input
            istr.ignore(100, '\n');
        }
        else { // if input is not from cin
            char tempName[51];

            // extracts name up to 50 characters or comma
            istr.get(tempName, 51, ',');

            // deletes existing name memory and allocates new memory for name
            delete[] m_name;
            m_name = new char[strlen(tempName) + 1];

            // copies new name
            strcpy(m_name, tempName);

            // clears input buffer
            istr.ignore();

            // extracts ohip number and assigns it
            istr >> m_ohipNumber;

            // ignores all chars in input buffer after ohip
            istr.ignore();

            // calls read method of patient's ticket
            m_ticket.read(istr);
        }

        return istr;
    }
}