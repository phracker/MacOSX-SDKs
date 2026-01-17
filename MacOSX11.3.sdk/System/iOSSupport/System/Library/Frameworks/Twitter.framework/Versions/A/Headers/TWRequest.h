//
//  TWRequest.h
//  Twitter
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

// This class has been  deprecated in iOS 6. Please use SLRequest (in the Social framework) instead.

#import <Foundation/Foundation.h>
#import <Social/SLRequest.h>

@class ACAccount;

enum {
    TWRequestMethodGET = SLRequestMethodGET,
    TWRequestMethodPOST = SLRequestMethodPOST,
    TWRequestMethodDELETE = SLRequestMethodDELETE
};

typedef SLRequestMethod TWRequestMethod; // available in iPhone 5.0

// Completion block for performRequestWithHandler. 
typedef SLRequestHandler TWRequestHandler;

NS_DEPRECATED(NA, NA, 5_0, 6_0) __attribute__((visibility("default")))
@interface TWRequest : NSObject

- (id)initWithURL:(NSURL *)url parameters:(NSDictionary *)parameters requestMethod:(TWRequestMethod)requestMethod;

// Optional account information used to authenticate the request. Defaults to nil.
@property (nonatomic, retain) ACAccount *account;

// The request method
@property (nonatomic, readonly) TWRequestMethod requestMethod;

// The request URL
@property (nonatomic, readonly) NSURL *URL;

// The parameters 
@property (nonatomic, readonly) NSDictionary *parameters;

// Specify a named MIME multi-part value. As of version 6.0, if you set parameters,
// the parameters will automatically be added as form data in the multi-part data.
- (void)addMultiPartData:(NSData*)data withName:(NSString*)name type:(NSString*)type; 

// Returns an OAuth compatible NSURLRequest for use with NSURLConnection. 
- (NSURLRequest *)signedURLRequest;

// Issue the request. This block is not guaranteed to be called on any particular thread.
- (void)performRequestWithHandler:(TWRequestHandler)handler;

@end

