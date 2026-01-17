/* CoreAnimation - CACIFilterAdditions.h

   Copyright (c) 2006-2007 Apple Inc.
   All rights reserved. */

#import <QuartzCore/CABase.h>
#import <QuartzCore/CIFilter.h>

@class NSString;

/* We add two additional attributes to CIFilter objects; they're
 * accessible both via the NSKeyValueCoding protocol and through the
 * properties declared below. */

@interface CIFilter (CACIFilterAdditions)

/* The name of the filter. Can be used to construct keypaths, e.g. to
 * set an attribute of a filter attached to a layer, a path such as
 * "filters.myExposureFilter.inputEV" could be used. Layer animations
 * may also access filter attributes via these key-paths. */

@property(copy) NSString *name;

/* The filter is only applied to its input when this property is set to
 * true. This property is animatable. */

@property(getter=isEnabled) BOOL enabled;

@end
