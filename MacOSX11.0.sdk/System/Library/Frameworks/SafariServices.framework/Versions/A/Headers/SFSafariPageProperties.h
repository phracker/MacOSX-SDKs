//
//  SFSafariPageProperties.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariPageProperties : NSObject

@property (nonatomic, readonly, nullable) NSURL *url;
@property (nonatomic, copy, readonly, nullable) NSString *title;
@property (nonatomic, readonly) BOOL usesPrivateBrowsing;
@property (nonatomic, readonly, getter=isActive) BOOL active;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
