/*
 *  GKTurnBasedMatch.h
 *  GameKit
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */
#import <GameKit/GKDefines.h>

@class GKMatchRequest, GKTurnBasedMatch;

// Constants that describe the state of the overall match
enum {
    GKTurnBasedMatchStatusUnknown   = 0,
    GKTurnBasedMatchStatusOpen      = 1,
    GKTurnBasedMatchStatusEnded     = 2,
    GKTurnBasedMatchStatusMatching  = 3
};
typedef NSInteger GKTurnBasedMatchStatus;


// Constants that describe the state of individual participants in the match
enum {
    // Statuses that are set by GameKit
    GKTurnBasedParticipantStatusUnknown     = 0,
    GKTurnBasedParticipantStatusInvited     = 1,    // a participant has been invited but not yet responded
    GKTurnBasedParticipantStatusDeclined    = 2,    // a participant that has declined an invite to this match
    GKTurnBasedParticipantStatusMatching    = 3,    // a participant that is waiting to be matched
    GKTurnBasedParticipantStatusActive      = 4,    // a participant that is active in this match
    GKTurnBasedParticipantStatusDone        = 5,    // a participant is done with this session
};
typedef NSInteger GKTurnBasedParticipantStatus;

// Constants that describe the game result for a given participant who has reached the done state.  The developer is free to use these constants or add additional ones

enum { 
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
    
    GKTurnBasedMatchOutcomeCustomRange = 0x00FF0000	// game result range available for custom app use
    
};
typedef NSInteger GKTurnBasedMatchOutcome;


// GKTurnBasedMatch represents an ongoing turn-based game among the matched group of participants
// Existing matches can be shown and new matches created using GKTurnBasedMatchmakerViewController
// A list of existing matches can be retrieved using +loadMatchesWithCompletionHandler:
//
// By default turn based events will badge your app.  To opt out of this add GKGameCenterBadgingDisabled  with a boolean value of YES to your info plist

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedParticipant : NSObject {
@private
	id _internal;
}

@property(readonly, copy, NS_NONATOMIC_IOSONLY)  NSString                        *playerID;
@property(readonly, copy, NS_NONATOMIC_IOSONLY)  NSDate                          *lastTurnDate;
@property(readonly, NS_NONATOMIC_IOSONLY)        GKTurnBasedParticipantStatus    status;
@property(assign, NS_NONATOMIC_IOSONLY)          GKTurnBasedMatchOutcome         matchOutcome;
@property(readonly, copy,NS_NONATOMIC_IOSONLY)  NSDate                          *timeoutDate __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

@end


@protocol GKTurnBasedEventHandlerDelegate
@optional

// If Game Center initiates a match the developer should create a GKTurnBasedMatch from playersToInvite and present a GKTurnbasedMatchmakerViewController.
- (void)handleInviteFromGameCenter:(NSArray *)playersToInvite;		

// handleTurnEventForMatch is called when becomes this player's turn.  It may also get called if the player's turn has a timeout and it is about to expire.  Note this may also arise from the player accepting an invite from another player.  Because of this the app needs to be prepared to handle this even while the player is taking a turn in an existing match.  The boolean indicates whether this event launched or brought to forground the app.
- (void)handleTurnEventForMatch:(GKTurnBasedMatch *)match didBecomeActive:(BOOL)didBecomeActive __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);
- (void)handleTurnEventForMatch:(GKTurnBasedMatch *)match __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8,__MAC_10_9,__IPHONE_5_0,__IPHONE_6_0);  // this is called only if the new version is not implemented

// handleMatchEnded is called when the match has ended.
- (void)handleMatchEnded:(GKTurnBasedMatch *)match;

@end

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedEventHandler : NSObject {
@private
	NSObject<GKTurnBasedEventHandlerDelegate>	*_delegate;
    id _internal1;
    BOOL _internal2;
}
+ (GKTurnBasedEventHandler *)sharedTurnBasedEventHandler;

@property (assign, NS_NONATOMIC_IOSONLY) 		NSObject<GKTurnBasedEventHandlerDelegate>	*delegate;

@end


// Turn timeout constants

extern NSTimeInterval		GKTurnTimeoutDefault __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);	// use a default timeout of one week
extern NSTimeInterval		GKTurnTimeoutNone __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GKTurnBasedMatch : NSObject {
@private
	id _internal;
}

@property(readonly, copy, NS_NONATOMIC_IOSONLY)   NSString                *matchID;
@property(readonly, copy, NS_NONATOMIC_IOSONLY)   NSDate                  *creationDate;
@property(readonly, retain, NS_NONATOMIC_IOSONLY) NSArray                 *participants;          // array of GKTurnBasedParticipant objects
@property(readonly, NS_NONATOMIC_IOSONLY)         GKTurnBasedMatchStatus  status;

