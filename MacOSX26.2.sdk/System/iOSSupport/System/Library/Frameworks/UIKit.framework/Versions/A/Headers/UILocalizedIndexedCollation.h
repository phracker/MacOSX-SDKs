#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UILocalizedIndexedCollation.h>)
//
//  UILocalizedIndexedCollation.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UILocalizedIndexedCollation : NSObject

+ (instancetype)currentCollation;

// Provides the list of section titles used to group results (e.g. A-Z,# in US/English)
@property(nonatomic, readonly) NSArray<NSString *> * sectionTitles;

// Provides the list of index titles used to quickly jump to particular sections
@property(nonatomic, readonly) NSArray<NSString *> *sectionIndexTitles;

// Specifies the section that should be scrolled to for the title at the given index.
// This method allows you to map between a given item in the index
// and a given section where there isn't a one-to-one mapping.
- (NSInteger)sectionForSectionIndexTitleAtIndex:(NSInteger)indexTitleIndex;

// Returns the index of the section that will contain the object.
// selector must not take any arguments and return an NSString.
- (NSInteger)sectionForObject:(id)object collationStringSelector:(SEL)selector;

// Used for sorting objects within the same section.
// selector must not take any arguments and return an NSString.
// In the process of sorting the array, each object may receive
// selector multiple times, so this method should be fast.
- (NSArray *)sortedArrayFromArray:(NSArray *)array collationStringSelector:(SEL)selector;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UILocalizedIndexedCollation.h>
#endif
