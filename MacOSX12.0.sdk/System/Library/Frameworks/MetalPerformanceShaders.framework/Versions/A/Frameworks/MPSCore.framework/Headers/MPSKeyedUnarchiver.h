//
//  MPSKeyedUnarchiver.h
//  MPSCore
//
//  Created on 1/23/18.
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef MPSKeyedUnarchiver_h
#define MPSKeyedUnarchiver_h
#ifdef __cplusplus
extern "C" {
#endif
    
#import <MPSCore/MPSCoreTypes.h>

/*! @class MPSKeyedUnarchiver
 *  @abstract A NSKeyedArchiver that supports the MPSDeviceProvider protocol for MPSKernel decoding */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13.4), ios(11.3), macCatalyst(13.0), tvos(11.3))
@interface MPSKeyedUnarchiver : NSKeyedUnarchiver <MPSDeviceProvider>

/* Common NSKeyedUnarchiver methods */
+ (nullable id)unarchivedObjectOfClasses:(NSSet<Class> * __nonnull)classes
                                fromData:(NSData * __nonnull)data
                                  device: (__nonnull id <MTLDevice>) device
                                   error:(NSError * __nullable * __nullable)error
        MPS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));

+ (nullable id)unarchivedObjectOfClass:(__nonnull Class)cls
                              fromData:(NSData * __nonnull)data
                                device: (__nonnull id <MTLDevice>) device
                                 error:(NSError * __nullable * __nullable)error
        MPS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));

- (nonnull instancetype)initForReadingFromData: (NSData * __nonnull)data
                                        device: (__nonnull id <MTLDevice>) device
                                         error: (NSError * __nullable * __nullable)error
        MPS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0));

/*! @abstract   Reports which device to use for unarchiving MPSKernels */
-(__nonnull id <MTLDevice>) mpsMTLDevice;

/* Unavailable API from superclass. */
+ (nullable id)unarchivedObjectOfClasses:(NSSet<Class> * __nonnull)classes
                                fromData:(NSData * __nonnull)data
                                   error:(NSError * __nullable * __nullable)error NS_UNAVAILABLE;
+ (nullable id)unarchivedObjectOfClass:(__nonnull Class)cls
                              fromData:(NSData * __nonnull)data
                                 error:(NSError * __nullable * __nullable)error NS_UNAVAILABLE;
- (nonnull instancetype)init NS_UNAVAILABLE;
- (nonnull instancetype)initForReadingFromData:(NSData * __nonnull)data
                                         error:(NSError * __nullable * __nullable)error NS_UNAVAILABLE;


/* Deprecated API. */
+ (nullable id)unarchiveObjectWithData: (NSData * __nonnull)data NS_UNAVAILABLE;
+ (nullable id)unarchiveObjectWithData: (NSData *__nonnull)data
                                device: (__nonnull id <MTLDevice>) device
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Please use -unarchivedObjectOfClass:fromData:device:error: instead", macos(10.13.4, 10.14), ios(11.3, 12.0), tvos(11.3,12.0))  MPS_UNAVAILABLE(macCatalyst);
+ (nullable id)unarchiveTopLevelObjectWithData:(NSData *__nonnull)data
                                         error:(NSError * __nullable * __nullable)error NS_UNAVAILABLE;
+ (nullable id)unarchiveTopLevelObjectWithData:(NSData *__nonnull)data
                                        device: (__nonnull id <MTLDevice>) device
                                         error:(NSError * __nullable * __nullable)error
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Please use -unarchivedObjectOfClass:fromData:device:error: instead", macos(10.13.4, 10.14), ios(11.3, 12.0), tvos(11.3,12.0))  MPS_UNAVAILABLE(macCatalyst);

+ (nullable id)unarchiveObjectWithFile:(NSString * __nonnull)path NS_UNAVAILABLE;
- (nonnull instancetype)initForReadingWithData:(NSData * __nonnull)data NS_UNAVAILABLE;

+ (nullable id)unarchiveObjectWithFile:(NSString * __nonnull)path
                                device: (__nonnull id <MTLDevice>) device
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Please use -initForReadingFromData:device:error: instead", macos(10.13.4, 10.14), ios(11.3, 12.0), tvos(11.3,12.0))  MPS_UNAVAILABLE(macCatalyst);

- (nullable instancetype)initWithDevice: (__nonnull id <MTLDevice>) device
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Please use -initForReadingFromData:device:error: instead", macos(10.13.4, 10.14), ios(11.3, 12.0), tvos(11.3,12.0))  MPS_UNAVAILABLE(macCatalyst);

- (nonnull instancetype)initForReadingWithData:(NSData * __nonnull)data
                                        device: (__nonnull id <MTLDevice>) device
        MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Please use -initForReadingFromData:device:error: instead", macos(10.13.4, 10.14), ios(11.3, 12.0), tvos(11.3,12.0))  MPS_UNAVAILABLE(macCatalyst);

@end
    
    
#ifdef __cplusplus
}
#endif


#endif /* MPSKeyedArchiver_h */
