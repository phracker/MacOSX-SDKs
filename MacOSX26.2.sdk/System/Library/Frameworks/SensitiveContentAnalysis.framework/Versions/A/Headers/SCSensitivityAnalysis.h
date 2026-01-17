//
//  SCSensitivityAnalysis.h
//  SensitiveContentAnalysis
//
//  Copyright (c).2024, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Sensitive Analysis Results object is returned after sensitivity analysis is performed on media
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface SCSensitivityAnalysis : NSObject
/// Set to YES if analyzed media contains sensitive content
@property(readonly, getter=isSensitive) BOOL sensitive;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
