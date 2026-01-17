//
//  CTCellularPlanProvisioning.h
//  CoreTelephony
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>
#import <CoreTelephony/CTCellularPlanProvisioningRequest.h>
#import <CoreTelephony/CTCellularPlanProperties.h>

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(12_0)
@interface CTCellularPlanProvisioning : NSObject

@property (nonatomic, readonly) BOOL supportsEmbeddedSIM  __API_AVAILABLE(ios(16.0));

- (BOOL)supportsCellularPlan   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_12_0);

- (void)addPlanWith:(CTCellularPlanProvisioningRequest *)request completionHandler:(void (^)(CTCellularPlanProvisioningAddPlanResult result))completionHandler   __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_12_0) API_UNAVAILABLE(macos, tvos);

- (void)addPlanWithRequest:(CTCellularPlanProvisioningRequest *)request properties:(CTCellularPlanProperties * _Nullable)properties completionHandler:(void (^)(CTCellularPlanProvisioningAddPlanResult result))completionHandler NS_SWIFT_NAME(addPlan(request:properties:completionHandler:)) __API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos);

- (void)updateCellularPlanProperties:(CTCellularPlanProperties *)properties completionHandler:(void (^)(NSError* _Nullable error))completionHandler __API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
