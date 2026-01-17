//
//  CTCellularPlanStatus.h
//  CFTelephony
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(19_0)
@interface CTCellularPlanStatus : NSObject

+ (void) getTokenWithCompletion:(void (^)(NSString * _Nullable token, NSError* _Nullable error))completionHandler __API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, watchos);
+ (void) checkValidityOfToken:(NSString *)token completionHandler:(void (^)(BOOL isValid, NSError* _Nullable error))completionHandler __API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
