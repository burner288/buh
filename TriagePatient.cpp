#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "TriagePatient.h"

using namespace std;

namespace seneca {
    int nextTriageTicket = 1; // definition of global variable

    // default constructor:
    // initializes symptoms to null
    // passes nextTriageTicket to constructor of Patient
    // and increases value of nextTriageTicket by 1
    TriagePatient::TriagePatient() 
    : Patient(nextTriageTicket++), symptoms(nullptr) {}

    // copy constructor
    TriagePatient::TriagePatient(const TriagePatient& other) 
    : Patient(other.number()) {
        if (other.symptoms) {
            symptoms = new char[strlen(other.symptoms) + 1];
            strcpy(symptoms, other.symptoms);
        }
        else {
            symptoms = nullptr;
        }
    }

    // copy assignment constructor
    TriagePatient& TriagePatient::operator=(const TriagePatient& other) {
        if (this != &other) {
            Patient::operator=(other);
            delete[] symptoms;

            if (other.symptoms) {
                symptoms = new char[strlen(other.symptoms) + 1];
                strcpy(symptoms, other.symptoms);
            }
            else {
                symptoms = nullptr;
            }
        }
        return *this;
    }

    // destructor
    TriagePatient::~TriagePatient() {
        delete[] symptoms;
        symptoms = nullptr;
    }

    // only returns char 'T'
    char TriagePatient::type() const {
        return 'T';
    }

    // override function that calls write function in base class
    std::ostream& TriagePatient::write(std::ostream& os) const {
        // if os from cout, prints "TRIAGE" label, inserts patient, then displays symptoms
        if (&os == &cout) {
            os << "TRIAGE" << endl;
            Patient::write(os);
            os << "Symptoms: " << (symptoms ? symptoms : "") << endl;
        }
        // if os not from clog, then inserts "," and patient's symptoms 
        else if (&os != &clog) {
            Patient::write(os);
            os << "," << (symptoms ? symptoms : "");
        }
        else {
            Patient::write(os);
        }
        // then returns os
        return os;
    }

    // override function that calls read function in base class
    std::istream& TriagePatient::read(std::istream& is) {
        // deletes memory pointed by symptoms member variable
        delete[] symptoms;
        symptoms = nullptr;

        // calls read function of base class
        Patient::read(is);

        // if is not from cin,
        if (&is != &cin) {
            // cstring is held locally and made sure to not exceed 511 chars
            char temp[512];

            // ignoring null byte
            //is.ignore();

            // appends ccc to the input stream due to buggy nature
            //is.putback(' ');
            //is.putback('c');
            //is.putback('c');
            //is.putback('c');

            // reads the entire line until EOF
            is.getline(temp, 512, '\n');

            // allocating memory then copies into allocated memory
            symptoms = new char[strlen(temp) + 1];
            strcpy(symptoms, temp);

            // sets nextTriageTicket to (return value of number() + 1)
            nextTriageTicket = number() + 1;
        }
        // otherwise,
        else {
            // displays:
            cout << "Symptoms: ";

            // cstring is held dynamically and made sure to not exceed 512 chars
            char temp[513];

            // reads for symptoms up to 512 chars
            is.getline(temp, 513, '\n');

            // allocating memory
            symptoms = new char[strlen(temp) + 1];

            // copies new symptoms
            strcpy(symptoms, temp);

            // validates if symptoms exceeds 512 characters
            if (strlen(symptoms) > 512) {
                symptoms[512] = '\0';
            }

            // if in any case, is fails to read the information
            // any dynamically allocated memory held by the attribute is deleted 
            // and the pointer is set to nullptr.
            if (is.fail()) {
                delete[] symptoms;
                symptoms = nullptr;
            }
        }
        // concludes by returning is
        return is;
    }

}