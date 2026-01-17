/*
    TestAssertions.h
    CPlusTest
    Copyright (c) 2005 Apple Computer, Inc.
    All rights reserved.
*/

#ifndef __CPlusTest_TestAssertions__
#define __CPlusTest_TestAssertions__ 1

#include <exception>

#include <CPlusTest/TestFailure.h>

/*!
 @defined CPTAssert
 @param x An expression that should evaluate to anything non-false on success and false on failure.
 @abstract Basic assertion macro.
 @discussion The basic assertion macro in CPlusTest records the file, line number, and reason for failure if the passed expression is false.  It will also catch exceptions descending from std::exception and report their reason for failure, and will report other thrown exceptions as generic uncaught exceptions.
 */
#define CPTAssert(x) \
do { \
    try { \
        if (not (x)) { \
            throw TestFailure(__FILE__, __LINE__, #x); \
        } \
    } \
    catch (TestFailure& testFaiure) { \
        throw; \
    } \
    catch (std::exception& exception) { \
        throw TestFailure(__FILE__, __LINE__, exception.what()); \
    } \
    catch (...) { \
        throw TestFailure(__FILE__, __LINE__, "Uncaught exception"); \
    } \
} while (0)

#endif /* __CPlusTest_TestAssertions__ */
