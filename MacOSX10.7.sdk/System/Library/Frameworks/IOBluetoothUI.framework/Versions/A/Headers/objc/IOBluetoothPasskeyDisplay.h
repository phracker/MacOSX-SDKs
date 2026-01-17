//
//  IOBluetoothPasskeyDisplay.h
//  Copyright 2010 Apple, Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@class IOBluetoothDevice;

typedef enum {
    kBluetoothKeyboardANSIReturn,
	kBluetoothKeyboardISOReturn,
    kBluetoothKeyboardJISReturn
} BluetoothKeyboardReturnType;

@interface IOBluetoothPasskeyDisplay : NSView
{
	IBOutlet NSImageView *		mReturnImageView;
	NSImage *					mReturnImage;
	NSImage *					mReturnHighlightImage;
	IBOutlet NSImageView *		mBackgroundImage;
	
	IBOutlet NSTextField *		mPasskeyString;
	
	NSMutableArray *			mPasskeyCharacters;
	NSUInteger					mPasskeyIndex;
	BOOL						mPasskeyIndicatorEnabled;
    BOOL                        mSSPDevice;
}

@property (retain) NSImage * returnImage;
@property (retain) NSImage * returnHighlightImage;

+ (IOBluetoothPasskeyDisplay *) sharedDisplayView;

- (void) setPasskeyString:(NSString *)inString;

- (void) setReturnType:(BluetoothKeyboardReturnType)inReturnType;

- (void) advancePasskeyIndicator;
- (void) retreatPasskeyIndicator;

- (void) resetAll;
- (void) resetPasskeyIndicator;
- (void) setPasskeyIndicatorEnabled:(BOOL)inEnabled;

- (void) setupUIForDevice:(IOBluetoothDevice *)device;

- (void) setupUIForSSPDevice:(IOBluetoothDevice *)device;

@end

// Accessiblity support
@interface IOBluetoothAccessibilityIgnoredTextFieldCell : NSTextFieldCell {}
@end

@interface IOBluetoothAccessibilityIgnoredImageCell: NSImageCell {}
@end

