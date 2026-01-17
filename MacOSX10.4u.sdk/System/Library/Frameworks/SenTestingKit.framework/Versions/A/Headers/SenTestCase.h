/*$Id: SenTestCase.h,v 1.26 2005/04/02 03:18:20 phink Exp $*/

// Copyright (c) 1997-2005, Sen:te (Sente SA).  All rights reserved.
//
// Use of this source code is governed by the following license:
// 
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// 
// (1) Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer.
// 
// (2) Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation 
// and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL Sente SA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Note: this license is equivalent to the FreeBSD license.
// 
// This notice may not be removed from this file.


#import <Foundation/NSObject.h>
#import "SenTest.h"

#define STAssertNil(a1, description, ...)
#define STAssertNotNil(a1, description, ...)
#define STAssertTrue(expression, description, ...)
#define STAssertFalse(expression, description, ...)
#define STAssertEqualObjects(a1, a2, description, ...)
#define STAssertEquals(a1, a2, description, ...)
#define STAssertEqualsWithAccuracy(left, right, accuracy, description, ...)
#define STAssertThrows(expression, description, ...)
#define STAssertThrowsSpecific(expression, specificException, description, ...)
#define STAssertThrowsSpecificNamed(expr, specificException, aName, description, ...)
#define STAssertNoThrow(expression, description, ...)
#define STAssertNoThrowSpecific(expression, specificException, description, ...)
#define STAssertNoThrowSpecificNamed(expr, specificException, aName, description, ...)
#define STFail(description, ...)
#define STAssertTrueNoThrow(expression, description, ...)
#define STAssertFalseNoThrow(expression, description, ...)

/*" These marcos are deprecated "*/
#ifdef STEnableDeprecatedAssertionMacros
#define should(expression) 
#define should1(expression,description)
#define shouldnt(expression)
#define shouldnt1(expression,description)
#define shouldBeEqual(left,right)
#define shouldBeEqual1(left,right,description)
#define shouldRaise(expression)
#define shouldRaise1(expression,description)
#define shouldntRaise(expression)
#define shouldntRaise1(expression,description)
#define fail()
#define fail1(description)
#define shouldnoraise(expression)
#define should1noraise(expression,description)
#define shouldntnoraise(expression)
#define shouldnt1noraise(expression,description)
#endif


#import "SenTestCase_Macros.h"
#import "NSException_SenTestFailure.h"

/*"A test case defines the fixture to run multiple tests. To define a test case:

1) create a subclass of SenTestCase

2) implement test methods

3) optionally define instance variables that store the state of the fixture

4) optionally initialize the fixture state by overriding setUp

5) optionally clean-up after a test by overriding tearDown.


Test methods with no parameters, returning no value, and prefixed with 'test', such as:
!{
- (void) testSomething;
}

are automatically recognized as test cases by the SenTestingKit framework. Each SenTestCase subclass' defaultTestSuite is a SenTestSuite which includes theses tests.

Test methods implementations usually contains assertions that must be verified for the test to pass: the STAssertTrue() macro defined below. Here is an example:

!{
@interface MathTest : SenTestCase
{
    float f1;
    float f2;
}
- (void) testAddition;
@end


@implementation MathTest
- (void) setUp
{
    f1 = 2.0;
    f2 = 3.0;
}

- (void) testAddition
{
    STAssertTrue (f1 + f2 == 5.0, @"%f + %f should equal 5.0", f1, f2);
}
@end
}

"*/

@class SenTestSuite;
@class SenTestCaseRun;

@interface SenTestCase : SenTest <NSCoding>
{
    @private
    NSInvocation *invocation;
    SenTestCaseRun *run;
    SEL failureAction;
}

/*"Creating test cases"*/
+ (id) testCaseWithInvocation:(NSInvocation *) anInvocation;
- (id) initWithInvocation:(NSInvocation *) anInvocation;

+ (id) testCaseWithSelector:(SEL) aSelector;
- (id) initWithSelector:(SEL) aSelector;

/*"Setting and returning invocation and selector"*/
- (void) setInvocation:(NSInvocation *) anInvocation;
- (NSInvocation *) invocation;
- (SEL) selector;

/*"Setting test case behavior after a failure"*/
- (void) continueAfterFailure;
- (void) raiseAfterFailure;

/*"Failing a test, used by all macros"*/
- (void) failWithException:(NSException *) anException;

/*"Returning the class' test methods"*/
+ (NSArray *) testInvocations;
@end


@interface SenTestCase (Suite)
/*"Returning a test suite with all the test cases"*/
+ (id) defaultTestSuite;
@end


@interface SenTestCase (_Protected)
- (SEL) failureAction;
- (void) setFailureAction:(SEL) aSelector;
@end
