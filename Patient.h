#ifndef SENECA_PATIENT_H_
#define SENECA_PATIENT_H_

#include "IOAble.h"
#include "Ticket.h"
#include "Utils.h"

namespace seneca {

    class Patient : public IOAble {
        // dynamically allocated C-string represented by char pointer variable,
        // used to store patient's name
        char* m_name;

        // integer attribute used to store the patient’s OHIP (Ontario Health Insurance Plan) number. 
        int m_ohipNumber;   // (should usually contain 9 digits)

        // Ticket object is used to represent the patient’s ticket for the lineup. 
        // this object encapsulates all relevant information:
        // the patient’s position in the queue, their arrival time and priority level.
        Ticket m_ticket;

    public: // meaningful comments for functions written in Patient.cpp file
        Patient(int ticketNumber = 0);
        Patient(const Patient& other);
        Patient& operator=(const Patient& other);
        ~Patient();
        virtual char type() const;
        bool operator==(char type) const;
        bool operator==(const Patient& other) const;
        void setArrivalTime();
        std::string time() const;
        int number() const;
        operator bool() const;
        operator const char* () const;
        std::ostream& write(std::ostream& ostr) const override;
        std::istream& read(std::istream& istr) override;
    };
}

#endif // SENECA_PATIENT_H_