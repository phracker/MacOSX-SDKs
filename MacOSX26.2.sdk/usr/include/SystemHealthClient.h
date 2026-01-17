//
//  SystemHealthClient.h
//  SystemHealth
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SystemHealthManager.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  Clients must override getComponentStatusWithError in a sub Class of SystemHealthClient
 */
__attribute__((visibility("default")))
@interface SystemHealthClient : NSObject

@property (nonatomic) SHComponentType componentType;

- (instancetype) init __attribute__((unavailable("Please use initWithComponentType")));
- (instancetype) initWithComponentType:(SHComponentType) component;

- (SHComponentStatus) getComponentStatusWithError:(NSError **) error;

@end

NS_ASSUME_NONNULL_END
