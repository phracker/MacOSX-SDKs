//
//  HKQueryAnchor.h
//  HealthKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKQueryAnchor
 @discussion    This object encapsulates the state of an HKAnchoredObjectQuery
 */
HK_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0))
@interface HKQueryAnchor : NSObject <NSSecureCoding, NSCopying>

/*!
 @method        anchorFromValue:
 @discussion    Creates an HKQueryAnchor with an integer anchor which was previously obtained from an
                HKAnchoredObjectQuery prior to iOS 9.0.
 */
+ (instancetype)anchorFromValue:(NSUInteger)value;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
