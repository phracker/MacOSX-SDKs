//
//  GKTurnBasedMatch.h
//  Game Center
//
//  Copyright 2010-2021 Apple Inc. All rights reserved.
//

#import <GameKit/GKPlayer.h>
#import <GameKit/GKLeaderboardScore.h>

@class GKMatchRequest, GKTurnBasedMatch, GKTurnBasedExchange, GKTurnBasedExchangeReply, GKScore, GKAchievement;

/// Constants that describe the state of the overall match
typedef NS_ENUM(NSInteger, GKTurnBasedMatchStatus) {
    GKTurnBasedMatchStatusUnknown   = 0,
    GKTurnBasedMatchStatusOpen      = 1,
    GKTurnBasedMatchStatusEnded     = 2,
    GKTurnBasedMatchStatusMatching  = 3
};

/// Constants that describe the state of individual participants in the match
typedef NS_ENUM(NSInteger, GKTurnBasedParticipantStatus) {
    // Statuses that are set by GameKit
    GKTurnBasedParticipantStatusUnknown     = 0,
    GKTurnBasedParticipantStatusInvited     = 1,    // a participant has been invited but not yet responded
    GKTurnBasedParticipantStatusDeclined    = 2,    // a participant that has declined an invite to this match
    GKTurnBasedParticipantStatusMatching    = 3,    // a participant that is waiting to be matched
    GKTurnBasedParticipantStatusActive      = 4,    // a participant that is active in this match
    GKTurnBasedParticipantStatusDone        = 5,    // a participant is done with this session
};

/// Constants that describe the game result for a given participant who has reached the done state.  The developer is free to use these constants or add additional ones
typedef NS_ENUM(NSInteger, GKTurnBasedMatchOutcome) {
    GKTurnBasedMatchOutcomeNone         = 0,        // Participants who are not done with a match have this state
    GKTurnBasedMatchOutcomeQuit         = 1,        // Participant quit
    GKTurnBasedMatchOutcomeWon          = 2,        // Participant won
    GKTurnBasedMatchOutcomeLost         = 3,        // Participant lost
    GKTurnBasedMatchOutcomeTied         = 4,        // Participant tied
    GKTurnBasedMatchOutcomeTimeExpired  = 5,        // Game ended due to time running out
    GKTurnBasedMatchOutcomeFirst        = 6,
    GKTurnBasedMatchOutcomeSecond       = 7,
    GKTurnBasedMatchOutcomeThird        = 8,
    GKTurnBasedMatchOutcomeFourth       = 9,
    
    GKTurnBasedMatchOutcomeCustomRange = 0x00FF0000    // game result range available for custom app use
    
};

/// GKTurnBasedMatch represents an ongoing turn-based game among the matched group of participants
/// Existing matches can be shown and new matches created using GKTurnBasedMatchmakerViewController
/// A list of existing matches can be retrieved using +loadMatchesWithCompletionHandler:
///
/// By default turn based events will badge your app.  To opt out of this add GKGameCenterBadgingDisabled  with a boolean value of YES to your info plist

NS_CLASS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0)
@interface GKTurnBasedParticipant : NSObject

