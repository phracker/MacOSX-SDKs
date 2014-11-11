//
//  JRSRemoteLayer.h
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>


@protocol JRSRemoteLayer
@property(readonly) uint32_t layerID;
@end

@interface CALayer (JavaRuntimeSupport)
- (NSObject<JRSRemoteLayer> *) createRemoteLayerBoundTo:(mach_port_t)serverPort;
- (void) hostRemoteLayer:(uint32_t)layerID;
@end

@interface JRSRenderServer : NSObject { }
+ (mach_port_t) startRenderServer;
+ (NSString *) sendRenderServer:(mach_port_t)serverPort;
+ (mach_port_t) recieveRenderServer:(NSString *)serverName;
@end
