#ifndef DA_NOTIMPLEMENTEDEXCEPTION_H
#define	DA_NOTIMPLEMENTEDEXCEPTION_H

#include "da/DAException.h"

namespace da {

struct NotImplementedException : public DAException {
    NotImplementedException(const std::string &where, unsigned long line,
                            const std::string &source,
                            const std::string &feature) :
    DAException(where, line, source, feature + " has not been implemented") { }
};

}

#endif

