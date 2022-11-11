//
//  PHASEGeneratorParameters.h
//  PHASE
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef PHASEGeneratorParams_h
#define PHASEGeneratorParams_h

#import <PHASE/PHASEGroup.h>
#import <PHASE/PHASETypes.h>

@class PHASENumberMetaParameterDefinition;

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*! @interface PHASEGeneratorParameters
 *  @abstract An object that holds a standard set of audio parameters common to several objects
 */
OS_EXPORT API_DEPRECATED("", macos(10.15, 10.15), ios(14.0,14.0), tvos(15.0,15.0)) API_UNAVAILABLE(watchos)
@interface PHASEGeneratorParameters : NSObject

/*! @property gain
    @abstract Linear gain scalar.
    @note Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic, assign) double gain;

/*! @property gain
    @abstract Linear gain scalar.
    @note Values are clamped to the range [0.25, 4]. Default value is 1.
*/
@property(nonatomic, assign) double rate;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEGeneratorParams_h */
