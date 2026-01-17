//
//  CTCellularData.h
//  CFTelephony
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#ifdef __OBJC__

#import <CoreTelephony/CoreTelephonyDefines.h>
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, CTCellularDataRestrictedState) {
	kCTCellularDataRestrictedStateUnknown,
	kCTCellularDataRestricted,
	kCTCellularDataNotRestricted
};

typedef void (^CellularDataRestrictionDidUpdateNotifier)(CTCellularDataRestrictedState);

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(9_0)
@interface CTCellularData : NSObject
/*
 * cellularDataRestrictionDidUpdateNotifier
 *
 * A block that will be dispatched on the default priority global dispatch queue the first time 
 * app sets the callback handler and everytime there is a change in cellular data allowed policy 
 * for the app.
 */

@property (copy, nullable) CellularDataRestrictionDidUpdateNotifier cellularDataRestrictionDidUpdateNotifier API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos);
@property (nonatomic, readonly) CTCellularDataRestrictedState restrictedState API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos);
@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
