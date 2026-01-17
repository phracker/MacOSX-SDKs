/*!
 @header     MSMessageLiveLayout
 @copyright  Copyright (c) 2017 Apple Inc. All rights reserved.
 */

#import <Messages/Messages.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class      MSMessageLiveLayout
 @abstract   The MSMessageLiveLayout is used to indicate a message should be rendered in Messages using an instance of `MSMessagesAppViewController` with a `presentationStyle` of `MSMessagesAppPresentationStyleTranscript`.
 */
NS_CLASS_AVAILABLE_IOS(11_0)
@interface MSMessageLiveLayout : MSMessageLayout

/*!
 @param alternateLayout The alternate layout of the message. This layout will be used on devices that don't support live layout or don't have the iMessage app installed.
 */
- (instancetype)initWithAlternateLayout:(MSMessageTemplateLayout *)alternateLayout NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @property   alternateLayout
 @abstract   The alternate layout of the message. This layout will be used on devices that don't support live layout or don't have the iMessage app installed.
 */
@property (nonatomic, readonly) MSMessageTemplateLayout *alternateLayout;

@end

NS_ASSUME_NONNULL_END
