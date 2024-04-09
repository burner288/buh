#include "IOAble.h"

namespace seneca {
    std::ostream& operator<<(std::ostream& os, const IOAble& io) {
        io.write(os);
        return os;
    }

    std::istream& operator>>(std::istream& is, IOAble& io) {
        io.read(is);
        return is;
    }
}