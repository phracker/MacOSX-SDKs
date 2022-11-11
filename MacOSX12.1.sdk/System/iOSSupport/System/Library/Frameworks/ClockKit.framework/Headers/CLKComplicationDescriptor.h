//
//  CLKComplicationDescriptor.h
//  ClockKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClockKit/CLKDefines.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(watchos(7.0)) API_UNAVAILABLE(ios)
@interface CLKComplicationDescriptor : NSObject

/// Identifies this complication.
@property (nonatomic, readonly) NSString *identifier;

/// The display name for this complication.
/// This will be displayed when editing complications of a watch face.
@property (nonatomic, readonly) NSString *displayName;

/// An array of `CLKComplicationFamily`s that this complication supports.
@property (nonatomic, readonly) NSArray<NSNumber *> *supportedFamilies NS_REFINED_FOR_SWIFT;

/// An optional dictionary that can be used to pass information back to your extension via CLKComplication.
@property (nonatomic, readonly, nullable) NSDictionary *userInfo;

/// An optional user activity that can be used to pass information back to your extension via CLKComplication.
/// This activity will be used to launch your app when the complication is tapped on.
@property (nonatomic, readonly, nullable) NSUserActivity *userActivity;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       displayName:(NSString *)displayName
                 supportedFamilies:(NSArray<NSNumber *> *)supportedFamilies NS_REFINED_FOR_SWIFT;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       displayName:(NSString *)displayName
                 supportedFamilies:(NSArray<NSNumber *> *)supportedFamilies
                          userInfo:(NSDictionary *)userInfo NS_REFINED_FOR_SWIFT;

- (instancetype)initWithIdentifier:(NSString *)identifier
                       displayName:(NSString *)displayName
                 supportedFamilies:(NSArray<NSNumber *> *)supportedFamilies
                      userActivity:(NSUserActivity *)userActivity NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