@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY) GKPlayer            *player NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0);
@property(readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSDate                *lastTurnDate;
@property(readonly, NS_NONATOMIC_IOSONLY)       GKTurnBasedParticipantStatus    status;
@property(assign, NS_NONATOMIC_IOSONLY)         GKTurnBasedMatchOutcome         matchOutcome;
@property(readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSDate                *timeoutDate NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

@end

@interface GKTurnBasedParticipant (Obsoleted)
/*** This property is obsolete. ***/
@property(readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSString              *playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use player") ;
@end

NS_ASSUME_NONNULL_BEGIN
@protocol GKTurnBasedEventListener
@optional

/// If Game Center initiates a match the developer should create a GKTurnBasedMatch from playersToInvite and present a GKTurnbasedMatchmakerViewController.
- (void)player:(GKPlayer *)player didRequestMatchWithOtherPlayers:(NSArray<GKPlayer *> *)playersToInvite NS_AVAILABLE(10_10, 8_0) API_UNAVAILABLE(watchos);

/// called when it becomes this player's turn.  It also gets called under the following conditions:
///      the player's turn has a timeout and it is about to expire.
///      the player accepts an invite from another player.
/// when the game is running it will additionally recieve turn events for the following:
///      turn was passed to another player
///      another player saved the match data
/// Because of this the app needs to be prepared to handle this even while the player is taking a turn in an existing match.  The boolean indicates whether this event launched or brought to forground the app.
- (void)player:(GKPlayer *)player receivedTurnEventForMatch:(GKTurnBasedMatch *)match didBecomeActive:(BOOL)didBecomeActive NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

/// called when the match has ended.
- (void)player:(GKPlayer *)player matchEnded:(GKTurnBasedMatch *)match;

/// this is called when a player receives an exchange request from another player.
- (void)player:(GKPlayer *)player receivedExchangeRequest:(GKTurnBasedExchange *)exchange forMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

/// this is called when an exchange is canceled by the sender.
- (void)player:(GKPlayer *)player receivedExchangeCancellation:(GKTurnBasedExchange *)exchange forMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

/// called when all players either respond or timeout responding to this request.  This is sent to both the turn holder and the initiator of the exchange
- (void)player:(GKPlayer *)player receivedExchangeReplies:(NSArray<GKTurnBasedExchangeReply *> *)replies forCompletedExchange:(GKTurnBasedExchange *)exchange forMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

/// Called when a player chooses to quit a match and that player has the current turn.  The developer should call participantQuitInTurnWithOutcome:nextParticipants:turnTimeout:matchData:completionHandler: on the match passing in appropriate values.  They can also update matchOutcome for other players as appropriate.
- (void)player:(GKPlayer *)player wantsToQuitMatch:(GKTurnBasedMatch *)match NS_AVAILABLE(10_11, 9_0) __WATCHOS_AVAILABLE(3_0);

/// Deprecated
- (void)player:(GKPlayer *)player didRequestMatchWithPlayers:(NSArray<NSString *> *)playerIDsToInvite NS_DEPRECATED_IOS(7_0, 8_0, "use didRequestMatchWithOtherPlayers") ;

@end

// Turn timeout constants

extern NSTimeInterval        GKTurnTimeoutDefault NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);    // use a default timeout of one week
extern NSTimeInterval        GKTurnTimeoutNone NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);

NS_CLASS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0)
@interface GKTurnBasedMatch : NSObject

@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  NSString                           *matchID;
@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  NSDate                             *creationDate;
@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedParticipant *>  *participants;          // array of GKTurnBasedParticipant objects
@property(readonly, NS_NONATOMIC_IOSONLY)                    GKTurnBasedMatchStatus             status;

// This indicates the participant who has the current turn.  This is set by passing the next participant into endTurnWithNextParticipant:matchData:completionHandler:
@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  GKTurnBasedParticipant  *currentParticipant;

// Developer-defined data representing the current state of the game. This property is nil until loaded by loadMatchDataWithCompletionHandler:
// The developer can submit updated matchData by passing it into endTurnWithNextParticipant:matchData:completionHandler: or endMatchInTurnWithMatchData:completionHandler:
@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  NSData                  *matchData;

// If the developer wishes to display a message in GKTurnBasedMatchmakerViewController at the end of a turn or end of the match.  Only the current participant can set this.
// Sets a localizable mesage that will be localized on the receiver side if the game is installed and on the sender side as a fallback.
// The key and arguments offer a subset of formated strings as follows
//    key is a string in a Localizable.strings file for the current localization (which is set by the user’s language preference).  key string can be formatted with %@ and %n$@ specifiers to take the variables specified in loc-args
//    arguments is an array of strings that will be substituted using the format string.
// Notes: The localized message will be evaluated locally from these keys and sent across as well so that devices that do not have the game installed will see the message in the sender's localization
//        The developer can access resulting string using the message property
//        This is a similar concept to the way we handle localization for Push Notifications. See the "Local and Push Notification Programming Guide" for more details.
- (void)setLocalizableMessageWithKey:(NSString*)key arguments:(nullable NSArray<NSString *> *)arguments NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// returns the localizable message in the current locale. Setting this is equivalent to calling [self setLocalizableMessageWithKey:message arguments:nil]
@property(readwrite, nullable, copy, NS_NONATOMIC_IOSONLY)   NSString                *message;


