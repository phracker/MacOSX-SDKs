//
//  SLRequest.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Social/SocialDefines.h>
#import <Social/SLServiceTypes.h>

@class ACAccount;

typedef NS_ENUM(NSInteger, SLRequestMethod)  {
    SLRequestMethodGET,
    SLRequestMethodPOST,
    SLRequestMethodDELETE,
    SLRequestMethodPUT
};


// Completion block for performRequestWithHandler. 
typedef void(^SLRequestHandler)(NSData *responseData, NSHTTPURLResponse *urlResponse, NSError *error);


SOCIAL_CLASS_AVAILABLE(10_8, 6_0)
@interface SLRequest : NSObject

+ (SLRequest *)requestForServiceType:(NSString *)serviceType requestMethod:(SLRequestMethod)requestMethod URL:(NSURL *)url parameters:(NSDictionary *)parameters;

// Optional account information used to authenticate the request. Defaults to nil.
@property (retain, nonatomic) ACAccount *account;

// The request method
@property (readonly, nonatomic) SLRequestMethod requestMethod;

// The request URL
@property (readonly, nonatomic) NSURL *URL;

// The parameters 
@property (readonly, nonatomic) NSDictionary *parameters;

// Specify a named MIME multi-part value. If you set parameters,
// the parameters will automatically be added as form data in the multi-part data.
- (void)addMultipartData:(NSData *)data
                withName:(NSString *)name
                    type:(NSString *)type
                filename:(NSString *)filename;

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
// DEPRECATED: Please use addMultipartData:withName:type:filename: instead.
- (void)addMultipartData:(NSData *)data
                withName:(NSString *)name
                    type:(NSString*)type __attribute__((deprecated));
#endif

// Returns a NSURLRequest for use with NSURLConnection.
// If an account has been set the returned request is either signed (OAuth1),
// or has the appropriate token set (OAuth2)
- (NSURLRequest *)preparedURLRequest;

// Issue the request. This block is not guaranteed to be called on any particular thread.
- (void)performRequestWithHandler:(SLRequestHandler)handler;

@end


