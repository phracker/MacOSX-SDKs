/*	NSArchiver.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>

@class NSString, NSData, NSMutableData, NSMutableDictionary, NSMutableArray;

NS_ASSUME_NONNULL_BEGIN

/************		Archiving: Writing	****************/

@interface NSArchiver : NSCoder {
@private
    void		* __strong mdata;
    void		*pointerTable;
    void		*stringTable;
    void		*ids;
    void		*map;
    void		*replacementTable;
    void		*reserved;
}

- (instancetype)initForWritingWithMutableData:(NSMutableData *)mdata NS_DESIGNATED_INITIALIZER;
    
@property (readonly, retain) NSMutableData *archiverData;

- (void)encodeRootObject:(id)rootObject;
- (void)encodeConditionalObject:(nullable id)object;

+ (NSData *)archivedDataWithRootObject:(id)rootObject;

+ (BOOL)archiveRootObject:(id)rootObject toFile:(NSString *)path;

- (void)encodeClassName:(NSString *)trueName intoClassName:(NSString *)inArchiveName;
- (nullable NSString *)classNameEncodedForTrueClassName:(NSString *)trueName;

- (void)replaceObject:(id)object withObject:(id)newObject;

@end

/************		Archiving: Reading		****************/

@interface NSUnarchiver : NSCoder {
@private
    void *		datax;
    NSUInteger		cursor;
    NSZone              *objectZone;
    NSUInteger		systemVersion;
    signed char		streamerVersion;
    char		swap;
    char		unused1;
    char		unused2;
    void		*pointerTable;
    void		*stringTable;
    id			classVersions;
    NSInteger			lastLabel;
     void		*map;
    void		*allUnarchivedObjects;
    id			reserved;
}

- (nullable instancetype)initForReadingWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

- (void)setObjectZone:(nullable NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (nullable NSZone *)objectZone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

@property (getter=isAtEnd, readonly) BOOL atEnd;

@property (readonly) unsigned int systemVersion;

+ (nullable id)unarchiveObjectWithData:(NSData *)data;
+ (nullable id)unarchiveObjectWithFile:(NSString *)path;

+ (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;

- (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;

+ (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;
- (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;

- (void)replaceObject:(id)object withObject:(id)newObject;

@end

/************		Exceptions		****************/

FOUNDATION_EXPORT NSString * const NSInconsistentArchiveException;

/************		Object call back		****************/

@interface NSObject (NSArchiverCallback)

@property (nullable, readonly) Class classForArchiver;
- (nullable id)replacementObjectForArchiver:(NSArchiver *)archiver;

@end

NS_ASSUME_NONNULL_END
