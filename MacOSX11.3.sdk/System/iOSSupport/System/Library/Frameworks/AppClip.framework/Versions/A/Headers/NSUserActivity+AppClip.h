// Copyright © 2020 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

@class APActivationPayload;

NS_ASSUME_NONNULL_BEGIN

/*!
* @category    NSUserActivity
*
* @discussion  App clip category for NSUserActivity.
*/
@interface NSUserActivity (AppClip)

/*!
*  @property appClipActivationPayload
*
*  @discussion The activation payload object that triggers the app clip launch.
*/
@property (nonatomic, strong, readonly, nullable) APActivationPayload *appClipActivationPayload API_AVAILABLE(ios(14.0));

@end

NS_ASSUME_NONNULL_END
