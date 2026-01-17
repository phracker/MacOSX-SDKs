/*	SBObject.h
	Copyright (c) 2006, Apple, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <ApplicationServices/ApplicationServices.h>


NS_ASSUME_NONNULL_BEGIN

@class SBAppContext, SBElementArray;


/// The `SBObject` class declares methods that can be invoked on any object in a
/// scriptable application. It defines methods for getting elements and
/// properties of an object, as well as setting a given object to a new value.
///
/// Each `SBObject` is built around an object specifier, which tells Scripting
/// Bridge how to locate the object. Therefore, you can think of an `SBObject`
/// as a reference to an object in an target application rather than an object
/// itself. To bypass this reference-based approach and force evaluation, use
/// the ``SBObject/get`` method.
///
/// Typically, rather than create `SBObject` instances explictly, you receive
/// `SBObject` objects by calling methods of an ``SBApplication`` subclass. For
/// example, if you wanted to get an `SBObject` representing the current iTunes
/// track, you would use code like this (where `iTunesTrack` is a subclass of
/// `SBObject`):
///
/// ```objc
/// iTunesApplication *iTunes = [SBApplication applicationWithBundleIdentifier:@"com.apple.iTunes"];
/// iTunesTrack *track = [iTunes currentTrack];
/// ```
///
/// You can discover the names of dynamically generated classes such as
/// `iTunesApplication` and `iTunesTrack` by examining the header file created
/// by the `sdp` tool. Alternatively, you give these variables the dynamic
/// Objective-C type `id`.
API_AVAILABLE(macos(10.5), macCatalyst(13.0))
@interface SBObject : NSObject <NSCoding>
{
	AEDesc _specifier;
	SBAppContext *_ctx;
	id _reserved;
}


/// Initializes and returns an instance of an `SBObject` subclass.
///
/// Scripting Bridge does not actually create an object in the target
/// application until you add the object returned from this method to an element
/// array (``SBElementArray``).
///
/// - Returns: An `SBObject` object or `nil` if the object could not be
/// initialized.
- (instancetype) init;

/// Returns an instance of an `SBObject` subclass initialized with the specified
/// properties.
///
/// Scripting Bridge does not actually create an object in the target
/// application until you add the object returned from this method to an element
/// array (``SBElementArray``).
///
/// - Parameters:
///   - properties: A dictionary with keys specifying the names of properties
/// (that is, attributes or to-one relationships) and the values for those
/// properties.
///
/// - Returns: An `SBObject` object or `nil` if the object could not be
/// initialized.
- (instancetype) initWithProperties:(NSDictionary *)properties;

/// Returns an instance of an `SBObject` subclass initialized with the given
/// data.
///
/// Scripting Bridge does not actually create an object in the target
/// application until you add the object returned from this method to an element
/// array (``SBElementArray``).
///
/// - Parameters:
///   - data: An object containing data for the new `SBObject` object. The data
/// varies according to the type of scripting object to be created.
///
/// - Returns: An `SBObject` object or `nil` if the object could not be
/// initialized.
- (instancetype) initWithData:(id)data;

/// Forces evaluation of the receiver, causing the real object to be returned
/// immediately.
///
/// This method forces the current object reference (the receiver) to be
/// evaluated, resulting in the return of the referenced object. By default,
/// Scripting Bridge deals with references to objects until you actually request
/// some concrete data from them or until you call the `get` method.
///
/// - Returns: For most properties, the result is a Foundation object such as an `NSString`. For properties with no Foundation equivalent, the result is an `NSAppleEventDescriptor` or another ``SBObject`` for most elements.
- (nullable id) get;

/// The error from the last event this object sent, or nil if it succeeded.
- (nullable NSError *) lastError NS_AVAILABLE(10_6, NA);

@end


API_AVAILABLE(macos(10.5), macCatalyst(13.0))
@interface SBObject (SBGlueInterface)
// These methods, while public, are primarily intended for use by sdp-generated glue
// code.  You are not expected to use them directly, but you may, for example, to control
// a generic application without glue.


/// Returns an instance of an `SBObject` subclass initialized with the specified
/// properties and data and added to the designated element array.
///
/// Unlike the other initializers of this class, this method not only
/// initializes the `SBObject` object but adds it to a specified element array.
/// This method is the designated initializer.
///
/// - Parameters:
///   - code: A four-character code used to identify an element in the target
/// application’s scripting interface. See
/// <doc://com.apple.documentation/documentation/applicationservices/apple_event_manager>
/// for details.
///
///   - properties: A dictionary with <doc://com.apple.documentation/documentation/foundation/nsnumber> keys specifying the four-character codes of properties
/// (that is, attributes or to-one relationships) and the values for those
/// properties. Pass `nil` if you are initializing the object by `data` only.
///
///   - data: An object containing data for the new `SBObject` object. The data
/// varies according to the type of scripting object to be created. Pass `nil`
/// if you initializing the object by `properties` only.
///
/// - Returns: An `SBObject` object or `nil` if the object could not be
/// initialized.
- (instancetype) initWithElementCode:(DescType)code properties:(nullable NSDictionary<NSString *, id> *)properties data:(nullable id)data;

/// Returns an object representing the specified property of the receiver.
///
/// `SBObject` subclasses use this method to implement application-specific
/// property accessor methods. You should not need to call this method directly.
///
/// - Parameters:
///   - code: A four-character code that uniquely identifies a property of the
/// receiver.
///
/// - Returns: An object representing the receiver’s property as identified by
/// `code`.
- (SBObject *) propertyWithCode:(AEKeyword)code;

/// Returns an object of the designated scripting class representing the
/// specified property of the receiver
///
/// `SBObject` subclasses use this method to implement application-specific
/// property accessor methods. You should not need to call this method directly.
///
/// > Note: This method doesn't retrieve the value of the property. To get the
///   value, call ``get``.
///
/// - Parameters:
///   - class: The `SBObject` subclass with which to instantiate the object.
///
///   - code: A four-character code that uniquely identifies a property of the
/// receiver.
///
/// - Returns: An instance of the designated `class` that represents the
/// receiver’s property identified by `code`.
- (SBObject *) propertyWithClass:(Class)cls code:(AEKeyword)code;

/// Returns an array containing every child of the receiver with the given
/// class-type code.
///
/// `SBObject` subclasses use this method to implement application-specific
/// property accessor methods. You should not need to call this method directly.
///
/// > Note: This method doesn't retrieve the value of the property. To get the
///   value, call ``get``.
///
/// - Parameters:
///   - code: A four-character code that identifies a scripting class.
///
/// - Returns: An ``SBElementArray`` object containing every child of the
/// receiver whose class matches `code`.
- (SBElementArray *) elementArrayWithCode:(DescType)code;

/// Sends an Apple event with the given event class, event ID, and format to the
/// target application.
///
/// Scripting Bridge uses this method to communicate with target applications.
/// If the target application responds to this method by sending an Apple event
/// representing an error, the receiver calls its delegate's
/// ``SBApplicationDelegate/eventDidFail:withError:`` method. If no delegate has
/// been assigned, the receiver raises an exception.
///
/// You should rarely have to call this method directly.
///
/// - Parameters:
///   - eventClass: The event class of the Apple event to be sent.
///
///   - eventID: The event ID of the Apple event to be sent.
///
///   - firstParamCode,...: A list of four-character parameter codes
/// (<doc://com.apple.documentation/documentation/coreservices/desctype>) and
/// object values (`id`) terminated by a zero.
///
/// - Returns: The target application's Apple event sent in reply; it is
/// converted to a Cocoa object of an appropriate type.
- (id) sendEvent:(AEEventClass)eventClass id:(AEEventID)eventID parameters:(DescType)firstParamCode, ...;

/// Sets the receiver to a specified value.
///
/// You should not call this method directly.
///
/// - Parameters:
///   - value: The data the receiver should be set to. It can be an
/// <doc://com.apple.documentation/documentation/foundation/nsstring>,
/// <doc://com.apple.documentation/documentation/foundation/nsnumber>,
/// <doc://com.apple.documentation/documentation/foundation/nsarray>,
/// `SBObject`, or any other type of object supported by the Scripting Bridge
/// framework.
- (void) setTo:(nullable id)value;

@end

NS_ASSUME_NONNULL_END
