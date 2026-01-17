//
//  SNTypes.h
//  SoundAnalysis
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SoundAnalysis/SNDefines.h>

/// Identifiers denoting particular recognized sound classifiers.
typedef NSString *SNClassifierIdentifier NS_TYPED_ENUM API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Denotes the first edition of the Apple-provided sound classifier.
SN_EXPORT SNClassifierIdentifier const SNClassifierIdentifierVersion1 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));


