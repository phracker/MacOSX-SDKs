//
//  ASWebAuthenticationSessionRequest.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASWebAuthenticationSessionRequest;

AS_EXTERN API_AVAILABLE(macCatalyst(13.0), macos(10.15)) API_UNAVAILABLE(ios, tvos)
@protocol ASWebAuthenticationSessionRequestDelegate <NSObject>
@optional
- (void)authenticationSessionRequest:(ASWebAuthenticationSessionRequest *)authenticationSessionRequest didCompleteWithCallbackURL:(NSURL *)callbackURL;
- (void)authenticationSessionRequest:(ASWebAuthenticationSessionRequest *)authenticationSessionRequest didCancelWithError:(NSError *)error;
@end

AS_EXTERN API_AVAILABLE(macCatalyst(13.0), macos(10.15)) API_UNAVAILABLE(ios, tvos)
@interface ASWebAuthenticationSessionRequest : NSObject <NSSecureCoding, NSCopying>

@property (readonly, nonatomic) NSUUID *UUID;
@property (readonly, nonatomic) NSURL *URL;
@property (nullable, readonly, nonatomic, copy) NSString *callbackURLScheme;
@property (readonly, nonatomic) BOOL shouldUseEphemeralSession;
@property (nullable, nonatomic, weak) id<ASWebAuthenticationSessionRequestDelegate> delegate;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (void)cancelWithError:(NSError *)error;
- (void)completeWithCallbackURL:(NSURL *)url;
@end

NS_ASSUME_NONNULL_END
