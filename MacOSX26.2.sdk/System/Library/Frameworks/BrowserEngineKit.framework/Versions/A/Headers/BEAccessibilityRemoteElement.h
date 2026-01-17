//
//  BEAccessibilityRemoteElement.h
//  BrowserEngineKit
//
//  Created by Joshua Hoffman on 03/24/25.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IOS
/**
 @abstract BEAccessibilityRemoteHostElement connects the accessibility hierarchy of two separate processes. The remote host and remote elements share the same identifier to facilitate this connection. To use this, return this remote element from an object in your view hierarchy via its `accessibilityElements` method.
 */
BROWSERENGINE_EXTERN BROWSERENGINE_ACCESSIBILITY_REMOTE_AVAILABILITY
@interface BEAccessibilityRemoteHostElement : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 @abstract Initializes a remote element in the hosting process.
 @param identifier Unique identifier to connect this remote element to the remote element it hosts. This should be unique per pair of remote elements.
 @param remotePid The PID of the hosted remote element's process.
 */
- (id)initWithIdentifier:(NSString *)identifier remotePid:(pid_t)remotePid;

/**
 @abstract The accessibility ancestor of this element.
 @discussion This may be used by accessibility technologies to traverse from the remote element to the elements above it in the hierarchy.
*/
@property (nonatomic, weak) id accessibilityContainer;

@end

/**
 @abstract BEAccessibilityRemoteElement represents the destination of a BEAccessibilityRemoteHostElement in a different process. The elements it contains are defined by the `accessibilityElements` API. `BEAccessibilityRemoteElement` does not need to be returned in any element array.
 */
BROWSERENGINE_EXTERN BROWSERENGINE_ACCESSIBILITY_REMOTE_AVAILABILITY
@interface BEAccessibilityRemoteElement : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 @abstract Initializes and registers a remote element. This element doesn't need to be returned anywhere.
 @param identifier Unique identifier to connect this remote element to the hosting remote element. This should be unique per pair of remote elements.
 @param hostPid The PID of the host's remote element process.
 */
- (id)initWithIdentifier:(NSString *)identifier hostPid:(pid_t)hostPid;

@end

#endif // TARGET_OS_IOS

NS_ASSUME_NONNULL_END
