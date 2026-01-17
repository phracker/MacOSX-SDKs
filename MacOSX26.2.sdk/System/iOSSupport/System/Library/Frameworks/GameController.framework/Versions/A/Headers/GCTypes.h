//
//  GCTypes.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

NS_ASSUME_NONNULL_BEGIN

struct GCPoint2 {
    float x;
    float y;
} API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1));
typedef struct CF_BOXABLE GCPoint2 GCPoint2;

/* The "zero" point -- equivalent to GCPoint2Make(0, 0). */
GAMECONTROLLER_EXPORT const GCPoint2 GCPoint2Zero API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1));

API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1))
CF_INLINE GCPoint2
GCPoint2Make(float x, float y) {
    GCPoint2 p; p.x = x; p.y = y; return p;
}

API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1))
CF_INLINE bool
GCPoint2Equal(GCPoint2 point1, GCPoint2 point2) {
    return point1.x == point2.x && point1.y == point2.y;
}

GAMECONTROLLER_EXPORT NSString* NSStringFromGCPoint2(GCPoint2 point) API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1));


@interface NSValue (GCTypes)

+ (instancetype)valueWithGCPoint2:(GCPoint2)point API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1));

@property(nonatomic, readonly) GCPoint2 GCPoint2Value API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1));

@end

NS_ASSUME_NONNULL_END
