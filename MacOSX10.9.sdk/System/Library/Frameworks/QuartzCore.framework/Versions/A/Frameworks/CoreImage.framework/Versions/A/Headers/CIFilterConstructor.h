/* CoreImage - CIFilter.h
 
 Copyright (c) 2010 Apple Computer, Inc.
 All rights reserved. */


@class NSString;
@class CIFilter;

/** Used by +[CIFilter registerFilterName:constructor:classAttributes:] */
@protocol CIFilterConstructor
- (CIFilter *)filterWithName:(NSString *)name;
@end
