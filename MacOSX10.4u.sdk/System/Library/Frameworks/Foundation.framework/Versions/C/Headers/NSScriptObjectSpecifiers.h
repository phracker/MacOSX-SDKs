/*
	NSScriptObjectSpecifiers.h
	Copyright (c) 1997-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSAppleEventDescriptor, NSScriptClassDescription, NSScriptWhoseTest, NSString;

// Error codes for specific problems evaluating specifiers
enum {
    NSNoSpecifierError = 0,
    NSNoTopLevelContainersSpecifierError, // Someone called evaluate with nil.
    NSContainerSpecifierError, // Error evaluating container specifier.
    NSUnknownKeySpecifierError, // Receivers do not understand the key.
    NSInvalidIndexSpecifierError, // Index out of bounds
    NSInternalSpecifierError, // Other internal error
    NSOperationNotSupportedForKeySpecifierError // Attempt made to perform an unsuppported opweration on some key
};


typedef enum {
    NSPositionAfter,
    NSPositionBefore,
    NSPositionBeginning,
    NSPositionEnd,
    NSPositionReplace
} NSInsertionPosition;


typedef enum {
    NSRelativeAfter = 0,
    NSRelativeBefore
} NSRelativePosition;


typedef enum {
    NSIndexSubelement = 0,
    NSEverySubelement = 1,
    NSMiddleSubelement = 2,
    NSRandomSubelement = 3,
    NSNoSubelement = 4 // Only valid for the end subelement
} NSWhoseSubelementIdentifier;


// This class represents a specifier to a set of objects.  It can be evaluated to return the objects it specifiers.  This abstract superclass is subclassed for each type of specifier.
// A specifier always accesses a specific property of an object or array of objects.  The object accessed is called the container (or container).  When object specifiers are nested the container[s] are described by the container specifier.  When an object specifier has no container specifier, the container objects must be supplied explicitly.
// Object specifiers can be nested.  The child retains its container specifier.

@interface NSScriptObjectSpecifier : NSObject <NSCoding> {
    @private
    NSScriptObjectSpecifier *_container;
    NSScriptObjectSpecifier *_child;
    NSString *_key;
    NSScriptClassDescription *_containerClassDescription;
    BOOL _containerIsObjectBeingTested;
    BOOL _containerIsRangeContainerObject;
    char _padding[2];
    NSAppleEventDescriptor *_descriptor;
    int _error;
}

- (id)initWithContainerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property;
    // This figures out the container class desc from the container specifier.

- (id)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property;
    // Designated initializer.

- (NSScriptObjectSpecifier *)childSpecifier;
- (void)setChildSpecifier:(NSScriptObjectSpecifier *)child;
    // You generally should not call the set method.  It is called automatically by setContainerSpecifier:.

- (NSScriptObjectSpecifier *)containerSpecifier;
- (void)setContainerSpecifier:(NSScriptObjectSpecifier *)subRef;
     // setContainerSpecifier: calls [child setChildSpecifier:self] as well.

- (BOOL)containerIsObjectBeingTested;
- (void)setContainerIsObjectBeingTested:(BOOL)flag;
    // If our containerSpecifier is nil, this flag determines whether the top-level container is the default top-level object or the object currently being tested by an NSWhoseSpecifier.
- (BOOL)containerIsRangeContainerObject;
- (void)setContainerIsRangeContainerObject:(BOOL)flag;
    // If our containerSpecifier is nil, this flag determines whether the top-level container is the default top-level object or the object that is the container for the current range specifier being evaluated.
    // One or neither of -containerIsObjectBeingTested and -containerIsRangeContainerObject should be set to YES.  Setting both of these to YES makes no sense.

- (NSString *)key;
- (void)setKey:(NSString *)key;
    // The name of the key in the container object to be accessed by this specifier.

- (NSScriptClassDescription *)containerClassDescription;
- (void)setContainerClassDescription:(NSScriptClassDescription *)classDesc;
- (NSScriptClassDescription *)keyClassDescription;

- (int *)indicesOfObjectsByEvaluatingWithContainer:(id)container count:(int *)count;
    // Returning with count == -1 is shorthand for all indices.
    // count == 0 means no objects match.
- (id)objectsByEvaluatingWithContainers:(id)containers;
- (id)objectsByEvaluatingSpecifier;

- (int)evaluationErrorNumber;
- (void)setEvaluationErrorNumber:(int)error;

- (NSScriptObjectSpecifier *)evaluationErrorSpecifier;

@end


@interface NSObject (NSScriptObjectSpecifiers)

- (NSScriptObjectSpecifier *)objectSpecifier;
    // Overridden by objects that can provide a fully specified object specifier to themselves within an app.

- (NSArray *)indicesOfObjectsByEvaluatingObjectSpecifier:(NSScriptObjectSpecifier *)specifier;
    // Containers that want to evaluate some specifiers on their own should implement this method.  The result array should be full of NSNumber objects which identify the indices of the matching objects.  If this method returns nil, the object specifier will go on to do its own evaluation.  If this method returns an array, the object specifier will use the NSNumbers in it as the indices.  So, if you evaluate the specifier and there are no objects which match, you should return an empty array, not nil.  If you find only one object you should still return its index in an array.  Returning an array with a single index where the index is -1 is interpretted to mean all the objects.

@end


// An Index specifiers return the object at the specified index for the specifier's property.  A negative index counts from the end of the array.

@interface NSIndexSpecifier : NSScriptObjectSpecifier {
    @private
    int _index;
}

- (id)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property index:(int)index;

- (int)index;
- (void)setIndex:(int)index;

@end


// A Middle specifier returns the middle object from the objects for the specifier's property.  If there are an even number of objects it returns the object before the midpoint.

@interface NSMiddleSpecifier : NSScriptObjectSpecifier {}

@end


#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

// A Name specifier returns the object with the specified name.

@interface NSNameSpecifier : NSScriptObjectSpecifier {
    @private
    NSString *_name;
}

- (id)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property name:(NSString *)name;

- (NSString *)name;
- (void)setName:(NSString *)name;

@end

#endif


@interface NSPositionalSpecifier : NSObject {
    @private
    NSScriptObjectSpecifier *_specifier;
    NSInsertionPosition _unadjustedPosition;
    NSScriptClassDescription *_insertionClassDescription;
    id _moreVars;
    void *_reserved0;
}

// Given an object specifier and an insertion position relative to the specified object, initialize.
- (id)initWithPosition:(NSInsertionPosition)position objectSpecifier:(NSScriptObjectSpecifier *)specifier;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

// Set the class description for the object or objects to be inserted.  This message can be sent at any time after object initialization, but must be sent before evaluation to have any effect.
- (void)setInsertionClassDescription:(NSScriptClassDescription *)classDescription;

#endif

// Evaluate this positional specifier.  If evaluation is successful, subsequent -insertionContainer, -insertionKey, -insertionIndex, and -insertionReplaces messages sent to this object will return the results of the evaluation.
- (void)evaluate;

// Return the container into which insertion should be done, if evaluation has been successful, or nil otherwise.  If this object has never been evaluated, evaluation is attempted.
- (id)insertionContainer;

// Return the key for the to-many relationship for which insertion should be done, if evaluation has been successful, or nil otherwise.  If this object has never been evaluated, evaluation is attempted.
- (NSString *)insertionKey;

// Return an index into the set of keyed to-many relationship objects before which insertion should be done in the insertion container, if evaluation has been successful, or -1 otherwise.  If this object has never been evaluated, evaluation is attempted.
- (int)insertionIndex;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

// Return YES if evaluation has been successful and the object to be inserted should actually replace the keyed, indexed object in the insertion container, instead of being inserted before it, or NO otherwise.  If this object has never been evaluated, evaluation is attempted.
- (BOOL)insertionReplaces;

#endif

@end


// This returns all the objects for the specifier's property.  This is used for accessing singular properties as well as for the "Every" specifier type for plural properties.

@interface NSPropertySpecifier : NSScriptObjectSpecifier {}

@end


// A Random specifier returns an object chosen at random from the objects for the specifier's property.

@interface NSRandomSpecifier : NSScriptObjectSpecifier {}

@end


// A Range specifier returns a contiguous subset of the objects for the specifier's property.

@interface NSRangeSpecifier : NSScriptObjectSpecifier {
    @private
    NSScriptObjectSpecifier *_startSpec;
    NSScriptObjectSpecifier *_endSpec;
}

- (id)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property startSpecifier:(NSScriptObjectSpecifier *)startSpec endSpecifier:(NSScriptObjectSpecifier *)endSpec;

- (NSScriptObjectSpecifier *)startSpecifier;
- (void)setStartSpecifier:(NSScriptObjectSpecifier *)startSpec;

- (NSScriptObjectSpecifier *)endSpecifier;
- (void)setEndSpecifier:(NSScriptObjectSpecifier *)endSpec;

@end


@interface NSRelativeSpecifier : NSScriptObjectSpecifier {
    @private
    NSRelativePosition _relativePosition;
    NSScriptObjectSpecifier *_baseSpecifier;
}

- (id)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property relativePosition:(NSRelativePosition)relPos baseSpecifier:(NSScriptObjectSpecifier *)baseSpecifier;

- (NSRelativePosition)relativePosition;
- (void)setRelativePosition:(NSRelativePosition)relPos;

- (NSScriptObjectSpecifier *)baseSpecifier;
- (void)setBaseSpecifier:(NSScriptObjectSpecifier *)baseSpecifier;
    // This is another object specifier (which will be evaluated within the same container objects that this specifier is evalutated in).  To find the indices for this specifier we will evaluate the base specifier and take the index before or after the indices returned.

@end


#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED

// A Unique ID specifier returns the object with the specified ID.

@interface NSUniqueIDSpecifier : NSScriptObjectSpecifier {
    @private
    id _uniqueID;
}

- (id)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property uniqueID:(id)uniqueID;

- (id)uniqueID;
- (void)setUniqueID:(id)uniqueID;

@end

#endif


// A Qualified specifier uses a qualifier and another object specifier to get a subset of the objects for the specifier's property.  The other object specifier is evaluated for each object using that object as the container and the objects that result are tested with the qualifier.  An example makes this easier to understand.
// Take the specifier "paragraphs where color of third word is blue".
// This would result in an NSWhoseSpecifier where:
//     property name = "paragraphs"
//     other specifier = Index specifier with property "words" and index 3
//     qualifier = key value qualifier for key "color" and value [NSColor blueColor]

// The "subelement" stuff is to support stuff like "the first word whose..."

@interface NSWhoseSpecifier : NSScriptObjectSpecifier {
    @private
    NSScriptWhoseTest *_test;
    NSWhoseSubelementIdentifier _startSubelementIdentifier;
    int _startSubelementIndex;
    NSWhoseSubelementIdentifier _endSubelementIdentifier;
    int _endSubelementIndex;
}

- (id)initWithContainerClassDescription:(NSScriptClassDescription *)classDesc containerSpecifier:(NSScriptObjectSpecifier *)container key:(NSString *)property test:(NSScriptWhoseTest *)test;

- (NSScriptWhoseTest *)test;
- (void)setTest:(NSScriptWhoseTest *)test;


- (NSWhoseSubelementIdentifier)startSubelementIdentifier;
- (void)setStartSubelementIdentifier:(NSWhoseSubelementIdentifier)subelement;

- (int)startSubelementIndex;
- (void)setStartSubelementIndex:(int)index;
    // Only used if the startSubelementIdentifier == NSIndexSubelement

- (NSWhoseSubelementIdentifier)endSubelementIdentifier;
- (void)setEndSubelementIdentifier:(NSWhoseSubelementIdentifier)subelement;

- (int)endSubelementIndex;
- (void)setEndSubelementIndex:(int)index;
    // Only used if the endSubelementIdentifier == NSIndexSubelement

@end
