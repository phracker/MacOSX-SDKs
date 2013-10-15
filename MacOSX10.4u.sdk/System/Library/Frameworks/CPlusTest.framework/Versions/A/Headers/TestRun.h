/*
    TestRun.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_TestRun__
#define __CPlusTest_TestRun__ 1

#include <list>

class Test;
class TestFailure;
class TestObserver;
class TestSuite;

/*!
 @class TestRun
 @abstract Class that represents the execution of one or more unit tests.
 @discussion A TestRun represents the execution of one or more unit tests, and records success and failure information about those tests.  It can have any number of TestObservers attached, which it also informs of test progress for the purposes of logging and reporting.
 */
class TestRun {
protected:
    unsigned int _runCount;
    unsigned int _failureCount;
    std::list<TestObserver*> _observers;
    
public:
    /*!
     @abstract Constructor for the TestRun class.
     @discussion Constructor for the TestRun class.  Initializes the TestRun to a run and failure count of zero, and to have no observers.
     */
    TestRun();
    
    /*!
     @abstract Destructor for the TestRun class.
     @discussion Destructor for the TestRun class.
     */
    virtual ~TestRun();
    
    /*!
     @abstract Informs the TestRun that the given Test has started.
     @discussion Informs the TestRun that the given Test has started.  The TestRun increments its run count and passes this information to any observers.
     @param test The Test that started execution.
     */
    virtual void startedTest(Test& test);
    
    /*!
     @abstract Informs the TestRun that the given Test has completed.  A Test either completes or fails, never both.
     @discussion Informs the TestRun that the given Test has completed.  The TestRun passes this information to any observers.  A Test either completes or fails, never both.
     @param test The Test that completed execution.
     */
    virtual void stoppedTest(Test& test);
    
    /*!
     @abstract Informs the TestRun that the given Test has failed.
     @discussion Informs the TestRun that the given Test has failed.  The TestRun increments its failure count and passes this information to any observers.  A Test either completes or fails, never both.
     @param test The Test that failed execution.
     @param testFailure Information about the failure of the Test.
     */
    virtual void failedTest(Test& test, const TestFailure& failure);
    
    /*!
     @abstract Informs the TestRun that the given TestSuite has started.
     @discussion Informs the TestRun that the given TestSuite has started.  The TestRun passes this information to any observers.
     @param testSuite The TestSuite that started execution.
     */
    virtual void startedTestSuite(TestSuite& testSuite);
    
    /*!
     @abstract Informs the TestRun that the given TestSuite has completed.
     @discussion Informs the TestRun that the given TestSuite has completed.  A TestSuite always completes execution.  The TestRun passes this information to any observers.
     @param testSuite The TestSuite that started execution.
     */
    virtual void stoppedTestSuite(TestSuite& testSuite);
    
    /*!
     @abstract Gets the number of Tests run.
     @discussion Gets the number of Tests run, regardless of whether they were successful.  TestSuites are not counted.  This can be called at any time, it isn't necessary to wait until all test execution has completed.
     @result Returns the number of Tests run so far, regardless of their success.
     */
    virtual unsigned int runCount();
    
    /*!
     @abstract Gets the number of Tests that failed.
     @discussion Gets the number of Tests that failed in the current run.  TestSuites are not counted.  This can be called at any time, it isn't necessary to wait until all test execution has completed.
     @result Returns the number of Tests that failed so far.
     */
    virtual unsigned int failureCount();
    
    /*!
     @abstract Adds a TestObserver to a TestRun.
     @discussion Adds a TestObserver that will be notified of various events during execution of Tests.  These events include Test start, Test completion, Test failure, TestSuite start, and TestSuite completion.  You should not rely on order of notification of observers.
     @param observer The TestObserver to notify of events.
     */
    virtual void addObserver(TestObserver* observer);
    
    /*!
     @abstract Removes a TestObserver from a TestRun.
     @discussion Removes a TestObserver from a TestRun so it will no longer be notified of events occurring during the run.
     @param observer The TestObserver to stop notifying of events.
     */
    virtual void removeObserver(TestObserver* observer);
};

#endif /* __CPlusTest_TestRun__ */
