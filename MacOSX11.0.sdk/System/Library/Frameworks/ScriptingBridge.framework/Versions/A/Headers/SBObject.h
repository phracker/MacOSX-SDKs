/*	SBObject.h
	Copyright (c) 2006, Apple, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <ApplicationServices/ApplicationServices.h>


NS_ASSUME_NONNULL_BEGIN

@class SBAppContext, SBElementArray;

NS_CLASS_AVAILABLE(10_5, NA)
@interface SBObject : NSObject <NSCoding>
{
	AEDesc _specifier;
	SBAppContext *_ctx;
	id _reserved;
}

- (instancetype) init;
- (instancetype) initWithProperties:(NSDictionary *)properties;
- (instancetype) initWithData:(id)data;
	// Initializers.  Calling one of these does not create an object in the target
	// application; you must add the result to an SBElementArray for that.

- (nullable id) get;
	// Evaluate the object by sending it to the target application.  Depending on what
	// the object points to, the result may be a Foundation object such as an NSString
	// (for most properties), an NSAppleEventDescriptor (for properties of a type with
	// no Foundation equivalent), or another SBObject (for most elements).

- (nullable NSError *) lastError NS_AVAILABLE(10_6, NA);
	// Return the error from the last event this object sent, or nil if it succeeded.

@end


@interface SBObject (SBGlueInterface)
// These methods, while public, are primarily intended for use by sdp-generated glue
// code.  You are not expected to use them directly, but you may, for example, to control
// a generic application without glue.

- (instancetype) initWithElementCode:(DescType)code properties:(nullable NSDictionary<NSString *, id> *)properties data:(nullable id)data;
	// Basic initializer.  The property dictionary keys should be NSNumbers with the
	// four-byte codes of the properties.  Like the rest of the initializers, this does
	// not create an object in the target application.

- (SBObject *) propertyWithCode:(AEKeyword)code;
- (SBObject *) propertyWithClass:(Class)cls code:(AEKeyword)code;
	// Get a property specifier.  This does not get the value of the property; you must
	// call -get for that.  The class parameter of -propertyWithClass:code: must be a
	// descendant of SBObject; this method is typically not useful without glue.

- (SBElementArray *) elementArrayWithCode:(DescType)code;
	// Get an element array specifier.  Like -propertyWithCode, this does not get the
	// value; you must call -get or one of the array accessors such as -objectAtIndex:
	// for that.

- (id) sendEvent:(AEEventClass)eventClass id:(AEEventID)eventID parameters:(DescType)firstParamCode, ...;
	// Send an Apple event.  The direct parameter is the specifier of the receiver if it
	// is non-null.  Other parameters are given using "parameters:" as a list of pairs
	// of the parameter four-byte code followed by an Objective-C object; use a parameter
	// code of 0 to mark the end of the list.

- (void) setTo:(nullable id)value;
	// Set the value of the object.  This is shorthand for "sendEvent:'core' id:'setd'
	// parameters:'data', value, 0".

@end

NS_ASSUME_NONNULL_END