// Returns the maximum size for the match data.
@property(readonly, NS_NONATOMIC_IOSONLY)          NSUInteger              matchDataMaximumSize NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

// exchanges that are in progress on this match.  Once an exchange has completed and has been resolved by merging it into the match data by the current turn holder then it will be removed from this list
@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedExchange *>                 *exchanges NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// returns the exchanges that currently await a reply from the local player
@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedExchange *>                 *activeExchanges NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// returns the exchanges that have been completed and need to be merged by the local participant.  This will be nil unless the local participant is the current turn holder for this match
@property(readonly, nullable, strong, NS_NONATOMIC_IOSONLY)  NSArray<GKTurnBasedExchange *>                 *completedExchanges NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// maximum data allowed for exchange data
@property(readonly, NS_NONATOMIC_IOSONLY)          NSUInteger              exchangeDataMaximumSize NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// limit of the number of exchanges that this player can have initiated at a given time
@property(readonly, NS_NONATOMIC_IOSONLY)          NSUInteger              exchangeMaxInitiatedExchangesPerPlayer NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// Attempt to find a turn-based match for the specified request. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
+ (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler;

// This method retrieves the list of GKTurnBasedMatches that the current player is or has participated in. The callback’s array contains GKTurnBasedMatches
+ (void)loadMatchesWithCompletionHandler:(void(^__nullable)(NSArray<GKTurnBasedMatch *> * __nullable matches, NSError * __nullable error))completionHandler;

// load a match based on a previously known match ID
+ (void)loadMatchWithID:(NSString *)matchID withCompletionHandler:(void(^__nullable)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// Recreate a previously existing turn based match that ended. A new match with the same set of players will be returned by the completion handler. If multiple players do this then multiple new matches will be created. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
- (void)rematchWithCompletionHandler:(void(^__nullable)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);

// If the local participant has status invited then accept the invite, otherwise returns an error
- (void)acceptInviteWithCompletionHandler:(void(^__nullable)(GKTurnBasedMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// If the local participant has status invited then decline the invite, otherwise returns an error
- (void)declineInviteWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0) __WATCHOS_AVAILABLE(3_0);

// Remove a declined or completed match (one with a matchOutcome set) from the player's list of matches. If using the GKTurnBasedMatchmakerViewController UI, this will remove it from the finished sessions.  The developer should not do this without user input.
- (void)removeWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler;

// This method fetches the match data and exchanges for this match.  This data is the state of the game at this point in time.  This may update the status and/or participant properties if they have changed.
- (void)loadMatchDataWithCompletionHandler:(void(^__nullable)(NSData * __nullable matchData, NSError * __nullable error))completionHandler;


// Ends the current player's turn. You may update the matchOutcome for any GKTurnBasedPlayerInfos that you wish to before ending the turn.
// This will asynchronously report error in these cases:
// 1. Communications problem
// 2. Is not current player's turn
// 3. Session is closed
- (void)endTurnWithNextParticipants:(NSArray<GKTurnBasedParticipant *> *)nextParticipants
                        turnTimeout:(NSTimeInterval)timeout
                          matchData:(NSData*)matchData
                 completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);


// Ends the current player's turn by quitting the match.  The caller must indicate the next player and pass in updated matchData (if used).  All completed exchanges must be resolved or canceled before calling this.
- (void)participantQuitInTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome
                        nextParticipants:(NSArray<GKTurnBasedParticipant *> *)nextParticipants
                             turnTimeout:(NSTimeInterval)timeout
                               matchData:(NSData*)matchData
                       completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0) __WATCHOS_AVAILABLE(3_0);

// Abandon the match when it is not the current participant's turn.  In this there is no update to matchData and no need to set nextParticipant.
- (void)participantQuitOutOfTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler;

// This will end the match for all participants. You must set each participant’s matchOutcome before calling this method.  All completed exchanges must be resolved or canceled before calling this.
- (void)endMatchInTurnWithMatchData:(NSData*)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler;

// This will end the match and submit scores and achievements for all participants. Scores should be submitted for all involved players, and multiple scores may be submitted for each to different leaderboards. Earned achievements may also be submitted for any participants. You must set each participant’s matchOutcome before calling this method. All completed exchanges must be resolved or canceled before calling this.
- (void)endMatchInTurnWithMatchData:(NSData*)matchData scores:(nullable NSArray<GKScore *> *)scores achievements:(nullable NSArray<GKAchievement *> *)achievements completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_10, 11_0, 6_0, 14_0, "pass GKLeaderboardScore to endMatchInTurnWithMatchData:scores:completionHandler instead");

