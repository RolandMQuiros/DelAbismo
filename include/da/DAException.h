/* 
 * File:   Exception.h
 * Author: rquiros
 *
 * Created on January 7, 2012, 5:27 PM
 */

#ifndef DA_DAEXCEPTION_H
#define	DA_DAEXCEPTION_H

#include <stdexcept>
#include <stack>
#include <string>
#include <cstring>

#define __RELFILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : \
                                                      __FILE__)
#define __EXCEPTSRC__ __RELFILE__, __LINE__, __func__

namespace da {

class DAException {
public:
    DAException(const std::string &where, unsigned long line,
                const std::string &source, const std::string &what);
    DAException(const DAException &other);
    DAException &operator=(const DAException &other);
    virtual ~DAException();
    
    /**Push a message on top of the current one
     * @param what message to push
     */
    void pushMessage(const std::string &what);

    /**Push the message of another Exception on top of the current one
     * @param what Exception to push
     */
    void pushMessage(const DAException &what);

    /**Returns the name of the source file from which this Exception originated
     * Returns the originating source file of this (topmost) Exception.
     * @return name of origin files
     */
    const std::string &where() const;
    
    /**Returns the line number in the source file where this originates
     * @return line number
     */
    unsigned long line() const;
    
    /**Returns info string regarding the source of this Exception
     * Typically used to store the method name where this Exception was thrown.
     * @return info string regarding source
     */
    const std::string &source() const;
    
    /**Returns this Exception's message.
     * @return message
     */
    const std::string &what() const;
    
    /**Returns entire message stack as a string
     * @return message stack
     */
    std::string message() const;    
private:
    std::string mvWhere;
    unsigned long mvLine;
    std::string mvSource;
    std::string mvWhat;
    
    std::string mvMessage;
};

}
#endif

