/*	
    AMBundleAction.h
    Copyright (C) 2004-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>
#import <Automator/AMAction.h>

@class NSView;

// AMBundleAction
// =============

@interface AMBundleAction : AMAction <NSCoding, NSCopying> 
{
@private
	IBOutlet NSView *_view;
	NSBundle *_bundle;
	NSArray *_topLevelObjects;
	
	AM_UNUSED_FOR_ANALYZER id _reserved;
	AM_UNUSED_FOR_ANALYZER id _reserved2;
	AM_UNUSED_FOR_ANALYZER id _reserved3;
	AM_UNUSED_FOR_ANALYZER id _reserved4;
}

// Construction
- (instancetype)initWithDefinition:(NSDictionary *)dict fromArchive:(BOOL)archived;

// Operations
- (void)awakeFromBundle;
@property (readonly) BOOL hasView;

// Accessors
@property (readonly, strong) NSView *view;
@property (readonly, strong) NSBundle *bundle;
@property (strong) NSMutableDictionary *parameters;

@end
