//
//  CLKComplicationDataSource.h
//  ClockKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClockKit/CLKDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class CLKComplication;
@class CLKTextProvider;
@class CLKComplicationTemplate;
@class CLKComplicationTimelineEntry;
@class CLKComplicationDescriptor;

API_AVAILABLE(watchos(2.0)) API_UNAVAILABLE(ios)
@protocol CLKComplicationDataSource <NSObject>

#pragma mark Timeline Configuration

/// If you provide an end date then we will ask you for future entries up to the date.
/// If you return nil or do not implement this method we will only ask for your current timeline entry.
/// Timeline entries after the timeline end date will not be displayed.
@optional
- (void)getTimelineEndDateForComplication:(CLKComplication *)complication
                              withHandler:(void(^)(NSDate * __nullable date))handler;

/// Indicate whether your complication's data should be hidden when the watch is locked.
@optional
- (void)getPrivacyBehaviorForComplication:(CLKComplication *)complication
                              withHandler:(void(^)(CLKComplicationPrivacyBehavior behavior))handler;

/// Indicate your complication's animation behavior when transitioning between timeline entries.
@optional
- (void)getTimelineAnimationBehaviorForComplication:(CLKComplication *)complication
                                        withHandler:(void(^)(CLKComplicationTimelineAnimationBehavior behavior))handler;

/// Provide the entry that should currently be displayed during always on time.
/// If you pass back nil, we will continue to show the current timeline entry if it exists.
@optional
- (void)getAlwaysOnTemplateForComplication:(CLKComplication *)complication
                               withHandler:(void(^)(CLKComplicationTemplate * __nullable))handler API_AVAILABLE(watchos(6.0)) API_UNAVAILABLE(ios);


#pragma mark Timeline Population

/// Provide the entry that should currently be displayed.
/// If you pass back nil, we will conclude you have no content loaded and will stop talking to your until you next call -reloadTimelineForComplication:.
@required
- (void)getCurrentTimelineEntryForComplication:(CLKComplication *)complication
                                   withHandler:(void(^)(CLKComplicationTimelineEntry * __nullable))handler;

/// The owning complication will use these methods to extend its timeline forward.
/// @param date The date of the last entry we already have. Return the batch of entries after this date.
/// @param limit Maximum number of entries to return.
@optional
- (void)getTimelineEntriesForComplication:(CLKComplication *)complication
                                afterDate:(NSDate *)date
                                    limit:(NSUInteger)limit
                              withHandler:(void(^)(NSArray<CLKComplicationTimelineEntry *> * __nullable entries))handler;


#pragma mark - Sample Templates

/// This method will be called once per supported complication when your extension is installed, and the results cached.
/// It will be called again for each complication after you call -reloadComplicationDescriptors, and the results cached.

/// Provide a localizable template (that is, a template populated with localizable text providers) showing sample data for this complication. The template
/// should as much as possible reflect what your complication would normally look like, but the data should be fake.
/// If you pass back nil, we will use the default placeholder template (which is a combination of your icon and app name).
@optional
- (void)getLocalizableSampleTemplateForComplication:(CLKComplication *)complication
                                        withHandler:(void(^)(CLKComplicationTemplate * __nullable complicationTemplate))handler API_AVAILABLE(watchos(3.0)) API_UNAVAILABLE(ios);

#pragma mark - Multiple Complications

/// This method will be called once when your extension is installed, and the results cached.
/// If you need to invalidate this, call -reloadComplicationDescriptors.
/// Provide a complete list of the current complication descriptors that your extension supports. These will be available
/// during complication editing.
@optional
- (void)getComplicationDescriptorsWithHandler:(void(^)(NSArray<CLKComplicationDescriptor *> *))handler API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);

/// This method will be called each time a watch face is shared with this device that contains complications
/// from your extension. Ensure you do any necessary work to support these complications as much as possible.
@optional
- (void)handleSharedComplicationDescriptors:(NSArray<CLKComplicationDescriptor *> *)complicationDescriptors API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios);



#pragma mark - Deprecated

@optional
- (void)getPlaceholderTemplateForComplication:(CLKComplication *)complication withHandler:(void(^)(CLKComplicationTemplate * __nullable complicationTemplate))handler API_DEPRECATED_WITH_REPLACEMENT("getLocalizableSampleTemplateForComplication:withHandler:", watchos(2.0, 4.0));

#pragma mark Time Travel

@optional
- (void)getSupportedTimeTravelDirectionsForComplication:(CLKComplication *)complication withHandler:(void(^)(CLKComplicationTimeTravelDirections directions))handler API_DEPRECATED("Time Travel is no longer supported. Use CLKComplicationDataSource's getTimelineEndDateWithHandler: to specify forward timeline support.", watchos(2.0, 7.0));

@optional
- (void)getTimelineStartDateForComplication:(CLKComplication *)complication withHandler:(void(^)(NSDate * __nullable date))handler API_DEPRECATED("Time Travel and backwards extension of timelines are no longer supported.", watchos(2.0, 7.0));

@optional
- (void)getTimelineEntriesForComplication:(CLKComplication *)complication beforeDate:(NSDate *)date limit:(NSUInteger)limit
                              withHandler:(void(^)(NSArray<CLKComplicationTimelineEntry *> * __nullable entries))handler API_DEPRECATED("Time Travel and backwards extension of timelines are no longer supported.", watchos(2.0, 7.0));

#pragma mark Update Scheduling

/// These methods will no longer be called for clients adopting the WKRefreshBackgroundTask APIs, which are the recommended means of scheduling updates.
/// In a future release these methods will no longer be called.

/// Return the date when you would next like to be given the opportunity to update your complication content.
/// We will make an effort to launch you at or around that date, subject to power and budget limitations.
@optional
- (void)getNextRequestedUpdateDateWithHandler:(void(^)(NSDate * __nullable updateDate))handler API_DEPRECATED("Use WKRefreshBackgroundTask instead", watchos(2.0, 4.0));

/// This method will be called when you are woken due to a requested update. If your complication data has changed you can
/// then call -reloadTimelineForComplication: or -extendTimelineForComplication: to trigger an update.
@optional
- (void)requestedUpdateDidBegin API_DEPRECATED("Use WKRefreshBackgroundTask instead", watchos(2.0, 4.0));

/// This method will be called when we would normally wake you for a requested update but you are out of budget. You can can
/// trigger one more update at this point (by calling -reloadTimelineForComplication: or -extendTimelineForComplication:) but
/// this will be the last time you will be woken until your budget is replenished.
@optional
- (void)requestedUpdateBudgetExhausted API_DEPRECATED("Use WKRefreshBackgroundTask instead", watchos(2.0, 4.0));

@end


NS_ASSUME_NONNULL_END
