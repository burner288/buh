#include "Time.h"
#include <string>
#include <sstream>
using namespace std;

namespace seneca {

    // initializes time to either safe empty state or given parameter
    Time::Time(unsigned int min) {
        if (min == 0) {
            minutes = 0;
        }
        else {
            minutes = min;
        }
    }

    // resets Time object by using Utils method
    Time& Time::reset() {
        minutes = U.getTime();
        return *this;
    }

    // output stream operator that writes time in HH:MM format
    void Time::write(std::ostream& os) const {
        cout.width(2);
        cout.fill('0');
        os << (minutes / 60);

        os << ":";

        cout.width(2);
        cout.fill('0');
        os << (minutes % 60);
    }

    // input stream operator that validates user input in H:M format only
    void Time::read(std::istream& is) {
        string input;
        char colon;
        int hours = 0, mins = 0;

        // reads the user input as a whole
        is >> input;

        // uses stringstream to parse the input
        stringstream ss(input);

        ss >> hours; // reads hours
        if (ss.peek() == ':') {
            ss >> colon >> mins; // reads seperated user input
        }
        else {  // else, sets fail bit instead
            is.setstate(std::ios::failbit);
            return;
        }

        // if input is valid, sets the time
        minutes = hours * 60 + mins;
    }

    // overloads cast to unsigned int, which will then return num of minutes held in object
    Time::operator unsigned int() const {
        return minutes;
    }

    // overloads multiplication assignment for Time class which then returns a reference of minutes for current object
    Time& Time::operator*= (int val) {
        minutes *= val;
        return *this;
    }

    // overloads substraction assignment for Time class which calculates time difference between current Time object and the D object passed as argument
    Time& Time::operator-= (const Time& D) {
        int diff = minutes - D.minutes;

        if (diff < 0) {
            diff += 1440;
        }

        minutes = diff;
        return *this;
    }

    // performs same operation as -=, except doesn't modify the current object
    Time Time::operator-(const Time& T) const {
        int diff = minutes - T.minutes;

        if (diff < 0) {
            diff += 1440;
        }

        return Time(diff);
    }

    // overloads extraction operator to be able to extract data from ostream object into write method
    std::ostream& operator<<(std::ostream& os, const Time& t) {
        t.write(os);
        return os;
    }

    // overloads extraction operator to be able to extract data from istream object into read method
    std::istream& operator>>(std::istream& is, Time& t) {
        t.read(is);
        return is;
    }

}