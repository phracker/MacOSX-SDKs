//
//  CPNowPlayingMode.h
//  CarPlay
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <CarPlay/CPTemplate.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNowPlayingMode : NSObject <NSSecureCoding>

/**
 The default now playing mode. While this mode is active,
 your app will display now playing metadata as donated to
 the shared system now playing info center.
 */
@property (nonatomic, class, readonly) CPNowPlayingMode *defaultNowPlayingMode;

@end

@class CPNowPlayingSportsClock;
@class CPNowPlayingSportsTeam;
@class CPNowPlayingSportsTeamLogo;
@class CPNowPlayingSportsEventStatus;

/**
 The sports mode represents a layout for now playing suited to live-streaming or
 recorded playback of a sporting event that features exactly two teams.
 */
API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNowPlayingModeSports : CPNowPlayingMode <NSSecureCoding>

/**
 Initialize a sports mode for display on the CarPlay now playing screen.
 
 @param leftTeam The sports team that should appear on the left side of the
 now playing screen. This is commonly (but not always) the AWAY or VISITING team.
 This team will be on the left in all layouts; it does not flip to the right
 side when in a right-to-left language or a right-hand-drive vehicle.
 
 @param rightTeam The sports team that should appear on the right side of the
 now playing screen. This is commonly (but not always) the HOME team.
 This team will be on the right in all layouts; it does not flip to the left
 side when in a right-to-left language or a right-hand-drive vehicle.
 
 @param eventStatus A representation of the current event status. See
 @c CPNowPlayingSportsEventStatus for more information.
 
 @param backgroundArtwork A large colorful image for the background of the
 now playing screen. A gradient or crossfade image works best, especially
 when it includes the primary colors of each team. Provide an image no larger
 than 500x500.
 */
- (instancetype)initWithLeftTeam:(CPNowPlayingSportsTeam *)leftTeam
                       rightTeam:(CPNowPlayingSportsTeam *)rightTeam
                     eventStatus:(nullable CPNowPlayingSportsEventStatus *)eventStatus
               backgroundArtwork:(nullable UIImage *)backgroundArtwork;

/**
 The sports team that should appear on the left side of the
 now playing screen. This is commonly (but not always) the AWAY or VISITING team.
 This team will be on the left in all layouts; it does not flip to the right
 side when in a right-to-left language or a right-hand-drive vehicle.
 */
@property (nonatomic, strong, readonly) CPNowPlayingSportsTeam *leftTeam;

/**
 The sports team that should appear on the right side of the
 now playing screen. This is commonly (but not always) the HOME team.
 This team will be on the right in all layouts; it does not flip to the left
 side when in a right-to-left language or a right-hand-drive vehicle.
 */
@property (nonatomic, strong, readonly) CPNowPlayingSportsTeam *rightTeam;

/**
 A representation of the current event status. See
 @c CPNowPlayingSportsEventStatus for more information.
 */
@property (nonatomic, strong, nullable, readonly) CPNowPlayingSportsEventStatus *eventStatus;

/**
 A large colorful image for the background of the
 now playing screen. A gradient or crossfade image works best, especially
 when it includes the primary colors of each team. Provide an image no larger
 than 500x500.
 */
@property (nonatomic, copy, nullable, readonly) UIImage *backgroundArtwork;

@end

/**
 A representation of a sports team for the now playing screen,
 in sports that have exactly two teams.
 */
API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNowPlayingSportsTeam : NSObject <NSSecureCoding>

/**
 Initialize a sports team for display on the now playing screen.
 
 @param name A localized, user-visible name for this sports team.
 @param logo The team logo or, if no logo is available, the initials/abbreviation for this team.
 @param teamStandings An optional additional label displayed near the team name. This could be a
 win-loss ratio string, team standings, or other statistics relevant to this team.
 Depending on the size of the car screen, a maximum of 15-20 characters may
 be displayed.
 @param eventScore The score string for this team in the current event. Depending on the size
 of the car screen, a maximum of 3 to 5 characters may be displayed.
 @param possessionIndicator An optional indicator used to indicate possession by this team.
 Only one team should have possession at a given time.
 @param favorite If true, the team is marked with a star to indicate it has been saved as a
 user favorite.
 */
- (instancetype)initWithName:(NSString *)name
                        logo:(CPNowPlayingSportsTeamLogo *)logo
               teamStandings:(nullable NSString *)teamStandings
                  eventScore:(NSString *)eventScore
         possessionIndicator:(nullable UIImage *)possessionIndicator
                    favorite:(BOOL)favorite;

/**
 A localized, user-visible name for this sports team.
 */
@property (nonatomic, copy, readonly) NSString *name;

/**
 The team logo or, if no logo is available, the initials/abbreviation for this team.
 See @c CPNowPlayingSportsTeamLogo.
 */
@property (nonatomic, copy, readonly) CPNowPlayingSportsTeamLogo *logo;

/**
 An optional additional label displayed near the team name. This could be a
 win-loss ratio string, team standings, or other statistics relevant to this team.
 Depending on the size of the car screen, a maximum of 15-20 characters may
 be displayed.
 */
@property (nonatomic, copy, nullable, readonly) NSString *teamStandings;

/**
 The numeric score string for this team in the current event. Depending on the size
 of the car screen, a maximum of 3 to 5 characters may be displayed.
 */
@property (nonatomic, copy, readonly) NSString *eventScore;

