//
//  SceneKitTypes.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

/*! @header SceneKitTypes
    @abstract Various types and utility functions used throughout SceneKit
 */

struct _SCNVector3
{
	CGFloat x, y, z;
};

typedef struct _SCNVector3 SCNVector3;

struct _SCNVector4
{
	CGFloat x, y, z, w;
};

typedef struct _SCNVector4 SCNVector4;


/*! Returns true if 'a' is exactly equal to 'b'. */
SCENEKIT_EXTERN bool SCNVector3EqualToVector3 (SCNVector3 a, SCNVector3 b);

/*! Returns true if 'a' is exactly equal to 'b'. */
SCENEKIT_EXTERN bool SCNVector4EqualToVector4 (SCNVector4 a, SCNVector4 b);

/*! Returns an initialized SCNVector3 */
SCENEKIT_INLINE SCNVector3 SCNVector3Make(CGFloat x, CGFloat y, CGFloat z) {
    SCNVector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

/*! Returns an initialized SCNVector4 */
SCENEKIT_INLINE SCNVector4 SCNVector4Make(CGFloat x, CGFloat y, CGFloat z, CGFloat w) {
    SCNVector4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

#ifdef __OBJC__

/*! @category NSValue(SceneKitAdditions)
 @abstract Adds methods to wrap vectors in NSValue objects.
 */

@interface NSValue (SceneKitAdditions)

+ (NSValue *)valueWithSCNVector3:(SCNVector3)v;
+ (NSValue *)valueWithSCNVector4:(SCNVector4)v;

- (SCNVector3)SCNVector3Value;
- (SCNVector4)SCNVector4Value;

@end

//domain for errors from SceneKit API.
SCENEKIT_EXTERN NSString *const SCNErrorDomain;

// NSError codes in SCNErrorDomain.
enum 
{
	SCNProgramCompilationError = 1
};


#endif /* __OBJC__ */

