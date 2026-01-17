//
//  SCContentSharingPicker.h
//  ScreenCaptureKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 @typedef SCContentSharingPickerMode
 @abstract SCContentSharingPickerModeSingleWindow picker mode for single window selection
 @constant SCContentSharingPickerModeMultipleWindows picker mode for multiple window selection
 @constant SCContentSharingPickerModeSingleApplication picker mode for application selection
 @constant SCContentSharingPickerModeSingleDisplay picker mode for full display selection
*/
typedef NS_OPTIONS(NSUInteger, SCContentSharingPickerMode) {
    SCContentSharingPickerModeSingleWindow          = 1 << 0,
    SCContentSharingPickerModeMultipleWindows       = 1 << 1,
    SCContentSharingPickerModeSingleApplication     = 1 << 2,
    SCContentSharingPickerModeMultipleApplications  = 1 << 3,
    SCContentSharingPickerModeSingleDisplay         = 1 << 4
} API_AVAILABLE(macos(14.0), macCatalyst(18.2));

@protocol SCContentSharingPickerObserver;

/*!
 @abstract SCContentSharingPickerConfiguration
 @discussion SCContentSharingPickerConfiguration is an object which can optionally be set on the SCContentSharingPicker for customized configuration.
*/
API_AVAILABLE(macos(14.0), macCatalyst(18.2))
NS_REFINED_FOR_SWIFT
@interface SCContentSharingPickerConfiguration <NSCopying>: NSObject
/*!
 @abstract allowedPickerModes Limits the type of selections available to the user when the picker is presented. Default is 0, no excluded picking modes
 */
@property (nonatomic, assign) SCContentSharingPickerMode allowedPickerModes;

/*!
 @abstract excludedWindowIDs Excludes CGWindowIDs for picking
 */
@property (nonatomic, strong) NSArray<NSNumber *> *excludedWindowIDs;

/*!
 @abstract excludedBundleIDs Excludes bundle IDs for picking
 */
@property (nonatomic, strong) NSArray<NSString *> *excludedBundleIDs;

/*!
 @abstract allowsChangingSelectedContent Controls if the user can make updates to the content filter after the initial selection. Defaults is YES.
 */
@property (nonatomic, assign) BOOL allowsChangingSelectedContent;

@end

/*!
 @abstract SCContentSharingPicker
 @discussion SCContentSharingPicker is an object created by client applications to opt-in to Control Center's content picker
*/
API_AVAILABLE(macos(14.0), macCatalyst(18.2))
@interface SCContentSharingPicker : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @abstract sharedPicker the singleton shared picker for the application
 */
@property (class, readonly) SCContentSharingPicker *sharedPicker;

/*!
 @abstract defaultConfiguration for the content sharing picker. If a stream does not have a configuration, the default configuration will be used.
 */
@property (nonatomic, copy) SCContentSharingPickerConfiguration *defaultConfiguration NS_REFINED_FOR_SWIFT;

/*!
 @abstract maximumStreamCount An integer value that, if set, limits when Control Center will show the UI to present a picker with no associated stream. If set to 0, Control Center will never ever show UI to present a picker without an associated stream.
 */
@property (nonatomic, nullable, strong) NSNumber *maximumStreamCount NS_REFINED_FOR_SWIFT;

/*!
 @abstract active A picker needs to be marked as active for its UI to appear. If `startPickingContent` is called and the picker is not marked as active, the picker will not appear.
 */
@property (nonatomic, assign, getter=isActive) BOOL active;

/*!
 @abstract addObserver:
 @param observer the observer object that adheres to SCContentSharingPickerObserver protocol
 @discussion Adds an observer object that will receive the results of user interaction with a displayed picker
*/
- (void)addObserver:(id<SCContentSharingPickerObserver>)observer;

/*!
 @abstract removeObserver:
 @param observer the observer object that adheres to SCContentSharingPickerObserver protocol
 @discussion Removes an observer object that will receive the results of user interaction with a displayed picker
*/
- (void)removeObserver:(id<SCContentSharingPickerObserver>)observer;

/*!
 @abstract setConfiguration:forStream:
 @param pickerConfig configuration for the picker
 @param stream stream for optional picking configuration
 @discussion Sets optional configuration for the picker for a specific stream. If this is not set, the stream will use the defaultConfiguration instead
*/
- (void)setConfiguration:(nullable SCContentSharingPickerConfiguration *)pickerConfig forStream:(SCStream *)stream NS_REFINED_FOR_SWIFT;

/*!
 @abstract present
 @discussion show content sharing picker to get content for updating a new stream
*/
- (void)present;

/*!
 @abstract presentPickerUsingContentStyle:
 @param contentStyle the mode in which picking should start
 @discussion Takes a person straight into picking particular windows or displays
*/
- (void)presentPickerUsingContentStyle:(SCShareableContentStyle)contentStyle;

/*!
 @abstract presentPickerForStream:
 @param stream the stream to update
 @discussion show content sharing picker with an existing stream
*/
- (void)presentPickerForStream:(SCStream *)stream;

/*!
 @abstract presentPickerForStream:usingContentStyle:
 @param stream the stream that the picker will display
 @param contentStyle the mode in which picking should start
 @discussion Takes a person straight into picking particular windows or displays
*/
- (void)presentPickerForStream:(SCStream *)stream usingContentStyle:(SCShareableContentStyle)contentStyle;
@end

/*!
 @abstract SCContentSharingPickerObserver
 @discussion SCContentSharingPickerObserver the protocol that is used to inform client when the picker did make selection or cancel
*/
API_AVAILABLE(macos(14.0), macCatalyst(18.2))
@protocol SCContentSharingPickerObserver <NSObject>
/*!
 @abstract contentSharingPicker:didCancelforStream:
 @param picker the SCContentSharingPicker object
 @param stream the optional associated stream for this picker
 @discussion the observer callback method when the picker has been canceled with no selection.
*/
- (void)contentSharingPicker:(SCContentSharingPicker *)picker didCancelForStream:(nullable SCStream *)stream;

/*!
 @abstract contentSharingPicker:didUpdateWithFilter:forStream:
 @param picker the SCContentSharingPicker object
 @param filter the updated filter
 @param stream the updated stream
 @discussion the observer callback method when the user has finished updating content for a stream
*/
- (void)contentSharingPicker:(SCContentSharingPicker *)picker didUpdateWithFilter:(SCContentFilter *)filter forStream:(nullable SCStream *)stream;

/*!
 @abstract contentSharingPickerStartDidFailWithError:
 @param error the error denoted for the failure to start picker
 @discussion the observer callback method when the picker was asked to start but failed to do so.
*/
- (void)contentSharingPickerStartDidFailWithError:(NSError *)error;
@end

NS_ASSUME_NONNULL_END
