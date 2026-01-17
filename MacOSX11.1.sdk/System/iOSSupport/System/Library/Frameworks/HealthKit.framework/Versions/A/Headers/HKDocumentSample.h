//
//  HKDocumentSample.h
//  HealthKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <HealthKit/HKSample.h>

NS_ASSUME_NONNULL_BEGIN

@class HKDocumentType;

/*!
 @class         HKDocumentSample
 @abstract      An abstract class representing a health document.
 */
HK_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0))
@interface HKDocumentSample : HKSample

@property (readonly, strong) HKDocumentType *documentType;

@end

NS_ASSUME_NONNULL_END
