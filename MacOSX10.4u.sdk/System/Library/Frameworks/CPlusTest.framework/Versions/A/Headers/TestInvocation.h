/*
    TestInvocation.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_TestInvocation__
#define __CPlusTest_TestInvocation__ 1

#include <string>
#include <functional>

class Test;

/*!
 @class TestInvocation
 @abstract Abstract base class describing an invocation of a test.
 @discussion TestInvocation is an abstract base class describing the invocation of a test.  This base class makes it possible to specify invocations as arguments and instance variables without requiring the spread of template declarations.  Generally you will use the macro TEST_INVOCATION to create a TestInvocation, passing it a Test subclass and an instance method.  In order to actually invoke a test method, CPlusTest sends the TestInvocation representing it invokeWithTarget and passes that a pointer to the individual Test to invoke the method on.
 */
class TestInvocation {
public:
    /*!
     @abstract Constructor for the TestInvocation class.
     @discussion Constructor for the TestInvocation class.
     */
    TestInvocation();
    
    /*!
     @abstract Destructor for the TestInvocation class.
     @discussion Destructor for the TestInvocation class.
    */
    virtual ~TestInvocation();
    
    /*!
     @abstract Gets the name of the TestInvocation.
     @discussion Gets the name of the TestInvocation.  Generally this should be in the form "ClassName::methodName" however this is not required.
     @result Returns the name of the TestInvocation.
     */
    virtual const std::string& name() = 0;
    
    /*!
     @abstract Invokes the method this invocation represents on the passed Test.
     @discussion Invokes the method this invocation represents on the passed Test.  This may throw an exception.
     @param target The Test the method this invocation represents should be invoked on.
    */
    virtual void invokeWithTarget(Test* target) = 0;
};

/*!
 @class ConcreteTestInvocation
 @abstract Concrete class describing an invocation of a test method.
 @discussion ConcreteTestInvocation is a concrete class that uses std::mem_fun_t to represent an invocation of a test method that can later be invoked on an arbitrary Test.  You probably don't want to subclass this; if you really want to create a custom type of invocation, you probably want to subclass TestInvocation itself.
 */
template <class T>
class ConcreteTestInvocation : public TestInvocation {
protected:
    std::mem_fun_t<void, T> _methodImp;
    std::string _name;
    
public:
    ConcreteTestInvocation(const std::string& className, const std::string& methodName, std::mem_fun_t<void, T> methodImp) : TestInvocation(), _methodImp(methodImp), _name()
    {
        _name += className;
        _name += "::";
        _name += methodName;
    }
    
    virtual ~ConcreteTestInvocation() {
        // do nothing
    }
    
    virtual const std::string& name() {
        return _name;
    }
    
    virtual void invokeWithTarget(Test* target) {
        _methodImp(static_cast<T*>(target));
    }
};

/*!
 @defined TEST_INVOCATION
 @abstract Creates a complete concrete test invocation given a class and instance method.
 @discussion The TEST_INVOCATION macro creates a concrete test invocation given a class and an instance method, describing not only the instance method of the specified class that the invocation should invoke but also giving the invocation a proper name.
 @param c The class of the test invocation to create.
 @param m The instance method to use for the created test invocation.
 @result Returns a new ConcreteTestInvocation that can be used to invoke the given instance method on a particular object.
*/
#define TEST_INVOCATION(c,m) new ConcreteTestInvocation<c>(#c, #m, std::mem_fun<void, c>(&c::m))

#endif /* __CPlusTest_TestInvocation__ */
