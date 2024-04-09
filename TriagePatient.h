#ifndef SENECA_TRIAGEPATIENT_H_
#define SENECA_TRIAGEPATIENT_H_

#include <iostream>
#include "Patient.h"

namespace seneca {
    extern int nextTriageTicket;   // global variable that determines ticket number of next triage patient

    class TriagePatient : public Patient {
        char* symptoms; // pointer member variable that holds symptoms of arriving patient
    public:
        // default constructor
        TriagePatient();

        // rule of three:
        // copy constructor
        TriagePatient(const TriagePatient& other);
        // copy assignment operator
        TriagePatient& operator=(const TriagePatient& other);
        // destructor
        ~TriagePatient();

        // type override of base class
        char type() const override;
        // write override of base class
        std::ostream& write(std::ostream& os) const override;
        // read override of base class
        std::istream& read(std::istream& is) override;
    };

}

#endif // SENECA_TRIAGEPATIENT_H_