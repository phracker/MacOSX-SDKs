//  
//  GCEventInteraction.h
//  GameController
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Constants that represent types of events.
 */
typedef NS_OPTIONS(NSUInteger, GCUIEventTypes) {
    GCUIEventTypeNone           = (0U),
    /** A constant that represents events from a game controller. */
    GCUIEventTypeGamepad        = (1U << 0),
    /** A constant that represents events from a stylus. */
    GCUIEventTypeStylus         API_AVAILABLE(visionos(26.2)) API_UNAVAILABLE(macCatalyst, ios, tvos) API_UNAVAILABLE(macos) = (1U << 1),
} API_AVAILABLE(macCatalyst(18.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos);


/**
 *  An interaction that indicates the view's intent to receive game controller
 *  events through the Game Controller framework.
 *
 *  @discussion
 *  On visionOS, users can interact with your app using a game controller. By
 *  default, the system converts game controller actions into pinch events and
 *  sends them to the view the user is gazing at, its gesture recognizers, and
 *  then up the responder chain.
 *
 *  If you use the Game Controller framework to handle game controller events
 *  for part of your user interface, add an instance of `GCEventInteraction`
 *  to the root of that part of your app’s view hierarchy.  For example, if you
 *  are writing a game using Metal, add this interaction to the view that hosts
 *  your game’s `CAMetalLayer`.
 *
 *  @note
 *  This class should not be subclassed.
 */
API_AVAILABLE(macCatalyst(18.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos)
@interface GCEventInteraction : NSObject

/** Creates a game controller interaction. */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 *  The types of events that should be delivered through the Game Controller
 *  framework.
 */
@property (nonatomic, readwrite) GCUIEventTypes handledEventTypes;

/**
 *  A Boolean value that determines whether events are delivered exclusively
 *  through the Game Controller framework.
 *
 *  If `YES`, events of the types specified by `handledEventTypes` are
 *  delivered both through the Game Controller framework and as UIKit event
 *  objects to your app's views and gesture recognizers.
 *
 *  If `NO`, events of the types specified by `handledEventTypes` are
 *  delivered **exclusively** through the Game Controller framework.
 *
 *  The default value of this property is `NO`.
 *  This property has no effect if `handledEventTypes` is `GCUIEventTypeNone`.
 */
@property (nonatomic, readwrite) BOOL receivesEventsInView API_AVAILABLE(macCatalyst(26.0), ios(26.0), visionos(26.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos);

@end


@interface GCEventInteraction (UIInteraction) <UIInteraction>
@end

NS_ASSUME_NONNULL_END
