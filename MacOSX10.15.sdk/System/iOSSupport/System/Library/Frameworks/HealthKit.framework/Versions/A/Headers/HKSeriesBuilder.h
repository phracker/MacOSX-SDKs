//
//  HKSeriesBuilder.h
//  HealthKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKSeriesBuilder
 @abstract      An HKSeriesBuilder is an abstract class for generating HKSeriesSample objects. 
                Concrete subclasses generate the actual HKSeriesSample objects.
 */
HK_EXTERN
@interface HKSeriesBuilder : NSObject

/*!
 @method        discard
 @abstract      Stop series generation and discard all collected data.
 @discussion    This method informs the receiver that no more data should be collected and all
                previously collected data should be deleted and the receiver will be considered
                invalid. Any further calls to the receiver will result in an exception.
 */
- (void)discard;


/*!
 @method        init
 @abstract      Use only subclass initializer methods.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
