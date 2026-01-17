//
//  ILClassificationResponse.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILClassificationActions.h>

NS_ASSUME_NONNULL_BEGIN

/// A response to an ILClassificationRequest.
IL_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILClassificationResponse : NSObject <NSSecureCoding>

@property (nonatomic, readonly, assign) ILClassificationAction action;

/*
 The value of this string will be sent when a value for
 ILClassificationExtensionSMSReportDestination has been set in the extension's Info.plist
 */
@property (nonatomic, readwrite, copy, nullable) NSString *userString API_AVAILABLE(ios(12.1));

/*
 The JSON representation of this dictionary will be sent when a value for
 ILClassificationExtensionNetworkReportDestination has been set in the extension's Info.plist

 The keys and values in this dictionary must conform to the NSJSONSerialization specifications:
 - Top level object is an NSDictionary
 - All objects are NSString, NSNumber, NSArray, NSDictionary, or NSNull
 - All dictionary keys are NSStrings
 - NSNumbers are not NaN or infinity
 */
@property (nonatomic, readwrite, copy, nullable) NSDictionary<NSString *, id> *userInfo;

- (instancetype)initWithClassificationAction:(ILClassificationAction)action NS_SWIFT_NAME(init(action:)) NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
