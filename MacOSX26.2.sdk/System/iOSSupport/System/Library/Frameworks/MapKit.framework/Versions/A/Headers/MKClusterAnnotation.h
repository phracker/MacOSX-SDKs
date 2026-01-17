//
//  MKClusterAnnotation.h
//  MapKit
//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#import <MapKit/MKAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0) API_UNAVAILABLE(watchos)
@interface MKClusterAnnotation : NSObject <MKAnnotation>

@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) NSString *subtitle;
@property (nonatomic, readonly) NSArray<id<MKAnnotation>> *memberAnnotations;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithMemberAnnotations:(NSArray<id<MKAnnotation>> *)memberAnnotations NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
