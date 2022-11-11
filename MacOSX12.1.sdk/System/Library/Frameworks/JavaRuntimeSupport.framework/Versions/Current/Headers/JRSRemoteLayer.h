//
//  JRSRemoteLayer.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <JavaRuntimeSupport/JRSDefines.h>

JRS_BEGIN_DECLS

JRS_EXPORT
JRS_DEPRECATED_2020_11
@protocol JRSRemoteLayer
@property(readonly) uint32_t layerID;
@end

JRS_DEPRECATED_2020_11
@interface CALayer (JavaRuntimeSupport)
- (NSObject<JRSRemoteLayer> *) createRemoteLayerBoundTo:(mach_port_t)serverPort NS_RETURNS_RETAINED;
- (void) hostRemoteLayer:(uint32_t)layerID;
@end

JRS_EXPORT
JRS_DEPRECATED_2020_11
@interface JRSRenderServer : NSObject { }
+ (mach_port_t) startRenderServer;
+ (NSString *) sendRenderServer:(mach_port_t)serverPort;
+ (mach_port_t) recieveRenderServer:(NSString *)serverName;
@end

JRS_END_DECLS
