//
// MCPeerID.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
   @class MCPeerID
   @abstract
   MCPeerID represents a peer in a multipeer session.

   @discussion
    MCPeerID is used to reference a peer in a multipeer session.

    Use the init method -initWithDisplayName: to create a new ID for the
    local app, and associate a display name with the ID.

    Note that the displayName is intended for a UI element, and should
    be short and descriptive of the local peer.  The hard limit of
    displayName is 63 bytes in UTF8 encoding.  The displayName parameter
    may not be nil or an empty string.

    MCPeerID conforms to NSCopying and can be used as a key in a
    NSDictionary.
 */

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCPeerID : NSObject <NSCopying, NSSecureCoding>
- (instancetype)initWithDisplayName:(NSString *)myDisplayName NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) NSString *displayName;
@end
NS_ASSUME_NONNULL_END
