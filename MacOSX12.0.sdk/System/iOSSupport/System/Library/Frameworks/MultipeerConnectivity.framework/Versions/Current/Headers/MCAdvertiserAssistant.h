//
// MCAdvertiserAssistant.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import <MultipeerConnectivity/MCPeerID.h>
#import <MultipeerConnectivity/MCSession.h>

@protocol MCAdvertiserAssistantDelegate;

//
// @class MCAdvertiserAssistant
//   @abstract
//      MCAdvertiserAssistant is a convenience class that handles advertising,
//      presents incoming invitations to the user and handles user's responses.
//
//   @discussion
//      To create the MCAdvertiserAssistant object a new MCPeerID should be
//      created to represent the local peer, and a service type needs to be
//      specified.
//
//      The serviceType parameter is a short text string used to describe the
//      app's networking protocol.  It should be in the same format as a
//      Bonjour service type: up to 15 characters long and valid characters
//      include ASCII lowercase letters, numbers, and the hyphen. A short name
//      that distinguishes itself from unrelated services is recommended;
//      for example, a text chat app made by ABC company could use the service
//      type "abc-txtchat".
//
//      The discoveryInfo parameter is a dictionary of string key/value pairs
//      that will be advertised for browsers to see. Both keys and values must
//      be NSString objects. The content of discoveryInfo will be advertised
//      within Bonjour TXT records, and keeping the dictionary small is good
//      for keeping network traffic low.
//
//      A delegate that conforms to the MCAdvertiserAssistantDelegate protocol
//      must be provided. No assumption should be made as to which queue the
//      callbacks are called on.
//
//      See Bonjour APIs https://developer.apple.com/bonjour/ for more
//      information about service types.
//
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCAdvertiserAssistant : NSObject
- (instancetype)initWithServiceType:(NSString *)serviceType
                      discoveryInfo:(nullable NSDictionary<NSString *, NSString *> *)info
                            session:(MCSession *)session NS_DESIGNATED_INITIALIZER;

// The methods -start and -stop are used to start and stop the assistant.
- (void)start;
- (void)stop;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCAdvertiserAssistantDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCSession *session;
@property (readonly, NS_NONATOMIC_IOSONLY, nullable) NSDictionary<NSString *, NSString *> *discoveryInfo;
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *serviceType;

@end

@protocol MCAdvertiserAssistantDelegate <NSObject>
@optional

// An invitation will be presented to the user.
- (void)advertiserAssistantWillPresentInvitation:(MCAdvertiserAssistant *)advertiserAssistant;

// An invitation was dismissed from screen.
- (void)advertiserAssistantDidDismissInvitation:(MCAdvertiserAssistant *)advertiserAssistant;

@end
NS_ASSUME_NONNULL_END

