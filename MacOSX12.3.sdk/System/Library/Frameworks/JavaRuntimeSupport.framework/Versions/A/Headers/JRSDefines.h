/*
 *  JRSDefines.h
 *  Copyright 2011 Apple Inc. All rights reserved.
 *
 */

#include <os/availability.h>
#include <sys/cdefs.h>

#define JRS_BEGIN_DECLS \
    __BEGIN_DECLS \
    API_UNAVAILABLE_BEGIN(ios)

#define JRS_END_DECLS \
    API_UNAVAILABLE_END \
    __END_DECLS

#define JRS_EXPORT __attribute__((visibility("default")))

/* 2020 API audit of jdk7u, jdk8u, jdk9, jdk10, jdk11, and jdk(master)
 * API not used in any of those are getting marked as JRS_DEPRECATED_2020
 * API last used in Java 7 is getting marked as JRS_DEPRECATED_2020_7
 * API last used in Java 11 is getting marked as JRS_DEPRECATED_2020_11
 */

#define JRS_DEPRECATED_2020 API_DEPRECATED("This functionality is longer supported as it does not seem to be used in Java 7+. It may be removed in a future version of macOS.", macos(10.10, 11.0))
#define JRS_DEPRECATED_2020_7 API_DEPRECATED("This functionality is no longer supported as it does not seem to be used in Java 8+. It may be removed in a future version of macOS.", macos(10.10, 11.0))
#define JRS_DEPRECATED_2020_11 API_DEPRECATED("This functionality is no longer supported as it does not seem to be used in modern versions of Java. It may be removed in a future version of macOS.", macos(10.10, 11.0))
