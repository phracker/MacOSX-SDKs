//
//  AEAssessmentApplication.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), macCatalyst(15.0), macos(12.0))
@interface AEAssessmentApplication : NSObject <NSCopying>

@property (nonatomic, copy, readonly) NSString *bundleIdentifier API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);
@property (nonatomic, copy, readonly, nullable) NSString *teamIdentifier API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);
@property (nonatomic, assign) BOOL requiresSignatureValidation API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);

- (instancetype)initWithBundleIdentifier:(NSString *)bundleIdentifier API_AVAILABLE(macCatalyst(15.0), macos(12.0)) API_UNAVAILABLE(ios);
- (instancetype)initWithBundleIdentifier:(NSString *)bundleIdentifier
                          teamIdentifier:(nullable NSString *)API_AVAILABLE(macCatalyst(15.0), macos(12.0)) teamIdentifier API_UNAVAILABLE(ios);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
