/*
    TestSuite.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_TestSuite__
#define __CPlusTest_TestSuite__ 1

#include <string>
#include <list>

#include <CPlusTest/Test.h>

class TestRun;

/*!
 @class TestSuite
 @abstract Named collection of unit tests.
 @discussion Test suites in CPlusTest are named collections of Tests (which can be both TestCases and other TestSuites).  When a TestSuite is run, all of its component Tests are run.  The order of Test execution within a TestSuite is undefined so you should not depend on it.  There is a global TestSuite named "All" to which all instances of TestCase and TestSuite are added automatically; this can be accessed via the static TestSuite::allTests method.  Generally, you will just want to create and use TestSuite instances rather than create subclasses.  TestSuites do not currently create a fixture around execution of their Tests.
 */
class TestSuite : public Test {
protected:
    static TestSuite _allTests;
    
    std::string _name;
    std::list<Test*> _tests;
    
public:
    /*!
     @abstract Gets a TestSuite named "All" containing all currently-instantiated TestCases and TestSuites.
     @discussion Gets a TestSuite containing all currently-instantiated TestCases and TestSuites.  By default whenever a TestCase or a TestSuite is instantiated, it adds itself to the "All" TestSuite.  This can be used as a simple way to run all unit tests.
     @result Returns a TestSuite that will contain all currently-instanted TestCases and TestSuites.
    */
    static TestSuite& allTests();
    
    /*!
     @abstract Constructor for the TestSuite class.
     @discussion Constructor for the TestSuite class.  Configures the TestSuite to have the given name, and adds the TestSuite to the global TestSuite named "All" (accessed via TestSuite::allTests).
     @param name The name of this test suite.  It may be human-readable.  The name "All" is reserved by the testing framework.
     */
    TestSuite(const std::string& name);
    
    /*!
     @abstract Destructor for the TestSuite class.
     @discussion Destructor for the TestSuite class.  Removes the TestSuite from the global TestSuite named "All" (accessed via TestSuite::allTests).
     */
    virtual ~TestSuite();
    
    /*!
     @abstract Gets the name of the TestSuite.
     @discussion Gets the name of the TestSuite.
     @result Returns the name of the TestSuite.
     */
    virtual const std::string& name();
    
    /*!
     @abstract Overridden from Test.
     */
    virtual void setUp();
    
    /*!
     @abstract Overridden from Test.
     */
    virtual void tearDown();
    
    /*!
     @abstract Runs all of the Tests in the TestSuite against the given TestRun.
     @discussion Runs all of the Tests in the TestSuite against the given TestRun, and records their success or failure.  The TestSuite will run all of its Tests regardless of whether they succeed.  No assumptions should be made regarding the order in which Tests are run.
     @param run The TestRun in which to record test progress, success, or failure.
     */
    virtual void run(TestRun& run);
    
    /*!
     @abstract Gets all of the Tests in this TestSuite.
     @discussion Gets all of the Tests in this TestSuite.
     @result Returns all of the Tests in this TestSuite.
     */
    virtual std::list<Test*>& tests();
    
    /*!
     @abstract Adds a Test to the TestSuite, without taking ownership of it.
     @discussion Adds a Test to the TestSuite.  The TestSuite does not take ownership of the Test; that is, it does not guarantee the Test will be deleted by the TestSuite's destructor or when the Test is removed from the TestSuite.  This ensures it is safe to register global Tests with a TestSuite.  No assumptions should be made regarding the order in which Tests are run.
     @param test The Test to add to the TestSuite.
     */
    virtual void addTest(Test* test);
    
    /*!
     @abstract Removes a Test from the TestSuite, without deleting it.
     @discussion Removes a Test from the TestSuite.  Since the TestSuite never takes ownership of the Tests added to the TestSuite, removing a Test from a TestSuite does not result in the Test being deleted or its destructor being invoked.  This ensures it is safe to register global Tests with a TestSuite.
     @param test The Test to remove from the TestSuite, which must be present within the TestSuite.
     */
    virtual void removeTest(Test* test);
    
    /*!
     @abstract Gets a Test in the TestSuite by name.
     @discussion Locates a Test in the TestSuite given the name of the Test, and returns a pointer to it.  If the Test is not found, NULL is returned.
     @param name The name of the Test to find in the TestSuite.
     @result Returns the Test in the TestSuite with the given name, or NULL if no Test with the given name could be found.
     */
    virtual Test* testWithName(const std::string& name);
};

#endif /* __CPlusTest_TestSuite__ */
