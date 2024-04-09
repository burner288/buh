#ifndef SENECA_IOABLE_H_
#define SENECA_IOABLE_H_

#include <iostream>

namespace seneca {

    class IOAble {
    public:
        virtual std::ostream& write(std::ostream& ostr) const = 0;
        virtual std::istream& read(std::istream& istr) = 0;
        virtual ~IOAble() {}
    };

    std::ostream& operator<<(std::ostream& os, const IOAble& io);
    std::istream& operator>>(std::istream& is, IOAble& io);
}

#endif // SENECA_IOABLE_H_

