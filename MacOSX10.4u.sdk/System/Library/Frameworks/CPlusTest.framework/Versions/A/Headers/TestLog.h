/*
    TestLog.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_TestLog__
#define __CPlusTest_TestLog__ 1

#include <iostream>

#include <CPlusTest/TestObserver.h>

/*!
 @class TestLog
 @abstract TestObserver that logs the execution of a test run as text.
 @discussion A TestLog is a TestObserver that has a std::ostream on which it logs the executon of a test run as text.  It writes a line of text for test start, test stop, test failure, test suite start, and test suite stop.  When it writes a line of text for test failure, it outputs that line in a compiler-like format so the failure information can be easily parsed.
 */
class TestLog : public TestObserver {
protected:
    std::ostream& _stream;
    
public:
    /*!
     @abstract Constructor for the TestLog class, takes the stream to log to.
     @discussion Constructor for the TestLog class.  Its parameter is the stream to log test execution to, which defaults to std::cerr (stderr).
     @param stream The stream to log test execution to.  Defaults to std::cerr.
     */
    TestLog(std::ostream& stream = std::cerr);
    
    /*!
     @abstract Destructor for the TestLog class.
     @discussion Destructor for the TestLog class.
     */
    virtual ~TestLog();
    
    /*!
     @abstract Logs that the input Test started execution.
     @discussion Logs that the input Test started execution.
     @param test The Test that started execution.
     */
    virtual void testDidStart(Test& test);
    
    /*!
     @abstract Logs that the input Test completed execution.
     @discussion Logs that the input Test completed execution.  Tests either complete or fail, they don't do both.
     @param test The Test that completed execution.
     */
    virtual void testDidStop(Test& test);
    
    /*!
     @abstract Logs that the input Test failed execution.
     @discussion Logs that the input Test failed execution, and includes information about the failure.  This information is formatted in a compiler-like format including the source code file name and line number, followed by an informative message.
     @param test The Test that failed execution.
     @param failure Information about why the Test failed.
     */
    virtual void testDidFail(Test& test, const TestFailure& failure);

    /*!
     @abstract Logs that the input TestSuite started execution.
     @discussion Logs that the input TestSuite started execution.
     @param testSuite The TestSuite that started execution.
    */
    virtual void testSuiteDidStart(TestSuite& testSuite);
    
    /*!
     @abstract Logs that the input TestSuite completed execution.
     @discussion Logs that the input TestSuite completed execution.  TestSuites always complete, regardless of whether any of their compenent tests fail.
     @param test The TestSuite that completed execution.
     */
    virtual void testSuiteDidStop(TestSuite& testSuite);
};

#endif /* __CPlusTest_TestLog__ */
