//
//  IOBluetoothTransferProgressUI.h
//  IOBluetoothFamily
//
//  Created by mat on Mon Mar 24 2003.
//  Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#import <IOBluetooth/objc/IOBluetoothTransferProgress.h>

@interface IOBluetoothTransferProgressUI : IOBluetoothTransferProgress {

	NSProgressIndicator * mProgressIndicator;
	NSTextField * mStatusField;
	NSTextField * mBytesTransferredField;
	NSTextField * mTimeRemainingField;
}


- (void) setProgressIndicator: (NSProgressIndicator*) inProgress;
- (void) setTransferedBytesField: (NSTextField*) inField;
- (void) setTimeRemainingField: (NSTextField*) inField;

- (void) transferStarted;
- (void) transferCancelled;

- (void) updateUI;

- (NSString*) getBytesTransferredAsString;
- (NSString *) getByteSizeString:(UInt32)numBytes;

- (NSString *)locString:(NSString *)keyString;

@end