/**
 An optional indicator used to indicate possession by this team.
 Only one team should have possession at a given time.
 */
@property (nonatomic, copy, nullable, readonly) UIImage *possessionIndicator;

/**
 If true, the team is marked with a star to indicate it has been saved as a
 user favorite.
 */
@property (nonatomic, assign, readonly, getter=isFavorite) BOOL favorite;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A representation of the status of a sporting event.
 */
API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNowPlayingSportsEventStatus : NSObject <NSSecureCoding>

/**
 Initialize an event status with optional event status text, an optional event status image,
 and an optional event clock.
 
 @param eventStatusText Up to three separate strings for event status may be displayed.
 
 The first string should always be used to show the play period (quarter, inning, period)
 using as few characters as possible; e.g. "2nd" for the 2nd quarter.
 
 The second and third strings can be used to display additional information, like "1st & 10" and "SF 15"
 for an American football game.
 
 All three strings should be kept as brief as possible to ensure they display well on car screens
 of various sizes.
 @param eventStatusImage An optional event status image for this event, if it applies to this event. For example,
 a baseball game could display a representation of the bases and outs, indicating
 how many bases are loaded and the number of outs in the current inning.
 @param eventClock The event timer, if it applies to this event. See @c CPNowPlayingSportsClock.

 */
- (instancetype)initWithEventStatusText:(nullable NSArray <NSString *> *)eventStatusText
                       eventStatusImage:(nullable UIImage *)eventStatusImage
                             eventClock:(nullable CPNowPlayingSportsClock *)eventClock;

/**
 Up to three separate strings for event status may be displayed.
 
 The first string should always be used to show the play period (quarter, inning, period)
 using as few characters as possible; e.g. "2nd" for the 2nd quarter.
 
 The second and third strings can be used to display additional information, like "1st & 10" and "SF 15"
 for an American football game.
 
 All three strings should be kept as brief as possible to ensure they display well on car screens
 of various sizes.
 */
@property (nonatomic, copy, nullable, readonly) NSArray <NSString *> *eventStatusText;

/**
 The event timer, if it applies to this event. See @c CPNowPlayingSportsClock.
 */
@property (nonatomic, copy, nullable, readonly) CPNowPlayingSportsClock *eventClock;

/**
 An optional event status image for this event, if it applies to this event. For example,
 a baseball game could display a representation of the bases and outs, indicating
 how many bases are loaded and the number of outs in the current inning.
 */
@property (nonatomic, copy, nullable, readonly) UIImage *eventStatusImage;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A representation of the amount of time elapsed so far in this event,
 for events where the clock counts UP.
 
 Or, a representation of the amount of time remaining in the event,
 or a section of the event (period/quarter/etc.) for events where the
 clock counts DOWN.
 */
API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNowPlayingSportsClock : NSObject <NSSecureCoding>

/**
 Represents a duration of time that has elapsed so far in this event, or play period of the event (quarter/inning/period).
 
 When displayed on the now playing screen, the clock will count UP.
 
 @property elapsedTime The amount of time elapsed so far in this event.
 @property paused If YES, the clock will be paused at the specified elapsed time value. If NO, the clock will count up.
 */
- (instancetype)initWithElapsedTime:(NSTimeInterval)elapsedTime
                             paused:(BOOL)paused;

/**
 Represents an amount of time remaining in the event, or play period of the event (quarter/inning/period).
 
 When displayed on the now playing screen, the clock will count DOWN.
 
 @property timeRemaining The amount of time remaining in the event, or a play period of the event (quarter/inning/period).
 @property paused If YES, the clock will be paused at the specified time remaining value. If NO, the clock will count down.
 */
- (instancetype)initWithTimeRemaining:(NSTimeInterval)timeRemaining
                               paused:(BOOL)paused;

/**
 The time value in the clock; either elapsed time or time remaining.
 */
@property (nonatomic, assign, readonly) NSTimeInterval timeValue;

/**
 Whether the clock should be paused, e.g. due to a stoppage in play.
 
 If YES, the clock will be paused at the specified value.
 
 If NO, the clock will count up (or down).
 */
@property (nonatomic, assign, readonly, getter=isPaused) BOOL paused;

/**
 If true, the timer is counting UP, so as to indicate an amount of time elapsed
 so far in this event.
 
 If false, the timer is counting DOWN, so as to indicate an amount of time
 remaining in the event, or a play period of the event (quarter/inning/period).
 */
@property (nonatomic, assign, readonly) BOOL countsUp;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A logo image or, if no image is available, an abbreviation
 or initialism for this team.
 */
API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
CARPLAY_TEMPLATE_UI_ACTOR
@interface CPNowPlayingSportsTeamLogo : NSObject <NSSecureCoding>

/**
 Initialize a team logo with an image representation of this team.
 Provide an image no larger than 350x350; larger images will be resized down.
 */
- (instancetype)initWithTeamLogo:(UIImage *)teamLogo;

/**
 If no team logo image is available, initialize a team logo
 with an abbreviation or initialism for this team.
 
 A maximum of 3 characters may be displayed for the team initials.
 */
- (instancetype)initWithTeamInitials:(NSString *)teamInitials;

/**
 A team logo image for this team.
 */
@property (nonatomic, copy, nullable, readonly) UIImage *logo;

/**
 An abbreviation or initialism for this team, used only if
 no logo image is available for this team.
 */
@property (nonatomic, copy, nullable, readonly) NSString *initials;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
