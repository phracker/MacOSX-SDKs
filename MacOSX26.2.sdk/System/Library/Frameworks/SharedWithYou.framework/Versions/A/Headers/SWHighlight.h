//
//  SWHighlight.h
//  SWHighlight
//
//  Copyright (c) 2021 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
     @class SWHighlight
     @abstract A model object representing a universal link shared by any number of contacts, in any number of conversations. The identities of the contacts are not exposed to the application.
     @discussion The system tracks universal links shared with the current user, and decides which links to elevate for consumption in an app. When the system deems a link to be useful, it surfaces that link to the hosting app in the form of an `SWHighlight` object. Only universal links can be surfaced in this way.
 */
API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0))
SW_EXTERN @interface SWHighlight : NSObject <NSSecureCoding, NSCopying>

/*!
    @abstract The unique identifier for this highlight
 */
@property (copy, readonly, nonatomic) id <NSSecureCoding, NSCopying> identifier;

/*!
    @abstract The surfaced content URL
 */
@property (copy, readonly, nonatomic) NSURL *URL;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
