//
//  VSAccountApplicationProvider.h
//  VideoSubscriberAccount
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An object which provides an account provider to be added to the list of providers in your application.
VS_EXPORT API_AVAILABLE(ios(14.2), tvos(14.2)) API_UNAVAILABLE(macCatalyst)
@interface VSAccountApplicationProvider : NSObject

/// Unavailable for this class.
VS_INIT_UNAVAILABLE

/// Returns an application provider using a given display name and identifier.
/// Both the localizedDisplayName and identifier parameters must be non-empty strings.
- (instancetype)initWithLocalizedDisplayName:(NSString *)localizedDisplayName identifier:(NSString *)identifier;

/// The display name of the provider as it will appear in the list of providers.
@property (nonatomic, readonly) NSString *localizedDisplayName;

/// The identifier of the provider.
/// If selected, this value is returned to your application.
@property (nonatomic, readonly) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
