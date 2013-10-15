/*	
    AMBundleAction.h
    Copyright (C) 2004 Apple Computer, Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMAction.h>

// AMBundleAction
// =============

@interface AMBundleAction : AMAction <NSCoding, NSCopying> 
{
@private
	IBOutlet NSView *_view;
	NSBundle *_bundle;
	NSArray *_topLevelObjects;
	
	id _reserved;
	id _reserved2;
	id _reserved3;
	id _reserved4;
}

// Construction
- (id)initWithDefinition:(NSDictionary *)dict fromArchive:(BOOL)archived;

// Operations
- (void)awakeFromBundle;
- (BOOL)hasView;

// Accessors
- (NSView *)view;
- (NSBundle *)bundle;
- (NSMutableDictionary *)parameters;
- (void)setParameters:(NSMutableDictionary *)newParameters;

@end
