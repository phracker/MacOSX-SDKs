//
//  MLCPlatform.h
//  MLCompute
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCDefines.h>

/*!
 @class     MLCPlatform
 @abstract  Utility class to set MLCompute global properties
 */
NS_ASSUME_NONNULL_BEGIN

MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MLCPlatform : NSObject

/*!
@method    setRNGSeedTo
@abstract  sets the RNG seed. The seed should be of type long int.
*/
+ (void)setRNGSeedTo:(NSNumber *)seed;

/*!
@method    getRNGseed
@abstract  gets the RNG seed value. If the value is not set it would return nil
*/
+ (NSNumber * _Nullable)getRNGseed;

@end

NS_ASSUME_NONNULL_END