// This indicates the participant who has the current turn.  This is set by passing the next participant into endTurnWithNextParticipant:matchData:completionHandler:
@property(readonly, retain, NS_NONATOMIC_IOSONLY)  GKTurnBasedParticipant  *currentParticipant;

// Developer-defined data representing the current state of the game. This propery is nil until loaded by loadMatchDataWithCompletionHandler:
// The developer can submit updated matchData by passing it into endTurnWithNextParticipant:matchData:completionHandler: or endMatchInTurnWithMatchData:completionHandler:
@property(readonly, retain, NS_NONATOMIC_IOSONLY)  NSData                  *matchData;            

// If the developer wishes to display a message in GKTurnBasedMatchmakerViewController at the end of a turn or end of the match.  Only the current participant can set this.
@property(readwrite, copy, NS_NONATOMIC_IOSONLY)   NSString                *message;

// Returns the maximum size for the match data.
@property(readonly, NS_NONATOMIC_IOSONLY)  NSUInteger                      matchDataMaximumSize __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

// Attempt to find a turn-based match for the specified request. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
+ (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^)(GKTurnBasedMatch *match, NSError *error))completionHandler;

// This method retrieves the list of GKTurnBasedMatches that the current player is or has participated in. The callback’s array contains GKTurnBasedMatches
+ (void)loadMatchesWithCompletionHandler:(void(^)(NSArray *matches, NSError *error))completionHandler;

// load a match based on a previously known match ID
+ (void)loadMatchWithID:(NSString *)matchID withCompletionHandler:(void(^)(GKTurnBasedMatch *match, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

// Recreate a previously existing turn based match that ended. A new match with the same set of players will be returned by the completion handler. If multiple players do this then multiple new matches will be created. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
- (void)rematchWithCompletionHandler:(void(^)(GKTurnBasedMatch *match, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

// If the local participant has status invited then accept the invite, otherwise returns an error
- (void)acceptInviteWithCompletionHandler:(void(^)(GKTurnBasedMatch *match, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

// If the local participant has status invited then decline the invite, otherwise returns an error
- (void)declineInviteWithCompletionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

// Remove a declined or completed match (one with a matchOutcome set) from the player's list of matches. If using the GKTurnBasedMatchmakerViewController UI, this will remove it from the finished sessions.  The developer should not do this without user input.
- (void)removeWithCompletionHandler:(void(^)(NSError *error))completionHandler;

// This method fetches the match data for this match.  This data is the state of the game at this point in time.  This may update the status and/or participant properties if they have changed.
- (void)loadMatchDataWithCompletionHandler:(void(^)(NSData *matchData, NSError *error))completionHandler;


// Ends the current player's turn. You may update the matchOutcome for any GKTurnBasedPlayerInfos that you wish to before ending the turn.
// This will asynchronously report error in these cases:
// 1. Communications problem
// 2. Is not current player's turn
// 3. Session is closed
- (void)endTurnWithNextParticipants:(NSArray *)nextParticipants turnTimeout:(NSTimeInterval)timeout matchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);
- (void)endTurnWithNextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8,__MAC_10_9,__IPHONE_5_0,__IPHONE_6_0);;

// Ends the current player's turn by quitting the match.  The caller must indicate the next player and pass in updated matchData (if used)
- (void)participantQuitInTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome nextParticipants:(NSArray *)nextParticipants turnTimeout:(NSTimeInterval)timeout matchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);
- (void)participantQuitInTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome nextParticipant:(GKTurnBasedParticipant *)nextParticipant matchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8,__MAC_10_9,__IPHONE_5_0,__IPHONE_6_0);;

// Abandon the match when it is not the current participant's turn.  In this there is no update to matchData and no need to set nextParticipant.
- (void)participantQuitOutOfTurnWithOutcome:(GKTurnBasedMatchOutcome)matchOutcome withCompletionHandler:(void(^)(NSError *error))completionHandler;

// This will end the match for all participants. You must set each participant’s matchOutcome before calling this method.
- (void)endMatchInTurnWithMatchData:(NSData*)matchData completionHandler:(void(^)(NSError *error))completionHandler;

// saves the matchData for the current turn without ending the turn.  If other players have the game running they will receive a handleTurnEventForMatch to indicate that the matchData has changed.  This is useful to initialize the game state for the first player when they take their turn or for updating the turn data due to the user taking an irreversible action within their turn.
- (void)saveCurrentTurnWithMatchData:(NSData *)matchData completionHandler:(void(^)(NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);
@end