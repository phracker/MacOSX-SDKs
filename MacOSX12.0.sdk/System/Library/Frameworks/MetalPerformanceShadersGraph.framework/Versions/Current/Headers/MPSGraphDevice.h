//
//  MPSGraphDevice.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/12/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphDevice_h
#define MPSGraphDevice_h

#import <MetalPerformanceShadersGraph/MPSGraphCore.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @typedef    MPSGraphDeviceType
 *  @abstract   Device type, Metal
 *
 *  @constant   MPSGraphDeviceTypeMetal           Device of type Metal
 */
typedef NS_ENUM(uint32_t, MPSGraphDeviceType)
{
    MPSGraphDeviceTypeMetal                            MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(metal)  =   0L,
};

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphDevice : NSObject

/*! @property   type
 */
@property (readonly, nonatomic) MPSGraphDeviceType type;

/*! @property   metalDevice
 *  @discussion if deviceType GPU then returns MTLDevice or nil
 */
@property (readonly, nonatomic, nullable) id<MTLDevice> metalDevice;

/*!
 *  @abstract   Creates a MEtal MPSGraphDevice from a MTLDevice
 *
 *  @param      metalDevice                                           MTLDevice to create an MPSGraphDevice from
 *  @return     A valid MPSGraphDevice
 */
+(instancetype) deviceWithMTLDevice:(id<MTLDevice>) metalDevice;

@end

NS_ASSUME_NONNULL_END

#endif /* MPSGraphDevice_h */
