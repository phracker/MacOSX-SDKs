/*	
    AMBundleAction.h
    Copyright (C) 2004-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/Foundation.h>
#import <Automator/AMAction.h>

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(ios)

@class NSView;

// AMBundleAction

NS_CLASS_AVAILABLE_MAC(10_4)
@interface AMBundleAction : AMAction <NSCopying, NSSecureCoding>
{
	@private
	__weak NSView *_view;
	NSBundle *_bundle;
	NSArray *_topLevelObjects;

	AM_UNUSED_FOR_ANALYZER id _reserved;
	AM_UNUSED_FOR_ANALYZER id _reserved2;
	AM_UNUSED_FOR_ANALYZER id _reserved3;
	AM_UNUSED_FOR_ANALYZER id _reserved4;
}

// Operations
- (void)awakeFromBundle;

@property (readonly, nonatomic) BOOL hasView;

// Accessors
@property (nullable, readonly, strong, nonatomic) NSView *view;
@property (readonly, strong, nonatomic) NSBundle *bundle;
@property (nullable, strong, nonatomic) NSMutableDictionary<NSString *, id> *parameters;

@end

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
