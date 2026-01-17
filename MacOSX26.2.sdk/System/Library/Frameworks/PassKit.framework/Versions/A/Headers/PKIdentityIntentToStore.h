#if !__has_include(<PassKitCore/PKIdentityIntentToStore.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKIdentityIntentToStore.h
//    PassKit
//
//  Copyright © 2022 Apple, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Indicates your intention to store an identity element. This covers not only
/// the element value, but also information derived from the element value such
/// as signatures or digests.
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface PKIdentityIntentToStore: NSObject <NSCopying>

/// Indicates the data element returned in the response will not be stored for
/// a period longer than necessary to process the result in realtime.
@property (class, nonatomic, readonly) PKIdentityIntentToStore *willNotStoreIntent NS_SWIFT_NAME(willNotStore);

/// Indicates the data element may be stored for an indefinite length of time.
@property (class, nonatomic, readonly) PKIdentityIntentToStore *mayStoreIntent NS_SWIFT_NAME(mayStore);

/// Indicates the data element may be stored for no longer than than the provided number of days.
+ (instancetype)mayStoreIntentForDays:(NSInteger)days NS_SWIFT_NAME(mayStore(days:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKIdentityIntentToStore.h>
#endif