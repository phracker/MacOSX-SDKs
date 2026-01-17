/*
	NSColorList.h
	Application Kit
	Copyright (c) 1994-2016, Apple Inc.
	All rights reserved.
*/

/* An NSColorList is an ordered list of NSColors, identified by keys. These keys are used to identify the colors in the list and are used to display the color to the user in the color panel. Note that the key is only used in identifying a color in a color list; it has nothing to do with the contents of the color, unless, of course the color list was set up in such a way that the keys matched the color names.

Instances of NSColorList are created for all user-created color lists (those in the color panel) and various color catalogs available on the system.

NSColorLists post "NSColorListDidChangeNotification" when changed.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSNotification.h>
#import <AppKit/AppKitDefines.h>
#import <CoreFoundation/CFDictionary.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSBundle;

@interface NSColorList : NSObject <NSSecureCoding> {
    /*All instance variables are private*/
    NSMutableArray *_keyArray;
    NSMutableArray *_colorArray;
    CFMutableDictionaryRef _keyToIndexTable;
    NSString *_name;
    NSString *_printerType;
    NSString *_fileName;
    struct _colorListFlags {
	unsigned int colorsLoaded:1;
	unsigned int editable:1;
	unsigned int hasDeviceSpecificLists:1;
	unsigned int dirty:1;
	unsigned int hasFrozen:1;
	unsigned int notificationsDisabled:1;
        unsigned int hasAttemptedLoadingBundleForDirectory:1;
	unsigned int isProfileBased:1;
	unsigned int :24;
#if __LP64__
	unsigned int :32;
#endif
    } _flags;
    id _clAuxiliaryStorage;
}

/* Returns all color lists in the user's color list path, including those added at runtime. Creating a named color list and saving with writeToFile:nil will add it to this list; removeFile will remove it from this list. (That is what happens as the user creates and destroys color lists in the color panel.)
*/
+ (NSArray<NSColorList *> *)availableColorLists;

/* Returns the named color list from availableColorLists
*/
+ (nullable NSColorList *)colorListNamed:(NSString *)name;

/* Creates a color list; specify @"" if you don't want a name. NOTE that this does not add the color list to availableColorLists until the color list is saved into the user's path with writeToFile:nil.
*/
- (instancetype)initWithName:(NSString *)name;			
- (nullable instancetype)initWithName:(NSString *)name fromFile:(nullable NSString *)path;	/* Load initial contents */

/* Name of the color list
*/
@property (nullable, readonly, copy) NSString *name;

/* If key already exists, sets the corresponding color. Otherwise inserts the color at the end.
*/
- (void)setColor:(NSColor *)color forKey:(NSString *)key;

/* Inserts color at the specified location. If a color by the same key is already in the list but at a different location it is removed from there.
*/
- (void)insertColor:(NSColor *)color key:(NSString *)key atIndex:(NSUInteger)loc;

/* No-op if key doesn't exist.
*/
- (void)removeColorWithKey:(NSString *)key;

/* Returns nil if key doesn't exist.
*/
- (nullable NSColor *)colorWithKey:(NSString *)key;

/* Use this array to get count of colors and enumerate them according to the ordering specified when inserting.
*/
@property (readonly, copy) NSArray<NSString *> *allKeys;

/* Depends on the source of the colorlist file
*/
@property (getter=isEditable, readonly) BOOL editable;

/* Save the color list using secure keyed archive format. Specify nil to save to the user's private colorlists directory (and also update availableColorLists), using the name of the color list.
 */
- (BOOL)writeToURL:(nullable NSURL *)url error:(NSError **)errPtr NS_AVAILABLE_MAC(10_11);

/* Save the color list using unkeyed archive format. Specify nil to save to the user's private colorlists directory (and also update availableColorLists), using the name of the color list.
 
   Use of the unkeyed archive format (and hence this API) is discouraged since it cannot represent some colors (including custom colorspace based ones) without loss. Use writeToURL:error: instead.
*/
- (BOOL)writeToFile:(nullable NSString *)path;	

/* If the color list is in the user's private colorlists directory, removes the corresponding file and the color list from availableColorLists. If there are no outstanding references to the color list this might deallocate the object as well.
*/
- (void)removeFile;

@end

/* Notifications */
APPKIT_EXTERN NSNotificationName NSColorListDidChangeNotification;

NS_ASSUME_NONNULL_END

