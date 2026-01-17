/*
    TestObserver.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_TestObserver__
#define __CPlusTest_TestObserver__ 1

class Test;
class TestFailure;
class TestSuite;

/*!
 @class TestObserver
 @abstract Abstract base class for objects that can observe the execution of tests.
 @discussion A TestObserver can be added to a TestRun to observe the execution of tests as they run and track their progress.  It will be notified when tests start, stop, and fail, as well as when test suites start and stop.
 */
class TestObserver {
public:
    /*!
     @abstract Constructor for the TestObserver class.
     @discussion Constructor for the TestObserver class.
     */
    TestObserver();
    
    /*!
     @abstract Destructor for the TestObserver class.
     @discussion Destructor for the TestObserver class.
     */
    virtual ~TestObserver();
    
    /*!
     @abstract Informs the observer that the input Test started execution.
     @discussion Informs the observer that the input Test started execution.
     @param test The Test that started execution.
     */
    virtual void testDidStart(Test& test) = 0;
    
    /*!
     @abstract Informs the observer that the input Test completed execution.
     @discussion Informs the observer that the input Test completed execution.  A Test only completes if it did not fail.
     @param test The Test that completed execution.
     */
    virtual void testDidStop(Test& test) = 0;
    
    /*!
     @abstract Informs the observer that the input Test failed execution, and of information about the failure.
     @discussion Informs the observer that the input Test failed execution, and of information about the failure.  This information includes source code file name and line number, as well as an informative message.  A Test can either complete (stop) or fail, not both.
     @param test The Test that failed execution.
     @param failure Information about why the Test failed.
     */
    virtual void testDidFail(Test& test, const TestFailure& failure) = 0;
    
    /*!
     @abstract Informs the observer that the input TestSuite started execution.
     @discussion Informs the observer that the input TestSuite started execution.
     @param testSuite The TestSuite that started execution.
     */
    virtual void testSuiteDidStart(TestSuite& testSuite) = 0;
    
    /*!
     @abstract Informs the observer that the input TestSuite completed execution.
     @discussion Informs the observer that the input TestSuite completed execution.  TestSuites always complete, regardless of whether any of their component Tests fail.
     @param testSuite The TestSuite that completed execution.
     */
    virtual void testSuiteDidStop(TestSuite& testSuite) = 0;
};

#endif /* __CPlusTest_TestObserver__ */
