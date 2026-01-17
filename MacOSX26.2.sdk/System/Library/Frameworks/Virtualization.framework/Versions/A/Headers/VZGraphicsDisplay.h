//
//  VZGraphicsDisplay.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZGraphicsDisplayConfiguration;
@protocol VZGraphicsDisplayObserver;

/*!
 @abstract Class representing a graphics display in a virtual machine.
 @discussion
    VZGraphicsDisplay should not be instantiated directly.

    Graphics displays are first configured on a VZGraphicsDeviceConfiguration subclass.
    When a VZVirtualMachine is created from the configuration, the displays
    are available through the VZGraphicsDevice's `displays` property.

 @see VZMacGraphicsDisplayConfiguration
 @see VZVirtioGraphicsScanoutConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZGraphicsDisplay : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract The size of the display, in pixels.
*/
@property (readonly) CGSize sizeInPixels;

/*!
 @abstract Resize this display.
 @param sizeInPixels New display width and height in pixels.
 @param error If not nil, assigned with an error describing why the new size is not valid.
 @return YES if the resize is successful, NO otherwise.
 @discussion
    If successful, the new size will be passed to the guest but the guest may or may
    not respond to the new size. The guest not using the size does not return an error.

    Reconfiguration triggers a display state change which can be tracked by VZGraphicsDisplayObservers.
*/
- (BOOL)reconfigureWithSizeInPixels:(CGSize)sizeInPixels error:(NSError **)error NS_SWIFT_NAME(reconfigure(sizeInPixels:));

/*!
 @abstract Reconfigure this display.
 @param configuration New display configuration.
 @param error If not nil, assigned with an error describing why the new configuration is not valid.
 @return YES if the reconfiguration is successful, NO otherwise.
 @discussion
    The type of the configuration must match the corresponding type that caused this display to be created.

    If successful, the new configuration will be passed to the guest but the guest may or may
    not respond to parts of the configuration. The guest not using the new configuration does not
    return an error.

    Reconfiguration triggers a display state change which can be tracked by VZGraphicsDisplayObservers.
*/
- (BOOL)reconfigureWithConfiguration:(VZGraphicsDisplayConfiguration *)configuration error:(NSError **)error NS_SWIFT_NAME(reconfigure(configuration:));

/*!
 @abstract Add an observer.
 @param observer The new observer to be notified of display state changes.
*/
- (void)addObserver:(id <VZGraphicsDisplayObserver>)observer NS_SWIFT_NAME(addObserver(_:));

/*!
 @abstract Remove an observer.
 @param observer The observer to be removed.
*/
- (void)removeObserver:(id <VZGraphicsDisplayObserver>)observer NS_SWIFT_NAME(removeObserver(_:));

@end

/*!
 @abstract VZGraphicsDisplayObserver observes a VZGraphicsDisplay for state changes.
*/
VZ_EXPORT API_AVAILABLE(macos(14.0))
@protocol VZGraphicsDisplayObserver <NSObject>
@optional

/*!
 @abstract A reconfiguration operation has begun.
 @discussion
    A configuration change, such as a resize, has been issued and new frames are expected with a new size or configuration.
    This method will be invoked on the virtual machine's queue.
 @param display The display whose state is changing.
*/
- (void)displayDidBeginReconfiguration:(VZGraphicsDisplay *)display;

/*!
 @abstract A reconfiguration operation has ended.
 @discussion
    Frame updates have arrived at the most recently requested display size and configuration.
    This method will be invoked on the virtual machine's queue.
 @param display The display whose state is changing.
*/
- (void)displayDidEndReconfiguration:(VZGraphicsDisplay *)display;

@end

NS_ASSUME_NONNULL_END
