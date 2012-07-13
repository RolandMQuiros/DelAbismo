#include "da/Helper.h"

namespace da {

std::vector<std::string> tokenize(const std::string &string,
                                  const std::string &delimiters) {
    std::vector<std::string> ret;
    
    int start = 0;
    int end;
    
    while (end != std::string::npos) {
        std::string token;
        end = string.find_first_of(delimiters, start);
        token = string.substr(start, end-start);
        ret.push_back(token);
        start = end + 1;
    }
    
    return ret;
}

}
