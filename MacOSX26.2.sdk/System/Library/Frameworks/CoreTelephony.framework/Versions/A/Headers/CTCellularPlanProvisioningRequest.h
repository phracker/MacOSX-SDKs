//
//  CTCellularPlanProvisioningRequest.h
//  CFTelephony
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

API_AVAILABLE_BEGIN(ios(12.0), watchos(5.0))

typedef NS_ENUM(NSUInteger, CTCellularPlanProvisioningAddPlanResult) {
	CTCellularPlanProvisioningAddPlanResultUnknown,
	CTCellularPlanProvisioningAddPlanResultFail,
	CTCellularPlanProvisioningAddPlanResultSuccess,
	CTCellularPlanProvisioningAddPlanResultCancel API_AVAILABLE(ios(17.0))
};

CORETELEPHONY_EXTERN_CLASS 
API_UNAVAILABLE(macos, tvos)
@interface CTCellularPlanProvisioningRequest : NSObject<NSSecureCoding>

@property (nonatomic, strong, nonnull)  NSString *address           API_UNAVAILABLE(tvos, macosx);	
@property (nonatomic, strong, nullable) NSString *matchingID        API_UNAVAILABLE(tvos, macosx);
@property (nonatomic, strong, nullable) NSString *OID               API_UNAVAILABLE(tvos, macosx);
@property (nonatomic, strong, nullable) NSString *confirmationCode  API_UNAVAILABLE(tvos, macosx);
@property (nonatomic, strong, nullable) NSString *ICCID             API_UNAVAILABLE(tvos, macosx);
@property (nonatomic, strong, nullable) NSString *EID               API_UNAVAILABLE(tvos, macosx);

@end
API_AVAILABLE_END

#endif // __OBJC__
