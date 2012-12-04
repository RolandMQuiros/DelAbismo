#ifndef DA_STRINGHELPER_H
#define	DA_STRINGHELPER_H

#include <vector>
#include <string>

#include <sstream>
#include "da/DAException.h"

namespace da {
namespace StringHelper {
    
template< typename T > T convert(const std::string& str) {
    std::istringstream iss(str);
    T ret;

    iss >> std::ws >> ret >> std::ws;

    if(!iss.eof()) {
        throw DAException(__FILE__, __LINE__, "StringConvert(string)",
                          "\"" + str + "\" cannot be converted to a number "
                          "type");
    }

    return ret; 
}

std::vector<std::string> tokenize(const std::string &string,
                                  const std::string &delimiters);

std::string getFileText(const std::string &filename);

std::string toLower(const std::string &str);
std::string toUpper(const std::string &str);
    
}
}

#endif
