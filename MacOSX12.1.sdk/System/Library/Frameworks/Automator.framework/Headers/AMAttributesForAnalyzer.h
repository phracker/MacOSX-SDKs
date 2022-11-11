/*
 *  AMAttributesForAnalzyer.h
 *  Automator
 *
 *  Created by Michael Gorbach on 12/3/10.
 *  Copyright 2010, 2014 Apple Inc. All rights reserved.
 *
 */

#ifdef __clang__
#define AM_UNUSED_FOR_ANALYZER __attribute__((unused))
#define AM_RETURNS_NONRETAINED_FOR_ANALYZER __attribute__((ns_returns_not_retained))
#define AM_RETURNS_RETAINED_FOR_ANALYZER __attribute__((ns_returns_retained))
#else
#define AM_UNUSED_FOR_ANALYZER
#define AM_RETURNS_NONRETAINED_FOR_ANALYZER
#define AM_RETURNS_RETAINED_FOR_ANALYZER
#endif
