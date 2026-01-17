//
//  NSUserActivity+CoreNFC.h
//  CoreNFC NSUserActivity category
//
//  Copyright © 2017 Apple. All rights reserved.
//
#ifndef NSUserActivity_CoreNFC_h
#define NSUserActivity_CoreNFC_h

#import <Foundation/Foundation.h>

@class NFCNDEFMessage;

NS_ASSUME_NONNULL_BEGIN


/*!
 * @category    NSUserActivity
 *
 * @discussion  Core NFC category for NSUserActivity.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos);
@interface NSUserActivity (CoreNFC)
/*!
 *  @property ndefMessagePayload
 *
 *  @discussion The NFC NDEF message with an Universal Link object that triggers the application launch.
 */
@property (readonly, nonnull, nonatomic) NFCNDEFMessage *ndefMessagePayload API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos, macos, tvos, visionos);

@end

NS_ASSUME_NONNULL_END

#endif
