#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneActivationConditions.h>)
//
//  UISceneActivationConditions.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UISceneActivationConditions : NSObject <NSSecureCoding>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

/* A scene "can" activate for target content if it is possible for that content to be displayed in that scene. A scene "prefers" to activate for content if it is a better scene session to activate for that content than any scene that only "can" view it.
 
 These predicates are used to match against targetContentIdentifier NSStrings wherever they occur, for example in UNNotificationContent, as well as against NSString text of URL links the user may tap if the application handles URLs.
 
 Predicates used here must not be block or selector based, must not use the 'MATCHES' operator, and may not access any key paths other than 'self' off of the NSString they're evaluated against.
 */
@property(nonatomic, copy) NSPredicate *canActivateForTargetContentIdentifierPredicate; // default is [NSPredicate predicateWithValue:YES]
@property(nonatomic, copy) NSPredicate *prefersToActivateForTargetContentIdentifierPredicate; // default is [NSPredicate predicateWithValue:NO];

@end


UIKIT_EXTERN @interface NSUserActivity (UISceneActivationConditions)
// used with UISceneActivationConditions to customize what scene should be activated for a user activity
@property (nullable, nonatomic, copy) NSString *targetContentIdentifier API_AVAILABLE(ios(13.0)); //  default nil
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISceneActivationConditions.h>
#endif
