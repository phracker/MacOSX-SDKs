//
//  MLModelMetadataKeys.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * Keys to a dictionary that holds useful information about a model.
 * All are optional with the aim of being helpful to a developer or user
 * for descriptive purposes.
 */
typedef NSString * MLModelMetadataKey NS_STRING_ENUM;

/// A short description of what the model does and/or its purpose
extern MLModelMetadataKey const MLModelDescriptionKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A version number encoded as a string
extern MLModelMetadataKey const MLModelVersionStringKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// The author of this model
extern MLModelMetadataKey const MLModelAuthorKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// License information for the model
extern MLModelMetadataKey const MLModelLicenseKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


