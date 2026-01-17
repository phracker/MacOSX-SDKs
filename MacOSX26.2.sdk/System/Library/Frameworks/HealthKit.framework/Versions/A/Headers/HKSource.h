//
//  HKSource.h
//  HealthKit
//
//  Copyright (c) 2014-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class     HKSource
 @abstract  Represents the entity that created an object stored by HealthKit.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKSource : NSObject <NSSecureCoding, NSCopying>

/*!
 @property      name
 @abstract      The name of the source represented by the receiver.  If the source is an app, then the name is the
                localized name of the app.
 */
@property (readonly, strong) NSString *name;

/*!
 @property  bundleIdentifier
 @abstract  The bundle identifier of the source represented by the receiver.
 */
@property (readonly, strong) NSString *bundleIdentifier;

/*!
 @method    defaultSource
 @abstract  Returns the source representing the calling application.
 */
+ (HKSource *)defaultSource;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
