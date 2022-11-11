/*
 * QuartzFilters -  QuartzFilter.h
 * Copyright (c) 2005 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef QUARTZFILTER_H_
#define QUARTZFILTER_H_

#import <Cocoa/Cocoa.h>

API_UNAVAILABLE_BEGIN(ios)

@interface QuartzFilter : NSObject
{
    id _privateData;
}

+ (QuartzFilter*) quartzFilterWithURL:(NSURL*) aURL;  /* autoreleased */

+ (QuartzFilter*) quartzFilterWithProperties:(NSDictionary*) properties;  /* autoreleased */

+ (QuartzFilter*) quartzFilterWithOutputIntents:(NSArray*) outputIntents;  /* autoreleased */

- (NSDictionary*) properties;   /* autorelased copy, can be flattened to XML */

- (NSURL*) url;

- (NSString*) localizedName;

- (BOOL) applyToContext:(CGContextRef) aContext;    /* YES on success */

- (void) removeFromContext:(CGContextRef) aContext;

@end

API_UNAVAILABLE_END

#endif /* QUARTZFILTER_H_ */

