/*
    Test.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_Test__
#define __CPlusTest_Test__ 1

#include <string>

class TestRun;

/*!
 @class Test
 @abstract Abstract base class for unit tests.
 @discussion Test is an abstract base class that defines a common interface for unit tests, both individual test cases and test suites.  A test has a name and can be run against a TestRun, which is used to record the results of the test.  Immediately before it is run a test will have a fixture set up (via setUp) and immediately after it is done running this fixture will be torn down (via tearDown).
*/
class Test {
public:
    /*!
     @abstract Plain constructor for the Test class.
     @discussion Plain constructor for the Test class.  Does nothing, since Test is an abstract base class.
     */
    Test();
    
    /*!
     @abstract Destructor for the Test class.
     @discussion Destructor for the Test class.  Does nothing, since Test is an abstract base class.
     */
    virtual ~Test();
    
    /*!
     @abstract Gets the name of the test.
     @discussion Gets the name of the test.  For test cases this is generally in standard C++ "class::method" format, while for test suites this is generally the name of the test suite class.
     @result Returns the name of the test.
     */
    virtual const std::string& name() = 0;
    
    /*!
     @abstract Sets up any necessary state before a test is run.
     @discussion Sets up any state needed by a test immediately before it is run.  State used by a test should be set up here rather than in the test constructor so that it is only present when necessary.
     */
    virtual void setUp() = 0;
    
    /*!
     @abstract Tears down any state previously set up in setUp after a test has run.
     @discussion Tears down any state needed by a test immediately after it has run.  State used by a test should be torn down here rather than in the test destructor so that it is only present as long as necessary.
     */
    virtual void tearDown() = 0;
    
    /*!
     @abstract Runs the test, recording the results.
     @discussion Runs the test and record the success or any failure information in the passed TestRun.  This will invoke the test's setUp and tearDown methods around the actual invocation of the test.
     @param run A TestRun in which test success or failure is recorded.
     */
    virtual void run(TestRun& run) = 0;
};

#endif /* __CPlusTest_Test__ */
