//
//  IOBluetoothPasskeyDisplay.h
//  Copyright 2010 Apple, Inc.. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@class IOBluetoothDevice;

typedef enum {
    kBluetoothKeyboardANSIReturn,
	kBluetoothKeyboardISOReturn,
    kBluetoothKeyboardJISReturn,
    kBluetoothKeyboardNoReturn
} BluetoothKeyboardReturnType;

@interface IOBluetoothPasskeyDisplay : NSView
{
	IBOutlet NSImageView *		mReturnImageView;
	NSImage *					mReturnImage;
	NSImage *					mReturnHighlightImage;
	IBOutlet NSImageView *		mBackgroundImage;
	
	BOOL						usePasskeyNotifications;
    BOOL                        isIncomingRequest;
    BOOL						showFeedback;
    NSString *					passkey;
    IBOutlet NSTextField *		mPasskeyString;
    
	NSMutableArray *			mPasskeyCharacters;
	NSUInteger					mPasskeyIndex;
    
    NSLayoutConstraint *		backgroundImageConstraint;
    NSView *centeredView;
}

// Private
@property (assign)	BOOL			usePasskeyNotificaitons;
@property (assign)	BOOL			isIncomingRequest;
@property (copy)	NSString *		passkey;
@property (retain)	NSImage *		returnImage;
@property (retain)	NSImage *		returnHighlightImage;

@property (assign) IBOutlet NSView *centeredView;
@property (assign) IBOutlet NSLayoutConstraint *backgroundImageConstraint;


// Public
+ (IOBluetoothPasskeyDisplay *) sharedDisplayView;

- (void) setPasskey:(NSString *)inString forDevice:(IOBluetoothDevice *)device usingSSP:(BOOL)isSSP;

- (void) advancePasskeyIndicator;
- (void) retreatPasskeyIndicator;
- (void) resetPasskeyIndicator;



// Deprecated methods
- (void) setupUIForDevice:(IOBluetoothDevice *)device DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;
- (void) setupUIForSSPDevice:(IOBluetoothDevice *)device DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

// Must be called after setupUIFor(SSP)Device is called
- (void) setPasskeyString:(NSString *)inString DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;
- (void) setPasskeyIndicatorEnabled:(BOOL)inEnabled DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;
- (void) resetAll DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

@end

// Accessiblity support
@interface IOBluetoothAccessibilityIgnoredTextFieldCell : NSTextFieldCell {}
@end

@interface IOBluetoothAccessibilityIgnoredImageCell: NSImageCell {}
@end

