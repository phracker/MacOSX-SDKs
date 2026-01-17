#import <TargetConditionals.h>
#if !TARGET_OS_TV
//
//  SWHighlightMentionEvent_Private.h
//  SocialLayer
//
//  Created by Elliot Barer on 2/7/22.
//

#import <Foundation/Foundation.h>
#import <SharedWithYou/SWHighlight.h>
#import <SharedWithYou/SWHighlightEvent.h>

@class SWHighlight;
@class SWPersonIdentity;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class _SWHighlightMentionEvent
 @abstract A model object representing a mention event that has happened on some content.
 */
API_AVAILABLE(ios(16.0), macos(13.0))
SW_EXTERN @interface SWHighlightMentionEvent : NSObject <SWHighlightEvent>

/// The person being mentioned by the sender.
@property (nonatomic, readonly, strong) NSString *mentionedPersonHandle;

/// Initializes a highlight mention event object when the sender mentions another participant.
/// @param highlight The object on which the event occurred.
/// @param handle The CloudKit handle of the person being mentioned by the sender.
- (instancetype)initWithHighlight:(SWHighlight *)highlight mentionedPersonCloudKitShareHandle:(NSString *)handle;

/// Initializes a highlight mention event object when the sender mentions another participant.
/// @param highlight The object on which the event occurred.
/// @param identity The identity of the person being mentioned by the sender.
- (instancetype)initWithHighlight:(SWHighlight *)highlight mentionedPersonIdentity:(SWPersonIdentity *)identity;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // !TARGET_OS_TV
