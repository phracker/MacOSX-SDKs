/*	NSObject.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSZone.h>

@class NSInvocation, NSMethodSignature, NSCoder, NSString, NSEnumerator;
@class Protocol;

/***************	Basic protocols		***************/

@protocol NSObject

- (BOOL)isEqual:(id)object;
- (NSUInteger)hash;

- (Class)superclass;
- (Class)class;
- (id)self;
- (NSZone *)zone;

- (id)performSelector:(SEL)aSelector;
- (id)performSelector:(SEL)aSelector withObject:(id)object;
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;

- (BOOL)isProxy;

- (BOOL)isKindOfClass:(Class)aClass;
- (BOOL)isMemberOfClass:(Class)aClass;
- (BOOL)conformsToProtocol:(Protocol *)aProtocol;

- (BOOL)respondsToSelector:(SEL)aSelector;

- (id)retain;
- (oneway void)release;
- (id)autorelease;
- (NSUInteger)retainCount;

- (NSString *)description;

@end

@protocol NSCopying

- (id)copyWithZone:(NSZone *)zone;

@end

@protocol NSMutableCopying

- (id)mutableCopyWithZone:(NSZone *)zone;

@end

@protocol NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder;
- (id)initWithCoder:(NSCoder *)aDecoder;

@end

/***********	Base class		***********/

@interface NSObject <NSObject> {
    Class	isa;
}

+ (void)load;

+ (void)initialize;
- (id)init;

+ (id)new;
+ (id)allocWithZone:(NSZone *)zone;
+ (id)alloc;
- (void)dealloc;

- (void)finalize AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

- (id)copy;
- (id)mutableCopy;

+ (id)copyWithZone:(NSZone *)zone;
+ (id)mutableCopyWithZone:(NSZone *)zone;

+ (Class)superclass;
+ (Class)class;
+ (BOOL)instancesRespondToSelector:(SEL)aSelector;
+ (BOOL)conformsToProtocol:(Protocol *)protocol;
- (IMP)methodForSelector:(SEL)aSelector;
+ (IMP)instanceMethodForSelector:(SEL)aSelector;
- (void)doesNotRecognizeSelector:(SEL)aSelector;

- (id)forwardingTargetForSelector:(SEL)aSelector;
- (void)forwardInvocation:(NSInvocation *)anInvocation;
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector;

+ (NSMethodSignature *)instanceMethodSignatureForSelector:(SEL)aSelector;

+ (NSString *)description;

+ (BOOL)isSubclassOfClass:(Class)aClass AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

+ (BOOL)resolveClassMethod:(SEL)sel AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
+ (BOOL)resolveInstanceMethod:(SEL)sel AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@interface NSObject (NSCoderMethods)

+ (NSInteger)version;
+ (void)setVersion:(NSInteger)aVersion;
- (Class)classForCoder;
- (id)replacementObjectForCoder:(NSCoder *)aCoder;
- (id)awakeAfterUsingCoder:(NSCoder *)aDecoder;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSObject (NSDeprecatedMethods)

+ (void)poseAsClass:(Class)aClass DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER
#if __OBJC2__
UNAVAILABLE_ATTRIBUTE
#endif
;

@end
#endif


#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED

/***********	Discardable Content		***********/

@protocol NSDiscardableContent
@required
- (BOOL)beginContentAccess;
- (void)endContentAccess;
- (void)discardContentIfPossible;
- (BOOL)isContentDiscarded;
@end

@interface NSObject (NSDiscardableContentProxy)
- (id)autoContentAccessingProxy AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
@end

#endif

/***********	Object Allocation / Deallocation		*******/
    
FOUNDATION_EXPORT id NSAllocateObject(Class aClass, NSUInteger extraBytes, NSZone *zone);

FOUNDATION_EXPORT void NSDeallocateObject(id object);

FOUNDATION_EXPORT id NSCopyObject(id object, NSUInteger extraBytes, NSZone *zone);

FOUNDATION_EXPORT BOOL NSShouldRetainWithZone(id anObject, NSZone *requestedZone);

FOUNDATION_EXPORT void NSIncrementExtraRefCount(id object);

FOUNDATION_EXPORT BOOL NSDecrementExtraRefCountWasZero(id object);

FOUNDATION_EXPORT NSUInteger NSExtraRefCount(id object);


