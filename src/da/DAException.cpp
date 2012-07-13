/* 
 * File:   Exception.cpp
 * Author: rquiros
 * 
 * Created on January 7, 2012, 5:27 PM
 */

#include <sstream>
#include "da/DAException.h"

namespace da {

DAException::DAException(const std::string &where, unsigned long line,
                         const std::string &source, const std::string &what) :
mvWhere(where),
mvLine(line),
mvSource(source),
mvWhat(what) {
    std::stringstream ss;
    ss << where << " (line " << line << "): " << source << ":" << '\n'
       << "    " << what << '\n';
    mvMessage = ss.str();
}

DAException::DAException(const DAException &other) :
mvWhere(other.mvWhere),
mvLine(other.mvLine),
mvSource(other.mvSource),
mvWhat(other.mvWhat),
mvMessage(other.mvMessage) { }

DAException &DAException::operator=(const DAException &other) {
    mvWhere = other.mvWhere;
    mvLine = other.mvLine;
    mvSource = other.mvSource;
    mvWhat = other.mvWhat;
    mvMessage = other.mvMessage;
    
    return *this;
}

DAException::~DAException() {
}

void DAException::pushMessage(const std::string &what) {
    mvMessage = what + '\n' + mvMessage;
}

void DAException::pushMessage(const DAException &what) {
    mvMessage = what.message() + mvMessage;
}

const std::string &DAException::where() const {
    return mvWhere;
}

unsigned long DAException::line() const {
    return mvLine;
}

const std::string &DAException::source() const {
    return mvSource;
}

const std::string &DAException::what() const {
    return mvWhat;
}

std::string DAException::message() const {
    return mvMessage;
}

}

