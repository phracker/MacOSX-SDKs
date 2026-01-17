//
//  HKSeriesSample.h
//  HealthKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @class         HKSeriesSample
 @abstract      This class represents a type of HKSample that references a series of data.
 */
HK_EXTERN
@interface HKSeriesSample : HKSample

/*!
 @property      count
 @abstract      The number of individual series datum represented by the receiver and accessible
                through the appropriate HKQuery series subclass.
 */
@property (readonly) NSUInteger count;

@end


NS_ASSUME_NONNULL_END
