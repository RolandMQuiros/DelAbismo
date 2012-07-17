#include <fstream>
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

std::string getFileText(const std::string &filename) {
    std::string ret;
    std::ifstream ifs(filename);
    
    if (ifs.is_open()) {
        ifs.seekg(0, std::ios::end);
        ret.reserve((unsigned long int)ifs.tellg());
        ifs.seekg(0, std::ios::beg);
        ret.assign((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());
        ifs.close();
    }
    
    return ret;
}

}
