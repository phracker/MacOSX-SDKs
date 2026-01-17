/*
    TestFailure.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlus_Test_TestFailure__
#define __CPlus_Test_TestFailure__ 1

#include <string>

/*!
 @class TestFailure
 @abstract Exception that represents the failure of a unit test.
 @discussion A TestFailure is an exception that represents the failure of a unit test and records the file and line number of the failure along with a message describing the failure.  While this class does not descend from std::exception it may be thrown.
 */
class TestFailure {
protected:
    std::string _file;
    unsigned int _line;
    std::string _message;
    
public:
    /*!
     @abstract Constructor for the TestFailure exception.
     @discussion Constructor for the TestFailure exception.
     @param file The name of the source file in which the failure occurred.
     @param line The number of the line in the source file on which the failure occurred.
     @param message Informative text describing the failure.
     */
    TestFailure(const std::string& file, const unsigned int line, const std::string& message) throw();
    
    /*!
     @abstract Destructor for the TestFailure exception.
     @discussion Destructor for the TestFailure exception.
     */
    virtual ~TestFailure() throw();
    
    /*!
     @abstract Gets the source file in which the failure occurred.
     @discussion Gets the source file in which the failure occurred.
     @result The source file in which the failure occurred.
     */
    const std::string& file() const throw();
    
    /*!
     @abstract Gets the line in the source file on which the failure occurred.
     @discussion Gets the line in the source file on which the failure occurred.
     @result The line in the source file on which the failure occurred.
     */
    const unsigned int line() const throw();
    
    /*!
     @abstract Gets informative text describing the failure.
     @discussion Gets informative text describing the failure.
     @result Informative text describing the failure.
     */
    const std::string& message() const throw();
};

#endif /* __CPlus_Test_TestFailure__ */
