//
//  BEHostingHandle.h
//  BrowserEngineKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(ios(17.4))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
BROWSERENGINE_FINAL
NS_SWIFT_SENDABLE
NS_SWIFT_NAME(LayerHierarchyHandle)
@interface BELayerHierarchyHandle : NSObject <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

#if BROWSERENGINEKIT_HAS_LIBXPC
+ (nullable BELayerHierarchyHandle *)handleWithXPCRepresentation:(nullable xpc_object_t)xpcRepresentation error:(NSError **)error NS_SWIFT_NAME(init(xpcRepresentation:));
- (xpc_object_t)createXPCRepresentation NS_SWIFT_NAME(createXPCRepresentation());
#endif

/// Decodes a handle form a `mach_port_t` send right and its accompanying metadata.
/// - This method takes ownership of the port right (even if it returns an error).
+ (nullable BELayerHierarchyHandle *)handleWithPort:(mach_port_t)port
                                               data:(NSData *)data
                                              error:(NSError **)error NS_SWIFT_NAME(init(port:data:)) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos, tvos, visionos);

/// Encodes the handle into a `mach_port_t` send right and its accompanying metadata.
/// - The block is responsible for disposing of `copiedPort` - failure to manage its lifecycle will leak the port. Note that some functions (like ``handleWithPort:data:error:``) will assume control of the right for you.
/// - `copiedPort` will be `MACH_PORT_NULL` if the ``BELayerHierarchy`` pointed to by the handle is already invalidated.
/// - The port and data should ultimately be consumed together  by ``handleWithPort:data:error:``.
- (void)encodeWithBlock:(void(^ NS_NOESCAPE)(mach_port_t copiedPort, NSData *data))block NS_SWIFT_NAME(encode(_:)) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, watchos, tvos, visionos);

@end

NS_ASSUME_NONNULL_END
