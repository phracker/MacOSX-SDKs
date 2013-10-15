/*
    TestCase.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_TestCase__
#define __CPlusTest_TestCase__ 1

#include <string>

#include <CPlusTest/Test.h>
#include <CPlusTest/TestFailure.h>
#include <CPlusTest/TestInvocation.h>
#include <CPlusTest/TestRun.h>

/*!
 @class TestCase
 @abstract Base class for test cases in CPlusTest.
 @discussion Unit tests in CPlusTest are implemented by writing individual test methods and grouping them into test cases that use a common fixture.  This fixture is common but not shared; one fixture is created and torn down around each invocation of a test method.  There should be one instance of a test case subclass per test method in the subclass.  This enables the tests to be made part of the "all tests" test suite automatically.
 */
class TestCase : public Test {
protected:
    TestInvocation* _invocation;
    std::string _name;
    
public:
    /*!
     @abstract Principal constructor for the TestCase class (must be invoked by subclasses).
     @discussion The principal constructor for the TestCase class, which must be invoked by all subclasses.  It derives the name of the test from the invocation it is passed.  It also registers the test with the "all tests" test suite.
     @param invocation An invocation representing the individual test method to run.
     */
    TestCase(TestInvocation* invocation);
    
    /*!
     @abstract Destructor for the TestCase class.
     @discussion Destructor for the TestCase class.  It removes the test from the "all tests" test suite.
     */
    virtual ~TestCase();
    
    /*!
     @abstract Gets the name of the test.
     @discussion Gets the name of the test, which is derived at construction from the name of the invocation passed to the constructor.  It is in the format "ClassName::testName".  Subclasses should not need to override this method.
     */
    virtual const std::string& name();
    
    /*!
     @abstract Sets up any necessary state before a test is run.
     @discussion Sets up any state needed by a test immediately before it is run.  State used by a test should be set up here rather than in the test constructor so that it is only present when necessary.  Subclasses may but do not need to invoke TestCase::setUp.
     */
    virtual void setUp();
    
    /*!
     @abstract Tears down any state previously set up in setUp after a test has run.
     @discussion Tears down any state needed by a test immediately after it has run.  State used by a test should be torn down here rather than in the test destructor so that it is only present as long as necessary.  Subclasses may but do not need to invoke TestCase::tearDown.
     */
    virtual void tearDown();
    
    /*!
     @abstract Runs the test, recording the results.
     @discussion Runs the test and record the success or any failure information in the passed TestRun.  This will invoke the test's setUp and tearDown methods around the actual invocation of the test, and will use the invocation passed to the constructor to invoke the test.
     @param run A TestRun in which test success or failure is recorded.
     */
    virtual void run(TestRun& run);
};

#endif /* __CPlusTest_TestCase__ */
