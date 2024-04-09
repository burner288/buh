#include "TestPatient.h"
using namespace std;

namespace seneca {
    int nextTestTicket = 1; // definition of global variable

    // increases value of nextTestTicket by one
    TestPatient::TestPatient() : Patient(nextTestTicket++) {}

    // no custom destructor
    TestPatient::~TestPatient() {}

    // only returns char 'C'
    char TestPatient::type() const {
        return 'C';
    }

    // inserts contagion test, newline, then calls write() of base class
    // then returns os
    std::ostream& TestPatient::write(std::ostream& os) const {
        if (&os == &cout) {
            os << "Contagion TEST" << endl;
        }
        Patient::write(os);
        return os;
    }

    // calls read() function of base class
    // if is not reading from file, then sets nextTestTicket to patient + 1
    // then returns is
    std::istream& TestPatient::read(std::istream& is) {
        Patient::read(is);
        if (&is != &cin) {
            nextTestTicket = number() + 1;
        }
        return is;
    }

}