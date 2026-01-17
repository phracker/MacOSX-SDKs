/*
 * QuartzFilters -  QuartzFilterManager.h
 * Copyright (c) 2005 Apple Computer, Inc.
 * All rights reserved.
 */


#import "QuartzFilter.h"

API_UNAVAILABLE_BEGIN(ios)

extern Boolean globalUpdateOK;

@interface QuartzFilterView : NSView
{
}
- (void) sizeToFit;

@end

@interface QuartzFilterManager : NSObject
{
    id _privateData;
}

+ (QuartzFilterManager*) filterManager;

+ (NSArray*) filtersInDomains:(NSArray*) domains;   /* returns an array of QuartzFilter objects */
                                                    /* can pass nil to get all domains */

- (NSPanel*) filterPanel;   /* provides UI to add, remove and edit QuartzFilters */

- (QuartzFilterView*) filterView;     /* ditto */

- (QuartzFilter*) selectedFilter;

- (BOOL) selectFilter:(QuartzFilter*)filter;    /* YES on success */

- (void) setDelegate:(id) aDelegate;

- (id) delegate;

- (QuartzFilter*) importFilter:(NSDictionary*) filterProperties;

@end

/*
 * The methods sent to a QuartzFilterManager’s delegate
 */

@interface NSObject (QuartzFilterManagerDelegate)

- (void) quartzFilterManager:(QuartzFilterManager*)sender didAddFilter:(QuartzFilter*) filter;
- (void) quartzFilterManager:(QuartzFilterManager*)sender didRemoveFilter:(QuartzFilter*) filter;
- (void) quartzFilterManager:(QuartzFilterManager*)sender didModifyFilter:(QuartzFilter*) filter;
- (void) quartzFilterManager:(QuartzFilterManager*)sender didSelectFilter:(QuartzFilter*) filter;

@end

/* Domains */

extern NSString* kQuartzFilterApplicationDomain;
extern NSString* kQuartzFilterPDFWorkflowDomain;
extern NSString* kQuartzFilterPrintingDomain;

/* Notifications */

extern NSString* kQuartzFilterManagerDidAddFilterNotification;
extern NSString* kQuartzFilterManagerDidRemoveFilterNotification;
extern NSString* kQuartzFilterManagerDidModifyFilterNotification;
extern NSString* kQuartzFilterManagerDidSelectFilterNotification;

API_UNAVAILABLE_END
