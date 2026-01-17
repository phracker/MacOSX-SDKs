//  
//  GCPhysicalInputSource.h
//  GameController
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCInputNames.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  One or more directions associated with a \c GCPhysicalInputSource.
 */
typedef NS_OPTIONS(NSUInteger, GCPhysicalInputSourceDirection) {
    GCPhysicalInputSourceDirectionNotApplicable   = 0,
    GCPhysicalInputSourceDirectionUp              = (1<<0UL),
    GCPhysicalInputSourceDirectionRight           = (1<<1UL),
    GCPhysicalInputSourceDirectionDown            = (1<<2UL),
    GCPhysicalInputSourceDirectionLeft            = (1<<3UL),
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));


/**
 *  A description of the actual physical input element that a user interacts
 *  with to manipulate the the value of an input that is exposed to the app.
 *
 *  By querying the source of an element's input that is returned from
 *  \c GCDevicePhysicalInput or \c GCDevicePhysicalInputState, an app
 *  can see through element remappings applied by the user in the system
 *  game controller settings.  For example, assuming the user has
 *  swapped the A and B buttons in the system game controller settings...
 *
 *      YES == [physicalInput.buttons[GCInputButtonA].pressedInput.source.elementAliases contains:GCInputButtonB]
 *      YES == [physicalInput.buttons[GCInputButtonB].pressedInput.source.elementAliases contains:GCInputButtonA]
 *
 *  Examining an input's source is discouraged, but may be necessary depending
 *  on how your game's input handling code is implemented.  If possible, prefer
 *  to load and display the \c sfSymbolsName and \c localizedName from the
 *  \c GCPhysicalInputElement in any in-game U.I.
 *
 *      // Use these anywhere you need to instruct the user to press the 'A'
 *      // button in your game UI.  The symbol name and localized string
 *      // returned will reflect the element that GCInputButtonA has been
 *      // remapped to (Button B in the above case).
 *      physicalInput.buttons[GCInputButtonA].localizedName
 *      physicalInput.buttons[GCInputButtonA].sfSymbolsName
 *
 *  @note
 *  Objects conforming to \c GCPhysicalInputSource protocol are vended by the
 *  GameController framework.  You should not conform to this protocol in your
 *  own types.
 */
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@protocol GCPhysicalInputSource <NSObject>

/** The set of aliases for the element that the user interacts with. */
@property (copy, readonly) NSSet<GCInputElementName> *elementAliases;

/** The localized name of the element that the user interacts with. */
@property (copy, readonly, nullable) NSString *elementLocalizedName;

/** The SF Symbol of the element that the user interacts with. */
@property (copy, readonly, nullable) NSString *sfSymbolsName;

/** One or more directions associated with the source. */
@property (readonly) GCPhysicalInputSourceDirection direction;

@end

NS_ASSUME_NONNULL_END