- (void)endMatchInTurnWithMatchData:(NSData*)matchData leaderboardScores:(NSArray<GKLeaderboardScore *> *)scores achievements:(NSArray *)achievements completionHandler:(void(^)(NSError * __nullable error))completionHandler NS_AVAILABLE(11_0, 14_0);

// saves the matchData for the current turn without ending the turn.  If other players have the game running they will receive a handleTurnEventForMatch to indicate that the matchData has changed.  This is useful to initialize the game state for the first player when they take their turn or for updating the turn data due to the user taking an irreversible action within their turn.  All completed exchanges must be resolved or canceled before calling this. If you are using exchanges use saveMergedMatchData instead.  
- (void)saveCurrentTurnWithMatchData:(NSData *)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

// saves the merged matchData for the current turn without ending the turn and mark the supplied exchanges as resolved meaning that the data has been merged into the match data. If other players have the game running they will receive a handleTurnEventForMatch to indicate that the matchData has changed.  It is required that all completed exchanges are resolved before ending a turn.  Otherwise calling endTurn, participantQuitInTurnWithOutCome or endMatchInTurn will return an error
- (void)saveMergedMatchData:(NSData *)matchData
      withResolvedExchanges:(NSArray<GKTurnBasedExchange *> *)exchanges
          completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// Send an exchange request to one or more participants.  Each recipient will receive a push notification using supplied localizable message.  If any of the participants have an inactive status (GKTurnBasedParticipantStatusDone) then this will return an error.  completionHandler gets passed the updated exchange with identifier, sender and recipients set
- (void)sendExchangeToParticipants:(NSArray<GKTurnBasedParticipant *> *)participants
                              data:(NSData *)data
             localizableMessageKey:(NSString *)key
                         arguments:(NSArray<NSString *> *)arguments
                           timeout:(NSTimeInterval)timeout
                 completionHandler:(void(^__nullable)(GKTurnBasedExchange * __nullable exchange, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0)  __WATCHOS_AVAILABLE(3_0);

// Send a reminder to one or more participants.  Each recipient will receive a push notification using supplied localizable message.  This allows a game to send reminders that a turn or exchange request needs action.  On the receiver side this will generate a turn event for the match.
- (void)sendReminderToParticipants:(NSArray<GKTurnBasedParticipant *> *)participants
             localizableMessageKey:(NSString *)key
                         arguments:(NSArray<NSString *> *)arguments
                 completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// deprecated methods
- (void)endTurnWithNextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_9, 5_0, 6_0, "Use endTurnWithNextParticipants:... instead") ;
- (void)participantQuitInTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome nextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_9, 5_0, 6_0, "Use participantQuitInTurnWithOutcome:nextParticipants:turnTimeout:... instead") ;

@end

// Turn Based Exchanges

// Constants that describe the status of exchanges and their replies

typedef NS_ENUM(int8_t, GKTurnBasedExchangeStatus) {
    GKTurnBasedExchangeStatusUnknown = 0,
    GKTurnBasedExchangeStatusActive = 1,
    GKTurnBasedExchangeStatusComplete = 2,
    GKTurnBasedExchangeStatusResolved = 3,
    GKTurnBasedExchangeStatusCanceled = 4
}  NS_ENUM_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// Exchange timeout constants

