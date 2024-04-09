#ifndef SENECA_TESTPATIENT_H_
#define SENECA_TESTPATIENT_H_

#include <iostream>
#include "Patient.h"

namespace seneca {

    extern int nextTestTicket; // global variable used to determine ticket number of next contagion test

    class TestPatient : public Patient {
    public:
        // constructor
        TestPatient();

        // destructor
        ~TestPatient();

        // type override of base class
        char type() const override;
        // write override of base class
        std::ostream& write(std::ostream& os) const override;
        // read override of base class
        std::istream& read(std::istream& is) override;
    };

}

#endif // SENECA_TESTPATIENT_H_