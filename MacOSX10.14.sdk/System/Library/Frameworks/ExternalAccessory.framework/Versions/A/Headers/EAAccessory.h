//
//  EAAccessory.h
//  ExternalAccessory
//
//  NOTE: Data to the external accessory is automatically wrapped into an iAP
//        packet after bring sent to the output stream. The iAP wrapper is
//        automatically stripped from incoming packets before being sent to
//        the EAAccessory input stream.
//
//        Further information related to these wrapper can be found in the
//        iAP specifications.
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class EAAccessoryInternal;
@protocol EAAccessoryDelegate;

enum {
    EAConnectionIDNone = 0,
};

__OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) @interface EAAccessory : NSObject {
@private
    EAAccessoryInternal *_internal;
}

@property(nonatomic, readonly, getter=isConnected) BOOL connected __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSUInteger connectionID __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSString *manufacturer __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSString *name __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSString *modelNumber __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSString *serialNumber __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSString *firmwareRevision __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSString *hardwareRevision __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@property(nonatomic, readonly) NSString *dockType __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_9_0);

// array of strings representing the protocols supported by the accessory
@property(nonatomic, readonly) NSArray<NSString *> *protocolStrings __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);

@property(nonatomic, assign, nullable) id<EAAccessoryDelegate> delegate __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);

@end

@protocol EAAccessoryDelegate <NSObject>
@optional
- (void)accessoryDidDisconnect:(EAAccessory *)accessory __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
@end

NS_ASSUME_NONNULL_END