extern NSTimeInterval        GKExchangeTimeoutDefault NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);    // use a default timeout of one day
extern NSTimeInterval        GKExchangeTimeoutNone NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);


NS_CLASS_AVAILABLE(10_10,7_0) __WATCHOS_AVAILABLE(3_0)
@interface  GKTurnBasedExchange : NSObject

@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSString                            *exchangeID;         // persistent identifier used to refer to this exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     GKTurnBasedParticipant              *sender;             // participant who sent the exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSArray<GKTurnBasedParticipant *>   *recipients;         // participants who are the recipients of the exchange
@property (assign, readonly, NS_NONATOMIC_IOSONLY)       GKTurnBasedExchangeStatus           status;              // status of the exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSString                            *message;            // localized message for the push notification sent to all recipients of this exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSData                              *data;               // data to send with the exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSDate                              *sendDate;           // send date for the exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSDate                              *timeoutDate;        // timeout date for the exchange.
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSDate                              *completionDate;     // date when this exchange completed

@property (readonly, nullable, NS_NONATOMIC_IOSONLY)     NSArray<GKTurnBasedExchangeReply *> *replies;            // Array of GKTurnBasedExchangeReply.

// cancel an exchange. It is possible to cancel an exchange that is active or complete. Each recipient will receive a push notification using supplied localizable message. Returns an error if the exchange has already been canceled.
- (void)cancelWithLocalizableMessageKey:(NSString *)key arguments:(NSArray<NSString *> *)arguments completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

// reply to an exchange. The sender will receive a push notification using supplied localizable message. Returns an error if the exchange has already been canceled.
- (void)replyWithLocalizableMessageKey:(NSString *)key arguments:(NSArray<NSString *> *)arguments data:(NSData *)data completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

@end

    
NS_CLASS_AVAILABLE(10_10,7_0) __WATCHOS_AVAILABLE(3_0)
@interface GKTurnBasedExchangeReply  : NSObject

@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          GKTurnBasedParticipant         *recipient;          // the recipient who this reply is from
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          NSString                       *message;            // localized message for the push notification generated by the reply of this exchange
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          NSData                         *data;               // data sent by the replying recipient
@property (readonly, nullable, NS_NONATOMIC_IOSONLY)          NSDate                         *replyDate NS_AVAILABLE(10_10, 8_0) __WATCHOS_AVAILABLE(3_0); // send date for the exchange.
@end

// deprecated

// see documentation for GKTurnBasedEventListener for the equivalent methods
NS_DEPRECATED(10_8, 10_10, 5_0, 7_0, "Use registerListener on GKLocalPlayer with an object that implements the GKTurnBasedEventListener protocol") 
@protocol  GKTurnBasedEventHandlerDelegate

- (void)handleInviteFromGameCenter:(NSArray<NSString *> *)playersToInvite NS_DEPRECATED(10_8, 10_10, 5_0, 7_0);
- (void)handleTurnEventForMatch:(GKTurnBasedMatch *)match didBecomeActive:(BOOL)didBecomeActive NS_DEPRECATED(10_9, 10_10, 6_0, 7_0);

@optional
- (void)handleTurnEventForMatch:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_9, 5_0, 7_0);
- (void)handleMatchEnded:(GKTurnBasedMatch *)match NS_DEPRECATED(10_8, 10_10, 6_0, 7_0);

@end

NS_CLASS_DEPRECATED(10_8, 10_10, 5_0, 7_0, "Use registerListener on GKLocalPlayer with an object that implements the GKTurnBasedEventListener protocol") 
@interface GKTurnBasedEventHandler : NSObject

+ (GKTurnBasedEventHandler *)sharedTurnBasedEventHandler NS_DEPRECATED(10_8, 10_10, 5_0, 7_0);

@property (weak, NS_NONATOMIC_IOSONLY)         NSObject<GKTurnBasedEventHandlerDelegate>    *delegate NS_DEPRECATED(10_8, 10_10, 5_0, 7_0);

@end

NS_ASSUME_NONNULL_END
