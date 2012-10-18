#ifndef DA_ERROR_XMLEXCEPTIONS_H
#define DA_ERROR_XMLEXCEPTIONS_H

#include <stdexcept>
#include <string>

#include "da/DAException.h"

namespace da {

struct XmlException : public DAException {
    XmlException(const std::string &where, unsigned long line,
                 const std::string &source, const std::string &what) :
    DAException(where, line, source, "XML: " + what) { }
};

struct ParseXmlException : public XmlException {
    ParseXmlException(const std::string &where, unsigned long line,
                      const std::string &source, const std::string &filename) :
    XmlException(where, line, source, "Error parsing file: " + filename) { }
};

struct NoSuchNodeXmlException : public XmlException {
    NoSuchNodeXmlException(const std::string &where, unsigned long line,
                           const std::string &source,
                           const std::string &parentName,
                           const std::string &nodeName) :
    XmlException(
        where, line, source,
        "Node \"" + parentName + "\" has no child node named \"" +
        nodeName + "\".  Check for spelling or case sensitivity."
    ) { }
};

struct NoSuchAttributeXmlException : public XmlException {
    NoSuchAttributeXmlException(const std::string &where, unsigned long line,
                                const std::string &source,
                                const std::string &nodeName,
                                const std::string &attributeName) :
    XmlException(
        where, line, source,
        "Node \"" + nodeName + "\" does not have an attribute named \"" +
        attributeName + "\".  Check for spelling or case sensitivity."
    ) { }
};

struct WrongNodeFormatXmlException : public XmlException {
    WrongNodeFormatXmlException(const std::string &where, unsigned long line,
                                const std::string &source,
                                const std::string &nodeName,
                                const std::string &expectedType,
                                const std::string &receivedType) :
    XmlException(
        where, line, source,
        "Node \"" + nodeName + "\" contents have incorrect format.  Expected " +
        expectedType + ", got " + receivedType
    ) { }
};

struct WrongAttributeFormatXmlException : public XmlException {
    WrongAttributeFormatXmlException(const std::string &where, unsigned long line,
                                     const std::string &source,
                                     const std::string &nodeName,
                                     const std::string &attributeName,
                                     const std::string &expectedType,
                                     const std::string &receivedType) :
    XmlException(
        where, line, source,
        "Attribute \"" + attributeName + "\" of node \"" + nodeName + 
        "has incorrect format.  Expected " + expectedType + ", got " +
        receivedType
    ) { }
};

struct IncorrectNodeXmlException : public XmlException {
    IncorrectNodeXmlException(const std::string &where, unsigned long line,
                              const std::string &source,
                              const std::string &expectedName,
                              const std::string &actualName) :
    XmlException( 
       where, line, source,
        "Current node does not have the right name.  Expected \"" + expectedName
        + ", Actual name: \"" + actualName + "\""
    ) { }
};
}

#endif
